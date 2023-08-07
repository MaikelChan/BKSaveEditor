#include "SaveFile.h"
#include "Utils.h"

inline uint32_t SaveSlot::CalculateChecksum() const
{
	return SaveFile::CalculateChecksum((uint8_t*)&Magic, (uint8_t*)&Checksum);
}

void SaveSlot::UpdateChecksum()
{
	Checksum = CalculateChecksum();
}

bool SaveSlot::IsValid() const
{
	return Checksum == CalculateChecksum();
}

uint32_t GlobalData::CalculateChecksum() const
{
	return SaveFile::CalculateChecksum((uint8_t*)&Unk, (uint8_t*)&Checksum);
}

void GlobalData::UpdateChecksum()
{
	Checksum = CalculateChecksum();
}

bool GlobalData::IsValid() const
{
	return Checksum == CalculateChecksum();
}

SaveFile::Types SaveFile::GetType() const
{
	for (uint8_t s = 0; s < TOTAL_NUM_SAVE_SLOTS; s++)
	{
		uint32_t checksum = saveSlots[s].CalculateChecksum();
		if (checksum == saveSlots[s].Checksum) return SaveFile::Types::PC;
		if (checksum == Swap32(saveSlots[s].Checksum)) return SaveFile::Types::Nintendo64;
	}

	uint32_t checksum = globalData.CalculateChecksum();
	if (checksum == globalData.Checksum) return SaveFile::Types::PC;
	if (checksum == Swap32(globalData.Checksum)) return SaveFile::Types::Nintendo64;

	return SaveFile::Types::NotValid;
}

SaveSlot* SaveFile::GetSaveSlot(const uint8_t slotIndex)
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

uint32_t SaveFile::TransformSeed(uint64_t* seed)
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

uint32_t SaveFile::CalculateChecksum(uint8_t* start, uint8_t* end)
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