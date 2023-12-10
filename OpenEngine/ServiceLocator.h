#pragma once

#include <unordered_map>
#include <string>
#include <typeinfo>
#include <any>
#include "Logger.h"

#define OESERVICE(T) (OpenEngine::ServiceLocator::GetService<T>())

namespace OpenEngine {
	class ServiceLocator {
	public:
		template <class T>
		static void RegisterService(T& service) {
			__SERVICE_LOCATOR_MAP[typeid(T).hash_code()] = std::make_any<T*>(&service);
		}
		template <class T>
		static T& GetService() {
			if (__SERVICE_LOCATOR_MAP.find(typeid(T).hash_code()) != __SERVICE_LOCATOR_MAP.end()) {
				return *std::any_cast<T*>(__SERVICE_LOCATOR_MAP.at(typeid(T).hash_code()));
			}
			else {
				OE_ERROR("Service " + std::string(typeid(T).name()) + " is not found");
			}
		}
	private:
		static std::unordered_map<size_t, std::any> __SERVICE_LOCATOR_MAP;
	};
}