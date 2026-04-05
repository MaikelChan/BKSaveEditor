#pragma once

#include <cstdint>
#include <filesystem>
#include <functional>
#include <string>

struct ImVec4;
struct ImFontAtlas;

class BaseUI;

struct FileDialogParams;
typedef void (*FileDialogCallback)(const FileDialogParams* fileDialogParams, const std::filesystem::path filePath, const char* error);

struct FileDialogFilter
{
	const char* name;
	const char* pattern;
};

struct FileDialogParams
{
	BaseUI* ui;
	std::filesystem::path defaultLocation;
	FileDialogCallback callback;
};

struct WindowParams
{
	std::string title;
	std::string description;
	std::string author;
	std::string url;

	int32_t initialWidth;
	int32_t initialHeight;
	std::string openDialogTitle;
	int32_t openDialogFiltersCount;
	const FileDialogFilter* openDialogFilters;

	std::function<void(ImVec4* colors)> configureStyleCallback;
	std::function<void(ImFontAtlas* fontAtlas)> configureFontsCallback;
};

class Window
{
protected:
	const WindowParams& params;
	bool isRunning = false;

public:
	Window(const WindowParams& params);
	virtual ~Window();

	const WindowParams& GetParams() const { return params; }

	virtual const char* GetBackendInfo() const = 0;
	virtual const char* GetBackendUrl() const = 0;

	virtual void Run(BaseUI& ui) = 0;
	void Terminate();

	virtual void ShowOpenFileDialog(const FileDialogParams* fileDialogParams) const = 0;
	virtual void SetTaskbarProgress(const float value) = 0;
};
