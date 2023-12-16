#pragma once

#include "IAssetImporter.h"
#include "Logger.h"
#include "Entity.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace OpenEngine::Importer {
	class ModelImporter : public IAssetImporter {
	public:
		std::vector<int> Import(std::string path, const Setting::ImportSetting& importSetting) {
			Assimp::Importer importer;
			const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
			if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
			{
				OE_ERROR("[ModelImporter] Assimp::" + std::string(importer.GetErrorString()));
				return;
			}
			Entity* root = new Entity(importSetting.GetProperty("name"));
			ProcessNode(scene->mRootNode, scene, root);
		}
	private:
		void ProcessNode(aiNode* node, const aiScene* scene,Entity* parent) {
			for (int i = 0;i < node->mNumMeshes;++i) {
				aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
				Entity* cur = new Entity("SubMesh" + std::to_string(i));
				cur->SetParent(parent);
				MeshRendererComponent* meshRenderer = new MeshRendererComponent();
				meshRenderer->SetMesh();
				cur->AddComponent<MeshRendererComponent>()
			}
			for (int i = 0;i < node->mNumChildren;++i) {
				Entity* cur = new Entity("Child" + std::to_string(i));
				cur->SetParent(parent);
				ProcessNode(node->mChildren[i], scene, cur);  
			}
		}
		void ProcessMesh() {

		}
	};
}