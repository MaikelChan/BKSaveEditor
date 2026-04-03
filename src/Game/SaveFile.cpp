#include "SaveData.h"
#include "../Utils.h"

#pragma region SaveSlot

uint32_t SaveSlot::CalculateChecksum() const
{
	return SaveData::CalculateChecksum((uint8_t*)&Magic, (uint8_t*)&Checksum);
}

void SaveSlot::UpdateChecksum(const bool endianSwap)
{
	const uint32_t checksum = CalculateChecksum();
	Checksum = endianSwap ? Utils::Swap32(checksum) : checksum;
}

bool SaveSlot::IsValid(const bool endianSwap) const
{
	const uint32_t checksum = CalculateChecksum();
	return Checksum == (endianSwap ? Utils::Swap32(checksum) : checksum);
}

uint8_t SaveSlot::GetMagic() const
{
	return Magic;
}

uint8_t SaveSlot::GetSlotIndex() const
{
	if (SlotIndex == 2) return 3;
	if (SlotIndex == 3) return 2;
	return SlotIndex;
}

void SaveSlot::SetSlotIndex(const uint8_t slotIndex)
{
	if (slotIndex < 1 || slotIndex > 3) return;

	uint8_t index = slotIndex;
	if (index == 2) index = 3;
	else if (index == 3) index = 2;

	SlotIndex = index;
}

bool SaveSlot::GetJiggy(const uint8_t jiggy) const
{
	return (Jiggies[(jiggy - 1) / 8] & (1 << (jiggy & 7))) != 0;
}

void SaveSlot::SetJiggy(const uint8_t jiggy, bool value)
{
	if (value) Jiggies[(jiggy - 1) / 8] |= (1 << (jiggy & 7));
	else Jiggies[(jiggy - 1) / 8] &= ~(1 << (jiggy & 7));
}

bool SaveSlot::GetHoneycomb(const uint8_t honeycomb) const
{
	return (Honeycombs[(honeycomb - 1) / 8] & (1 << (honeycomb & 7))) != 0;
}

void SaveSlot::SetHoneycomb(const uint8_t honeycomb, bool value)
{
	if (value) Honeycombs[(honeycomb - 1) / 8] |= (1 << (honeycomb & 7));
	else Honeycombs[(honeycomb - 1) / 8] &= ~(1 << (honeycomb & 7));
}

bool SaveSlot::GetMumboToken(const uint8_t token) const
{
	return (MumboTokens[(token - 1) / 8] & (1 << (token & 7))) != 0;
}

void SaveSlot::SetMumboToken(const uint8_t token, bool value)
{
	if (value) MumboTokens[(token - 1) / 8] |= (1 << (token & 7));
	else MumboTokens[(token - 1) / 8] &= ~(1 << (token & 7));
}

uint8_t SaveSlot::GetNotes(const uint8_t level) const
{
	if (!levelHasNotes[level]) return 0;

	const uint64_t* noteValuesPtr = reinterpret_cast<const uint64_t*>(NoteScores);
	const int8_t bitOffset = levelNotesBitOffsets[level];

	return (Utils::Swap64(*noteValuesPtr) >> bitOffset) & 0x7F;
}

