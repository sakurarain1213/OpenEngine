#pragma once
#include"ISystem.h"
#include<concurrent_priority_queue.h>
namespace OpenEngine {
	class InputSystem : public ISystem
	{
	public:

		InputSystem();

		int Initialize()noexcept;
		void Finalize()noexcept;
		void Tick()noexcept;



	private:

	};
}
