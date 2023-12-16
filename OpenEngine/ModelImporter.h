#pragma once

#include "IAssetImporter.h"
#include "Logger.h"
#include "Entity.h"
#include "Mesh.h"
#include "Material.h"
#include "ServiceLocator.h"
#include "AssetDatabase.hpp"
#include "StringConvert.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace OpenEngine::Importer {
	class ModelImporter : public IAssetImporter {
	public:
		ModelImporter() {
			supported_extensions.push_back(".pmx");
		}
		std::vector<int> Import(std::string path, const Setting::ImportSetting& importSetting) {
			Assimp::Importer importer;
			std::vector<int> ret;
			const aiScene* scene = importer.ReadFile(AnsiToUtf8(path), aiProcess_Triangulate | aiProcess_FlipUVs);
			if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
			{
				OE_ERROR("[ModelImporter] Assimp::" + std::string(importer.GetErrorString()));
				return ret;
			}
			Entity* root = new Entity(importSetting.GetProperty("name"));
			ProcessNode(scene->mRootNode, scene, root);
			ret.push_back(root->GetInstanceID());
			return ret;
		}
		Setting::ImportSetting GetDefaultSetting() {
			Setting::ImportSetting setting;
			setting.SetProperty("type", "Model");
			return setting;
		}
		void Save(std::string path, Object* obj) {
			OE_WARNING("[ModelImporter] " + obj->name + " can't be exported");
		}
		void Create(std::string path) {
			OE_WARNING("[ModelImporter] can't create texture");
		}
	private:
		void ProcessNode(aiNode* node, const aiScene* scene,Entity* parent) {
			for (int i = 0;i < node->mNumMeshes;++i) {
				aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
				Entity* cur = new Entity("SubMesh" + std::to_string(i));
				cur->SetParent(parent);
				MeshRendererComponent* meshRenderer = cur->AddComponent<MeshRendererComponent>();
				meshRenderer->SetMesh(ProcessMesh(mesh, scene));
				meshRenderer->SetMaterial(ProcessMaterial(mesh, scene));
			}
			for (int i = 0;i < node->mNumChildren;++i) {
				Entity* cur = new Entity("Child" + std::to_string(i));
				cur->SetParent(parent);
				ProcessNode(node->mChildren[i], scene, cur);  
			}
		}
		Mesh* ProcessMesh(aiMesh* mesh, const aiScene *scene) {
			std::vector<Vertex> vertices;
			std::vector<uint32_t> indices;
			for (int i = 0;i < mesh->mNumVertices; ++i) {
				Vertex vertex;
				vertex.position.x() = mesh->mVertices[i].x;
				vertex.position.y() = mesh->mVertices[i].y;
				vertex.position.z() = mesh->mVertices[i].z;
				vertex.normal.x() = mesh->mNormals[i].x;
				vertex.normal.y() = mesh->mNormals[i].y;
				vertex.normal.z() = mesh->mNormals[i].z;
				if (mesh->mTangents) {
					vertex.tangent.x() = mesh->mTangents[i].x;
					vertex.tangent.y() = mesh->mTangents[i].y;
					vertex.tangent.z() = mesh->mTangents[i].z;
				}
				if (mesh->mTextureCoords[0]) {
					vertex.texCoords.x() = mesh->mTextureCoords[0][i].x;
					vertex.texCoords.y() = mesh->mTextureCoords[0][i].y;
				}
				vertices.push_back(vertex);
			}
			for (int i = 0;i < mesh->mNumFaces;++i) {
				aiFace face = mesh->mFaces[i];
				for (int j = 0;j < face.mNumIndices;++j)
					indices.push_back(face.mIndices[j]);
			}
			return new Mesh(vertices, indices);
		}
		Material* ProcessMaterial(aiMesh* mesh, const aiScene* scene) {
			Material* mat = new Material(OESERVICE(Editor::AssetDatabase).GetAsset<Shader>("standard.shader", 0));
			if (mesh->mMaterialIndex >= 0) {
				aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
				if (material->GetTextureCount(aiTextureType_DIFFUSE)) {
					aiString str;
					material->GetTexture(aiTextureType_DIFFUSE, 0, &str);
					std::string str_ansi = Utf8ToAnsi(str.C_Str());
					OE_INFO("[ModelImporter] Texture load from " + str_ansi);
					Texture* tex = OESERVICE(Editor::AssetDatabase).GetAsset<Texture>(str_ansi, 0);
					mat->SetUniform<Texture*>("diffuseMap", tex);
				}
			}
			return mat;
		}
	};
}