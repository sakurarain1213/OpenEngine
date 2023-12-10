#pragma once

#include "AssetDatabase.hpp"
#include "AssetImporter.h"

namespace OpenEngine::Editor {

	AssetDatabase::AssetDatabase(std::string path) {
		assetPath = path;
		m_assetImporter = new Importer::AssetImporter();
		Initialize();
	}
	AssetDatabase::~AssetDatabase() {
		delete m_assetImporter;
	}
	Setting::ObjectReference AssetDatabase::GetObjectReference(Object* obj) {
		Setting::ObjectReference ref;
		if (Exist(obj)) {
			ref.guid = __OBJECT_TO_GUID_MAP[obj->GetInstanceID()];
			ref.localID = __OBJECT_TO_LOCALID_MAP[obj->GetInstanceID()];
		}
		return ref;
	}
	void AssetDatabase::ImportAsset(GUID guid) {
		if (__OBJECT_MAP.find(guid.uid) != __OBJECT_MAP.end()) return;
		if (__IMPORTPATH_MAP.find(guid.uid) != __IMPORTPATH_MAP.end()) {
			const std::vector<int>& objlist = m_assetImporter->Import(__IMPORTPATH_MAP[guid.uid], __IMPORTSETTING_MAP[guid.uid]);
			__OBJECT_MAP[guid.uid] = objlist;
			for (int i = 0; i < objlist.size(); ++i) {
				__OBJECT_TO_GUID_MAP[objlist[i]] = guid.uid;
				__OBJECT_TO_LOCALID_MAP[objlist[i]] = i;
			}
			OE_INFO(__IMPORTPATH_MAP[guid.uid] + " imported");
		}
		else {
			OE_WARNING("Asset with GUID " + guid.uid + " is not found");
		}
	}
	bool AssetDatabase::Exist(Object* obj) {
		if (!obj) return false;
		return __OBJECT_TO_GUID_MAP.find(obj->GetInstanceID()) != __OBJECT_TO_GUID_MAP.end();
	}
	bool AssetDatabase::ExistPath(std::string path) {
		return __PATH_TO_GUID_MAP.find(path) != __PATH_TO_GUID_MAP.end();
	}
	void AssetDatabase::CreateAsset(std::string path) {
		path = assetPath + "/" + path;
		if (!m_assetImporter->CanImport(path)) {
			OE_WARNING("[AssetDatabase::CreateAsset] " + path + " can't be created");
			return;
		}
		if (!ExistPath(path)) {
			CreateMetaFile(path);
			Setting::ImportSetting setting = LoadMetaFile(path);
			__IMPORTSETTING_MAP[setting.GetGUID().uid] = setting;
			__IMPORTPATH_MAP[setting.GetGUID().uid] = path;
			__PATH_TO_GUID_MAP[path] = setting.GetGUID().uid;
			m_assetImporter->Create(path);
			OE_INFO(path + " created");
			ImportAsset(setting.GetGUID().uid);
		}
		else {
			OE_WARNING("[AssetDatabase::CreateAsset] " + path + " is exist in assets");
		}
	}
	void AssetDatabase::Save(Object* obj) {
		if (!obj) {
			OE_WARNING("[AssetDatabase::Save] Object is not an instance");
			return;
		}
		if (!Exist(obj)) {
			OE_WARNING("[AssetDatabase::CreateAsset] Object " + obj->name + " is not exist in assets");
			return;
		}
		std::string uid = __OBJECT_TO_GUID_MAP[obj->GetInstanceID()];
		std::string path = __IMPORTPATH_MAP[uid];
		const Setting::ImportSetting& setting = __IMPORTSETTING_MAP[uid];
		SaveMetaFile(uid, setting);
		m_assetImporter->Save(path, obj);
		OE_INFO(obj->name  + " saved");
	}
	void AssetDatabase::ImportAllAssets() {
		for (auto it : __IMPORTSETTING_MAP) {
			ImportAsset(it.first);
		}
	}

	void AssetDatabase::CreateMetaFile(std::string path) {
		if (!m_assetImporter->CanImport(path)) return;
		std::ofstream fs(path + ".meta");
		if (!fs) {
			OE_ERROR(path + ".meta" + " can't be created");
			return;
		}
		Setting::ImportSetting setting = m_assetImporter->GetDefaultSetting(path);
		{
			boost::archive::xml_oarchive oa(fs);
			oa << BOOST_SERIALIZATION_NVP(setting);
		}
		fs.close();
	}
	Setting::ImportSetting AssetDatabase::LoadMetaFile(std::string path) {
		std::ifstream fs(path + ".meta");
		if (!fs) {
			OE_ERROR(path + ".meta" + " can't open");
			return Setting::ImportSetting();
		}
		Setting::ImportSetting setting;
		{
			boost::archive::xml_iarchive ia(fs);
			ia >> BOOST_SERIALIZATION_NVP(setting);
		}
		fs.close();
		return setting;
	}
	void AssetDatabase::SaveMetaFile(std::string path, const Setting::ImportSetting& setting) {
		std::ofstream fs(path + ".meta");
		if (!fs) {
			OE_ERROR(path + ".meta" + " can't open");
			return;
		}
		{
			boost::archive::xml_oarchive oa(fs);
			oa << BOOST_SERIALIZATION_NVP(setting);
		}
		fs.close();
	}
	void AssetDatabase::Initialize() {
		boost::filesystem::path path(assetPath);
		if (!boost::filesystem::exists(path)) {
			OE_WARNING("Directory \'" + assetPath + "\' is not found");
			return;
		}
		boost::filesystem::recursive_directory_iterator end_iter;
		std::vector<std::string> ret;
		for (boost::filesystem::recursive_directory_iterator itr(path);itr != end_iter;itr++) {
			try {
				if (!boost::filesystem::is_directory(*itr)) {
					if (itr->path().extension().string() != ".meta") {
						ret.push_back(itr->path().string());
					}
				}
			}
			catch (const std::exception& ex) {
				OE_ERROR(ex.what());
				continue;
			}
		}
		for (int i = 0;i < ret.size(); ++i) {
			if (!m_assetImporter->CanImport(ret[i])) continue;
			std::string metaFile = ret[i] + ".meta";
			if (!boost::filesystem::exists(boost::filesystem::path(metaFile))) {
				CreateMetaFile(ret[i]);
			}
			Setting::ImportSetting setting = LoadMetaFile(ret[i]);
			__IMPORTSETTING_MAP[setting.GetGUID().uid] = setting;
			__IMPORTPATH_MAP[setting.GetGUID().uid] = ret[i];
			__PATH_TO_GUID_MAP[ret[i]] = setting.GetGUID().uid;
		}
	}
}