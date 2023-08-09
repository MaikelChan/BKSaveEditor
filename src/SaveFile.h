#pragma once

#include <cstdint>

#define SAVE_FILE_SIZE 0x200

#define TOTAL_NUM_SAVE_SLOTS 4
#define ACTUAL_NUM_SAVE_SLOTS 3
#define SAVE_SLOT_MAGIC 0x11
#define SAVE_SLOT_SIZE 0x78
#define GLOBAL_DATA_SIZE 0x20

#pragma region Levels_Data

#define TOTAL_LEVEL_COUNT 11

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

const int8_t levelNotesBitOffsets[TOTAL_LEVEL_COUNT]
{
	-1, -1, 56, 49, 42, 35, 28, 21, 0, 7, 14
};

#pragma endregion

#pragma region Progress Flags

enum class ProgressFlags {

    FILEPROG_3_MUSIC_NOTE_TEXT = 0x3, // Done
    FILEPROG_4_MUMBO_TOKEN_TEXT, // Done
    FILEPROG_5_BLUE_EGG_TEXT, // Done
    FILEPROG_6_RED_FEATHER_TEXT, // Done
    FILEPROG_7_GOLD_FEATHER_TEXT, // Done
    FILEPROG_8_ORANGE_TEXT, // Done
    FILEPROG_9_GOLD_BULLION_TEXT, // Done
    FILEPROG_A_HONEYCOMB_TEXT, // Done
    FILEPROG_B_EMPTY_HONEYCOMB_TEXT, // Done
    FILEPROG_C_EXTRA_LIFE_TEXT, // Done
    FILEPROG_D_BEEHIVE_TEXT, // Done
    FILEPROG_E_JINJO_TEXT, // Done
    FILEPROG_F_HAS_TOUCHED_PIRAHANA_WATER,
    FILEPROG_10_HAS_TOUCHED_SAND_EEL_SAND,
    FILEPROG_11_HAS_MET_MUMBO,
    FILEPROG_12_HAS_TRANSFORMED_BEFORE,
    FILEPROG_13, //something with xmas tree jiggy progress
    FILEPROG_14_HAS_TOUCHED_FP_ICY_WATER,
    FILEPROG_15_ENTER_MMM_TEXT, // Done
    FILEPROG_16_STOOD_ON_JIGSAW_PODIUM,
    FILEPROG_17_HAS_HAD_ENOUGH_JIGSAW_PIECES,
    FILEPROG_18_MM_WITCH_SWITCH_JIGGY_PRESSED, // Done
    FILEPROG_19_MMM_WITCH_SWITCH_JIGGY_PRESSED, // Done
    FILEPROG_1A_TTC_WITCH_SWITCH_JIGGY_PRESSED, // Done
    FILEPROG_1B_MET_YELLOW_FLIBBITS,
    FILEPROG_1C_RBB_WITCH_SWITCH_JIGGY_PRESSED, // Done
    FILEPROG_1D_MMM_DINNING_ROOM_CUTSCENE,
    FILEPROG_1E_LAIR_GRATE_TO_BGS_PUZZLE_OPEN,
    FILEPROG_1F_CC_LOBBY_PIPE_1_RAISED,
    FILEPROG_20_CC_LOBBY_PIPE_2_RAISED,
    FILEPROG_21_CC_LOBBY_PIPE_3_RAISED,
    FILEPROG_22_WATER_SWITCH_1_PRESSED, // Done
    FILEPROG_23_LAIR_WATER_LEVEL_1,
    FILEPROG_24_WATER_SWITCH_2_PRESSED, // Done
    FILEPROG_25_LAIR_WATER_LEVEL_2,
    FILEPROG_26_WATER_SWITCH_3_PRESSED, // Done
    FILEPROG_27_LAIR_WATER_LEVEL_3,

