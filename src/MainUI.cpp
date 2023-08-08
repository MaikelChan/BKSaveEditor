﻿#include "main.h"
#include "MainUI.h"
#include "SaveEditorUI.h"
#include "PopupDialog.h"
#include "AboutWindow.h"
#include <fstream>
#define JSON_USE_IMPLICIT_CONVERSIONS 0
#include <nlohmann/json.hpp>
using json = nlohmann::json;

MainUI::MainUI() : BaseUI(nullptr)
{
	saveEditor = new SaveEditorUI(this);
	aboutWindow = new AboutWindow(this);
	popupDialog = new PopupDialog(this);

	currentFilePath.clear();
	currentFileName.clear();

	windowOpacity = 0.9f;

	fileDialog.SetTitle("Open a Banjo-Kazooie save file");
	fileDialog.SetTypeFilters({ ".eep", ".*" });

	LoadConfig();
}

MainUI::~MainUI()
{
	SaveConfig();

	delete saveEditor;
	saveEditor = nullptr;

	delete popupDialog;
	popupDialog = nullptr;

	delete aboutWindow;
	aboutWindow = nullptr;
}

void MainUI::VisibilityChanged(const bool isVisible)
{
	BaseUI::VisibilityChanged(isVisible);
}

void MainUI::DoRender()
{
	BaseUI::DoRender();

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open..."))
			{
				fileDialog.Open();
			}

			if (ImGui::MenuItem("Save"))
			{
				Save();
			}

			ImGui::Separator();

			if (ImGui::MenuItem("Quit"))
			{
				CloseMainWindow();
			}

			ImGui::EndMenu();
		}

		//if (saveData && ImGui::BeginMenu("Tools"))
		//{
		//	for (int s = 0; s < NUM_SAVE_SLOTS; s++)
		//	{
		//		if (ImGui::BeginMenu(tabNames[s]))
		//		{
		//			if (ImGui::MenuItem("100% Complete"))
		//			{
		//				CompleteSlot(s);
		//			}

		//			if (ImGui::MenuItem("Delete"))
		//			{
		//				DeleteSlot(s);
		//			}

		//			ImGui::EndMenu();
		//		}
		//	}

		//	ImGui::Separator();

		//	//if (ImGui::MenuItem("Show backup data", NULL, saveEditor->showBackup))
		//	//{
		//	//	saveEditor->showBackup = !saveEditor->showBackup;
		//	//}

		//	ImGui::EndMenu();
		//}

		if (ImGui::BeginMenu("Settings"))
		{
			ImGui::SliderFloat("Window Opacity", &windowOpacity, 0.0f, 1.0f);

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("About...", NULL, aboutWindow->GetIsVisible()))
			{
				aboutWindow->ToggleIsVisible();
			}

			ImGui::EndMenu();
		}

		if (saveData.IsSaveFileLoaded())
		{
			std::string fileText = std::string("Current file: ") + currentFileName;

			ImGui::SetCursorPosX(ImGui::GetWindowWidth() - ImGui::CalcTextSize(fileText.c_str()).x - 32);
			ImGui::Text("%s", fileText.c_str());
		}

		ImGui::EndMainMenuBar();
	}

	//ImGui::ShowDemoWindow();

	saveEditor->Render();
	popupDialog->Render();
	aboutWindow->Render();

	fileDialog.Display();

	if (fileDialog.HasSelected())
	{
		Load();
		SaveConfig();

		fileDialog.ClearSelected();
	}
}

void MainUI::LoadConfig()
{
	try
	{
		std::ifstream stream(CONFIG_FILE_NAME);

		if (!stream || !stream.is_open())
		{
			return;
		}

		json config;
		stream >> config;
		stream.close();

		if (config["lastPath"].is_string()) fileDialog.SetPwd(std::filesystem::u8path(config["lastPath"].template get<std::string>()));
		if (config["windowOpacity"].is_number_float()) windowOpacity = config["windowOpacity"].template get<float>();
	}
	catch (const json::parse_error& error)
	{
		printf("Json Error: %s\n", error.what());
	}
}

void MainUI::SaveConfig() const
{
	try
	{
		json config;
		config["lastPath"] = fileDialog.GetPwd().u8string();
		config["windowOpacity"] = windowOpacity;

		// The setw manipulator was overloaded to set the indentation for pretty printing.

		std::ofstream stream(CONFIG_FILE_NAME);
		stream << std::setw(4) << config << std::endl;
		stream.close();
	}
	catch (const json::type_error& error)
	{
		printf("Json Error: %s\n", error.what());
	}
}

