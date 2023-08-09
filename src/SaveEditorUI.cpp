#include "SaveEditorUI.h"
#include "MainUI.h"
#include "Utils.h"

SaveEditorUI::SaveEditorUI(const MainUI* mainUI) : BaseUI(mainUI)
{
	SaveEditorUI::mainUI = mainUI;
}

SaveEditorUI::~SaveEditorUI()
{

}

void SaveEditorUI::VisibilityChanged(const bool isVisible)
{
	BaseUI::VisibilityChanged(isVisible);
}

void SaveEditorUI::DoRender()
{
	BaseUI::DoRender();

	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->WorkPos);
	ImGui::SetNextWindowSize(viewport->WorkSize);

	if (ImGui::Begin("Save Editor", NULL, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBackground))
	{
		ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;

		const SaveData& saveData = mainUI->GetSaveData();
		SaveFile* saveFile = saveData.GetSaveFile();

		if (saveFile && ImGui::BeginTabBar("Save Slots", tab_bar_flags))
		{
			for (int s = 0; s < ACTUAL_NUM_SAVE_SLOTS; s++)
			{
				if (ImGui::BeginTabItem(tabNames[s]))
				{
					SaveSlot* saveSlot = saveFile->GetSaveSlot(s);

					if (!saveSlot)
					{
						ImGui::Text("The slot is empty.");
					}
					else
					{
						PrintChecksum(saveSlot->GetChecksum(saveData.NeedsEndianSwap()));

						if (ImGui::BeginTabBar("Sections", tab_bar_flags))
						{
							RenderMainSection(saveData, saveSlot);
							RenderProgressFlagsSection(saveData, saveSlot);

							ImGui::EndTabBar();
						}
					}

					/*if (ImGui::BeginTable("FlagsTable", 3))
					{
						ImGui::TableSetupColumn("DoorColumn", ImGuiTableColumnFlags_WidthStretch, 0.8f);
						ImGui::TableSetupColumn("CapColumn", ImGuiTableColumnFlags_WidthStretch);
						ImGui::TableSetupColumn("MiscColumn", ImGuiTableColumnFlags_WidthStretch, 0.4f);

						ImGui::TableNextRow();

						ImGui::TableSetColumnIndex(0);
						ImGui::SeparatorText("Unlocked Doors");
						if (ImGui::BeginTable("DoorsUnlockedTable", 2))
						{
							ImGui::TableNextRow();

							ImGui::TableSetColumnIndex(0);
							CheckboxSaveFlags("Basement Door", s, showBackup, SAVE_FLAG_UNLOCKED_BASEMENT_DOOR);
							CheckboxSaveFlags("WF Door", s, showBackup, SAVE_FLAG_UNLOCKED_WF_DOOR);
							CheckboxSaveFlags("CCM Door", s, showBackup, SAVE_FLAG_UNLOCKED_CCM_DOOR);
							CheckboxSaveFlags("BITDW Door", s, showBackup, SAVE_FLAG_UNLOCKED_BITDW_DOOR);
							CheckboxSaveFlags("50 Star Door", s, showBackup, SAVE_FLAG_UNLOCKED_50_STAR_DOOR);

							ImGui::TableSetColumnIndex(1);
							CheckboxSaveFlags("Upstairs Door", s, showBackup, SAVE_FLAG_UNLOCKED_UPSTAIRS_DOOR);
							CheckboxSaveFlags("JRB Door", s, showBackup, SAVE_FLAG_UNLOCKED_JRB_DOOR);
							CheckboxSaveFlags("PSS Door", s, showBackup, SAVE_FLAG_UNLOCKED_PSS_DOOR);
							CheckboxSaveFlags("BITFS Door", s, showBackup, SAVE_FLAG_UNLOCKED_BITFS_DOOR);

							ImGui::EndTable();
						}

						ImGui::TableSetColumnIndex(1);
						ImGui::SeparatorText("Mario's Cap");
						if (ImGui::BeginTable("MarioCapTable", 2))
						{
							ImGui::TableNextRow();

							ImGui::TableSetColumnIndex(0);
							CheckboxSaveFlags("Have Wing Cap", s, showBackup, SAVE_FLAG_HAVE_WING_CAP);
							CheckboxSaveFlags("Have Metal Cap", s, showBackup, SAVE_FLAG_HAVE_METAL_CAP);
							CheckboxSaveFlags("Have Vanish Cap", s, showBackup, SAVE_FLAG_HAVE_VANISH_CAP);

							ImGui::TableSetColumnIndex(1);
							CheckboxSaveFlags("Cap on Ground", s, showBackup, SAVE_FLAG_CAP_ON_GROUND);
							CheckboxSaveFlags("Cap on Klepto", s, showBackup, SAVE_FLAG_CAP_ON_KLEPTO);
							CheckboxSaveFlags("Cap on Ukiki", s, showBackup, SAVE_FLAG_CAP_ON_UKIKI);
							CheckboxSaveFlags("Cap on Mr Blizzard", s, showBackup, SAVE_FLAG_CAP_ON_MR_BLIZZARD);

							ImGui::SetNextItemWidth(24);
							if (ImGui::InputScalar("##Cap Level", ImGuiDataType_U8, &saveData->saveSlots[s][showBackup].CapLevel, NULL, NULL, "%u"))
							{
								if (saveData->saveSlots[s][showBackup].CapLevel > COURSE_STAGES_COUNT_INTERNAL)
									saveData->saveSlots[s][showBackup].CapLevel = COURSE_STAGES_COUNT_INTERNAL;
								saveData->saveSlots[s][showBackup].UpdateChecksum();
							}

							ImGui::SameLine();

							ImGui::SetNextItemWidth(24);
							if (ImGui::InputScalar("Cap Level/Area", ImGuiDataType_U8, &saveData->saveSlots[s][showBackup].CapArea, NULL, NULL, "%u"))
							{
								saveData->saveSlots[s][showBackup].UpdateChecksum();
							}

							ImGui::EndTable();
						}

						ImGui::TableSetColumnIndex(2);
						ImGui::SeparatorText("Miscellaneous");
						CheckboxSaveFlags("Basement Key", s, showBackup, SAVE_FLAG_HAVE_KEY_1);
						CheckboxSaveFlags("Upstairs Key", s, showBackup, SAVE_FLAG_HAVE_KEY_2);
						CheckboxSaveFlags("Moat Drained", s, showBackup, SAVE_FLAG_MOAT_DRAINED);
						CheckboxSaveFlags("DDD Moved Back", s, showBackup, SAVE_FLAG_DDD_MOVED_BACK);

						ImGui::EndTable();
					}

					ImGui::SeparatorText("Castle Stars");

					if (ImGui::BeginTable("CastleStarsTable", 2))
					{
						ImGui::TableNextRow();

						ImGui::TableSetColumnIndex(0);
						CheckboxSaveFlags("Toad Star 1", s, showBackup, SAVE_FLAG_COLLECTED_TOAD_STAR_1);
						ImGui::SameLine();
						CheckboxSaveFlags("Toad Star 2", s, showBackup, SAVE_FLAG_COLLECTED_TOAD_STAR_2);
						ImGui::SameLine();
						CheckboxSaveFlags("Toad Star 3", s, showBackup, SAVE_FLAG_COLLECTED_TOAD_STAR_3);

						ImGui::TableSetColumnIndex(1);
						CheckboxSaveFlags("Mips Star 1", s, showBackup, SAVE_FLAG_COLLECTED_MIPS_STAR_1);
						ImGui::SameLine();
						CheckboxSaveFlags("Mips Star 2", s, showBackup, SAVE_FLAG_COLLECTED_MIPS_STAR_2);

						ImGui::EndTable();
					}

					ImGui::SeparatorText("Courses");

					static ImGuiTableFlags flags = ImGuiTableFlags_ScrollY | ImGuiTableFlags_RowBg | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_BordersOuter;

					if (ImGui::BeginTable("CoursesTable", 11, flags))
					{
						ImGui::TableSetupScrollFreeze(0, 1);
						ImGui::TableSetupColumn("#");
						ImGui::TableSetupColumn("Name");
						ImGui::TableSetupColumn(u8"\u0101");
						ImGui::TableSetupColumn(u8"\u0101");
						ImGui::TableSetupColumn(u8"\u0101");
						ImGui::TableSetupColumn(u8"\u0101");
						ImGui::TableSetupColumn(u8"\u0101");
						ImGui::TableSetupColumn(u8"\u0101");
						ImGui::TableSetupColumn(u8"100 Coin \u0101");
						ImGui::TableSetupColumn("Cannon Open");
						ImGui::TableSetupColumn("Max Coins");

						ImGui::TableHeadersRow();

						for (int c = 0; c < COURSE_COUNT; c++)
						{
							ImGui::PushID(c);

							ImGui::TableNextRow();

							ImGui::TableSetColumnIndex(0);
							ImGui::Text("%i", c + 1);

							ImGui::TableSetColumnIndex(1);
							ImGui::Text("%s", courseNames[c]);

							for (int st = 0; st < courseStarCount[c]; st++)
							{
								ImGui::PushID(st);

								ImGui::TableSetColumnIndex(2 + st);
								CheckboxCourseData("##Star", s, showBackup, c, 1 << st);

								ImGui::PopID();
							}

							if (courseHasCannon[c])
							{
								ImGui::TableSetColumnIndex(9);
								CheckboxCourseData("##Cannon Open", s, showBackup, c + 1, SAVE_COURSE_FLAG_STAR_CANNON_OPEN);
							}

							ImGui::TableSetColumnIndex(10);

							if (c < COURSE_STAGES_COUNT)
							{
								if (ImGui::InputScalar("##Max Coins", ImGuiDataType_U8, &saveData->saveSlots[s][showBackup].CourseCoinScores[c], NULL, NULL, "%u"))
								{
									saveData->saveSlots[s][showBackup].UpdateChecksum();
								}
							}

							ImGui::PopID();
						}
						ImGui::EndTable();
					}*/

					//if (!fileExists) ImGui::EndDisabled();

					ImGui::EndTabItem();
				}
			}

			/*if (ImGui::BeginTabItem("Settings"))
			{
				if (showBackup) ImGui::BeginDisabled();

				ImGui::Dummy(ImVec2(21, 21));
				ImGui::SameLine();
				ImGui::AlignTextToFramePadding();
				PrintChecksum(saveData->settings[showBackup].Checksum);

				ImGui::SeparatorText("Sound Mode");

				int value = saveData->settings[showBackup].soundMode;
				ImGui::RadioButton("Stereo", &value, 0);
				ImGui::SameLine();
				ImGui::RadioButton("Mono", &value, 1);
				ImGui::SameLine();
				ImGui::RadioButton("Headset", &value, 2);
				if (saveData->settings[showBackup].soundMode != value)
				{
					saveData->settings[showBackup].soundMode = static_cast<uint16_t>(value);
					saveData->settings[showBackup].UpdateChecksum();
				}

				ImGui::SeparatorText("Language");

				value = saveData->settings[showBackup].language;
				ImGui::RadioButton("English", &value, 0);
				ImGui::SameLine();
				ImGui::RadioButton("French", &value, 1);
				ImGui::SameLine();
				ImGui::RadioButton("German", &value, 2);
				if (saveData->settings[showBackup].language != value)
				{
					saveData->settings[showBackup].language = static_cast<uint16_t>(value);
					saveData->settings[showBackup].UpdateChecksum();
				}

				ImGui::SeparatorText("Coin Ages");

				static ImGuiTableFlags flags = ImGuiTableFlags_ScrollY | ImGuiTableFlags_RowBg | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_BordersOuter;

				if (ImGui::BeginTable("CoinAges", 6, flags))
				{
					ImGui::TableSetupScrollFreeze(0, 1);
					ImGui::TableSetupColumn("#");
					ImGui::TableSetupColumn("Name");
					ImGui::TableSetupColumn("Mario A");
					ImGui::TableSetupColumn("Mario B");
					ImGui::TableSetupColumn("Mario C");
					ImGui::TableSetupColumn("Mario D");

					ImGui::TableHeadersRow();

					for (int c = 0; c < COURSE_STAGES_COUNT; c++)
					{
						ImGui::PushID(c);

						ImGui::TableNextRow();

						ImGui::TableSetColumnIndex(0);
						ImGui::Text("%i", c + 1);

						ImGui::TableSetColumnIndex(1);
						ImGui::Text("%s", courseNames[c]);

						const ImU8 step = 1;
						int shift = c * 2;

						for (int s = 0; s < NUM_SAVE_SLOTS; s++)
						{
							ImGui::PushID(s);

							uint8_t value = (saveData->settings[showBackup].CoinScoreAges[s] >> shift) & 0x3;

							ImGui::TableSetColumnIndex(2 + s);

							ImGui::SetNextItemWidth(80);
							if (ImGui::InputScalar("##CoinAgeCell", ImGuiDataType_U8, &value, &step, NULL, "%u"))
							{
								if (value > 3) value = 3;
								saveData->settings[showBackup].CoinScoreAges[s] &= ~(0x3 << shift);
								saveData->settings[showBackup].CoinScoreAges[s] |= value << shift;
								saveData->settings[showBackup].UpdateChecksum();
							}

							ImGui::PopID();
						}

						ImGui::PopID();
					}
					ImGui::EndTable();
				}

				if (showBackup) ImGui::EndDisabled();

				ImGui::EndTabItem();
			}*/

			ImGui::EndTabBar();
		}
	}
	ImGui::End();
}

