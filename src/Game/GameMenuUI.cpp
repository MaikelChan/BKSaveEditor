#include "GameMenuUI.h"

#include <imgui/imgui.h>

#include "../MainUI.h"

GameMenuUI::GameMenuUI(Window* window, BaseUI* parentUi, SaveEditorUI* saveEditorUi) : BaseUI(window, parentUi)
{
	this->mainUi = (MainUI*)parentUi;
	this->saveEditorUi = saveEditorUi;
}

GameMenuUI::~GameMenuUI()
{
}

void GameMenuUI::VisibilityChanged(const bool _isVisible)
{
}

void GameMenuUI::DoRender()
{
	if (ImGui::BeginMenu("Tools"))
	{
		for (uint8_t s = 0; s < TOTAL_SAVE_SLOTS; s++)
		{
			if (ImGui::BeginMenu(tabNames[s]))
			{
				if (ImGui::BeginMenu("Copy"))
				{
					for (uint8_t ds = 0; ds < TOTAL_SAVE_SLOTS; ds++)
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
	if (!mainUi->IsSaveFileLoaded()) return;

	SaveData* saveData = mainUi->GetSaveFile()->GetSaveData();
	SaveSlot* origin = saveData->GetSaveSlot(originSlotIndex);

	if (origin == nullptr)
	{
		DeleteSlot(destinationSlotIndex);
		return;
	}

	SaveSlot* destination = saveData->GetSaveSlot(destinationSlotIndex);
	if (destination == nullptr) destination = saveData->FindEmptyInternalSaveSlot();

	std::copy(origin, origin + 1, destination);
	destination->SetSlotIndex(destinationSlotIndex + 1);
	destination->UpdateChecksum(mainUi->GetSaveFile()->GetFileType());

	RecompSaveData* recompSaveData = mainUi->GetSaveFile()->GetRecompSaveData();

	if (recompSaveData != nullptr)
	{
		RecompSaveSlot* originRecompSlot = recompSaveData->GetSaveSlot(saveData, originSlotIndex);
		RecompSaveSlot* destinationRecompSlot = recompSaveData->GetSaveSlot(saveData, destinationSlotIndex);

		std::copy(originRecompSlot, originRecompSlot + 1, destinationRecompSlot);
	}
}

void GameMenuUI::DeleteSlot(const uint8_t slotIndex) const
{
	if (!mainUi->IsSaveFileLoaded()) return;

	SaveData* saveData = mainUi->GetSaveFile()->GetSaveData();
	RecompSaveData* recompSaveData = mainUi->GetSaveFile()->GetRecompSaveData();

	SaveSlot* saveSlot = saveData->GetSaveSlot(slotIndex);
	if (saveSlot == nullptr) return;

	if (recompSaveData != nullptr)
	{
		// We need to delete recomp data first, before deleting main save data,
		// as accessing the correct recomp save slot depends on main save slot.

		RecompSaveSlot* recompSaveSlot = recompSaveData->GetSaveSlot(saveData, slotIndex);
		memset(recompSaveSlot, 0, RECOMP_SAVE_SLOT_SIZE);
	}

	memset(saveSlot, 0, SAVE_SLOT_SIZE);
	saveSlot->UpdateChecksum(mainUi->GetSaveFile()->GetFileType());
}
