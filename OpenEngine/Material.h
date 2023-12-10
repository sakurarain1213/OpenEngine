#pragma once

#include "Shader.h"
#include "PropertyMap.h"

namespace OpenEngine {
	namespace Importer { class MaterialImporter; }
	class Material : public Object {
		friend class Importer::MaterialImporter;
	public:
		Material() : m_shader(nullptr), Object("New Material") {}
		Material(Shader* shader, std::string name = "New Material") :
			m_shader(shader),
			Object(name) {
			if (m_shader) {
				InitUniforms();
			}
		}
		template <typename T>
		void SetUniform(std::string name, T value) {
			if (!m_shader) return;
			if (m_uniforms.find(name) != m_uniforms.end()) {
				std::any& slot = m_uniforms.at(name);
				if (slot.type() == typeid(T)) {
					slot = std::make_any<T>(value);
				}
				else {
					OE_WARNING("[Material] " + name + ": Uniform " + name + " can't be set to type " + typeid(T).name() + " in shader " + m_shader->name);
				}
			}
			else {
				OE_WARNING("[Material] " + name + ": Uniform " + name + " is not found in shader " + m_shader->name);
			}
		}
		void SetShader(Shader* shader) {
			m_shader = shader;
			if (m_shader) {
				InitUniforms();
			}
		}
		std::vector<std::string> GetUniformsNames() {
			std::vector<std::string> ret;
			const std::vector<Uniform>& activeUniforms = m_shader->m_uniforms;
			for (int i = 0;i < activeUniforms.size();++i) {
				const std::string name = activeUniforms[i].name;
				ret.push_back(name);
			}
			return ret;
		}
	private:
		void InitUniforms() {
			m_uniforms.clear();
			const std::vector<Uniform>& activeUniforms = m_shader->m_uniforms;
			for (int i = 0;i < activeUniforms.size();++i) {
				m_uniforms[activeUniforms[i].name] = activeUniforms[i].value;
			}
		}
		void Use() {
			if (!m_shader) return;
			m_shader->Use();
			const std::vector<Uniform>& activeUniforms = m_shader->m_uniforms;
			int texcount = 0;
			for (int i = 0;i < activeUniforms.size();++i) {
				const std::string name = activeUniforms[i].name;
				const std::any value = m_uniforms[name];
				switch (activeUniforms[i].type)
				{
				case OpenEngine::OE_UNIFROM_BOOL:
					m_shader->SetUniform(name, std::any_cast<bool>(value));break;
				case OpenEngine::OE_UNIFORM_INT:
					m_shader->SetUniform(name, std::any_cast<int>(value));break;
				case OpenEngine::OE_UNIFORM_FLOAT:
					m_shader->SetUniform(name, std::any_cast<float>(value));break;
				case OpenEngine::OE_UNIFORM_VEC2:
					m_shader->SetUniform(name, std::any_cast<Vec2>(value));break;
				case OpenEngine::OE_UNIFORM_VEC3:
					m_shader->SetUniform(name, std::any_cast<Vec3>(value));break;
				case OpenEngine::OE_UNIFORM_VEC4:
					m_shader->SetUniform(name, std::any_cast<Vec4>(value));break;
				case OpenEngine::OE_UNIFORM_MAT4:
					m_shader->SetUniform(name, std::any_cast<Mat4>(value));break;
				case OpenEngine::OE_UNIFORM_SAMPLER2D: {
					Texture* tex = std::any_cast<Texture*>(value);
					m_shader->SetUniform(name, texcount);
					if (tex) {
						tex->Bind(texcount);
					}
					texcount++;
					break;
				}
				default:
					break;
				}
			}
		}
		Shader* m_shader;
		std::unordered_map<std::string, std::any> m_uniforms;
	};
}