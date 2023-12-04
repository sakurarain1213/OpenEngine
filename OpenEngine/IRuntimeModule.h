#pragma once
#include "Object.h"

namespace OpenEngine {
	class IRuntimeModule : public Object{
public:
	IRuntimeModule(std::string name) : Object(name) {
		
	}
	virtual ~IRuntimeModule() {};

	virtual int Initialize() = 0;
	virtual void Finalize() = 0;

	virtual void Tick() = 0;
	virtual std::string GetType() { return "IRuntimeModuel"; };
	};
}

