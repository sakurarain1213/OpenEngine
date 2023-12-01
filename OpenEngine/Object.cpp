#pragma once

#include "Object.h"

namespace OpenEngine {
	int Object::GetInstanceID() {
		return instanceID;
	}
	std::string Object::GetName() {
		return name;
	}
	Object::Object(std::string name) {
		this->name = name;
		instanceID = ++__OBJECT_INSTANCE_COUNT;
		__OBJECT_MAP[instanceID] = this;
	}
	void Object::Destroy() {
		if (!is_destoryed) {
			is_destoryed = true;
			__DESTROY_QUEUE.push(this);
		}
	}
	std::string Object::GetType() {
		return "Object";
	}
	Object::~Object() {
		__OBJECT_MAP[instanceID] = nullptr;
	}
	void Object::DestroyQueuingObject() {
		while (!__DESTROY_QUEUE.empty()) {
			delete __DESTROY_QUEUE.front();
			__DESTROY_QUEUE.pop();
		}
	}
	std::string Object::ClassType() {
		return "Object";
	}

	int Object::__OBJECT_INSTANCE_COUNT = 0;
	std::unordered_map<int, Object*> Object::__OBJECT_MAP;
	std::queue<Object*> Object::__DESTROY_QUEUE;
}