    FILEPROG_31_MM_OPEN = 0x31, // Done
    FILEPROG_32_TTC_OPEN, // Done
    FILEPROG_33_CC_OPEN, // Done
    FILEPROG_34_BGS_OPEN, // Done
    FILEPROG_35_FP_OPEN, // Done
    FILEPROG_36_GV_OPEN, // Done
    FILEPROG_37_MMM_OPEN, // Done
    FILEPROG_38_RBB_OPEN, // Done
    FILEPROG_39_CCW_OPEN, // Done
    FILEPROG_3A_NOTE_DOOR_50_OPEN, // Done
    FILEPROG_3B_NOTE_DOOR_180_OPEN, // Done
    FILEPROG_3C_NOTE_DOOR_260_OPEN, // Done
    FILEPROG_3D_NOTE_DOOR_350_OPEN, // Done
    FILEPROG_3E_NOTE_DOOR_450_OPEN, // Done
    FILEPROG_3F_NOTE_DOOR_640_OPEN, // Done
    FILEPROG_40_NOTE_DOOR_765_OPEN, // Done
    FILEPROG_41_NOTE_DOOR_810_OPEN, // Done
    FILEPROG_42_NOTE_DOOR_828_OPEN, // Done
    FILEPROG_43_NOTE_DOOR_846_OPEN, // Done
    FILEPROG_44_NOTE_DOOR_864_OPEN, // Done
    FILEPROG_45_NOTE_DOOR_882_OPEN, // Done
    FILEPROG_46_CCW_WITCH_SWITCH_JIGGY_PRESSED, // Done
    FILEPROG_47_FP_WITCH_SWITCH_JIGGY_PRESSED, // Done
    FILEPROG_48_FP_WITCH_SWITCH_ADVENT_DOOR_OPEN, // Done
    // {index=0x49, type="Prog", level=6, name="Pink Cauldron 1 Active"},
    // {index=0x4A, type="Prog", level=6, name="Pink Cauldron 2 Active"},
    // {index=0x4B, type="Prog", level=6, name="Green Cauldron 1 Active"},
    // {index=0x4C, type="Prog", level=6, name="Green Cauldron 2 Active"},
    // {index=0x4D, type="Prog", level=6, name="Red Cauldron 1 Active"},
    // {index=0x4E, type="Prog", level=6, name="Red Cauldron 2 Active"},
    // -- 0x4F - Unused Cauldron Pair?
    // -- 0x50 - Unused Cauldron Pair?
    // {index=0x51, type="Prog", level=6, name="Yellow Cauldron 1 Active"},
    // {index=0x52, type="Prog", level=6, name="Yellow Cauldron 2 Active"},
    FILEPROG_53_CCW_PUZZLE_PODIUM_SWITCH_PRESSED = 0x53, // Done
    FILEPROG_54_CCW_PUZZLE_PODIUM_ACTIVE,
    FILEPROG_55_FF_BK_SQUARE_INSTRUCTIONS,
    FILEPROG_56_FF_PICTURE_SQUARE_INSTRUCTIONS,
    FILEPROG_57_FF_MUSIC_SQAURE_INSTRUCTIONS,
    FILEPROG_58_FF_MINIGAME_SQAURE_INSTRUCTIONS,
    FILEPROG_59_FF_GRUNTY_SQAURE_INSTRUCTIONS,
    FILEPROG_5A_FF_DEATH_SQAURE_INSTRUCTIONS,
    FILEPROG_5B_FF_JOKER_SQAURE_INSTRUCTIONS,
    FILEPROG_5C_FF_PATTERN_SET,
    FILEPROG_5D_MM_PUZZLE_PIECES_PLACED = 0x5D, //1 bit
    FILEPROG_5E_TCC_PUZZLE_PIECES_PLACED = 0x5E, //2 bit
    FILEPROG_60_CC_PUZZLE_PIECES_PLACED = 0x60, //3 bit
    FILEPROG_63_BGS_PUZZLE_PIECES_PLACED = 0x63, //3 bit
    FILEPROG_66_FP_PUZZLE_PIECES_PLACED = 0x66, //4 bit
    FILEPROG_6A_GV_PUZZLE_PIECES_PLACED = 0x6A, //4 bit
    FILEPROG_6E_MMM_PUZZLE_PIECES_PLACED = 0x6E, //4 bit
    FILEPROG_72_RBB_PUZZLE_PIECES_PLACED = 0x72, //4 bit
    FILEPROG_76_CCW_PUZZLE_PIECES_PLACED = 0x76, //4 bit
    FILEPROG_7A_DOG_PUZZLE_PIECES_PLACED = 0x7A, //5 bit
    FILEPROG_7F_DOUBLE_HEALTH_PUZZLE_PIECES_PLACED = 0x7F, //3 bit
    // {index=0x82, unknown}
    FILEPROG_82_MET_TWINKLIES = 0x82,
    FILEPROG_83_MAGIC_GET_WEAK_TEXT, // Done
    FILEPROG_84_MAGIC_ALL_GONE_TEXT, // Done
    // {index=0x85, type="Prog", level=6, name="Lair Crypt Gate Open"},
    FILEPROG_86_HAS_TOUCHED_MMM_THORN_HEDGE = 0x86,

