#pragma once

#include <string>
#include "SaveFile.h"

class SaveData
{
public:
	enum class Types { NotValid, BigEndian, LittleEndian };
	struct InitializationResult
	{
		Types type;
		std::string message;
	};

private:
	SaveSlot saveSlots[TOTAL_NUM_SAVE_SLOTS] = {};
	GlobalData globalData = {};

public:
	SaveData();

	InitializationResult CheckAndInitialize();
	void BeginSaving(const Types type);
	void FinishSaving(const Types type);

	//inline Types GetType() const { return type; }
	inline bool NeedsEndianSwap() const { return false; } // TODO

private:
	void EndianSwap();
	Types CalculateType() const;

public:
	// Banjo specific stuff
	SaveSlot* GetRawSaveSlot(const uint8_t slotIndex);
	SaveSlot* GetSaveSlot(const uint8_t slotIndex);
	GlobalData* GetGlobalData();

	static uint32_t TransformSeed(uint64_t* seed);
	static uint32_t CalculateChecksum(uint8_t* start, uint8_t* end);
};
