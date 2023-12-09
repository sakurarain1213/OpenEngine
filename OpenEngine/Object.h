#pragma once

#include <string>
#include <unordered_map>
#include <queue>
#include "GUID.h"

namespace OpenEngine {
	class Object {
	public:
		int GetInstanceID();
		std::string GetName();
		Object(std::string name);
		virtual void Destroy();
		virtual std::string GetType();
		virtual ~Object();
		static void DestroyQueuingObject();
		template<class T>
		static T* GetObject(int id) {
			if (__OBJECT_MAP.find(id) != __OBJECT_MAP.end()) {
				Object* obj = __OBJECT_MAP[id];
				if (!obj) return nullptr;
				if (typeid(*obj) == typeid(T)) {
					return (T*)obj;
				}
				else {
					return nullptr;
				}
			}
			return nullptr;
		}
		static std::string ClassType();

		std::string name;
	protected:
		int instanceID;
	private:
		bool is_destoryed;
		static int __OBJECT_INSTANCE_COUNT;
		static std::unordered_map<int, Object*> __OBJECT_MAP;
		static std::queue<Object*> __DESTROY_QUEUE;
 	};
}