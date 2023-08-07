#pragma once

#include <cstdint>

#define SAVE_FILE_SIZE 0x200

#define TOTAL_NUM_SAVE_SLOTS 4
#define ACTUAL_NUM_SAVE_SLOTS 3
#define SAVE_SLOT_MAGIC 0x11
#define SAVE_SLOT_SIZE 0x78

#define TOTAL_LEVEL_COUNT 11

#define GLOBAL_DATA_SIZE 0x20

#pragma region Levels_Data

const uint8_t levelIndices[TOTAL_LEVEL_COUNT]
{
	10, 5, 0, 1, 2, 3, 4, 6, 9, 8, 7
};

const char* const levelNames[TOTAL_LEVEL_COUNT]
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

#pragma endregion

#pragma region Jiggies_Data

#define JIGGIES_COUNT 100
#define MAX_JIGGIES_PER_LEVEL 10

const uint8_t levelJiggiesCount[TOTAL_LEVEL_COUNT]
{
	0, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10
};

const uint8_t levelJiggiesIndices[TOTAL_LEVEL_COUNT][MAX_JIGGIES_PER_LEVEL]
{
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // Spiral Mountain
	{ 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C }, // Gruntilda's Lair
	{ 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A }, // Mumbo's Mountain
	{ 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14 }, // Treasure Trove Cove
	{ 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E }, // Clanker's Cavern
	{ 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28 }, // Bubblegloop Swamp
	{ 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32 }, // Freezeezy Peak
	{ 0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46 }, // Gobi's Valley
	{ 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 0x60, 0x61, 0x62, 0x63, 0x64 }, // Mad Monster Mansion
	{ 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A }, // Rusty Bucket Bay
	{ 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50 }  // Click Clock Wood
};

const char* const levelJiggiesNames[TOTAL_LEVEL_COUNT][MAX_JIGGIES_PER_LEVEL]
{
	{ "",            "",                 "",                "",                  "",                 "",                "",                 "",                  "",                 ""                 }, // Spiral Mountain
	{ "First Jiggy", "MM Witch Switch",  "CC Witch Switch", "TTC Witch Switch",  "BGS Witch Switch", "FP Witch Switch", "MMM Witch Switch", "GV Witch Switch",   "RBB Witch Switch", "CCW Witch Switch" }, // Gruntilda's Lair
	{ "Jinjos",      "Ticker's Tower",   "Mumbo's Skull",   "Juju",              "Huts",             "Ruins",           "Hill",             "Orange Pads",       "Chimpy",           "Conga"            }, // Mumbo's Mountain
	{ "Jinjos",      "Lighthouse",       "Alcove 1",        "Alcove 2",          "Pond",             "Sand Castle",     "Red X",            "Nipper",            "Lockup",           "Blubber"          }, // Treasure Trove Cove
	{ "Jinjos",      "Snippets",         "Clanker Raised",  "Bolt",              "Tail",             "Long Pipe",       "Tooth",            "Rings",             "Slow Sawblades",   "Fast Sawblades"   }, // Clanker's Cavern
	{ "Jinjos",      "Elevated Walkway", "Pink Egg",        "Croctus",           "Huts",             "Flibbits",        "Maze",             "Tanktup",           "Tiptup",           "Mr. Vile"         }, // Bubblegloop Swamp
	{ "Jinjos",      "Bounce on Boggy",  "Pipe",            "Second Boggy Race", "Snowman Buttons",  "Presents",        "Christmas Tree",   "First Boggy Race",  "Sir Slush",        "Wozza"            }, // Freezeezy Peak
	{ "Jinjos",      "Grabba",           "Shyinx",          "Matching Game",     "Maze",             "Water Pyramid",   "Histup",           "Gobi 1",            "Gobi 2",           "Ancient Ones"     }, // Gobi's Valley
	{ "Jinjos",      "Well",             "Napper",          "Cellar",            "Church Roof",      "Motzhand",        "Rain Barrel",      "Tumblar",           "Flower Pots",      "Loggo"            }, // Mad Monster Mansion
	{ "Jinjos",      "Warehouse",        "Snorkel",         "Whistle",           "Funnel",           "Boss Boom Box",   "Propellor",        "Captain's Cabin",   "Crane Cage",       "Engine Room"      }, // Rusty Bucket Bay
	{ "Jinjos",      "House",            "Eyrie",           "Nabnut",            "Gnawty",           "Zubbas",          "Flower",           "Summer Leaf Jumps", "Tree Top",         "Top Room"         }  // Click Clock Wood
};

#pragma endregion

#pragma region Honeycomb_Data

#define HONEYCOMB_COUNT 24
#define MAX_HONEYCOMBS_PER_LEVEL 6

const uint8_t levelHoneycombsCount[TOTAL_LEVEL_COUNT]
{
	6, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2
};

