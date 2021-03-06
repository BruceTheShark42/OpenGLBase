#pragma once

// For use by client applications
#include "GBC/Core/Core.h"
#include "GBC/Core/Application.h"
#include "GBC/Core/Input.h"
#include "GBC/Core/Logger.h"
#include "GBC/Core/Window.h"
#include "GBC/Debug/Profiler.h"
#include "GBC/Events/WindowEvents.h"
#include "GBC/Events/KeyEvents.h"
#include "GBC/Events/MouseEvents.h"
#include "GBC/Events/DeviceEvents.h"
#include "GBC/IO/FileIO.h"
#include "GBC/Rendering/Basic/BasicRenderer.h"
#include "GBC/Rendering/Buffer.h"
#include "GBC/Rendering/Framebuffer.h"
#include "GBC/Rendering/LocalTexture2D.h"
#include "GBC/Rendering/Renderer.h"
#include "GBC/Rendering/Shader.h"
#include "GBC/Rendering/Texture.h"
#include "GBC/Rendering/VertexArray.h"
#include "GBC/Scene/Scene.h"
#include "GBC/Scene/Entity.h"
#include "GBC/Scene/ScriptableEntity.h"
#include "GBC/Scene/Components/TransformComponent.h"
#include "GBC/Scene/Components/TagComponent.h"
#include "GBC/Scene/Components/RenderableComponent.h"
#include "GBC/Scene/Components/MeshComponent.h"
#include "GBC/Scene/Components/CameraComponent.h"
#include "GBC/Scene/Components/NativeScriptComponent.h"
#include "GBC/Util/Scripts/OrthographicCameraControllerScript.h"
#include "GBC/Util/Scripts/PerspectiveCameraControllerScript.h"
#include "GBC/Util/TextureAtlas.h"