void SaveSlot::SetNotes(const uint8_t level, const uint8_t value) const
{
	if (!levelHasNotes[level]) return;

	uint64_t* noteValuesPtr = const_cast<uint64_t*>(reinterpret_cast<const uint64_t*>(NoteScores));
	const int8_t bitOffset = levelNotesBitOffsets[level];

	const uint64_t mask = static_cast<uint64_t>(0x7f) << bitOffset;
	*noteValuesPtr &= Utils::Swap64(~mask);
	*noteValuesPtr |= Utils::Swap64(static_cast<uint64_t>(value & 0x7f) << bitOffset);
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

bool SaveSlot::GetProgressFlag(const ProgressFlags flag) const
{
	const uint8_t index = static_cast<uint8_t>(flag);
	return Flags[index / 8] & (1 << (index & 7));
}

void SaveSlot::SetProgressFlag(const ProgressFlags flag, const bool value)
{
	const uint8_t index = static_cast<uint8_t>(flag);
	if (value) Flags[index / 8] |= (1 << (index & 7));
	else Flags[index / 8] &= ~(1 << (index & 7));
}

uint8_t SaveSlot::GetProgressValue(const ProgressFlags flag, const uint8_t bitsCount) const
{
	uint8_t value = 0;
	const uint8_t index = static_cast<uint8_t>(flag);

	for (uint8_t i = 0; i < bitsCount; i++)
	{
		value |= (GetProgressFlag(static_cast<ProgressFlags>(index + i)) << i);
	}

	return value;
}

void SaveSlot::SetProgressValue(const ProgressFlags flag, const uint8_t bitsCount, const uint8_t value)
{
	const uint8_t index = static_cast<uint8_t>(flag);

	for (uint8_t i = 0; i < bitsCount; i++)
	{
		SetProgressFlag(static_cast<ProgressFlags>(index + i), (value >> i) & 1);
	}
}

uint8_t SaveSlot::GetHeldItem(const HeldItems heldItem) const
{
	return Items[static_cast<int>(heldItem)];
}

void SaveSlot::SetHeldItem(const HeldItems heldItem, const uint8_t value)
{
	Items[static_cast<int>(heldItem)] = value;
}

bool SaveSlot::GetLearnedAbility(const LearnableAbilities ability) const
{
	const uint8_t index = static_cast<uint8_t>(ability);
	uint32_t* abilityValuesPtr = const_cast<uint32_t*>(reinterpret_cast<const uint32_t*>(LearnedAbilities));

	return Utils::Swap32(*abilityValuesPtr) & (1 << index);
}

void SaveSlot::SetLearnedAbility(const LearnableAbilities ability, const bool value)
{
	const uint8_t index = static_cast<uint8_t>(ability);
	uint32_t* abilityValuesPtr = const_cast<uint32_t*>(reinterpret_cast<const uint32_t*>(LearnedAbilities));

	if (value) *abilityValuesPtr |= Utils::Swap32(1 << index);
	else *abilityValuesPtr &= Utils::Swap32(~(1 << index));
}

bool SaveSlot::GetUsedAbility(const UsableAbilities ability) const
{
	const uint8_t index = static_cast<uint8_t>(ability);
	uint32_t* abilityValuesPtr = const_cast<uint32_t*>(reinterpret_cast<const uint32_t*>(UsedAbilities));

	return Utils::Swap32(*abilityValuesPtr) & (1 << index);
}

void SaveSlot::SetUsedAbility(const UsableAbilities ability, const bool value)
{
	const uint8_t index = static_cast<uint8_t>(ability);
	uint32_t* abilityValuesPtr = const_cast<uint32_t*>(reinterpret_cast<const uint32_t*>(UsedAbilities));

	if (value) *abilityValuesPtr |= Utils::Swap32(1 << index);
	else *abilityValuesPtr &= Utils::Swap32(~(1 << index));
}

uint32_t SaveSlot::GetChecksum(const bool endianSwap) const
{
	return endianSwap ? Utils::Swap32(Checksum) : Checksum;
}

#pragma endregion

#pragma region GlobalData

uint32_t GlobalData::CalculateChecksum() const
{
	return SaveData::CalculateChecksum((uint8_t*)&SnsItems, (uint8_t*)&Checksum);
}

void GlobalData::UpdateChecksum(const bool endianSwap)
{
	const uint32_t checksum = CalculateChecksum();
	Checksum = endianSwap ? Utils::Swap32(checksum) : checksum;
}

bool GlobalData::IsValid(const bool endianSwap) const
{
	const uint32_t checksum = CalculateChecksum();
	return Checksum == (endianSwap ? Utils::Swap32(checksum) : checksum);
}

bool GlobalData::GetSnsItem(const SnS snsItem) const
{
	const uint8_t index = static_cast<uint8_t>(snsItem);
	return Utils::Swap32(SnsItems) & (1 << index);
}

void GlobalData::SetSnsItem(const SnS snsItem, const bool value)
{
	const uint8_t index = static_cast<uint8_t>(snsItem);

	if (value) SnsItems |= Utils::Swap32(1 << index);
	else SnsItems &= Utils::Swap32(~(1 << index));
}

uint32_t GlobalData::GetChecksum(const bool endianSwap) const
{
	return endianSwap ? Utils::Swap32(Checksum) : Checksum;
}

#pragma endregion
