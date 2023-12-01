#pragma once

#include "Object.h"
#include "ImportSetting.h"

namespace OpenEngine::Importer {
	class IAssetImporter {
	public:
		virtual std::vector<int> Import(std::string path, const Setting::ImportSetting& importSetting) = 0;
		virtual Setting::ImportSetting GetDefaultSetting() = 0;
		std::vector<std::string> supported_extensions;
	};
}