#pragma once

#include <boost/serialization/unordered_map.hpp>
#include <string>

namespace OpenEngine::Setting {
	class PropertyMap {
	public:
		std::string GetProperty(std::string property) const {
			return m_properties.find(property)->second;
		}
		bool GetPropertyBool(std::string property) const {
			return m_properties.find(property)->second == "true";
		}
		int GetPropertyInt(std::string property) const {
			return std::stoi(m_properties.find(property)->second);
		}
		void SetProperty(std::string property, std::string value) {
			m_properties[property] = value;
		}
		void SetProperty(std::string property, int value) {
			m_properties[property] = std::to_string(value);
		}
		void clear() {
			m_properties.clear();
		}
	protected:
		std::unordered_map<std::string, std::string> m_properties;
	};
}