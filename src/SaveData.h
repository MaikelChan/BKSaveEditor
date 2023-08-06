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

#pragma region Honeycomb_Data

#define HONEYCOMB_COUNT 0x19
#define MAX_HONEYCOMBS_PER_LEVEL 6

const uint8_t levelHoneycombsCount[]
{
	6, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2
};

const uint8_t levelHoneycombsIndices[TOTAL_LEVEL_COUNT][MAX_HONEYCOMBS_PER_LEVEL]
{
	{ 0x13, 0x14, 0x15, 0x16, 0x17, 0x18 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x01, 0x02, 0x00, 0x00, 0x00, 0x00 },
	{ 0x03, 0x04, 0x00, 0x00, 0x00, 0x00 },
	{ 0x05, 0x06, 0x00, 0x00, 0x00, 0x00 },
	{ 0x07, 0x08, 0x00, 0x00, 0x00, 0x00 },
	{ 0x09, 0x0A, 0x00, 0x00, 0x00, 0x00 },
	{ 0x0B, 0x0C, 0x00, 0x00, 0x00, 0x00 },
	{ 0x11, 0x12, 0x00, 0x00, 0x00, 0x00 },
	{ 0x0F, 0x10, 0x00, 0x00, 0x00, 0x00 },
	{ 0x0D, 0x0E, 0x00, 0x00, 0x00, 0x00 }
};

const char* const levelHoneycombsNames[TOTAL_LEVEL_COUNT][MAX_HONEYCOMBS_PER_LEVEL]
{
	{ "Stump",          "Waterfall",      "Underwater", "Tree", "Coliwobble", "Quarries" },
	{ "",               "",               "",           "",     "",           ""         },
	{ "Hill",           "Juju",           "",           "",     "",           ""         },
	{ "Underwater",     "Floating Box",   "",           "",     "",           ""         },
	{ "Underwater",     "Above Water",    "",           "",     "",           ""         },
	{ "Mumbo's Hut",    "Tanktup",        "",           "",     "",           ""         },
	{ "Wozza's Cave",   "Sir Slush",      "",           "",     "",           ""         },
	{ "Cactus",         "Gobi",           "",           "",     "",           ""         },
	{ "Church Rafters", "Floorboard",     "",           "",     "",           ""         },
	{ "Boat House",     "Engine Room",    "",           "",     "",           ""         },
	{ "Gnawty's House", "Nabnut's House", "",           "",     "",           ""         }
};

#pragma endregion

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
	uint8_t Times[11 * 2];
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

	inline bool GetHoneycomb(const uint8_t level, const uint8_t honeycomb) const
	{
		uint8_t indx = levelHoneycombsIndices[level][honeycomb];
		return (Honeycombs[(indx - 1) / 8] & (1 << (indx & 7))) != 0;
	}

	inline void SetHoneycomb(const uint8_t level, const uint8_t honeycomb, bool val)
	{
		uint8_t indx = levelHoneycombsIndices[level][honeycomb];
		if (val) Honeycombs[(indx - 1) / 8] |= (1 << (indx & 7));
		else Honeycombs[(indx - 1) / 8] &= ~(1 << (indx & 7));
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
