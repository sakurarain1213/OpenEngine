#pragma once
#include"IComponent.h"
#include"Action.h"
namespace OpenEngine {
	typedef void (*func)(int);
	class InputComponent : public IComponent
	{
	public:
		InputComponent();
		int Initialize()noexcept;
		void Finalize()noexcept;

		void BindAction( auto fun, auto obj);

	private:
		Action<int> actions;
	};
}
