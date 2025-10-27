#pragma once



// core
#include "Core/Assert.h"
#include "Core/Factory.h"
#include "Core/File.h"
#include "Core/Json.h"
#include "Core/Logger.h"
#include "Core/Random.h"
#include "Core/Singleton.h"
#include "Core/StringHelper.h"
#include "Core/Time.h"

// framework
#include "Framework/Object.h"
#include "Framework/Actor.h"
#include "Framework/Scene.h"

// math
#include "Math/Math.h"
#include "Math/Transform.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Rect.h"

// resources
#include "Resources/Resource.h"
#include "Resources/ResourceManager.h"

// event manager
#include "Event/Event.h"
#include "Event/EventManager.h"
#include "Event/Observer.h"

// input
#include "Input/InputSystem.h"

// audio
#include "Audio/AudioClip.h"
#include "Audio/AudioChannel.h"
#include "Audio/AudioSystem.h"

// renderer
#include "Renderer/Renderer.h"
#include "Renderer/Texture.h"
#include "Renderer/TextureAnimation.h"
#include "Renderer/Shader.h"
#include "Renderer/Program.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/Model.h"
#include "Renderer/Material.h"

// physics
#include "Physics/Collidable.h"

// third-party library
#include <fmod.hpp>
#include <fmod_errors.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// standard library
#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <map>
#include <list>
#include <cstdlib>
#include <random>
#include <algorithm>
#include <cmath>
#include <filesystem>