bool SaveEditorUI::CheckboxProgressFlags(const SaveData& saveData, SaveSlot* saveSlot, const char* label, const ProgressFlags flag) const
{
	bool value = saveSlot->GetProgressFlag(flag);

	if (ImGui::Checkbox(label, &value))
	{
		saveSlot->SetProgressFlag(flag, value);
		saveSlot->UpdateChecksum(saveData.NeedsEndianSwap());
	}

	return value;
}

void SaveEditorUI::PrintChecksum(const uint32_t checksum) const
{
	ImGui::SetCursorPosX(ImGui::GetWindowWidth() - ImGui::CalcTextSize("Checksum: 0xFFFFFFFF").x - 32);
	ImGui::TextColored(ImVec4(0.7f, 0.5f, 0.6f, 1.0f), "Checksum: 0x%x", checksum);
}

void SaveEditorUI::PrintHeader(const char* label) const
{
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.7f, 0.5f, 0.6f, 1.0f));
	ImGui::SeparatorText(label);
	ImGui::PopStyleColor();
}

void SaveEditorUI::RenderMainSection(const SaveData& saveData, SaveSlot* saveSlot)
{
	if (!ImGui::BeginTabItem("Main")) return;

	ImGui::SeparatorText("Held Items");

	uint8_t mumboTokens = saveSlot->GetHeldItem(HeldItems::MumboTokens);
	if (ImGui::InputScalar("Mumbo Tokens", ImGuiDataType_U8, &mumboTokens, NULL, NULL, "%u"))
	{
		if (mumboTokens > MAX_MUMBO_TOKENS) mumboTokens = MAX_MUMBO_TOKENS;
		saveSlot->SetHeldItem(HeldItems::MumboTokens, mumboTokens);
		saveSlot->UpdateChecksum(saveData.NeedsEndianSwap());
	}

	uint8_t eggs = saveSlot->GetHeldItem(HeldItems::Eggs);
	if (ImGui::InputScalar("Eggs", ImGuiDataType_U8, &eggs, NULL, NULL, "%u"))
	{
		if (eggs > MAX_EGGS) eggs = MAX_EGGS;
		saveSlot->SetHeldItem(HeldItems::Eggs, eggs);
		saveSlot->UpdateChecksum(saveData.NeedsEndianSwap());
	}

	uint8_t redFeathers = saveSlot->GetHeldItem(HeldItems::RedFeathers);
	if (ImGui::InputScalar("Red Feathers", ImGuiDataType_U8, &redFeathers, NULL, NULL, "%u"))
	{
		if (redFeathers > MAX_RED_FEATHERS) redFeathers = MAX_RED_FEATHERS;
		saveSlot->SetHeldItem(HeldItems::RedFeathers, redFeathers);
		saveSlot->UpdateChecksum(saveData.NeedsEndianSwap());
	}

	uint8_t goldFeathers = saveSlot->GetHeldItem(HeldItems::GoldFeathers);
	if (ImGui::InputScalar("Gold Feathers", ImGuiDataType_U8, &goldFeathers, NULL, NULL, "%u"))
	{
		if (goldFeathers > MAX_GOLD_FEATHERS) goldFeathers = MAX_GOLD_FEATHERS;
		saveSlot->SetHeldItem(HeldItems::GoldFeathers, goldFeathers);
		saveSlot->UpdateChecksum(saveData.NeedsEndianSwap());
	}

	uint8_t jiggies = saveSlot->GetHeldItem(HeldItems::Jiggies);
	if (ImGui::InputScalar("Jiggies", ImGuiDataType_U8, &jiggies, NULL, NULL, "%u"))
	{
		if (jiggies > JIGGIES_COUNT) jiggies = JIGGIES_COUNT;
		saveSlot->SetHeldItem(HeldItems::Jiggies, jiggies);
		saveSlot->UpdateChecksum(saveData.NeedsEndianSwap());
	}

	ImGui::SeparatorText("Levels");

	static ImGuiTableFlags flags = ImGuiTableFlags_ScrollY | ImGuiTableFlags_RowBg | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_BordersOuter;

	if (ImGui::BeginTable("LevelsTable", 6, flags))
	{
		uint8_t totalJiggies = 0;
		uint8_t totalHoneycombs = 0;
		uint32_t totalPlayTime = 0;

		ImGui::TableSetupScrollFreeze(0, 1);
		ImGui::TableSetupColumn("#");
		ImGui::TableSetupColumn("Name");
		ImGui::TableSetupColumn("Jiggies");
		ImGui::TableSetupColumn("Honeycombs");
		ImGui::TableSetupColumn("Note Score");
		ImGui::TableSetupColumn("Play Time (s)");

		ImGui::TableHeadersRow();

		for (int l = 0; l < TOTAL_LEVEL_COUNT; l++)
		{
			ImGui::PushID(l);

			ImGui::TableNextRow();

			ImGui::TableSetColumnIndex(0);
			ImGui::Text("%i", l + 1);

			ImGui::TableSetColumnIndex(1);
			ImGui::Text("%s", levelNames[l]);

			ImGui::TableSetColumnIndex(2);
			for (int j = 0; j < levelJiggiesCount[l]; j++)
			{
				ImGui::PushID(j);

				bool value = saveSlot->GetJiggy(l, j);
				if (ImGui::Checkbox("##Jiggy", &value))
				{
					saveSlot->SetJiggy(l, j, value);
					saveSlot->UpdateChecksum(saveData.NeedsEndianSwap());
				}

				if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNone))
					ImGui::SetTooltip(levelJiggiesNames[l][j]);

				if (value) totalJiggies++;

				ImGui::PopID();

				if (j < levelJiggiesCount[l] - 1) ImGui::SameLine();
			}

			ImGui::TableSetColumnIndex(3);
			for (int h = 0; h < levelHoneycombsCount[l]; h++)
			{
				ImGui::PushID(h);

				bool value = saveSlot->GetHoneycomb(l, h);
				if (ImGui::Checkbox("##Honeycomb", &value))
				{
					saveSlot->SetHoneycomb(l, h, value);
					saveSlot->UpdateChecksum(saveData.NeedsEndianSwap());
				}

				if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNone))
					ImGui::SetTooltip(levelHoneycombsNames[l][h]);

				if (value) totalHoneycombs++;

				ImGui::PopID();

				if (h < levelHoneycombsCount[l] - 1) ImGui::SameLine();
			}

			ImGui::TableSetColumnIndex(4);

			if (levelHasNotes[l])
			{
				uint8_t noteValue = saveSlot->GetNotes(l);
				if (ImGui::InputScalar("##Notes Score", ImGuiDataType_U8, &noteValue, NULL, NULL, "%u"))
				{
					if (noteValue > MAX_NOTES_PER_LEVEL) noteValue = MAX_NOTES_PER_LEVEL;
					saveSlot->SetNotes(l, noteValue);
					saveSlot->UpdateChecksum(saveData.NeedsEndianSwap());
				}
			}

			ImGui::TableSetColumnIndex(5);

			uint16_t time = saveSlot->GetPlayTime(l, saveData.NeedsEndianSwap());
			if (ImGui::InputScalar("##Play Time", ImGuiDataType_U16, &time, NULL, NULL, "%u"))
			{
				saveSlot->SetPlayTime(l, time, saveData.NeedsEndianSwap());
				saveSlot->UpdateChecksum(saveData.NeedsEndianSwap());
			}

			if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNone))
				ImGui::SetTooltip(Utils::GetTimeString(time).c_str());

			totalPlayTime += time;

			ImGui::PopID();
		}

		// Totals -----------------------------------------------

		ImGui::TableNextRow();

		ImGui::TableSetColumnIndex(0);
		ImGui::Text("--");

		ImGui::TableSetColumnIndex(1);
		ImGui::Text("Totals");

		ImGui::TableSetColumnIndex(2);
		ImGui::Text("%u", totalJiggies);

		ImGui::TableSetColumnIndex(3);
		ImGui::Text("%u", totalHoneycombs);

		ImGui::TableSetColumnIndex(4);
		ImGui::Text("");

		ImGui::TableSetColumnIndex(5);
		ImGui::Text("%u", totalPlayTime);

		if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNone))
			ImGui::SetTooltip(Utils::GetTimeString(totalPlayTime).c_str());

		ImGui::EndTable();
	}

	ImGui::EndTabItem();
}

