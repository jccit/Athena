#include "ImGuiHelper.h"
#include <imgui_sdl.h>
#include <imgui.h>
#include <imgui/backends/imgui_impl_sdl.h>

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
	ImGui::ShowDemoWindow();
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

