#pragma once

#include "PropertyMap.h"
#include "GUID.h"

namespace OpenEngine::Setting {
	class ImportSetting : public PropertyMap {
	public:
		GUID GetGUID() const {
			return guid;
		}
		ImportSetting() : guid() {}
	private:
	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version) {
			ar& guid;
			ar& m_properties;
		}
		GUID guid;
	};
}