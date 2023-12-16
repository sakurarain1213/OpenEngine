#pragma once

#include "Object.h"
#include "ImportSetting.h"
#include "Logger.h"
#include <boost/filesystem.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <fstream>

namespace OpenEngine::Importer { class AssetImporter; }

namespace OpenEngine::Editor {

	class AssetDatabase {
	public:
		AssetDatabase(std::string path);
		~AssetDatabase();
		template <class T>
		T* GetAsset(GUID guid, uint32_t localid) {
			if (guid.uid == "#") return nullptr;
			if (__OBJECT_MAP.find(guid.uid) == __OBJECT_MAP.end()) {
				ImportAsset(guid);
			}
			const std::vector<int>& assets = __OBJECT_MAP[guid.uid];
			if (assets.size() <= localid) return nullptr;
			else {
				return Object::GetObject<T>(assets[localid]);
			}
		}
		template <class T>
		T* GetAsset(std::string path, uint32_t localid) {
			path = assetPath + "\\" + path;
			if (__PATH_TO_GUID_MAP.find(path) == __PATH_TO_GUID_MAP.end()) {
				return nullptr;
			}
			return GetAsset<T>(GUID(__PATH_TO_GUID_MAP.at(path)), localid);
		}
		Setting::ObjectReference GetObjectReference(Object* obj);
		void ImportAsset(GUID guid);
		void ImportAllAssets();
		bool Exist(Object* obj);
		bool ExistPath(std::string path);
		void CreateAsset(std::string path);
		void Save(Object* obj);
	private:
		std::string assetPath;
		std::unordered_map<std::string, Setting::ImportSetting> __IMPORTSETTING_MAP;
		std::unordered_map<std::string, std::string> __IMPORTPATH_MAP;
		std::unordered_map<std::string, std::vector<int>> __OBJECT_MAP;
		std::unordered_map<std::string, std::string> __PATH_TO_GUID_MAP;
		std::unordered_map<int, std::string> __OBJECT_TO_GUID_MAP;
		std::unordered_map<int, int> __OBJECT_TO_LOCALID_MAP;
		Importer::AssetImporter* m_assetImporter;
		void CreateMeta(std::string path);
		void SaveMeta(std::string path, const Setting::ImportSetting& setting);
		Setting::ImportSetting LoadMeta(std::string path);
		void Initialize();
	};
}