#include "SaveFile.h"

#include "../Utils.h"
#include "SaveData.h"

SaveFile::SaveFile()
{
	saveData = nullptr;
	recompSaveData = nullptr;

	fileType = SaveFileTypes::NotValid;
}

SaveFile::~SaveFile()
{
	if (saveData != nullptr)
	{
		delete saveData;
		saveData = nullptr;
	}

	if (recompSaveData != nullptr)
	{
		delete recompSaveData;
		recompSaveData = nullptr;
	}
}

std::string SaveFile::Read(std::ifstream& stream, const size_t streamSize)
{
	SaveData* newSaveData = new SaveData();
	stream.read((char*)newSaveData, SAVE_DATA_SIZE);

	RecompSaveData* newRecompSaveData = nullptr;

	// Check what type of file is and initialize

	fileType = CalculateType(newSaveData);

	switch (fileType)
	{
		case SaveFileTypes::NotValid:
		{
			return "The selected file is not a valid Banjo-Kazooie save file.";
		}

		case SaveFileTypes::BigEndian:
		{
			newSaveData->EndianSwap();

			if (streamSize == RECOMP_SAVE_DATA_SIZE)
			{
				// Banjo Recompiled also uses save files in big endian.
				// There's no way to check if it's actually a Banjo Recompiled save or if
				// it's just an N64 file but with zeroes at the end, which some emulators add.
				// So let's assume it's from Banjo Recompiled.
				// Shouldn't break anything if it's actually a N64 save.

				newRecompSaveData = new RecompSaveData();
				stream.read((char*)newRecompSaveData, RECOMP_EXTENDED_DATA_SIZE);
			}

			break;
		}

		default:
		{
			throw std::runtime_error("SaveFile type " + std::to_string((int)fileType) + " not implemented.");
		}
	}

	// It's a valid file type, but check if there are data inconsistencies that should trigger a warning

	std::string warningMessages;

	for (uint8_t s = 0; s < ACTUAL_NUM_SAVE_SLOTS; s++)
	{
		SaveSlot* saveSlot = newSaveData->GetSaveSlot(s);
		if (saveSlot == nullptr) continue;

		if (!saveSlot->IsValid(fileType))
		{
			warningMessages += std::string("Save slot ") + std::to_string(s) + " has a wrong checksum. Data could be invalid.\n\n";
		}
	}

	if (!newSaveData->GetGlobalData()->IsValid(fileType))
	{
		warningMessages += "Global Data has a wrong checksum. Data could be invalid.\n\n";
	}

	// Assign references to the loaded data before finishing

	saveData = newSaveData;
	recompSaveData = newRecompSaveData;

	return warningMessages;
}

void SaveFile::Write(std::ofstream& stream)
{
	// Refresh all checksums

	for (uint8_t s = 0; s < ACTUAL_NUM_SAVE_SLOTS; s++)
	{
		SaveSlot* saveSlot = saveData->GetSaveSlot(s);
		if (saveSlot == nullptr) continue;

		saveSlot->UpdateChecksum(fileType);
	}

	saveData->GetGlobalData()->UpdateChecksum(fileType);

	// Do the saving

	if (fileType == SaveFileTypes::BigEndian) saveData->EndianSwap();

	stream.write((char*)saveData, SAVE_DATA_SIZE);

	if (recompSaveData != nullptr)
	{
		stream.write((char*)recompSaveData, RECOMP_EXTENDED_DATA_SIZE);
	}

	// Keep the data in memory in little endian

	if (fileType == SaveFileTypes::BigEndian) saveData->EndianSwap();
}

SaveFileTypes SaveFile::CalculateType(SaveData* saveData)
{
	if (saveData == nullptr) return SaveFileTypes::NotValid;

	for (uint8_t s = 0; s < TOTAL_NUM_SAVE_SLOTS; s++)
	{
		SaveSlot* slot = saveData->GetRawSaveSlot(s);

		uint32_t calculatedChecksum = slot->CalculateChecksum();
		uint32_t slotChecksum = slot->GetChecksum();
		if (calculatedChecksum == slotChecksum) return SaveFileTypes::LittleEndian;
		if (calculatedChecksum == Utils::Swap32(slotChecksum)) return SaveFileTypes::BigEndian;
	}

	GlobalData* globalData = saveData->GetGlobalData();

	uint32_t calculatedChecksum = globalData->CalculateChecksum();
	uint32_t globalDataChecksum = globalData->GetChecksum();
	if (calculatedChecksum == globalDataChecksum) return SaveFileTypes::LittleEndian;
	if (calculatedChecksum == Utils::Swap32(globalDataChecksum)) return SaveFileTypes::BigEndian;

	return SaveFileTypes::NotValid;
}
