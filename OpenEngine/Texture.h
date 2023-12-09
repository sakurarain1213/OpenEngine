#pragma once

#include "Object.h"
#include "RenderDriver.h"

namespace OpenEngine {
	enum TextureWrapMode
	{
		REPEAT = GL_REPEAT,
		MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
		CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
		CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER
	};

	enum TextureFilterMode {
		NEAREST = GL_NEAREST,
		LINEAR = GL_LINEAR,
		NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
		LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
		NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
		LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR
	};

	enum TextureFormat {
		GRAY = GL_RED,
		RGB = GL_RGB,
		RGBA = GL_RGBA
	};

	namespace Importer { class TextureImporter; }

	class Texture : Object {
		friend class Importer::TextureImporter;
		friend class Material;
	public:
		uint32_t GetHeight() { return m_height; }
		uint32_t GetWidth() { return m_width; }
		TextureFormat GetFormat() { return m_format; }
		Texture(uint32_t width, uint32_t height, TextureFormat format, bool useMipmap = true);
		void Apply();
		std::string GetType();
		static std::string ClassType();
		~Texture();

		TextureWrapMode wrapU;
		TextureWrapMode wrapV;
		TextureFilterMode minFilter;
		TextureFilterMode magFilter;
		bool useMipmap;

	private:
		void Initialize();
		void Bind(uint32_t slot);
		const unsigned char* m_raw;
		uint32_t m_height;
		uint32_t m_width;
		TextureFormat m_format;
		GLuint m_textureID;
		bool m_isReadable;
	};
}