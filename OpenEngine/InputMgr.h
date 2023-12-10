#pragma once
#include<string>
namespace OpenEngine {
	class InputMgr {
	public:
		static InputMgr& GetInstance();

		

	private:
		InputMgr();
		~InputMgr();
		InputMgr(const InputMgr& inputmgr) = delete;
		const InputMgr& operator=(const InputMgr& inputmgr) = delete;
	};


}