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
		void SetSize(Vec2 _size);
		Vec3 GetPosition();
		Vec2 GetSize();
		std::string GetText();

		
	private:
		
		std::string text;
		Vec2 size;//长宽

	};
}