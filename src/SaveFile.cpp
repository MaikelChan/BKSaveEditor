#include "SaveFile.h"
#include "Utils.h"

#pragma region SaveSlot

uint32_t SaveSlot::CalculateChecksum() const
{
	return SaveFile::CalculateChecksum((uint8_t*)&Magic, (uint8_t*)&Checksum);
}

void SaveSlot::UpdateChecksum(const bool endianSwap)
{
	const uint32_t checksum = CalculateChecksum();
	Checksum = endianSwap ? Utils::Swap32(checksum) : checksum;
}

bool SaveSlot::IsValid(const bool endianSwap) const
{
	const uint32_t checksum = CalculateChecksum();
	return Checksum == endianSwap ? Utils::Swap32(checksum) : checksum;
}

uint8_t SaveSlot::GetMagic() const
{
	return Magic;
}

uint8_t SaveSlot::GetSlotIndex() const
{
	return SlotIndex;
}

bool SaveSlot::GetHoneycomb(const uint8_t level, const uint8_t honeycomb) const
{
	uint8_t index = levelHoneycombsIndices[level][honeycomb];
	return (Honeycombs[(index - 1) / 8] & (1 << (index & 7))) != 0;
}

void SaveSlot::SetHoneycomb(const uint8_t level, const uint8_t honeycomb, bool value)
{
	uint8_t index = levelHoneycombsIndices[level][honeycomb];
	if (value) Honeycombs[(index - 1) / 8] |= (1 << (index & 7));
	else Honeycombs[(index - 1) / 8] &= ~(1 << (index & 7));
}

bool SaveSlot::GetJiggy(const uint8_t level, const uint8_t jiggy) const
{
	uint8_t index = levelJiggiesIndices[level][jiggy];
	return (Jiggies[(index - 1) / 8] & (1 << (index & 7))) != 0;
}

void SaveSlot::SetJiggy(const uint8_t level, const uint8_t jiggy, bool value)
{
	uint8_t index = levelJiggiesIndices[level][jiggy];
	if (value) Jiggies[(index - 1) / 8] |= (1 << (index & 7));
	else Jiggies[(index - 1) / 8] &= ~(1 << (index & 7));
}

uint8_t SaveSlot::GetNotes(const uint8_t level) const
{
	if (!levelHasNotes[level]) return 0;

	//uint8_t index = levelJiggiesIndices[level][jiggy];
	//return (Jiggies[(index - 1) / 8] & (1 << (index & 7))) != 0;
}

void SaveSlot::SetNotes(const uint8_t level, const uint8_t value) const
{

}

uint16_t SaveSlot::GetPlayTime(const uint8_t level, const bool endianSwap) const
{
	uint16_t value = Times[levelIndices[level]];
	return endianSwap ? Utils::Swap16(value) : value;
}

void SaveSlot::SetPlayTime(const uint8_t level, const uint16_t value, const bool endianSwap)
{
	Times[levelIndices[level]] = endianSwap ? Utils::Swap16(value) : value;
}

uint32_t SaveSlot::GetChecksum(const bool endianSwap) const
{
	return endianSwap ? Utils::Swap32(Checksum) : Checksum;
}

#pragma endregion

#pragma region GlobalData

uint32_t GlobalData::CalculateChecksum() const
{
	return SaveFile::CalculateChecksum((uint8_t*)&Unk, (uint8_t*)&Checksum);
}

void GlobalData::UpdateChecksum(const bool endianSwap)
{
	const uint32_t checksum = CalculateChecksum();
	Checksum = endianSwap ? Utils::Swap32(checksum) : checksum;
}

bool GlobalData::IsValid(const bool endianSwap) const
{
	const uint32_t checksum = CalculateChecksum();
	return Checksum == endianSwap ? Utils::Swap32(checksum) : checksum;
}

uint32_t GlobalData::GetChecksum(const bool endianSwap) const
{
	return endianSwap ? Utils::Swap32(Checksum) : Checksum;
}

#pragma endregion

#pragma region SaveFile

SaveSlot* SaveFile::GetSaveSlot(const uint8_t slotIndex)
{
	uint8_t index = slotIndex;
	if (index == 1) index = 2;
	else if (index == 2) index = 1;

	for (uint8_t s = 0; s < TOTAL_NUM_SAVE_SLOTS; s++)
	{
		if (saveSlots[s].GetMagic() != SAVE_SLOT_MAGIC) continue;
		if (saveSlots[s].GetSlotIndex() == index + 1) return &saveSlots[s];
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

#pragma endregion