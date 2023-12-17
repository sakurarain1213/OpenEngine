#pragma once
#include"IComponent.h"
namespace OpenEngine {
	class MonoBehaviour : public IComponent
	{
	public:
		MonoBehaviour(Entity* entity);
		~MonoBehaviour();

		virtual int Initialize() { return 0; };
		virtual void OnEnable(){};
		virtual void FixedUpdate(){};
		virtual	 void Update(){};
		virtual void OnDisable(){};
		virtual void Finalize(){};
		virtual void OnCollision() {};
		
		void SetActive(bool state);
	private:

	};
}
