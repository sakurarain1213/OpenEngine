#include "IniFile.h"

namespace OpenEngine {
	std::string trim(std::string s) {
		if (s.empty()) {
			return s;
		}
		s.erase(0, s.find_first_not_of(" \t\r\n"));
		s.erase(s.find_last_not_of(" \t\r\n") + 1);
		return s;
	}

	void IniFile::Reload() {
		clear();
		if (!file.is_open())
			return;
		std::string line;
		std::string section_name = "";
		while (!file.eof()) {
			std::getline(file, line);
			line = trim(line);
			if (!line.length()) continue;
			if (line[0] == '[') {
				for (int i = 1;i < line.length();++i) {
					if (line[i] == ']') {
						section_name = trim(line.substr(1, i - 1));
						break;
					}
				}
			}
			else if (line[0] == ';') {
				continue;
			}
			else {
				int equcnt = 0;
				int equpos = 0;
				for (int i = 0;i < line.length();++i) {
					if (line[i] == '=') {
						equcnt++;
						equpos = i;
						if (equcnt > 1) break;
					}
				}
				if (equcnt == 1) {
					std::string property = trim(line.substr(0, equpos));
					std::string value = trim(line.substr(equpos + 1, line.length() - equpos - 1));
					OE_INFO("SetProperty: " + section_name + '.' + property + " , " + value);
					SetProperty(section_name + '.' + property, value);
				}
			}
		}
	}

	std::string IniFile::GetString(std::string section_name, std::string property_name) {
		return GetProperty(section_name + '.' + property_name);
	}

	int IniFile::GetInt(std::string section_name, std::string property_name) {
		return std::stoi(GetProperty(section_name + '.' + property_name));
	}

	bool IniFile::Getbool(std::string section_name, std::string property_name) {
		return GetProperty(section_name + '.' + property_name) == "true";
	}
}