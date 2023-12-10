#pragma once

#include "GUID.h"

namespace OpenEngine::Setting {
	struct ObjectReference {

		GUID guid;
		int localID;

		ObjectReference() :
			guid("#"),localID(0) {}

		ObjectReference(std::string guid, int localID) :
			guid(guid),
			localID(localID) {}

		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version) {
			ar& BOOST_SERIALIZATION_NVP(guid);
			ar& BOOST_SERIALIZATION_NVP(localID);
		}
	};
}