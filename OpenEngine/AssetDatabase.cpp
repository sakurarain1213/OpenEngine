#pragma once

#include "AssetDatabase.hpp"

namespace OpenEngine::Editor {

	void AssetDatabase::CreateMetaFile(std::string path) {
		if (!m_assetImporter.CanImport(path)) return;
		std::ofstream fs(path + ".meta");
		if (!fs) {
			OE_ERROR(path + ".meta" + " can't be created");
			return;
		}
		boost::archive::text_oarchive oa(fs);
		Setting::ImportSetting setting = m_assetImporter.GetDefaultSetting(path);
		oa << setting;
		fs.close();
	}
	Setting::ImportSetting AssetDatabase::LoadMetaFile(std::string path) {
		std::ifstream fs(path + ".meta");
		if (!fs) {
			OE_ERROR(path + ".meta" + " can't open");
			return Setting::ImportSetting();
		}
		boost::archive::text_iarchive ia(fs);
		Setting::ImportSetting setting;
		ia >> setting;
		fs.close();
		return setting;
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
			std::string metaFile = ret[i] + ".meta";
			if (!boost::filesystem::exists(boost::filesystem::path(metaFile))) {
				CreateMetaFile(ret[i]);
			}
			Setting::ImportSetting setting = LoadMetaFile(ret[i]);
			__IMPORTSETTING_MAP[setting.GetGUID().uid] = setting;
			__IMPORTPATH_MAP[setting.GetGUID().uid] = ret[i];
		}
	}
}