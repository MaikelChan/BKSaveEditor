﻿#include "main.h"
#include "MainUI.h"
#include "SaveEditorUI.h"
#include "PopupDialog.h"
#include "AboutWindow.h"
#include <fstream>
#include <SimpleIni.h>

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

			if (ImGui::MenuItem("Save", NULL, false, saveData.IsSaveFileLoaded()))
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

		if (saveData.IsSaveFileLoaded() && ImGui::BeginMenu("Tools"))
		{
			for (uint8_t s = 0; s < ACTUAL_NUM_SAVE_SLOTS; s++)
			{
				if (ImGui::BeginMenu(tabNames[s]))
				{
					if (ImGui::BeginMenu("Copy"))
					{
						for (uint8_t ds = 0; ds < ACTUAL_NUM_SAVE_SLOTS; ds++)
						{
							if (s == ds) continue;

							char menuName[27];
							snprintf(menuName, 27, "To %s", tabNames[ds]);

							if (ImGui::MenuItem(menuName))
							{
								CopySlot(s, ds);
							}
						}

						ImGui::EndMenu();
					}

					if (ImGui::MenuItem("Delete"))
					{
						DeleteSlot(s);
					}

					ImGui::EndMenu();
				}
			}

			ImGui::EndMenu();
		}

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
	CSimpleIniA ini;
	ini.SetUnicode();

	SI_Error errorCode = ini.LoadFile(CONFIG_FILE_NAME);
	if (errorCode < 0)
	{
		printf("Error converting INI config data to string format. Error code: %i.\n", errorCode);
		return;
	};

	fileDialog.SetDirectory(std::filesystem::u8path(ini.GetValue(CONFIG_INI_SECTION, "lastPath", fileDialog.GetDirectory().u8string().c_str())));
	windowOpacity = (float)ini.GetDoubleValue(CONFIG_INI_SECTION, "windowOpacity", windowOpacity);
}

void MainUI::SaveConfig() const
{
	CSimpleIniA ini;
	ini.SetUnicode();

	SI_Error errorCode;

	errorCode = ini.SetValue(CONFIG_INI_SECTION, "lastPath", fileDialog.GetDirectory().u8string().c_str());
	errorCode = ini.SetDoubleValue(CONFIG_INI_SECTION, "windowOpacity", windowOpacity);

	std::string data;
	errorCode = ini.Save(data);

	if (errorCode < 0)
	{
		printf("Error getting INI data in string format. Error code: %i.\n", errorCode);
		return;
	};

	errorCode = ini.SaveFile(CONFIG_FILE_NAME);
	if (errorCode < 0)
	{
		printf("Error saving INI file to %s. Error code: %i.\n", CONFIG_FILE_NAME, errorCode);
	};
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

	for (uint8_t s = 0; s < ACTUAL_NUM_SAVE_SLOTS; s++)
	{
		SaveSlot* saveSlot = saveData.GetSaveFile()->GetSaveSlot(s);
		if (!saveSlot) continue;

		if (!saveSlot->IsValid(saveData.NeedsEndianSwap()))
		{
			saveSlot->UpdateChecksum(saveData.NeedsEndianSwap());
			message += std::string("Save ") + tabNames[s] + " is corrupted. Data might be completely wrong.\n\n";
		}
	}

	if (!saveData.GetSaveFile()->GetGlobalData()->IsValid(saveData.NeedsEndianSwap()))
	{
		saveData.GetSaveFile()->GetGlobalData()->UpdateChecksum(saveData.NeedsEndianSwap());
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

void MainUI::CopySlot(const uint8_t originSlotIndex, const uint8_t destinationSlotIndex) const
{
	if (!saveData.IsSaveFileLoaded()) return;
	if (originSlotIndex == destinationSlotIndex) return;

	SaveSlot* origin = saveData.GetSaveFile()->GetSaveSlot(originSlotIndex);

	if (origin == nullptr)
	{
		DeleteSlot(destinationSlotIndex);
		return;
	}

	SaveSlot* destination = saveData.GetSaveFile()->GetSaveSlot(destinationSlotIndex);

	if (destination != nullptr)
	{
		memcpy(destination, origin, SAVE_SLOT_SIZE);
		destination->SetSlotIndex(destinationSlotIndex + 1);
		destination->UpdateChecksum(saveData.NeedsEndianSwap());
	}
	else
	{
		for (uint8_t s = 0; s < TOTAL_NUM_SAVE_SLOTS; s++)
		{
			destination = saveData.GetSaveFile()->GetRawSaveSlot(s);
			if (destination->GetMagic() == SAVE_SLOT_MAGIC) continue;

			memcpy(destination, origin, SAVE_SLOT_SIZE);
			destination->SetSlotIndex(destinationSlotIndex + 1);
			destination->UpdateChecksum(saveData.NeedsEndianSwap());

			break;
		}
	}
}

void MainUI::DeleteSlot(const uint8_t slotIndex) const
{
	if (!saveData.IsSaveFileLoaded()) return;

	SaveSlot* saveSlot = saveData.GetSaveFile()->GetSaveSlot(slotIndex);
	if (saveSlot == nullptr) return;

	memset(saveSlot, 0, SAVE_SLOT_SIZE);
	saveSlot->UpdateChecksum(saveData.NeedsEndianSwap());
}
