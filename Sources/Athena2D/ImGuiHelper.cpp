#include "pch.h"
#include "ImGuiHelper.h"
#include "ImGuiConsole.h"
#include "EntityInspector.h"
#include "PerfOverlay.h"
#include <imgui_sdl.h>
#include <imgui.h>
#include <imgui/backends/imgui_impl_sdl.h>

#include <Console/Console.h>
#include <Console/CVar.h>

CVar devEnable = CVar("dev_enable", g_devMode, CVAR_NONE, "Enable developer mode");
CVar perfEnable = CVar("perf_enable", g_devMode, CVAR_NONE, "Enable perf overlay");

PerfOverlay* perfOverlay;
std::shared_ptr<ImGuiConsole> console;
std::vector<std::shared_ptr<ImGuiTool>> tools;
bool showDemo = false;

ImGuiHelper::ImGuiHelper()
{
	console = std::shared_ptr<ImGuiConsole>(new ImGuiConsole());
	Console::getInstance().registerOutput(console);

	// Update CVars after boot
	devEnable.set(g_devMode);
	perfEnable.set(g_devMode);

	perfOverlay = new PerfOverlay();
}

ImGuiHelper::~ImGuiHelper()
{
	for (auto tool : tools)
	{
		tool.reset();
	}

	delete perfOverlay;
}

void ImGuiHelper::init(Window* win, World* w)
{
	world = w;
	tools.push_back(std::shared_ptr<EntityInspector>(new EntityInspector(world)));
	
	ImGui::CreateContext();
	ImGuiSDL::Initialize(win->getRenderer(), win->getWidth(), win->getHeight());

	SDL_RendererInfo info;
	ImGuiIO& io = ImGui::GetIO();
	SDL_GetRendererInfo(win->getRenderer(), &info);
	io.BackendPlatformName = "SDL";
	io.BackendRendererName = info.name;

	// Metal init does nothing other than init key and mouse handling
	// imgui_sdl is handling rendering so this is perfect for us
	ImGui_ImplSDL2_InitForMetal(win->getSDLWindow());

	LOG("Init", "ImGui");
}

void ImGuiHelper::shutdown()
{
	ImGuiSDL::Deinitialize();
	ImGui_ImplSDL2_Shutdown();

	LOG("Shutdown", "ImGui");
}

void ImGuiHelper::newFrame(float delta, Window* win)
{	
	ImGui_ImplSDL2_NewFrame(win->getSDLWindow());
	
	ImGuiIO& io = ImGui::GetIO();
	io.DeltaTime = delta;
	
	ImGui::NewFrame();

	// Always handle input and render console
	console->handleInput();
	console->render();

	bool showPerf = perfEnable.getBool();
	bool showDev = devEnable.getBool();
	if (showPerf) {
		perfOverlay->render(showDev);
	}
	
	if (showDev) {
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("Tools"))
			{
				console->renderMenu();

				ImGui::Separator();

				for (auto tool : tools)
				{
					tool->renderMenu();
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Misc"))
			{
				ImGui::MenuItem("ImGui demo", NULL, &showDemo);
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}

		for (auto tool : tools)
		{
			tool->handleInput();
			tool->render();
		}

		if (showDemo)
			ImGui::ShowDemoWindow(&showDemo);
	}
}

void ImGuiHelper::addTool(std::shared_ptr<ImGuiTool> tool)
{
	tools.push_back(tool);
}

void ImGuiHelper::render()
{
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
}

bool ImGuiHelper::wantsKeyboard()
{
	ImGuiIO& io = ImGui::GetIO();
	return io.WantCaptureKeyboard;
}

