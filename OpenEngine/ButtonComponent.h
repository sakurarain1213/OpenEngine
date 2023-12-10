#pragma once
#include"IComponent.h"
#include"Math.h"

namespace OpenEngine {
	class ButtonComponent : public IComponent
	{
	public:
		ButtonComponent(Entity* entity);
		ButtonComponent();

		virtual int Initialize();
		virtual void Finalize();

		void SetText(std::string str);

		Vec3 GetPosition();
	private:
		Vec2 posi;
		std::string text;


	};
}