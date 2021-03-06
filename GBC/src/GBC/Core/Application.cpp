#include "gbcpch.h"
#include "Application.h"
#include "GBC/Rendering/Renderer.h"
#include "GBC/Events/WindowEvents.h"

namespace gbc
{
	Application* Application::instance = nullptr;

	Application::Application(const WindowSpecifications& windowSpecs)
	{
		GBC_PROFILE_FUNCTION();

		GBC_CORE_ASSERT(instance == nullptr, "Application already exists!");
		instance = this;

		window = Window::CreateScope(windowSpecs);
		window->SetEventCallback(GBC_BIND_FUNC(OnEvent));

		Renderer::Init();

#if GBC_ENABLE_IMGUI
		imguiLayer = new ImGuiLayer();
		PushOverlay(imguiLayer);
#endif
	}

	Application::~Application()
	{
		GBC_PROFILE_FUNCTION();

		for (Layer* layer : layerStack)
		{
			layer->OnDetach();
			delete layer;
		}

		Renderer::Shutdown();
	}

	void Application::Run()
	{
		Timestep timestep;

		while (running)
		{
			GBC_PROFILE_SCOPE("RunLoop");

			timestep = window->GetContext().GetElapsedTime();

			for (Layer* layer : layerStack)
				layer->OnUpdate(timestep);

			if (rendering)
			{
				for (Layer* layer : layerStack)
					layer->OnRender();

#if GBC_ENABLE_IMGUI
				imguiLayer->Begin();
				for (Layer* layer : layerStack)
					layer->OnImGuiRender();
				imguiLayer->End();
#endif

				window->SwapBuffers();
			}

			window->PollEvents();
		}
	}

	void Application::Terminate()
	{
		running = false;
	}

	void Application::PushLayer(Layer* layer)
	{
		layerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		layerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::PopLayer(Layer* layer)
	{
		if (layerStack.PopLayer(layer))
			layer->OnDetach();
	}

	void Application::PopOverlay(Layer* overlay)
	{
		if (layerStack.PopOverlay(overlay))
			overlay->OnDetach();
	}

	void Application::OnEvent(Event& event)
	{
		GBC_PROFILE_FUNCTION();

		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(GBC_BIND_FUNC(OnWindowCloseEvent));
		dispatcher.Dispatch<WindowResizeEvent>(GBC_BIND_FUNC(OnWindowResizeEvent));
		dispatcher.Dispatch<WindowMinimizeEvent>(GBC_BIND_FUNC(OnWindowMinimizeEvent));

		for (auto it = layerStack.rbegin(); !event.handled && it != layerStack.rend(); ++it)
			(*it)->OnEvent(event);
	}

	bool Application::OnWindowCloseEvent(WindowCloseEvent& event)
	{
		Terminate();
		return true;
	}

	bool Application::OnWindowResizeEvent(WindowResizeEvent& event)
	{
		GBC_PROFILE_FUNCTION();

		if (event.GetWidth() == 0 || event.GetHeight() == 0)
		{
			rendering = false;
			return true;
		}
		else
		{
			rendering = true;
			Renderer::SetViewport(0, 0, event.GetWidth(), event.GetHeight());
			return false;
		}
	}

	bool Application::OnWindowMinimizeEvent(WindowMinimizeEvent& event)
	{
		rendering = !event.IsMinimized();
		return false;
	}
}