    FILEPROG_88_TRIED_LOGGO_AS_BEAR = 0x88,
    FILEPROG_89_ENTERED_LOGGO_AS_PUMPKIN,
    FILEPROG_8A_EXITED_LOGGO,
    FILEPROG_8B_CCW_SPRING_OPEN,
    FILEPROG_8C_CCW_SUMMER_OPEN,
    FILEPROG_8D_CCW_AUTUMN_OPEN,
    FILEPROG_8E_CCW_WINTER_OPEN,
    FILEPROG_8F_MET_BEE_INFESTED_BEEHIVE,
    FILEPROG_90_PAID_TERMITE_COST,
    FILEPROG_91_PAID_PUMPKIN_COST,
    FILEPROG_92_PAID_WALRUS_COST,
    FILEPROG_93_PAID_CROC_COST,
    FILEPROG_94_PAID_BEE_COST,

    FILEPROG_96_MET_BRENTILDA = 0x96,
    FILEPROG_97_ENTERED_LAIR_TEXT, // Done
    FILEPROG_98_EXITED_LEVEL_TEXT, // Done
    FILEPROG_99_PAST_50_NOTE_DOOR_TEXT, // Done
    FILEPROG_9A_CC_WITCH_SWITCH_PRESSED, // Done
    FILEPROG_9B_LAIR_CC_WITCH_SWITCH_EYES_ACTIVE, // Done
    FILEPROG_9C_LAIR_CC_WITCH_SWITCH_LEFT_EYE_PRESSED, // Done
    FILEPROG_9D_LAIR_CC_WITCH_SWITCH_RIGHT_EYE_PRESSED, // Done
    FILEPROG_9E_CRYPT_COFFIN_LID_OPEN,
    FILEPROG_9F_BGS_WITCH_SWITCH_JIGGY_PRESSED, // Done
    FILEPROG_A0_GV_WITCH_SWITCH_JIGGY_PRESSED, // Done
    FILEPROG_A1_STATUE_HAT_OPEN,
    FILEPROG_A2_GV_LOBBY_COFFIN_OPEN,
    FILEPROG_A3_GV_SNS_SWITCH_PRESSED, // Done
    FILEPROG_A4_GV_SNS_SARCOPHAGUS_OPEN,
    //crypt gate open?
    FILEPROG_A6_FURNACE_FUN_COMPLETE = 0xA6,
    FILEPROG_A7_NEAR_PUZZLE_PODIUM_TEXT, // Done
    FILEPROG_A8_HAS_DIED,
    FILEPROG_A9_HAS_TOUCHED_RBB_OVEN,
    FILEPROG_AA_HAS_TOUCHED_CCW_BRAMBLE_FIELD,
    FILEPROG_AB_SWIM_OILY_WATER,
    FILEPROG_AC_DIVE_OILY_WATER,
    FILEPROG_AD_CHEATO_BLUEEGGS_UNLOCKED,
    FILEPROG_AE_CHEATO_REDFEATHERS_UNLOCKED,
    FILEPROG_AF_CHEATO_GOLDFEATHERS_UNLOCKED,
    FILEPROG_B0_HAS_ENTERED_MM,
    FILEPROG_B1_HAS_ENTERED_BGS,
    FILEPROG_B2_HAS_ENTERED_TTC,
    FILEPROG_B3_HAS_ENTERED_GV,
    FILEPROG_B4_HAS_ENTERED_RBB,
    FILEPROG_B5_HAS_ENTERED_CCW,
    FILEPROG_B6_HAS_ENTERED_FP,
    FILEPROG_B7_HAS_ENTERED_MMM,
    FILEPROG_B8_HAS_ENTERED_CC,
    FILEPROG_B9_DOUBLE_HEALTH, // Done
    FILEPROG_BA_HAS_SEEN_TREX_TEXT, // Done
    FILEPROG_BB_MUMBO_MISTAKE_INDEX, //2 bits
    FILEPROG_BD_ENTER_LAIR_CUTSCENE = 0xBD,
    FILEPROG_BE_CHEATO_BLUEEGGS, // Done
    FILEPROG_BF_CHEATO_REDFEATHERS, // Done
    FILEPROG_C0_CHEATO_GOLDFEATHERS, // Done
    FILEPROG_C1_BADDIES_ESCAPE_TEXT, // Done
    FILEPROG_C2_GRATE_TO_RBB_PUZZLE_OPEN,
    FILEPROG_C3_ICE_BALL_TO_CHEATO_BROKEN, // Done
    FILEPROG_C4_STATUE_EYE_BROKEN, // Done
    FILEPROG_C5_RAREWARE_BOX_BROKEN, // Done
    FILEPROG_C6_LAIR_JUMP_PAD_SWITCH_PRESSED, // Done
    FILEPROG_C7_LAIR_JUMP_PAD_ACTIVE,
    FILEPROG_C8_LAIR_BRICKWALL_TO_WADINGBOOTS_BROKEN, // Done
    FILEPROG_C9_LAIR_BRICKWALL_TO_SHOCKJUMP_PAD_BROKEN, // Done
    FILEPROG_CA_COBWEB_BLOCKING_PURPLE_CAULDRON_BROKEN, // Done
    FILEPROG_CB_LAIR_COBWEB_OVER_FLIGHTPAD_BROKEN, // Done
    FILEPROG_CC_LAIR_COBWEB_OVER_GREEN_CAULDRON_BROKEN, // Done
    FILEPROG_CD_GRATE_TO_WATER_SWITCH_3_OPEN, // Done
    FILEPROG_CE_GRATE_TO_MMM_PUZZLE_OPEN,
    FILEPROG_CF_HAS_ENTERED_FINAL_FIGHT,

