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
		bool enableDepthTest;
		bool enableDepthWrite;
		TestFunc depthFunc;
		bool enableStencilTest;
		uint8_t stencilMask;
		TestFunc stencilFunc;
		uint8_t stencilFuncRef;
		uint8_t stencilFuncMask;
		TestOperation stencilFailOperation;
		TestOperation stencilDeepTestFailOperation;
		TestOperation stencilPassOperation;
		bool enableBlend;
		BlendFunc blendSrcFunc;
		BlendFunc blendDstFunc;
		bool enableCullFace;
		bool cullFaceFront;
		bool cullFaceBack;
		bool frontFaceCCW;

		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version) {
			ar& BOOST_SERIALIZATION_NVP(shader);
			ar& BOOST_SERIALIZATION_NVP(uniforms);
			ar& BOOST_SERIALIZATION_NVP(enableDepthTest);
			ar& BOOST_SERIALIZATION_NVP(enableDepthWrite);
			ar& BOOST_SERIALIZATION_NVP(depthFunc);
			ar& BOOST_SERIALIZATION_NVP(enableStencilTest);
			ar& BOOST_SERIALIZATION_NVP(stencilMask);
			ar& BOOST_SERIALIZATION_NVP(stencilFunc);
			ar& BOOST_SERIALIZATION_NVP(stencilFuncRef);
			ar& BOOST_SERIALIZATION_NVP(stencilFuncMask);
			ar& BOOST_SERIALIZATION_NVP(stencilFailOperation);
			ar& BOOST_SERIALIZATION_NVP(stencilDeepTestFailOperation);
			ar& BOOST_SERIALIZATION_NVP(stencilPassOperation);
			ar& BOOST_SERIALIZATION_NVP(enableBlend);
			ar& BOOST_SERIALIZATION_NVP(blendSrcFunc);
			ar& BOOST_SERIALIZATION_NVP(blendDstFunc);
			ar& BOOST_SERIALIZATION_NVP(enableCullFace);
			ar& BOOST_SERIALIZATION_NVP(cullFaceFront);
			ar& BOOST_SERIALIZATION_NVP(cullFaceBack);
			ar& BOOST_SERIALIZATION_NVP(frontFaceCCW);
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

			mat->enableDepthTest = material.enableDepthTest;
			mat->enableDepthWrite = material.enableDepthWrite;
			mat->depthFunc = material.depthFunc;
			mat->enableStencilTest = material.enableStencilTest;
			mat->stencilMask = material.stencilMask;
			mat->stencilFunc = material.stencilFunc;
			mat->stencilFuncRef = material.stencilFuncRef;
			mat->stencilFuncMask = material.stencilFuncMask;
			mat->stencilFailOperation = material.stencilFailOperation;
			mat->stencilDeepTestFailOperation = material.stencilDeepTestFailOperation;
			mat->stencilPassOperation = material.stencilPassOperation;
			mat->enableBlend = material.enableBlend;
			mat->blendSrcFunc = material.blendSrcFunc;
			mat->blendDstFunc = material.blendDstFunc;
			mat->enableCullFace = material.enableCullFace;
			mat->cullFaceFront = material.cullFaceFront;
			mat->cullFaceBack = material.cullFaceBack;
			mat->frontFaceCCW = material.frontFaceCCW;

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
			material.enableDepthTest = matraw->enableDepthTest;
			material.enableDepthWrite = matraw->enableDepthWrite;
			material.depthFunc = matraw->depthFunc;
			material.enableStencilTest = matraw->enableStencilTest;
			material.stencilMask = matraw->stencilMask;
			material.stencilFunc = matraw->stencilFunc;
			material.stencilFuncRef = matraw->stencilFuncRef;
			material.stencilFuncMask = matraw->stencilFuncMask;
			material.stencilFailOperation = matraw->stencilFailOperation;
			material.stencilDeepTestFailOperation = matraw->stencilDeepTestFailOperation;
			material.stencilPassOperation = matraw->stencilPassOperation;
			material.enableBlend = matraw->enableBlend;
			material.blendSrcFunc = matraw->blendSrcFunc;
			material.blendDstFunc = matraw->blendDstFunc;
			material.enableCullFace = matraw->enableCullFace;
			material.cullFaceFront = matraw->cullFaceFront;
			material.cullFaceBack = matraw->cullFaceBack;
			material.frontFaceCCW = matraw->frontFaceCCW;

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