void MainUI::Load()
{
	try
	{
		saveData.Load(fileDialog.GetSelected().string());

		currentFilePath = fileDialog.GetSelected().string();
		currentFileName = fileDialog.GetSelected().filename().string();

		LoadingProcess();

		saveEditor->SetIsVisible(true);
	}
	catch (const std::runtime_error& error)
	{
		popupDialog->SetMessage(MessageTypes::Error, "Error", error.what());
		popupDialog->SetIsVisible(true);
	}
}

void MainUI::LoadingProcess() const
{
	if (!saveData.IsSaveFileLoaded()) return;

	std::string message;

	for (int s = 0; s < ACTUAL_NUM_SAVE_SLOTS; s++)
	{
		SaveSlot* saveSlot = saveData.GetSaveFile()->GetSaveSlot(s);
		if (!saveSlot) continue;

		if (!saveSlot->IsValid(saveData.NeedsEndianSwap()))
		{
			saveSlot->UpdateChecksum(saveData.NeedsEndianSwap());
			message += std::string("Save ") + tabNames[s] + " is corrupted. Data might be completely wrong.\n\n";
		}
	}

	if (!saveData.GetSaveFile()->globalData.IsValid(saveData.NeedsEndianSwap()))
	{
		saveData.GetSaveFile()->globalData.UpdateChecksum(saveData.NeedsEndianSwap());
		message += "Global data is corrupted. Data might be completely wrong.\n\n";
	}

	if (!message.empty())
	{
		popupDialog->SetMessage(MessageTypes::Warning, "Load warnings", message);
		popupDialog->SetIsVisible(true);
	}
}

void MainUI::Save()
{
	if (!saveData.IsSaveFileLoaded()) return;

	SavingProcess();

	try
	{
		saveData.Save(currentFilePath);
	}
	catch (const std::runtime_error& error)
	{
		popupDialog->SetMessage(MessageTypes::Error, "Error", error.what());
		popupDialog->SetIsVisible(true);
	}
}

void MainUI::SavingProcess() const
{
	if (!saveData.IsSaveFileLoaded()) return;

	//for (int s = 0; s < NUM_SAVE_SLOTS; s++)
	//{
	//	saveData->saveSlots[s][0].Magic = SAVE_SLOT_MAGIC_LE;
	//	memcpy(&saveData->saveSlots[s][1], &saveData->saveSlots[s][0], SAVE_SLOT_SIZE);
	//}

	//saveData->settings[0].Magic = SETTINGS_DATA_MAGIC_LE;
	//memcpy(&saveData->settings[1], &saveData->settings[0], SETTINGS_DATA_SIZE);
}

void MainUI::CompleteSlot(const uint8_t slotIndex) const
{
	if (!saveData.IsSaveFileLoaded()) return;

	/*memset(&saveData->saveSlots[slotIndex][0], 0, SAVE_SLOT_SIZE);

	saveData->saveSlots[slotIndex][0].Flags = 0x1f10ffcf;

	for (int c = 0; c < COURSE_COUNT; c++)
	{
		for (int st = 0; st < courseStarCount[c]; st++)
		{
			saveData->saveSlots[slotIndex][0].CourseData[c] |= (1 << st);
		}

		if (courseHasCannon[c])
		{
			saveData->saveSlots[slotIndex][0].CourseData[c + 1] |= SAVE_COURSE_FLAG_STAR_CANNON_OPEN;
		}
	}

	for (int c = 0; c < COURSE_STAGES_COUNT; c++)
	{
		saveData->saveSlots[slotIndex][0].CourseCoinScores[c] = 100;
	}

	saveData->saveSlots[slotIndex][0].Magic = SAVE_SLOT_MAGIC_LE;
	saveData->saveSlots[slotIndex][0].UpdateChecksum();*/
}

void MainUI::DeleteSlot(const uint8_t slotIndex) const
{
	if (!saveData.IsSaveFileLoaded()) return;

	//memset(&saveData->saveSlots[slotIndex][0], 0, SAVE_SLOT_SIZE);
	//saveData->saveSlots[slotIndex][0].Magic = SAVE_SLOT_MAGIC_LE;
	//saveData->saveSlots[slotIndex][0].UpdateChecksum();
}
