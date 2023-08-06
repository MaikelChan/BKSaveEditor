#include "SaveData.h"
#include <string>
#include <fstream>
#include <exception>
#include <cassert>

void SaveSlot::UpdateChecksum()
{
	Checksum = SaveData::CalculateChecksum((uint8_t*)&Magic, (uint8_t*)&Checksum);
}

bool SaveSlot::IsValid() const
{
	return Checksum == SaveData::CalculateChecksum((uint8_t*)&Magic, (uint8_t*)&Checksum);
}

SaveData::SaveData()
{
	assert(sizeof(SaveSlot) == SAVE_SLOT_SIZE);
	assert(sizeof(SaveData) == SAVE_DATA_SIZE);
}

SaveData* SaveData::Load(const std::string filePath)
{
	std::ifstream stream = std::ifstream(filePath, std::ios::binary);

	if (!stream || !stream.is_open())
	{
		throw std::runtime_error("There was an error trying to open open the file.");
		return nullptr;
	}

	stream.seekg(0, std::ios_base::end);
	size_t size = stream.tellg();

	if (size != SAVE_DATA_SIZE)
	{
		stream.close();
		throw std::runtime_error("The selected file is not a valid Banjo-Kazooie save file.");
		return nullptr;
	}

	SaveData* saveData = new SaveData();

	stream.seekg(0, std::ios_base::beg);
	stream.read((char*)saveData, sizeof(SaveData));
	stream.close();

	SaveData::Types type = saveData->GetType();

	if (type == SaveData::Types::NotValid)
	{
		delete saveData;
		throw std::runtime_error("The selected file is not a valid Banjo-Kazooie save file.");
		return nullptr;
	}

	return saveData;
}

void SaveData::Save(const std::string filePath, const SaveData* saveData)
{
	std::ofstream stream = std::ofstream(filePath, std::ios::binary);

	if (!stream || !stream.is_open())
	{
		throw std::runtime_error(std::string("Can't open file \"") + filePath + "\".");
	}

	stream.write((char*)saveData, SAVE_DATA_SIZE);
	stream.close();
}

uint32_t SaveData::TransformSeed(uint64_t* seed)
{
	// ld         $a3, 0x0($a0)
	// dsll32     $a2, $a3, 31
	// dsll       $a1, $a3, 31
	// dsrl       $a2, $a2, 31
	// dsrl32     $a1, $a1, 0
	// dsll32     $a3, $a3, 12
	// or         $a2, $a2, $a1
	// dsrl32     $a3, $a3, 0
	// xor        $a2, $a2, $a3
	// dsrl       $a3, $a2, 20
	// andi       $a3, $a3, 0xFFF
	// xor        $a3, $a3, $a2
	// dsll32     $v0, $a3, 0
	// sd         $a3, 0x0($a0)
	// jr         $ra
	// dsra32     $v0, $v0, 0

	uint64_t a1 = 0;
	uint64_t a2 = 0;
	uint64_t a3 = 0;
	uint64_t v0 = 0;

	a3 = *seed;
	a2 = a3 << (31 + 32);
	a1 = a3 << 31;
	a2 = a2 >> 31;
	a1 = a1 >> (0 + 32);
	a3 = a3 << (12 + 32);
	a2 = a2 | a1;
	a3 = a3 >> (0 + 32);
	a2 = a2 ^ a3;
	a3 = a2 >> 20;
	a3 = a3 & 0xfff;
	a3 = a3 ^ a2;
	v0 = a3 << (0 + 32);
	*seed = a3;
	v0 = v0 >> (0 + 32);

	return (uint32_t)v0;
}

uint32_t SaveData::CalculateChecksum(uint8_t* start, uint8_t* end)
{
	uint8_t* p;
	uint32_t shift = 0;
	uint64_t seed = 0x8F809F473108B3C1;
	uint32_t crc1 = 0;
	uint32_t crc2 = 0;
	uint32_t tmp;

	for (p = start; p < end; p++)
	{
		seed += (uint64_t)(*p) << (shift & 15);
		tmp = TransformSeed(&seed);
		shift += 7;
		crc1 ^= tmp;
	}

	for (p = end - 1; p >= start; p--)
	{
		seed += (uint64_t)(*p) << (shift & 15);
		tmp = TransformSeed(&seed);
		shift += 3;
		crc2 ^= tmp;
	}

	return crc1 ^ crc2;
}

SaveData::Types SaveData::GetType() const
{
	//if ((saveSlots[0][0].Magic == SAVE_SLOT_MAGIC_LE || saveSlots[0][1].Magic == SAVE_SLOT_MAGIC_LE) &&
	//	(settings[0].Magic == SETTINGS_DATA_MAGIC_LE || settings[1].Magic == SETTINGS_DATA_MAGIC_LE))
	//{
	//	return SaveData::Types::PC;
	//}

	//if ((saveSlots[0][0].Magic == SAVE_SLOT_MAGIC_BE || saveSlots[0][1].Magic == SAVE_SLOT_MAGIC_BE) &&
	//	(settings[0].Magic == SETTINGS_DATA_MAGIC_BE || settings[1].Magic == SETTINGS_DATA_MAGIC_BE))
	//{
	//	return SaveData::Types::Nintendo64;
	//}

	return SaveData::Types::Nintendo64;
}

SaveSlot* SaveData::GetSaveSlot(const uint8_t slotIndex)
{
	uint8_t index = slotIndex;
	if (index == 1) index = 2;
	else if (index == 2) index = 1;

	for (uint8_t s = 0; s < TOTAL_NUM_SAVE_SLOTS; s++)
	{
		if (saveSlots[s].Magic != SAVE_SLOT_MAGIC) continue;
		if (saveSlots[s].SlotIndex == index + 1) return &saveSlots[s];
	}

	return nullptr;
}
