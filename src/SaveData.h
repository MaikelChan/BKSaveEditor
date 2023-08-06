#pragma once

#include <cstdint>
#include <string>

#define SAVE_DATA_SIZE 0x200

#define TOTAL_NUM_SAVE_SLOTS 4
#define ACTUAL_NUM_SAVE_SLOTS 3
#define SAVE_SLOT_MAGIC 0x11
#define SAVE_SLOT_SIZE 0x78

#define TOTAL_LEVEL_COUNT 11

const char* const levelNames[]
{
	"Spiral Mountain",
	"Gruntilda's Lair",
	"Mumbo's Mountain",
	"Treasure Trove Cove",
	"Clanker's Cavern",
	"Bubblegloop Swamp",
	"Freezeezy Peak",
	"Gobi's Valley",
	"Mad Monster Mansion",
	"Rusty Bucket Bay",
	"Click Clock Wood"
};

const uint8_t levelJiggiesCount[]
{
	0, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10
};

const uint8_t levelHoneycombsCount[]
{
	6, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2
};

const bool levelHasNotes[]
{
	false, false, true, true, true, true, true, true, true, true, true
};

struct SaveSlot
{
public:
	uint8_t Magic;
	uint8_t SlotIndex;
	uint8_t Jiggies[0xD];
	uint8_t Honeycombs[0x3];
	uint8_t MumboTokens[0x10];
	uint8_t Flags[0x25]; // ?
	uint8_t NoteScores[0x8];
	uint8_t Times[11*2];
	uint8_t Items[5];
	uint8_t Abilities[8];
	uint8_t Unk[0x2];
	uint32_t Checksum;

	inline uint16_t CalculateChecksum() const
	{
		uint16_t checksum = 0;
		//const uint8_t* p = &CapLevel;

		//for (int i = 0; i < SAVE_SLOT_SIZE - 2; i++)
		//{
		//	checksum += *p++;
		//}

		return checksum;
	}

	inline void UpdateChecksum()
	{
		Checksum = CalculateChecksum();
	}

	inline bool IsValid()
	{
		return Checksum == CalculateChecksum();
	}

	inline bool GetFlag(const uint32_t mask) const
	{
		return 0; // (Flags & mask) != 0;
	}

	inline void SetFlag(const uint32_t mask, const bool value)
	{
		//if (value) Flags |= mask;
		//else Flags &= ~mask;
	}

	//inline uint8_t GetTotalStars()
	//{
	//	uint8_t count = 0;

	//	for (int c = 0; c < COURSE_COUNT; c++)
	//	{
	//		for (int st = 0; st < courseStarCount[c]; st++)
	//		{
	//			if ((CourseData[c] & (1 << st)) != 0) count++;
	//		}
	//	}

	//	if ((Flags & SAVE_FLAG_COLLECTED_TOAD_STAR_1) != 0) count++;
	//	if ((Flags & SAVE_FLAG_COLLECTED_TOAD_STAR_2) != 0) count++;
	//	if ((Flags & SAVE_FLAG_COLLECTED_TOAD_STAR_3) != 0) count++;
	//	if ((Flags & SAVE_FLAG_COLLECTED_MIPS_STAR_1) != 0) count++;
	//	if ((Flags & SAVE_FLAG_COLLECTED_MIPS_STAR_2) != 0) count++;

	//	return count;
	//}
};

class SaveData
{
public:
	enum class Types { NotValid, PC, Nintendo64 };

private:
	SaveSlot saveSlots[TOTAL_NUM_SAVE_SLOTS] = {};
	uint8_t unk[0x20] = {};

public:
	SaveData();

	static SaveData* Load(const std::string filePath);
	static void Save(const std::string filePath, const SaveData* saveData);

	Types GetType() const;

	SaveSlot* GetSaveSlot(const uint8_t slotIndex);
};
