#pragma once
#include "Resources/Resource.h"
#include "Math/Vector2.h"
#include <string>
#include <glad/glad.h>

struct SDL_Texture;

namespace neu {
	/// <summary>
	/// Represents a 2D texture that can be rendered to the screen.
	/// This class wraps an SDL_Texture object and manages its lifetime.
	/// Textures are loaded from image files and stored in GPU memory for efficient rendering.
	/// Inherits from Resource to support the resource management system.
	/// </summary>
	class Texture : public Resource {
	public:
		Texture() = default;
		~Texture();

		/// <summary>
		/// Loads an image file and creates a texture for rendering.
		/// Supports common image formats like PNG, JPG, BMP through SDL_image.
		/// </summary>
		/// <param name="filename">Path to the image file (e.g., "assets/textures/player.png")</param>
		/// <param name="renderer">Reference to the Renderer that will manage this texture</param>
		/// <returns>True if the texture was successfully loaded; otherwise, false</returns>
		bool Load(const std::string& filename);

		void SetActive(GLuint unit) { glActiveTexture(unit); }
		void Bind() { glBindTexture(m_target, m_texture); }

		/// <summary>
		/// Gets the dimensions of the texture in pixels.
		/// </summary>
		/// <returns>A vec2 containing the width and height of the texture</returns>
		vec2 GetSize() { return m_size;  }

		// Allow Renderer class to access the texture for drawing operations
		friend class Renderer;
		GLuint m_texture{ 0 };           
	private:
		GLenum m_target = GL_TEXTURE_2D;

		// The dimensions of the texture in pixels
		vec2 m_size{ 0, 0 };
	};
}