#include "ImGuiHelper.h"
#include "ImGuiConsole.h"
#include <imgui_sdl.h>
#include <imgui.h>
#include <imgui/backends/imgui_impl_sdl.h>

#include <Console/Console.h>

std::vector<std::shared_ptr<ImGuiTool>> tools;

ImGuiHelper::ImGuiHelper()
{
	auto console = std::shared_ptr<ImGuiConsole>(new ImGuiConsole());
	Console::getInstance().registerOutput(console);
	tools.push_back(console);
}

ImGuiHelper::~ImGuiHelper()
{
	for (auto tool : tools)
	{
		tool.reset();
	}
}

void ImGuiHelper::init(Window* win)
{
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
}

void ImGuiHelper::shutdown()
{
	ImGuiSDL::Deinitialize();
	ImGui_ImplSDL2_Shutdown();
}

void ImGuiHelper::newFrame(float delta, Window* win)
{	
	ImGui_ImplSDL2_NewFrame(win->getSDLWindow());
	
	ImGuiIO& io = ImGui::GetIO();
	io.DeltaTime = delta;
	
	ImGui::NewFrame();
	
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("Tools"))
		{
			for (auto tool : tools)
			{
				tool->renderMenu();
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	for (auto tool : tools)
	{
		tool->render();
	}
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