    FILEPROG_D1_HAS_ACTIVATED_A_JINJO_STATUE_IN_FINAL_FIGHT = 0xD1,
    FILEPROG_D2_HAS_SPAWNED_A_JINJO_STATUE_IN_FINAL_FIGHT,
    FILEPROG_D3_FF_PATTERN, //8 bit


    // {index=0xDB, unknown},
    FILEPROG_DB_SKIPPED_TUTORIAL = 0xDB,
    FILEPROG_DC_HAS_HAD_ENOUGH_TOKENS_BEFORE,
    FILEPROG_DD_HAS_TOUCHED_ICY_WATER,
    FILEPROG_DE_USED_ALL_YOUR_PUZZLE_PIECES,
    FILEPROG_DF_CAN_REMOVE_ALL_PUZZLE_PIECES,
    FILEPROG_E0_CAN_PLACE_ALL_PUZZLE_PIECES,

    FILEPROG_E2_DOOR_OF_GRUNTY_OPEN = 0xE2, // Done
    FILEPROG_E3_CCW_FLOWER_SPRING,
    FILEPROG_E4_CCW_FLOWER_SUMMER,
    FILEPROG_E5_CCW_FLOWER_AUTUMN,
    FILEPROG_E6_SPRING_EYRIE_HATCHED,
    FILEPROG_E7_SUMMER_EYRIE_FED,
    FILEPROG_E8_AUTMN_EYRIE_FED,
    FILEPROG_E9_TALKED_TO_BRENTILDA_1, // Done
    FILEPROG_EA_TALKED_TO_BRENTILDA_2, // Done
    FILEPROG_EB_TALKED_TO_BRENTILDA_3, // Done
    FILEPROG_EC_TALKED_TO_BRENTILDA_4, // Done
    FILEPROG_ED_TALKED_TO_BRENTILDA_5, // Done
    FILEPROG_EE_TALKED_TO_BRENTILDA_6, // Done
    FILEPROG_EF_TALKED_TO_BRENTILDA_7, // Done
    FILEPROG_F0_TALKED_TO_BRENTILDA_8, // Done
    FILEPROG_F1_TALKED_TO_BRENTILDA_9, // Done
    FILEPROG_F2_TALKED_TO_BRENTILDA_10, // Done
    FILEPROG_F3_MET_DINGPOT,
    FILEPROG_F4_ENTER_FF_CUTSCENE,
    FILEPROG_F5_COMPLETED_A_WARP_CAULDRON_SET,
    FILEPROG_F6_SEEN_DOOR_OF_GRUNTY_PUZZLE_PODIUM,
    FILEPROG_F7_HAS_TRANSFORMED_IN_CRYPT,
    FILEPROG_F8_KING_SANDYBUTT_PYRAMID_STATE = 0xF8, //2bit
    // FILEPROG_F8_KING_SANDYBUTT_PYRAMID_STATE = 0xF9, //2bit

