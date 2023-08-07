#include "SaveData.h"
#include <fstream>
#include <exception>
#include <cassert>
#include "Utils.h"

SaveData::SaveData()
{
	assert(sizeof(SaveSlot) == SAVE_SLOT_SIZE);
	assert(sizeof(GlobalData) == GLOBAL_DATA_SIZE);
	assert(sizeof(SaveFile) == SAVE_FILE_SIZE);

	saveFile = nullptr;

	currentFileType = SaveFile::Types::NotValid;
}

SaveData::~SaveData()
{
	ClearSaveFile();
}

void SaveData::Load(const std::string filePath)
{
	std::ifstream stream = std::ifstream(filePath, std::ios::binary);

	if (!stream || !stream.is_open())
	{
		throw std::runtime_error("There was an error trying to open open the file.");
		return;
	}

	stream.seekg(0, std::ios_base::end);
	size_t size = stream.tellg();

	if (size != SAVE_FILE_SIZE)
	{
		stream.close();
		throw std::runtime_error("The selected file is not a valid Banjo-Kazooie save file.");
		return;
	}

	SaveFile* saveFile = new SaveFile();

	stream.seekg(0, std::ios_base::beg);
	stream.read((char*)saveFile, sizeof(SaveFile));
	stream.close();

	SaveFile::Types type = saveFile->GetType();

	if (type == SaveFile::Types::NotValid)
	{
		delete saveFile;
		throw std::runtime_error("The selected file is not a valid Banjo-Kazooie save file.");
		return;
	}

	ClearSaveFile();

	SaveData::saveFile = saveFile;
	currentFileType = type;

	EndianSwap();
}

void SaveData::Save(const std::string filePath)
{
	if (!IsSaveFileLoaded()) return;

	std::ofstream stream = std::ofstream(filePath, std::ios::binary);

	if (!stream || !stream.is_open())
	{
		throw std::runtime_error(std::string("Can't open file \"") + filePath + "\".");
	}

	stream.write((char*)saveFile, SAVE_FILE_SIZE);
	stream.close();
}

void SaveData::ClearSaveFile()
{
	if (!IsSaveFileLoaded()) return;

	delete saveFile;
	saveFile = nullptr;

	currentFileType = SaveFile::Types::NotValid;
}

void SaveData::EndianSwap() const
{
	if (!IsSaveFileLoaded()) return;
	if (currentFileType != SaveFile::Types::Nintendo64) return;

	for (int s = 0; s < TOTAL_NUM_SAVE_SLOTS; s++)
	{
		for (int t = 0; t < TOTAL_LEVEL_COUNT; t++)
		{
			saveFile->saveSlots[s].Times[t] = Swap16(saveFile->saveSlots[s].Times[t]);
		}

		saveFile->saveSlots[s].Checksum = Swap32(saveFile->saveSlots[s].Checksum);
	}

	saveFile->globalData.Checksum = Swap32(saveFile->globalData.Checksum);
}
