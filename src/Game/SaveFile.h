#pragma once

#include <fstream>

class SaveData;
class RecompSaveData;

enum class SaveFileTypes { NotValid, BigEndian, LittleEndian };

class SaveFile
{
private:
	SaveData* saveData;
	RecompSaveData* recompSaveData;

	SaveFileTypes fileType;

public:
	SaveFile();
	~SaveFile();

	std::string Read(std::ifstream& stream, const size_t streamSize);
	void Write(std::ofstream& stream);

	inline SaveData* GetSaveData() const { return saveData; }
	inline RecompSaveData* GetRecompSaveData() const { return recompSaveData; }

	inline SaveFileTypes GetFileType() const { return fileType; }

private:
	static SaveFileTypes CalculateType(SaveData* saveData);
};
