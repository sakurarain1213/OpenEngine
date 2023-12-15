#pragma once
#include"IComponent.h"
namespace OpenEngine {
	class Monobehaviour : public IComponent
	{
	public:
		int Initialize() {};
		void OnEnable(){};
		void FixedUpdate(){};
		void Update(){};
		void OnDisable(){};
		void Finalize(){};

	private:

	};
}