const uint8_t levelHoneycombsIndices[TOTAL_LEVEL_COUNT][MAX_HONEYCOMBS_PER_LEVEL]
{
	{ 0x13, 0x14, 0x15, 0x16, 0x17, 0x18 }, // Spiral Mountain
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // Gruntilda's Lair
	{ 0x01, 0x02, 0x00, 0x00, 0x00, 0x00 }, // Mumbo's Mountain
	{ 0x03, 0x04, 0x00, 0x00, 0x00, 0x00 }, // Treasure Trove Cove
	{ 0x05, 0x06, 0x00, 0x00, 0x00, 0x00 }, // Clanker's Cavern
	{ 0x07, 0x08, 0x00, 0x00, 0x00, 0x00 }, // Bubblegloop Swamp
	{ 0x09, 0x0A, 0x00, 0x00, 0x00, 0x00 }, // Freezeezy Peak
	{ 0x0B, 0x0C, 0x00, 0x00, 0x00, 0x00 }, // Gobi's Valley
	{ 0x11, 0x12, 0x00, 0x00, 0x00, 0x00 }, // Mad Monster Mansion
	{ 0x0F, 0x10, 0x00, 0x00, 0x00, 0x00 }, // Rusty Bucket Bay
	{ 0x0D, 0x0E, 0x00, 0x00, 0x00, 0x00 }  // Click Clock Wood
};

const char* const levelHoneycombsNames[TOTAL_LEVEL_COUNT][MAX_HONEYCOMBS_PER_LEVEL]
{
	{ "Stump",          "Waterfall",      "Underwater", "Tree", "Coliwobble", "Quarries" }, // Spiral Mountain
	{ "",               "",               "",           "",     "",           ""         }, // Gruntilda's Lair
	{ "Hill",           "Juju",           "",           "",     "",           ""         }, // Mumbo's Mountain
	{ "Underwater",     "Floating Box",   "",           "",     "",           ""         }, // Treasure Trove Cove
	{ "Underwater",     "Above Water",    "",           "",     "",           ""         }, // Clanker's Cavern
	{ "Mumbo's Skull",  "Tanktup",        "",           "",     "",           ""         }, // Bubblegloop Swamp
	{ "Wozza's Cave",   "Sir Slush",      "",           "",     "",           ""         }, // Freezeezy Peak
	{ "Cactus",         "Gobi",           "",           "",     "",           ""         }, // Gobi's Valley
	{ "Church Rafters", "Floorboard",     "",           "",     "",           ""         }, // Mad Monster Mansion
	{ "Boat House",     "Engine Room",    "",           "",     "",           ""         }, // Rusty Bucket Bay
	{ "Gnawty's House", "Nabnut's House", "",           "",     "",           ""         }  // Click Clock Wood
};

#pragma endregion

#pragma region Notes_Data

#define NOTES_COUNT 900
#define MAX_NOTES_PER_LEVEL 100

const bool levelHasNotes[TOTAL_LEVEL_COUNT]
{
	false, false, true, true, true, true, true, true, true, true, true
};

#pragma endregion

struct SaveSlot
{
public:
	uint8_t Magic;
	uint8_t SlotIndex;
	uint8_t Jiggies[13];
	uint8_t Honeycombs[3];
	uint8_t MumboTokens[16];
	uint8_t NoteScores[0x8];
	uint16_t Times[TOTAL_LEVEL_COUNT];
	uint8_t Flags[0x25]; // ?
	uint8_t Items[5];
	uint8_t Abilities[8];
	uint8_t Unk[0x2];
	uint32_t Checksum;

	inline uint32_t CalculateChecksum() const;
	void UpdateChecksum();
	bool IsValid() const;

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
		uint8_t index = levelHoneycombsIndices[level][honeycomb];
		return (Honeycombs[(index - 1) / 8] & (1 << (index & 7))) != 0;
	}

	inline void SetHoneycomb(const uint8_t level, const uint8_t honeycomb, bool val)
	{
		uint8_t index = levelHoneycombsIndices[level][honeycomb];
		if (val) Honeycombs[(index - 1) / 8] |= (1 << (index & 7));
		else Honeycombs[(index - 1) / 8] &= ~(1 << (index & 7));
	}

	inline bool GetJiggy(const uint8_t level, const uint8_t jiggy)
	{
		uint8_t index = levelJiggiesIndices[level][jiggy];
		return (Jiggies[(index - 1) / 8] & (1 << (index & 7))) != 0;
	}

	inline void SetJiggy(const uint8_t level, const uint8_t jiggy, bool val)
	{
		uint8_t index = levelJiggiesIndices[level][jiggy];
		if (val) Jiggies[(index - 1) / 8] |= (1 << (index & 7));
		else Jiggies[(index - 1) / 8] &= ~(1 << (index & 7));
	}

	inline uint8_t GetNotes(const uint8_t level)
	{
		if (!levelHasNotes[level]) return 0;

		//uint8_t index = levelJiggiesIndices[level][jiggy];
		//return (Jiggies[(index - 1) / 8] & (1 << (index & 7))) != 0;
	}

	inline bool GetPlayTime(const uint8_t level)
	{
		//uint8_t index = levelJiggiesIndices[level][jiggy];
		return 0;// (Jiggies[(index - 1) / 8] & (1 << (index & 7))) != 0;
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

struct GlobalData
{
public:
	uint8_t Unk[0x1C];
	uint32_t Checksum;

	inline uint32_t CalculateChecksum() const;
	void UpdateChecksum();
	bool IsValid() const;
};

struct SaveFile
{
public:
	SaveSlot saveSlots[TOTAL_NUM_SAVE_SLOTS] = {};
	GlobalData globalData = {};

	enum class Types { NotValid, PC, Nintendo64 };
	Types GetType() const;

	SaveSlot* GetSaveSlot(const uint8_t slotIndex);

	static uint32_t TransformSeed(uint64_t* seed);
	static uint32_t CalculateChecksum(uint8_t* start, uint8_t* end);
};