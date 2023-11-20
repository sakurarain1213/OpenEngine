#pragma once

#include <fstream>
#include <string>
#include "PropertyMap.h"
#include "Logger.h"

namespace OpenEngine {
	class IniFile : Setting::PropertyMap {
	public:
		IniFile(std::string path) {
			OE_WARNING("Open project setting : " + path);
			file.open(path);
			Reload();
		}
		void Reload();
		std::string GetString(std::string section_name, std::string property_name);
		int GetInt(std::string section_name, std::string property_name);
		bool Getbool(std::string section_name, std::string property_name);
	private:
		std::fstream file;
	};
}