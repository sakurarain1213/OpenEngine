#pragma once

#include <boost/serialization/unordered_map.hpp>
#include <boost/serialization/nvp.hpp>
#include <string>
#include "Math.h"
#include "ObjectReference.h"

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
		float GetPropertyFloat(std::string property) const {
			return std::stof(m_properties.find(property)->second);
		}
		Vec2 GetPropertyVec2(std::string property) const {
			std::stringstream stm(m_properties.find(property)->second);
			float val[2];
			stm >> val[0] >> val[1];
			return Vec2(val);
		}
		Vec3 GetPropertyVec3(std::string property) const {
			std::stringstream stm(m_properties.find(property)->second);
			float val[3];
			stm >> val[0] >> val[1] >> val[2];
			return Vec3(val);
		}
		Vec4 GetPropertyVec4(std::string property) const {
			std::stringstream stm(m_properties.find(property)->second);
			float val[4];
			stm >> val[0] >> val[1] >> val[2] >> val[3];
			return Vec4(val);
		}
		Mat4 GetPropertyMat4(std::string property) const {
			std::stringstream stm(m_properties.find(property)->second);
			float val[16];
			for (int i = 0;i < 16;++i)
				stm >> val[i];
			return Mat4(val);
		}
		ObjectReference GetPropertyObject(std::string property) const {
			std::stringstream stm(m_properties.find(property)->second);
			std::string guid, localid;
			stm >> guid >> localid;
			return ObjectReference(guid, std::stoi(localid));
		}
		void SetProperty(std::string property, std::string value) {
			m_properties[property] = value;
		}
		void SetProperty(std::string property, bool value) {
			m_properties[property] = (value ? "true" : "false");
		}
		void SetProperty(std::string property, int value) {
			m_properties[property] = std::to_string(value);
		}
		void SetProperty(std::string property, float value) {
			m_properties[property] = std::to_string(value);
		}
		void SetProperty(std::string property, Vec2 value) {
			m_properties[property] = std::to_string(value.x()) + "," + std::to_string(value.y());
		}
		void SetProperty(std::string property, Vec3 value) {
			m_properties[property] = std::to_string(value.x()) + "," + std::to_string(value.y()) + "," + std::to_string(value.z());
		}
		void SetProperty(std::string property, Vec4 value) {
			m_properties[property] = std::to_string(value.x()) + "," + std::to_string(value.y()) + "," + std::to_string(value.z()) + "," + std::to_string(value.w());
		}
		void SetProperty(std::string property, Mat4 value) {
			std::string data = "";
			for (int i = 0;i < 16;++i) {
				if (i) data += "";
				data += std::to_string(value.data()[i]);
			}
			m_properties[property] = data;
		}
		void SetProperty(std::string property, ObjectReference obj) {
			m_properties[property] = obj.guid.uid + " " + std::to_string(obj.localID);
		}
		void clear() {
			m_properties.clear();
		}

		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version) {
			ar& BOOST_SERIALIZATION_NVP(m_properties);
		}

	protected:
		std::unordered_map<std::string, std::string> m_properties;
	};
}