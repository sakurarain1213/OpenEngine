#pragma once

#include "Object.h"
#include "ImportSetting.h"

namespace OpenEngine::Importer {
	class IAssetImporter {
	public:
		virtual std::vector<int> Import(std::string path, const Setting::ImportSetting& importSetting) = 0;
		virtual void Save(std::string path, Object* obj) = 0;
		virtual void Create(std::string path) = 0;
		virtual Setting::ImportSetting GetDefaultSetting() = 0;
		std::vector<std::string> supported_extensions;
	};
}