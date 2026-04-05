#if !NDEBUG
// Test leaks with _CrtDumpMemoryLeaks()
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#include <imgui/imgui.h>

#include "WindowSDL.h"
#include "MainUI.h"

int RunMain()
{
	const FileDialogFilter openDialogFilters[] =
	{
		{ "N64 Saves (*.eep; *.sav)", "eep;sav" },
		{ "All files (*.*)", "*" }
	};

	WindowParams windowParams = {};
	windowParams.title = "Banjo-Kazooie - Save Editor";
	windowParams.description = "This is a save editor for the Nintendo 64 version of Banjo-Kazooie.";
	windowParams.author = "PacoChan";
	windowParams.url = "https://pacochan.net/software/bk-save-editor/";
	windowParams.initialWidth = 800;
	windowParams.initialHeight = 654;
	windowParams.backgroundColor = ImVec4(0.12, 0.05f, 0.012f, 1.0f);
	windowParams.openDialogTitle = "Open a Banjo-Kazooie save file";
	windowParams.openDialogFiltersCount = sizeof(openDialogFilters) / sizeof(openDialogFilters[0]);
	windowParams.openDialogFilters = openDialogFilters;
	windowParams.configureStyleCallback = [](ImVec4* colors)
		{
			ImGui::StyleColorsDark();

			constexpr float BG_COLOR_R = 0.71f;
			constexpr float BG_COLOR_G = 0.32f;
			constexpr float BG_COLOR_B = 0.07f;

			constexpr float NORMAL_COLOR_R = 0.80f;
			constexpr float NORMAL_COLOR_G = 0.50f;
			constexpr float NORMAL_COLOR_B = 0.22f;

			constexpr float HIGHLIGHT_COLOR_R = 0.80f;
			constexpr float HIGHLIGHT_COLOR_G = 0.54f;
			constexpr float HIGHLIGHT_COLOR_B = 0.03f;

			colors[ImGuiCol_FrameBg] = ImVec4(BG_COLOR_R, BG_COLOR_G, BG_COLOR_B, 0.35f);
			colors[ImGuiCol_FrameBgHovered] = ImVec4(BG_COLOR_R, BG_COLOR_G, BG_COLOR_B, 0.47f);
			colors[ImGuiCol_FrameBgActive] = ImVec4(BG_COLOR_R, BG_COLOR_G, BG_COLOR_B, 0.24f);
			colors[ImGuiCol_TitleBgActive] = ImVec4(HIGHLIGHT_COLOR_R, HIGHLIGHT_COLOR_G, HIGHLIGHT_COLOR_B, 0.86f);
			colors[ImGuiCol_ScrollbarBg] = ImVec4(BG_COLOR_R, BG_COLOR_G, BG_COLOR_B, 0.24f);
			colors[ImGuiCol_ScrollbarGrab] = ImVec4(NORMAL_COLOR_R, NORMAL_COLOR_G, NORMAL_COLOR_B, 0.59f);
			colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(HIGHLIGHT_COLOR_R, HIGHLIGHT_COLOR_G, HIGHLIGHT_COLOR_B, 1.00f);
			colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(NORMAL_COLOR_R, NORMAL_COLOR_G, NORMAL_COLOR_B, 0.78f);
			colors[ImGuiCol_CheckMark] = ImVec4(HIGHLIGHT_COLOR_R, HIGHLIGHT_COLOR_G, HIGHLIGHT_COLOR_B, 1.00f);
			colors[ImGuiCol_SliderGrab] = ImVec4(HIGHLIGHT_COLOR_R, HIGHLIGHT_COLOR_G, HIGHLIGHT_COLOR_B, 1.00f);
			colors[ImGuiCol_SliderGrabActive] = ImVec4(HIGHLIGHT_COLOR_R, HIGHLIGHT_COLOR_G, HIGHLIGHT_COLOR_B, 0.78f);
			colors[ImGuiCol_Button] = ImVec4(NORMAL_COLOR_R, NORMAL_COLOR_G, NORMAL_COLOR_B, 0.59f);
			colors[ImGuiCol_ButtonHovered] = ImVec4(HIGHLIGHT_COLOR_R, HIGHLIGHT_COLOR_G, HIGHLIGHT_COLOR_B, 1.00f);
			colors[ImGuiCol_ButtonActive] = ImVec4(NORMAL_COLOR_R, NORMAL_COLOR_G, NORMAL_COLOR_B, 0.78f);
			colors[ImGuiCol_Header] = ImVec4(NORMAL_COLOR_R, NORMAL_COLOR_G, NORMAL_COLOR_B, 0.35f);
			colors[ImGuiCol_HeaderHovered] = ImVec4(NORMAL_COLOR_R, NORMAL_COLOR_G, NORMAL_COLOR_B, 0.78f);
			colors[ImGuiCol_HeaderActive] = ImVec4(NORMAL_COLOR_R, NORMAL_COLOR_G, NORMAL_COLOR_B, 0.67f);
			colors[ImGuiCol_Separator] = ImVec4(HIGHLIGHT_COLOR_R, HIGHLIGHT_COLOR_G, HIGHLIGHT_COLOR_B, 0.71f);
			colors[ImGuiCol_TabHovered] = ImVec4(HIGHLIGHT_COLOR_R, HIGHLIGHT_COLOR_G, HIGHLIGHT_COLOR_B, 1.00f);
			colors[ImGuiCol_Tab] = ImVec4(BG_COLOR_R, BG_COLOR_G, BG_COLOR_B, 0.5f);
			colors[ImGuiCol_TabSelected] = ImVec4(HIGHLIGHT_COLOR_R, HIGHLIGHT_COLOR_G, HIGHLIGHT_COLOR_B, 0.86f);
			colors[ImGuiCol_TextLink] = ImVec4(HIGHLIGHT_COLOR_R, HIGHLIGHT_COLOR_G, HIGHLIGHT_COLOR_B, 1.00f);
			colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.63f);
		};
	windowParams.configureFontsCallback = [](ImFontAtlas* fontAtlas)
		{
			ImFontConfig configVector;
			configVector.MergeMode = false;
			configVector.OversampleH = 2;
			configVector.OversampleV = 2;
			configVector.RasterizerMultiply = 1.5f;

			fontAtlas->AddFontDefaultVector(&configVector);
		};

	try
	{
		WindowSDL window(windowParams);

		MainUI mainUi(&window);
		window.Run(mainUi);
	}
	catch (const std::runtime_error& error)
	{
		printf("%s\n", error.what());
		return -1;
	}

	return 0;
}

int main()
{
	// Run everything in RunMain so when the function exits, all the destructors,
	// including those of objects with automatic storage duration like std::string are called.
	// That will prevent _CrtDumpMemoryLeaks() from having some false positives.

	int result = RunMain();

#if !NDEBUG
	// Cause an intentional leak to check if the leak detector is working

	char* leakTest = new char[10];
	snprintf(leakTest, 10, "%s", "LEAK TEST");

	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();
#endif

	return result;
}
