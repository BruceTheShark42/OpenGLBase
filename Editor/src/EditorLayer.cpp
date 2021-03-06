#include "EditorLayer.h"
#include "imgui/imgui.h"
#include "Panels/StasticsPanel.h"
#include "Panels/ProfilingPanel.h"

namespace gbc
{
	void EditorLayer::OnAttach()
	{
		GBC_PROFILE_FUNCTION();

		Window& window = Application::Get().GetWindow();

		FramebufferSpecification framebufferSpecification;
		framebufferSpecification.width = window.GetWidth();
		framebufferSpecification.height = window.GetHeight();
		framebufferSpecification.attachments = {FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::Depth24Stencil8};
		framebuffer = Framebuffer::CreateRef(framebufferSpecification);

		scene = CreateRef<Scene>();

		// TODO: Deserialize scene
		Entity entity = scene->CreateEntity("Textured Square");
		BasicModel& model = entity.Add<MeshComponent>(BasicModel(4, 6)).model;
		entity.Add<RenderableComponent>(Texture::CreateRef(CreateRef<LocalTexture2D>("resources/textures/grass_side.png", 4, true)));

		model.vertices[0] = {{-0.5f, -0.5f, -1.0f}, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}};
		model.vertices[1] = {{ 0.5f, -0.5f, -1.0f}, {1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}};
		model.vertices[2] = {{ 0.5f,  0.5f, -1.0f}, {1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}};
		model.vertices[3] = {{-0.5f,  0.5f, -1.0f}, {0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}};
		model.indices[0] = 0;
		model.indices[1] = 1;
		model.indices[2] = 2;
		model.indices[3] = 2;
		model.indices[4] = 3;
		model.indices[5] = 0;

		Entity camera = scene->CreateEntity("Temp Camera Controller");
		auto& cameraCameraComponent = camera.Add<CameraComponent>();
		cameraCameraComponent.primary = true;
		cameraCameraComponent.camera.SetProjectionType(SceneCamera::ProjectionType::Perspective);
		camera.Add<NativeScriptComponent>().Bind<PerspectiveCameraControllerScript>();

		scene->OnCreate();

		sceneViewportPanel = AddPanel<SceneViewportPanel>("Scene Viewport", framebuffer);
		sceneHierarchyPanel = AddPanel<SceneHierarchyPanel>("Scene Hierarchy", scene);
		scenePropertiesPanel = AddPanel<ScenePropertiesPanel>("Scene Properties", sceneHierarchyPanel->GetSelectedEntity());
#if GBC_ENABLE_STATS
		AddPanel<StatisticsPanel>("Statistics", BasicRenderer::GetStatistics());
#endif
#if GBC_ENABLE_PROFILE_RUNTIME
		AddPanel<ProfilingPanel>("Profiling");
#endif
	}

	void EditorLayer::OnDetach()
	{
		GBC_PROFILE_FUNCTION();

		scene->OnDestroy();

		for (auto& [name, panel] : panels)
			delete panel;
	}

	void EditorLayer::OnUpdate(Timestep timestep)
	{
		GBC_PROFILE_FUNCTION();

		bool viewportFocused = sceneViewportPanel->IsViewportFocused();
		bool viewportHovered = sceneViewportPanel->IsViewportHovered();
		Application::Get().GetImGuiLayer().SetBlockEvents(!viewportFocused && !viewportHovered);

		if (sceneViewportPanel->HasViewportSizeChanged())
		{
			const glm::vec2& viewportSize = sceneViewportPanel->GetViewportSize();
			scene->OnViewportResize((int)viewportSize.x, (int)viewportSize.y);
		}

		// TODO: Editor Camera

		if (viewportFocused)
			scene->OnUpdate(timestep);
	}

	void EditorLayer::OnRender()
	{
		GBC_PROFILE_FUNCTION();

	#if GBC_ENABLE_STATS
		BasicRenderer::ResetStatistics();
	#endif

		framebuffer->Bind();
		scene->OnRender();
		framebuffer->Unbind();
	}

#if GBC_ENABLE_IMGUI
	void EditorLayer::OnImGuiRender()
	{
		GBC_PROFILE_FUNCTION();

		ImGuiWindowFlags dockspaceFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking
			| ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize
			| ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->GetWorkPos());
		ImGui::SetNextWindowSize(viewport->GetWorkSize());
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2());
		ImGui::Begin("Dockspace", nullptr, dockspaceFlags);
		ImGui::PopStyleVar(2);
		ImGui::DockSpace(ImGui::GetID("Dockspace"));

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit"))
					Application::Get().Terminate();

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("View"))
			{
				Window& window = Application::Get().GetWindow();
				if (ImGui::MenuItem(window.IsFullscreen() ? "Windowed" : "Fullscreen"))
					window.ToggleFullscreen();

				ImGui::Separator();

				for (auto& [name, panel] : panels)
					if (ImGui::MenuItem(name.c_str()))
						panel->ToggleEnabled();

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}
		ImGui::End();

		for (auto& [name, panel] : panels)
			panel->OnImGuiRender();
	}
#endif

	void EditorLayer::OnEvent(Event& event)
	{
		GBC_PROFILE_FUNCTION();
	}
}
