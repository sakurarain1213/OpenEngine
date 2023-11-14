#include <any>
#include <unordered_map>
#include <string>

namespace OpenEngine::Setting {
	class Setting {
	public:
		template <typename T>
		T GetProperty(uint8_t property_id) {
			return std::any_cast<T>(m_properties[property_id]);
		}
		template <typename T>
		T SetProperty(uint8_t property_id, T value) {
			return m_properties[property_id] = value;
		}
	private:
		std::unordered_map<std::string, std::any> m_properties;
	};
}