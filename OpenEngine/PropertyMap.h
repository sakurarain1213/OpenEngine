#pragma once

#include <unordered_map>
#include <string>

namespace OpenEngine::Setting {
	class PropertyMap {
	public:
		std::string GetProperty(std::string property) {
			return m_properties[property];
		}
		void SetProperty(std::string property, std::string value) {
			m_properties[property] = value;
		}
		void clear() {
			m_properties.clear();
		}
	private:
		std::unordered_map<std::string, std::string> m_properties;
	};
}