    FILEPROG_FC_DEFEAT_GRUNTY = 0xFC,
    FILEPROG_FD_CHEATCODES_ENTERED //2 bit
};

#pragma endregion

#pragma region Items Held

#define MAX_MUMBO_TOKENS 116
#define MAX_EGGS 200
#define MAX_RED_FEATHERS 100
#define MAX_GOLD_FEATHERS 20

enum class HeldItems
{
	MumboTokens = 0,
	Eggs,
	RedFeathers,
	GoldFeathers,
	Jiggies
};

#pragma endregion

struct SaveSlot
{
private:
	uint8_t Magic;
	uint8_t SlotIndex;
	uint8_t Jiggies[13];
	uint8_t Honeycombs[3];
	uint8_t MumboTokens[16];
	uint8_t NoteScores[0x8];
	uint16_t Times[TOTAL_LEVEL_COUNT];
	uint8_t Flags[0x25];
	uint8_t Items[5];
	uint8_t Abilities[8];
	uint8_t Unk[0x2];
	uint32_t Checksum;

public:
	uint32_t CalculateChecksum() const;
	void UpdateChecksum(const bool endianSwap);
	bool IsValid(const bool endianSwap) const;

	//inline bool GetFlag(const uint32_t mask) const
	//{
	//	return 0; // (Flags & mask) != 0;
	//}

	//inline void SetFlag(const uint32_t mask, const bool value)
	//{
	//	//if (value) Flags |= mask;
	//	//else Flags &= ~mask;
	//}

	uint8_t GetMagic() const;
	uint8_t GetSlotIndex() const;

	bool GetHoneycomb(const uint8_t level, const uint8_t honeycomb) const;
	void SetHoneycomb(const uint8_t level, const uint8_t honeycomb, bool value);

	bool GetJiggy(const uint8_t level, const uint8_t jiggy) const;
	void SetJiggy(const uint8_t level, const uint8_t jiggy, bool value);

	uint8_t GetNotes(const uint8_t level) const;
	void SetNotes(const uint8_t level, const uint8_t value) const;

	uint16_t GetPlayTime(const uint8_t level, const bool endianSwap) const;
	void SetPlayTime(const uint8_t level, const uint16_t value, const bool endianSwap);

	bool GetProgressFlag(const ProgressFlags flag) const;
	void SetProgressFlag(const ProgressFlags flag, const bool value);

	uint8_t GetHeldItem(const HeldItems heldItem) const;
	void SetHeldItem(const HeldItems heldItem, const uint8_t value);

	uint32_t GetChecksum(const bool endianSwap) const;
};

struct GlobalData
{
private:
	uint8_t Unk[0x1C];
	uint32_t Checksum;

public:
	uint32_t CalculateChecksum() const;
	void UpdateChecksum(const bool endianSwap);
	bool IsValid(const bool endianSwap) const;

	uint32_t GetChecksum(const bool endianSwap) const;
};

struct SaveFile
{
public:
	SaveSlot saveSlots[TOTAL_NUM_SAVE_SLOTS] = {};
	GlobalData globalData = {};

	SaveSlot* GetSaveSlot(const uint8_t slotIndex);

	static uint32_t TransformSeed(uint64_t* seed);
	static uint32_t CalculateChecksum(uint8_t* start, uint8_t* end);
};