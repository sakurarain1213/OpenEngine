#pragma once

#include "Object.h"
#include "RenderDriver.h"
#include "Math.h"
#include "Uniform.h"
#include "Texture.h"

namespace OpenEngine {
	namespace Importer { class ShaderImporter; }

	class Shader : public Object {
		friend class ShaderImporter;
		friend class Material;
	public:
		Shader(const std::string& vert, const std::string& frag, std::string name = "New Shader") :
			m_shaderID(0),
			Object(name) {

			const char* vertCode = vert.c_str();
			const char* fragCode = frag.c_str();
			GLuint vertID, fragID;
			GLint success;
			char log[512];

			vertID = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertID, 1, &vertCode, NULL);
			glCompileShader(vertID);
			glGetShaderiv(vertID, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(vertID, 512, NULL, log);
				OE_ERROR("[Shader] " + name + " : Vertex shader compilation failed (" + log + ")");
			}

			fragID = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragID, 1, &fragCode, NULL);
			glCompileShader(fragID);
			glGetShaderiv(fragID, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(fragID, 512, NULL, log);
				OE_ERROR("[Shader] " + name + " : Fragment shader Compilation failed (" + log + ")");
			}

			m_shaderID = glCreateProgram();
			glAttachShader(m_shaderID, vertID);
			glAttachShader(m_shaderID, fragID);
			glLinkProgram(m_shaderID);
			glGetProgramiv(m_shaderID, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(m_shaderID, 512, NULL, log);
				OE_ERROR("[Shader] " + name + " : Link failed (" + log + ")");
			}

			glDeleteShader(vertID);
			glDeleteShader(fragID);

			GetActiveUniforms();
			SetUniformBlock("GlobalUBO", 0);
		}
		~Shader() {
			glDeleteProgram(m_shaderID);
		}
		std::string GetType() {
			return "Shader";
		}
		static std::string ClassType() {
			return "Shader";
		}
		void SetUniform(const std::string& name, int val) {
			glUniform1i(GetUniformLocation(name), val);
		}
		void SetUniform(const std::string& name, float val) {
			glUniform1f(GetUniformLocation(name), val);
		}
		void SetUniform(const std::string& name, const Vec2& val) {
			glUniform2f(GetUniformLocation(name), val.x(), val.y());
		}
		void SetUniform(const std::string& name, const Vec3& val) {
			glUniform3f(GetUniformLocation(name), val.x(), val.y(), val.z());
		}
		void SetUniform(const std::string& name, const Vec4& val) {
			glUniform4f(GetUniformLocation(name), val.x(), val.y(), val.z(), val.w());
		}
		void SetUniform(const std::string& name, const Mat4& val) {
			glUniformMatrix4fv(GetUniformLocation(name), 1, GL_TRUE, val.data());
		}
		void SetUniformBlock(const std::string& block_name, GLuint bind_point) {
			GLuint blockIndex = glGetUniformBlockIndex(m_shaderID, block_name.c_str());
			OE_INFO("[shader] " + block_name + " " + std::to_string(blockIndex));
			glUniformBlockBinding(m_shaderID, blockIndex, bind_point);
		}
		int GetUniformInt(const std::string& name) {
			int value;
			glGetUniformiv(m_shaderID, GetUniformLocation(name), &value);
			return value;
		}
		float GetUniformFloat(const std::string& name) {
			float value;
			glGetUniformfv(m_shaderID, GetUniformLocation(name), &value);
			return value;
		}
		Vec2 GetUniformVec2(const std::string& name) {
			float value[2];
			glGetUniformfv(m_shaderID, GetUniformLocation(name), value);
			return Vec2(value);
		}
		Vec3 GetUniformVec3(const std::string& name) {
			float value[3];
			glGetUniformfv(m_shaderID, GetUniformLocation(name), value);
			return Vec3(value);
		}
		Vec4 GetUniformVec4(const std::string& name) {
			float value[4];
			glGetUniformfv(m_shaderID, GetUniformLocation(name), value);
			return Vec4(value);
		}
		Mat4 GetUniformMat4(const std::string& name) {
			float value[16];
			glGetUniformfv(m_shaderID, GetUniformLocation(name), value);
			return Mat4(value);
		}
		void GetActiveUniforms() {
			GLint activeUniformCount = 0;
			m_uniforms.clear();
			glGetProgramiv(m_shaderID, GL_ACTIVE_UNIFORMS, &activeUniformCount);
			GLchar buf[256];
			for (int i = 0; i < activeUniformCount; ++i) {
				GLint arraySize = 0;
				GLenum type = 0;
				GLsizei length = 0;
				glGetActiveUniform(m_shaderID, i, 256, &length, &arraySize, &type, buf);
				std::string name(buf, length);
				OE_INFO(name);
				if (name.rfind("OE_", 0) != 0) {
					std::any value;
					switch (type)
					{
					case OpenEngine::OE_UNIFROM_BOOL:
						value = std::make_any<bool>(GetUniformInt(name));break;
					case OpenEngine::OE_UNIFORM_INT:
						value = std::make_any<int>(GetUniformInt(name));break;
					case OpenEngine::OE_UNIFORM_FLOAT:
						value = std::make_any<float>(GetUniformFloat(name));break;
					case OpenEngine::OE_UNIFORM_VEC2:
						value = std::make_any<Vec2>(GetUniformVec2(name));break;
					case OpenEngine::OE_UNIFORM_VEC3:
						value = std::make_any<Vec3>(GetUniformVec3(name));break;
					case OpenEngine::OE_UNIFORM_VEC4:
						value = std::make_any<Vec4>(GetUniformVec4(name));break;
					case OpenEngine::OE_UNIFORM_MAT4:
						value = std::make_any<Mat4>(GetUniformMat4(name));break;
					case OpenEngine::OE_UNIFORM_SAMPLER2D:
						value = std::make_any<Texture*>(nullptr);break;
					default:
						break;
					}

					if (value.has_value()) {
						m_uniforms.emplace_back(name, (UniformType)type, value);
					}
				}
			}
		}
	private:
		GLint GetUniformLocation(const std::string& name) {
			if (m_uniformLocation.find(name) != m_uniformLocation.end())
				return m_uniformLocation.at(name);
			const GLint location = glGetUniformLocation(m_shaderID, name.c_str());
			if (location == -1) OE_WARNING("[shader] Uniform location " + name + " is not found");
			m_uniformLocation[name] = location;
			return location;
		}
		void Use() {
			glUseProgram(m_shaderID);
		}
		void UnUse() {
			glUseProgram(0);
		}
		GLuint m_shaderID;
		std::unordered_map<std::string, GLint> m_uniformLocation;
		std::vector<Uniform> m_uniforms;
	};
}