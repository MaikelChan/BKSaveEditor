#pragma once

#include <cstdint>
#include "BaseUI.h"
#include "SaveData.h"
class MainUI;

#define CONFIG_FILE_NAME "config.json"

const char* const tabNames[]
{
	"Slot 1 (Banjo Sleeping)",
	"Slot 2 (Banjo Cooking)",
	"Slot 3 (Banjo Playing)"
};

class SaveEditorUI : public BaseUI
{
private:
	const MainUI* mainUI;

public:
	SaveEditorUI(const MainUI* mainUI);
	~SaveEditorUI();

protected:
	virtual void VisibilityChanged(const bool isVisible) override;
	virtual void DoRender() override;

private:
	bool CheckboxProgressFlags(const SaveData& saveData, SaveSlot* saveSlot, const char* label, const ProgressFlags flag) const;
	uint8_t InputProgressFlags(const SaveData& saveData, SaveSlot* saveSlot, const char* label, const ProgressFlags flag, const uint8_t bitsCount, const uint8_t maxValue) const;
	void PrintChecksum(const uint32_t checksum) const;
	void PrintHeader(const char* label) const;
	void RenderMainSection(const SaveData& saveData, SaveSlot* saveSlot);
	void RenderProgressFlagsSection(const SaveData& saveData, SaveSlot* saveSlot);
};
