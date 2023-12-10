#pragma once

#include "IAssetImporter.h"
#include "ObjectReference.h"
#include "PropertyMap.h"
#include "Material.h"
#include "ServiceLocator.h"
#include "AssetDatabase.hpp"
#include <fstream>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

namespace OpenEngine::Importer {

	struct MaterialSerilized {
		Setting::ObjectReference shader;
		Setting::PropertyMap uniforms;

		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version) {
			ar& BOOST_SERIALIZATION_NVP(shader);
			ar& BOOST_SERIALIZATION_NVP(uniforms);
		}
	 };

	class MaterialImporter : public IAssetImporter {
	public:
		MaterialImporter() {
			supported_extensions.push_back(".material");
		}
		std::vector<int> Import(std::string path, const Setting::ImportSetting& importSetting) {
			std::ifstream ifs(path);
			MaterialSerilized material;
			{
				boost::archive::xml_iarchive ia(ifs);
				ia >> BOOST_SERIALIZATION_NVP(material);
			}
			ifs.close();
			Shader* shader = OESERVICE(Editor::AssetDatabase).GetAsset<Shader>(material.shader.guid, material.shader.localID);
			Material* mat = new Material(shader, importSetting.GetProperty("name"));
			std::unordered_map<std::string, std::any>& uniforms = mat->m_uniforms;
			for (auto it : uniforms) {
				std::string name = it.first;
				std::any& slot = it.second;
				size_t type = slot.type().hash_code();
				if (type == typeid(bool).hash_code()) {
					slot = std::make_any<bool>(material.uniforms.GetPropertyBool(name));
				}
				else if (type == typeid(int).hash_code()) {
					slot = std::make_any<int>(material.uniforms.GetPropertyInt(name));
				}
				else if (type == typeid(float).hash_code()) {
					slot = std::make_any<float>(material.uniforms.GetPropertyFloat(name));
				}
				else if (type == typeid(Vec2).hash_code()) {
					slot = std::make_any<Vec2>(material.uniforms.GetPropertyVec2(name));
				}
				else if (type == typeid(Vec3).hash_code()) {
					slot = std::make_any<Vec3>(material.uniforms.GetPropertyVec3(name));
				}
				else if (type == typeid(Vec4).hash_code()) {
					slot = std::make_any<Vec4>(material.uniforms.GetPropertyVec4(name));
				}
				else if (type == typeid(Mat4).hash_code()) {
					slot = std::make_any<Mat4>(material.uniforms.GetPropertyMat4(name));
				}
				else if (type == typeid(Texture*).hash_code()) {
					Setting::ObjectReference objRef = material.uniforms.GetPropertyObject(name);
					Texture* tex = OESERVICE(Editor::AssetDatabase).GetAsset<Texture>(objRef.guid, objRef.localID);
					slot = std::make_any<Texture*>(tex);
				}
			}
			std::vector<int> ret;
			ret.push_back(mat->GetInstanceID());
			return ret;
		}
		Setting::ImportSetting GetDefaultSetting() {
			Setting::ImportSetting setting;
			setting.SetProperty("type", "Material");
			return setting;
		}
		void Save(std::string path, Object* obj) {
			if (typeid(*obj) != typeid(Material)) {
				OE_WARNING("[MaterialImporter] " + obj->name + " is not instance of Material");
				return;
			}
			Material* matraw = (Material*)obj;
			MaterialSerilized material;
			material.shader = OESERVICE(Editor::AssetDatabase).GetObjectReference(matraw->m_shader);
			for (auto it : matraw->m_uniforms) {
				std::string name = it.first;
				std::any& slot = it.second;
				size_t type = slot.type().hash_code();
				if (type == typeid(bool).hash_code()) {
					material.uniforms.SetProperty(name, std::any_cast<bool>(slot));
				}
				else if (type == typeid(int).hash_code()) {
					material.uniforms.SetProperty(name, std::any_cast<int>(slot));
				}
				else if (type == typeid(float).hash_code()) {
					material.uniforms.SetProperty(name, std::any_cast<float>(slot));
				}
				else if (type == typeid(Vec2).hash_code()) {
					material.uniforms.SetProperty(name, std::any_cast<Vec2>(slot));
				}
				else if (type == typeid(Vec3).hash_code()) {
					material.uniforms.SetProperty(name, std::any_cast<Vec3>(slot));
				}
				else if (type == typeid(Vec4).hash_code()) {
					material.uniforms.SetProperty(name, std::any_cast<Vec4>(slot));
				}
				else if (type == typeid(Mat4).hash_code()) {
					material.uniforms.SetProperty(name, std::any_cast<Mat4>(slot));
				}
				else if (type == typeid(Texture*).hash_code()) {
					Setting::ObjectReference objRef = OESERVICE(Editor::AssetDatabase).GetObjectReference(std::any_cast<Texture*>(slot));
					material.uniforms.SetProperty(name, std::any_cast<Setting::ObjectReference>(objRef));
				}
			}
			std::ofstream ofs(path);
			{
				boost::archive::xml_oarchive oa(ofs);
				oa << BOOST_SERIALIZATION_NVP(material);
			}
			ofs.close();
		}
		void Create(std::string path) {
			Material mat;
			Save(path, &mat);
		}
	};
}