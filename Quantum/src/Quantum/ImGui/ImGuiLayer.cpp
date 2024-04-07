#include"qtpch.h"
#include"ImGuiLayer.h"
#include"imgui.h"
#include"imgui_impl_opengl3.h"
#include"imgui_impl_glfw.h"
#include"Quantum/Application.h"
//temp includes
#include<GLFW/glfw3.h>
#include<glad/glad.h>
namespace Quantum {
	Quantum::ImGuiLayer::ImGuiLayer()
		:Layer("ImGuiLayer")
	{
	}

	Quantum::ImGuiLayer::~ImGuiLayer()
	{
	}

	void Quantum::ImGuiLayer::onAttach()
	{
		//setup dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; //  Enable keyboard controls
	//	io.ConfigFlags |=
	//		ImGuiConfigFlags_NavEnableGamepad; // Enable gamepad controls
		io.ConfigFlags |=
			ImGuiConfigFlags_DockingEnable; // Enable dockgin
		io.ConfigFlags |=
			ImGuiConfigFlags_ViewportsEnable; // Enable dockgin
		//set up dear ImGui style 
		ImGui::StyleColorsDark();
		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}
		Application& app = Application::get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.getWindow().getNativeWindow());
		//setup platform renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init();

	}

	void Quantum::ImGuiLayer::onDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
	void ImGuiLayer::begin() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}
	void ImGuiLayer::end()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::get();
		io.DisplaySize = ImVec2((float)app.getWindow().getWidth(), (float)app.getWindow().getHeight());
		//rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}
	void ImGuiLayer::onImGuiRender()
	{
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}
	
}