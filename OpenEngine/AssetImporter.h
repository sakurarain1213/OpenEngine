#pragma once

#include "TextureImporter.h"
#include "ShaderImporter.h"
#include <boost/filesystem.hpp>

namespace OpenEngine::Importer {
	class AssetImporter {
	public:
		AssetImporter() {
			m_importers.push_back(std::make_unique<TextureImporter>());
			m_importers.push_back(std::make_unique<ShaderImporter>());
			for (int i = 0;i < m_importers.size();++i) {
				for (int j = 0;j < m_importers[i]->supported_extensions.size();++j)
					m_importer_map[m_importers[i]->supported_extensions[j]] = i;
			}
		}
		std::vector<int> Import(std::string path, const Setting::ImportSetting& importSetting) {
			boost::filesystem::path assetPath(path);
			std::string extension = assetPath.extension().string();
			if (m_importer_map.find(extension) != m_importer_map.end()) {
				return m_importers[m_importer_map[extension]]->Import(path, importSetting);
			}
		}
		Setting::ImportSetting GetDefaultSetting(std::string path) {
			boost::filesystem::path assetPath(path);
			std::string extension = assetPath.extension().string();
			if (m_importer_map.find(extension) != m_importer_map.end()) {
				Setting::ImportSetting setting = m_importers[m_importer_map[extension]]->GetDefaultSetting();
				setting.SetProperty("name", assetPath.filename().string());
				return setting;
			}
		}
		bool CanImport(std::string path) {
			boost::filesystem::path assetPath(path);
			std::string extension = assetPath.extension().string();
			return m_importer_map.find(extension) != m_importer_map.end();
		}
	private:
		std::unordered_map<std::string, int> m_importer_map;
		std::vector<std::unique_ptr<IAssetImporter>> m_importers;
	};
}