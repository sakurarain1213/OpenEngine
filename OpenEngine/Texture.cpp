#pragma once

#include "Texture.h"

namespace OpenEngine {
	Texture::Texture(uint32_t width, uint32_t height, TextureFormat format, bool useMipmap) :
		m_width(width),
		m_height(height),
		m_format(format),
		m_textureID(0),
		m_isReadable(true),
		m_raw(nullptr),
		wrapU(REPEAT),
		wrapV(REPEAT),
		minFilter(LINEAR_MIPMAP_LINEAR),
		magFilter(LINEAR),
		useMipmap(useMipmap),
		Object("New Texture") {
		Initialize();
	}

	std::string Texture::GetType() {
		return "Texture";
	}

	std::string Texture::ClassType() {
		return "Texture";
	}

	Texture::~Texture() {
		glDeleteTextures(1, &m_textureID);
	}

	void Texture::Initialize() {
		glGenTextures(1, &m_textureID);
	}

	void Texture::Apply() {
		glBindTexture(GL_TEXTURE_2D, m_textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapU);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapV);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
		if (m_raw) {
			glTexImage2D(GL_TEXTURE_2D, 0, m_format, m_width, m_height, 0, m_format, GL_UNSIGNED_BYTE, m_raw);
			OE_INFO(name + " " + std::to_string(instanceID) + " : " + "Load texture (" + std::to_string(m_width) + " x " + std::to_string(m_height) + ")");
		}
		else {
			OE_ERROR(name + " " + std::to_string(instanceID) + " : " + "Failed to load raw texture data");
			return;
		}
		if (useMipmap) {
			glGenerateMipmap(GL_TEXTURE_2D);
			OE_INFO(name + " " + std::to_string(instanceID) + " : " + "Generate mipmap");
		}
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::Bind(uint32_t slot) {
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_textureID);
	}
}