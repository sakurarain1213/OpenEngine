#pragma once

#include <string>

namespace OpenEngine::Asset {
	class IAsset {
		std::string path;
		std::string name;
		virtual void Load() = 0;
		virtual void Unload() = 0;
		virtual void Reload() = 0;
	};
}