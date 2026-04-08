#pragma once

#include <cstdint>

#include "../BaseUI.h"
#include "SaveData.h"

class MainUI;

const char* const tabNames[]
{
	"Game 1 (Banjo Sleeping)",
	"Game 2 (Banjo Cooking)",
	"Game 3 (Banjo Playing)"
};

class SaveEditorUI : public BaseUI
{
private:
	MainUI* mainUi;

public:
	SaveEditorUI(Window* window, BaseUI* parentUi);
	~SaveEditorUI();

protected:
	void VisibilityChanged(const bool _isVisible) override;
	void DoRender() override;

private:
	void RenderLevelDataSection(SaveSlot* saveSlot);
	void RenderAbilitiesItemsSection(SaveSlot* saveSlot);
	void RenderProgressFlagsSection(SaveSlot* saveSlot);
	void RenderGlobalDataSection(GlobalData* globalData);
	void RenderRecompDataSection(SaveSlot* saveSlot, RecompSaveSlot* recompSaveSlot);

	bool CheckboxProgressFlags(SaveSlot* saveSlot, const char* label, const ProgressFlags flag) const;
	uint8_t InputProgressFlags(SaveSlot* saveSlot, const char* label, const ProgressFlags flag, const uint8_t bitsCount, const uint8_t maxValue) const;
	void CheckboxLearnedAbility(SaveSlot* saveSlot, const char* label, const LearnableAbilities ability) const;
	void CheckboxUsedAbility(SaveSlot* saveSlot, const char* label, const UsableAbilities ability) const;
	void CheckboxSnS(GlobalData* globalData, const char* label, const SnS unlockedSnsItem, const SnS collectedSnsItem) const;
	void PrintChecksum(const uint32_t checksum) const;
	void PrintHeader(const char* label) const;
	void BeginProgressFlagsGroup(const char* label) const;
	void EndProgressFlagsGroup() const;

	uint8_t GetTotalJiggies(SaveSlot* saveSlot) const;
};
