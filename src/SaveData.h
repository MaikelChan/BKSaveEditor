#pragma once

#include <string>
#include "SaveFile.h"

class SaveData
{
private:
	SaveFile* saveFile;
	SaveFile::Types currentFileType;

public:
	SaveData();
	~SaveData();

	void Load(const std::string filePath);
	void Save(const std::string filePath);

	inline bool IsSaveFileLoaded() const { return saveFile != nullptr; }
	inline SaveFile* GetSaveFile() const { return saveFile; }

private:
	void ClearSaveFile();
	void EndianSwap() const;
};
