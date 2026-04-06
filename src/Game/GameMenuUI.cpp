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
	if (!mainUi->IsSaveFileLoaded()) return;

	SaveData* saveData = mainUi->GetSaveFile()->GetSaveData();

	int8_t originSlotActualIndex = mainUi->GetSaveFile()->GetSaveData()->GetSaveSlotActualIndex(originSlotIndex);
	SaveSlot* origin = originSlotActualIndex >= 0 ? saveData->GetRawSaveSlot(originSlotActualIndex) : nullptr;

	if (origin == nullptr)
	{
		DeleteSlot(destinationSlotIndex);
		return;
	}

	int8_t destinationSlotActualIndex = mainUi->GetSaveFile()->GetSaveData()->GetSaveSlotActualIndex(destinationSlotIndex);
	SaveSlot* destination = destinationSlotActualIndex >= 0 ? saveData->GetRawSaveSlot(destinationSlotActualIndex) : nullptr;

	if (destination != nullptr)
	{
		std::copy(origin, origin + 1, destination);
		destination->SetSlotIndex(destinationSlotIndex + 1);
		destination->UpdateChecksum(mainUi->GetSaveFile()->GetFileType());
	}
	else
	{
		for (uint8_t s = 0; s < TOTAL_NUM_SAVE_SLOTS; s++)
		{
			destination = saveData->GetRawSaveSlot(s);
			if (destination->GetMagic() == SAVE_SLOT_MAGIC) continue;

			destinationSlotActualIndex = s;

			std::copy(origin, origin + 1, destination);
			destination->SetSlotIndex(destinationSlotIndex + 1);
			destination->UpdateChecksum(mainUi->GetSaveFile()->GetFileType());

			break;
		}
	}

	if (mainUi->GetSaveFile()->GetRecompSaveData() != nullptr)
	{
		RecompSaveSlot* recompSlot = mainUi->GetSaveFile()->GetRecompSaveData()->GetRawSaveSlot(originSlotActualIndex);
		RecompSaveSlot* destinationRecompSlot = mainUi->GetSaveFile()->GetRecompSaveData()->GetRawSaveSlot(destinationSlotActualIndex);

		std::copy(recompSlot, recompSlot + 1, destinationRecompSlot);
	}
}

void GameMenuUI::DeleteSlot(const uint8_t slotIndex) const
{
	if (!mainUi->IsSaveFileLoaded()) return;

	SaveData* saveData = mainUi->GetSaveFile()->GetSaveData();
	int8_t slotActualIndex = mainUi->GetSaveFile()->GetSaveData()->GetSaveSlotActualIndex(slotIndex);

	SaveSlot* saveSlot = slotActualIndex >= 0 ? saveData->GetRawSaveSlot(slotActualIndex) : nullptr;
	if (saveSlot == nullptr) return;

	memset(saveSlot, 0, SAVE_SLOT_SIZE);
	saveSlot->UpdateChecksum(mainUi->GetSaveFile()->GetFileType());

	if (mainUi->GetSaveFile()->GetRecompSaveData() != nullptr)
	{
		RecompSaveSlot* recompSaveSlot = mainUi->GetSaveFile()->GetRecompSaveData()->GetRawSaveSlot(slotActualIndex);
		memset(recompSaveSlot, 0, RECOMP_SAVE_SLOT_SIZE);
	}
}
