#pragma once

#include "Object.h"
#include "ImportSetting.h"
#include "Logger.h"
#include "AssetImporter.h"
#include <boost/filesystem.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <fstream>

namespace OpenEngine::Editor {
	class AssetDatabase {
	public:
		AssetDatabase(std::string path) {
			assetPath = path;
			Initialize();
		}
		template <class T>
		T* GetAsset(GUID guid, uint32_t localid) {
			if (__OBJECT_MAP.find(guid.uid) == __OBJECT_MAP.end()) {
				ImportAsset(guid);
			}
			const std::vector<int>& assets = __OBJECT_MAP[guid.uid];
			if (assets.size() <= localid) return nullptr;
			else {
				return Object::GetObject(assets[localid]);
			}
		}
		void ImportAsset(GUID guid) {
			if (__IMPORTPATH_MAP.find(guid.uid) != __IMPORTPATH_MAP.end()) { 
				__OBJECT_MAP[guid.uid] = m_assetImporter.Import(__IMPORTPATH_MAP[guid.uid], __IMPORTSETTING_MAP[guid.uid]);
			}
		}
		void ImportAllAssets() {
			for (auto it : __IMPORTSETTING_MAP) {
				ImportAsset(it.first);
			}
		}
	private:
		std::string assetPath;
		std::unordered_map<std::string, Setting::ImportSetting> __IMPORTSETTING_MAP;
		std::unordered_map<std::string, std::string> __IMPORTPATH_MAP;
		std::unordered_map<std::string, std::vector<int>> __OBJECT_MAP;
		Importer::AssetImporter m_assetImporter;
		void CreateMetaFile(std::string path);
		Setting::ImportSetting LoadMetaFile(std::string path);
		void Initialize();
	};
}