void SaveEditorUI::RenderProgressFlagsSection(const SaveData& saveData, SaveSlot* saveSlot)
{
	if (!ImGui::BeginTabItem("Progress Flags")) return;

	ImGuiTableFlags tableFlags = ImGuiTableFlags_ScrollY;
	if (ImGui::BeginTable("FlagsTable", 4, tableFlags))
	{
		ImGui::TableSetupColumn("Column1", ImGuiTableColumnFlags_WidthStretch);
		ImGui::TableSetupColumn("Column2", ImGuiTableColumnFlags_WidthStretch);
		ImGui::TableSetupColumn("Column3", ImGuiTableColumnFlags_WidthStretch);
		ImGui::TableSetupColumn("Column4", ImGuiTableColumnFlags_WidthStretch);

		ImGui::TableNextRow();

		ImGui::TableSetColumnIndex(0);

		PrintHeader("Unlocked Doors");
		CheckboxProgressFlags(saveData, saveSlot, "50 Note Door", ProgressFlags::FILEPROG_3A_NOTE_DOOR_50_OPEN);
		CheckboxProgressFlags(saveData, saveSlot, "180 Note Door", ProgressFlags::FILEPROG_3B_NOTE_DOOR_180_OPEN);
		CheckboxProgressFlags(saveData, saveSlot, "260 Note Door", ProgressFlags::FILEPROG_3C_NOTE_DOOR_260_OPEN);
		CheckboxProgressFlags(saveData, saveSlot, "350 Note Door", ProgressFlags::FILEPROG_3D_NOTE_DOOR_350_OPEN);
		CheckboxProgressFlags(saveData, saveSlot, "450 Note Door", ProgressFlags::FILEPROG_3E_NOTE_DOOR_450_OPEN);
		CheckboxProgressFlags(saveData, saveSlot, "640 Note Door", ProgressFlags::FILEPROG_3F_NOTE_DOOR_640_OPEN);
		CheckboxProgressFlags(saveData, saveSlot, "765 Note Door", ProgressFlags::FILEPROG_40_NOTE_DOOR_765_OPEN);
		CheckboxProgressFlags(saveData, saveSlot, "810 Note Door", ProgressFlags::FILEPROG_41_NOTE_DOOR_810_OPEN);
		CheckboxProgressFlags(saveData, saveSlot, "828 Note Door", ProgressFlags::FILEPROG_42_NOTE_DOOR_828_OPEN);
		CheckboxProgressFlags(saveData, saveSlot, "846 Note Door", ProgressFlags::FILEPROG_43_NOTE_DOOR_846_OPEN);
		CheckboxProgressFlags(saveData, saveSlot, "864 Note Door", ProgressFlags::FILEPROG_44_NOTE_DOOR_864_OPEN);
		CheckboxProgressFlags(saveData, saveSlot, "882 Note Door", ProgressFlags::FILEPROG_45_NOTE_DOOR_882_OPEN);
		CheckboxProgressFlags(saveData, saveSlot, "Grunty's Door", ProgressFlags::FILEPROG_E2_DOOR_OF_GRUNTY_OPEN);

		PrintHeader("Broken Stuff");
		CheckboxProgressFlags(saveData, saveSlot, "Ice Ball to Cheato", ProgressFlags::FILEPROG_C3_ICE_BALL_TO_CHEATO_BROKEN);
		CheckboxProgressFlags(saveData, saveSlot, "Statue Eye", ProgressFlags::FILEPROG_C4_STATUE_EYE_BROKEN);
		CheckboxProgressFlags(saveData, saveSlot, "Rareware Box", ProgressFlags::FILEPROG_C5_RAREWARE_BOX_BROKEN);
		CheckboxProgressFlags(saveData, saveSlot, "Bricks to Wading Boots", ProgressFlags::FILEPROG_C8_LAIR_BRICKWALL_TO_WADINGBOOTS_BROKEN);
		CheckboxProgressFlags(saveData, saveSlot, "Bricks to Shock Jump Pad", ProgressFlags::FILEPROG_C9_LAIR_BRICKWALL_TO_SHOCKJUMP_PAD_BROKEN);
		CheckboxProgressFlags(saveData, saveSlot, "Cobweb Purple Cauldron", ProgressFlags::FILEPROG_CA_COBWEB_BLOCKING_PURPLE_CAULDRON_BROKEN);
		CheckboxProgressFlags(saveData, saveSlot, "Cobweb Flight Pad", ProgressFlags::FILEPROG_CB_LAIR_COBWEB_OVER_FLIGHTPAD_BROKEN);
		CheckboxProgressFlags(saveData, saveSlot, "Cobweb Green Cauldron", ProgressFlags::FILEPROG_CC_LAIR_COBWEB_OVER_GREEN_CAULDRON_BROKEN);

		ImGui::TableSetColumnIndex(1);

		PrintHeader("Unlocked Worlds");
		CheckboxProgressFlags(saveData, saveSlot, "Mumbo's Mountain", ProgressFlags::FILEPROG_31_MM_OPEN);
		CheckboxProgressFlags(saveData, saveSlot, "Treasure Trove Cove", ProgressFlags::FILEPROG_32_TTC_OPEN);
		CheckboxProgressFlags(saveData, saveSlot, "Clanker's Cavern", ProgressFlags::FILEPROG_33_CC_OPEN);
		CheckboxProgressFlags(saveData, saveSlot, "Bubblegloop Swamp", ProgressFlags::FILEPROG_34_BGS_OPEN);
		CheckboxProgressFlags(saveData, saveSlot, "Freezeezy Peak", ProgressFlags::FILEPROG_35_FP_OPEN);
		CheckboxProgressFlags(saveData, saveSlot, "Gobi's Valley", ProgressFlags::FILEPROG_36_GV_OPEN);
		CheckboxProgressFlags(saveData, saveSlot, "Mad Monster Mansion", ProgressFlags::FILEPROG_37_MMM_OPEN);
		CheckboxProgressFlags(saveData, saveSlot, "Rusty Bucket Bay", ProgressFlags::FILEPROG_38_RBB_OPEN);
		CheckboxProgressFlags(saveData, saveSlot, "Click Clock Wood", ProgressFlags::FILEPROG_39_CCW_OPEN);

		PrintHeader("Texts Read");
		CheckboxProgressFlags(saveData, saveSlot, "Music Note", ProgressFlags::FILEPROG_3_MUSIC_NOTE_TEXT);
		CheckboxProgressFlags(saveData, saveSlot, "Mumbo Token", ProgressFlags::FILEPROG_4_MUMBO_TOKEN_TEXT);
		CheckboxProgressFlags(saveData, saveSlot, "Blue Egg", ProgressFlags::FILEPROG_5_BLUE_EGG_TEXT);
		CheckboxProgressFlags(saveData, saveSlot, "Red Feather", ProgressFlags::FILEPROG_6_RED_FEATHER_TEXT);
		CheckboxProgressFlags(saveData, saveSlot, "Gold Feather", ProgressFlags::FILEPROG_7_GOLD_FEATHER_TEXT);
		CheckboxProgressFlags(saveData, saveSlot, "Honeycomb", ProgressFlags::FILEPROG_A_HONEYCOMB_TEXT);
		CheckboxProgressFlags(saveData, saveSlot, "Empty Honeycomb", ProgressFlags::FILEPROG_B_EMPTY_HONEYCOMB_TEXT);
		CheckboxProgressFlags(saveData, saveSlot, "Extra Life", ProgressFlags::FILEPROG_C_EXTRA_LIFE_TEXT);
		CheckboxProgressFlags(saveData, saveSlot, "Jinjo", ProgressFlags::FILEPROG_E_JINJO_TEXT);
		CheckboxProgressFlags(saveData, saveSlot, "Beehive", ProgressFlags::FILEPROG_D_BEEHIVE_TEXT);
		CheckboxProgressFlags(saveData, saveSlot, "Orange", ProgressFlags::FILEPROG_8_ORANGE_TEXT);
		CheckboxProgressFlags(saveData, saveSlot, "Gold Bullion", ProgressFlags::FILEPROG_9_GOLD_BULLION_TEXT);
		CheckboxProgressFlags(saveData, saveSlot, "Enter MMM", ProgressFlags::FILEPROG_15_ENTER_MMM_TEXT);
		CheckboxProgressFlags(saveData, saveSlot, "Magic Weak", ProgressFlags::FILEPROG_83_MAGIC_GET_WEAK_TEXT);
		CheckboxProgressFlags(saveData, saveSlot, "Magic Gone", ProgressFlags::FILEPROG_84_MAGIC_ALL_GONE_TEXT);
		CheckboxProgressFlags(saveData, saveSlot, "Entered Lair", ProgressFlags::FILEPROG_97_ENTERED_LAIR_TEXT);
		CheckboxProgressFlags(saveData, saveSlot, "Exited Level", ProgressFlags::FILEPROG_98_EXITED_LEVEL_TEXT);
		CheckboxProgressFlags(saveData, saveSlot, "Past 50 Note Door", ProgressFlags::FILEPROG_99_PAST_50_NOTE_DOOR_TEXT);
		CheckboxProgressFlags(saveData, saveSlot, "Near Puzzle Podium", ProgressFlags::FILEPROG_A7_NEAR_PUZZLE_PODIUM_TEXT);
		CheckboxProgressFlags(saveData, saveSlot, "Has Seen Trex", ProgressFlags::FILEPROG_BA_HAS_SEEN_TREX_TEXT);
		CheckboxProgressFlags(saveData, saveSlot, "Baddies Escaped", ProgressFlags::FILEPROG_C1_BADDIES_ESCAPE_TEXT);

		ImGui::TableSetColumnIndex(2);

		PrintHeader("Stats");
		CheckboxProgressFlags(saveData, saveSlot, "Double Health", ProgressFlags::FILEPROG_B9_DOUBLE_HEALTH);
		CheckboxProgressFlags(saveData, saveSlot, "Cheato Blue Eggs", ProgressFlags::FILEPROG_BE_CHEATO_BLUEEGGS);
		CheckboxProgressFlags(saveData, saveSlot, "Cheato Red Feathers", ProgressFlags::FILEPROG_BF_CHEATO_REDFEATHERS);
		CheckboxProgressFlags(saveData, saveSlot, "Cheato Gold Feathers", ProgressFlags::FILEPROG_C0_CHEATO_GOLDFEATHERS);

		PrintHeader("Pressed Witch Switches");
		CheckboxProgressFlags(saveData, saveSlot, "Lair Jump Pad", ProgressFlags::FILEPROG_C6_LAIR_JUMP_PAD_SWITCH_PRESSED);
		CheckboxProgressFlags(saveData, saveSlot, "MM Jiggy", ProgressFlags::FILEPROG_18_MM_WITCH_SWITCH_JIGGY_PRESSED);
		CheckboxProgressFlags(saveData, saveSlot, "TTC Jiggy", ProgressFlags::FILEPROG_1A_TTC_WITCH_SWITCH_JIGGY_PRESSED);
		CheckboxProgressFlags(saveData, saveSlot, "CC", ProgressFlags::FILEPROG_9A_CC_WITCH_SWITCH_PRESSED);
		CheckboxProgressFlags(saveData, saveSlot, "CC Eyes Active", ProgressFlags::FILEPROG_9B_LAIR_CC_WITCH_SWITCH_EYES_ACTIVE);
		CheckboxProgressFlags(saveData, saveSlot, "CC Left Eye", ProgressFlags::FILEPROG_9C_LAIR_CC_WITCH_SWITCH_LEFT_EYE_PRESSED);
		CheckboxProgressFlags(saveData, saveSlot, "CC Right Eye", ProgressFlags::FILEPROG_9D_LAIR_CC_WITCH_SWITCH_RIGHT_EYE_PRESSED);
		CheckboxProgressFlags(saveData, saveSlot, "BGS Jiggy", ProgressFlags::FILEPROG_9F_BGS_WITCH_SWITCH_JIGGY_PRESSED);
		CheckboxProgressFlags(saveData, saveSlot, "FP Jiggy", ProgressFlags::FILEPROG_47_FP_WITCH_SWITCH_JIGGY_PRESSED);
		CheckboxProgressFlags(saveData, saveSlot, "FP Advent Door Open", ProgressFlags::FILEPROG_48_FP_WITCH_SWITCH_ADVENT_DOOR_OPEN);
		CheckboxProgressFlags(saveData, saveSlot, "GV Jiggy", ProgressFlags::FILEPROG_A0_GV_WITCH_SWITCH_JIGGY_PRESSED);
		CheckboxProgressFlags(saveData, saveSlot, "GV Stop 'N' Swop", ProgressFlags::FILEPROG_A3_GV_SNS_SWITCH_PRESSED);
		CheckboxProgressFlags(saveData, saveSlot, "MMM Jiggy", ProgressFlags::FILEPROG_19_MMM_WITCH_SWITCH_JIGGY_PRESSED);
		CheckboxProgressFlags(saveData, saveSlot, "RBB Jiggy", ProgressFlags::FILEPROG_1C_RBB_WITCH_SWITCH_JIGGY_PRESSED);
		CheckboxProgressFlags(saveData, saveSlot, "CCW Jiggy", ProgressFlags::FILEPROG_46_CCW_WITCH_SWITCH_JIGGY_PRESSED);
		CheckboxProgressFlags(saveData, saveSlot, "CCW Puzzle Podium", ProgressFlags::FILEPROG_53_CCW_PUZZLE_PODIUM_SWITCH_PRESSED);

		PrintHeader("Pressed Misc Switches");
		CheckboxProgressFlags(saveData, saveSlot, "Grate to Water Switch 3", ProgressFlags::FILEPROG_CD_GRATE_TO_WATER_SWITCH_3_OPEN);
		CheckboxProgressFlags(saveData, saveSlot, "Water Switch 1", ProgressFlags::FILEPROG_22_WATER_SWITCH_1_PRESSED);
		CheckboxProgressFlags(saveData, saveSlot, "Water Switch 2", ProgressFlags::FILEPROG_24_WATER_SWITCH_2_PRESSED);
		CheckboxProgressFlags(saveData, saveSlot, "Water Switch 3", ProgressFlags::FILEPROG_26_WATER_SWITCH_3_PRESSED);

		ImGui::TableSetColumnIndex(3);

		PrintHeader("Brentilda");
		CheckboxProgressFlags(saveData, saveSlot, "Talked to Brentilda 1", ProgressFlags::FILEPROG_E9_TALKED_TO_BRENTILDA_1);
		CheckboxProgressFlags(saveData, saveSlot, "Talked to Brentilda 2", ProgressFlags::FILEPROG_EA_TALKED_TO_BRENTILDA_2);
		CheckboxProgressFlags(saveData, saveSlot, "Talked to Brentilda 3", ProgressFlags::FILEPROG_EB_TALKED_TO_BRENTILDA_3);
		CheckboxProgressFlags(saveData, saveSlot, "Talked to Brentilda 4", ProgressFlags::FILEPROG_EC_TALKED_TO_BRENTILDA_4);
		CheckboxProgressFlags(saveData, saveSlot, "Talked to Brentilda 5", ProgressFlags::FILEPROG_ED_TALKED_TO_BRENTILDA_5);
		CheckboxProgressFlags(saveData, saveSlot, "Talked to Brentilda 6", ProgressFlags::FILEPROG_EE_TALKED_TO_BRENTILDA_6);
		CheckboxProgressFlags(saveData, saveSlot, "Talked to Brentilda 7", ProgressFlags::FILEPROG_EF_TALKED_TO_BRENTILDA_7);
		CheckboxProgressFlags(saveData, saveSlot, "Talked to Brentilda 8", ProgressFlags::FILEPROG_F0_TALKED_TO_BRENTILDA_8);
		CheckboxProgressFlags(saveData, saveSlot, "Talked to Brentilda 9", ProgressFlags::FILEPROG_F1_TALKED_TO_BRENTILDA_9);
		CheckboxProgressFlags(saveData, saveSlot, "Talked to Brentilda 10", ProgressFlags::FILEPROG_F2_TALKED_TO_BRENTILDA_10);

		ImGui::EndTable();
	}

	ImGui::EndTabItem();
}
