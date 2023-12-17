#pragma once
#include"IComponent.h"
namespace OpenEngine {
	class MonoBehaviour : public IComponent
	{
	public:
		MonoBehaviour(Entity* entity);
		~MonoBehaviour();

		int Initialize() { return 0; };
		void OnEnable(){};
		void FixedUpdate(){};
		void Update(){};
		void OnDisable(){};
		void Finalize(){};
		void OnCollision() {};

		void SetActive(bool state);
	private:

	};
}
