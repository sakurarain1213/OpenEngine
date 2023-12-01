#pragma once

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/serialization/access.hpp>

namespace OpenEngine {
	struct GUID {
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version) {
			ar& uid;
		}
		std::string uid;
		GUID() {
			uid = boost::uuids::to_string(boost::uuids::random_generator()());
		}
		GUID(std::string s) {
			uid = s;
		}
	};
}