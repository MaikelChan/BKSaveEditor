#include "GameMenuUI.h"

#include <imgui/imgui.h>

#include "../MainUI.h"
#include "SaveData.h"
#include "SaveEditorUI.h"

GameMenuUI::GameMenuUI(Window* window, BaseUI* parentUi, SaveEditorUI* saveEditorUi) : BaseUI(window, parentUi)
{
	this->mainUi = (MainUI*)parentUi;
	this->saveEditorUi = saveEditorUi;
}

GameMenuUI::~GameMenuUI()
{
}

void GameMenuUI::VisibilityChanged(const bool isVisible)
{
}

void GameMenuUI::DoRender()
{
	if (ImGui::BeginMenu("Tools"))
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
}

void GameMenuUI::CopySlot(const uint8_t originSlotIndex, const uint8_t destinationSlotIndex) const
{
	if (originSlotIndex == destinationSlotIndex) return;
	if (!mainUi->IsSaveDataLoaded()) return;

	SaveData* saveData = mainUi->GetSaveData();

	SaveSlot* origin = saveData->GetSaveSlot(originSlotIndex);

	if (origin == nullptr)
	{
		DeleteSlot(destinationSlotIndex);
		return;
	}

	SaveSlot* destination = saveData->GetSaveSlot(destinationSlotIndex);

	if (destination != nullptr)
	{
		memcpy(destination, origin, SAVE_SLOT_SIZE); // TODO: Don't use memcpy
		destination->SetSlotIndex(destinationSlotIndex + 1);
		destination->UpdateChecksum(mainUi->GetSaveDataType());
	}
	else
	{
		for (uint8_t s = 0; s < TOTAL_NUM_SAVE_SLOTS; s++)
		{
			destination = saveData->GetRawSaveSlot(s);
			if (destination->GetMagic() == SAVE_SLOT_MAGIC) continue;

			memcpy(destination, origin, SAVE_SLOT_SIZE);
			destination->SetSlotIndex(destinationSlotIndex + 1);
			destination->UpdateChecksum(mainUi->GetSaveDataType());

			break;
		}
	}
}

void GameMenuUI::DeleteSlot(const uint8_t slotIndex) const
{
	if (!mainUi->IsSaveDataLoaded()) return;

	SaveData* saveData = mainUi->GetSaveData();

	SaveSlot* saveSlot = saveData->GetSaveSlot(slotIndex);
	if (saveSlot == nullptr) return;

	memset(saveSlot, 0, SAVE_SLOT_SIZE);
	saveSlot->UpdateChecksum(mainUi->GetSaveDataType());
}
