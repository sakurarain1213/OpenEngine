#include"InputMgr.h"

OpenEngine::InputMgr& OpenEngine::InputMgr::GetInstance() {
	static InputMgr inputMgr;
	return inputMgr;
}

OpenEngine::InputMgr::InputMgr() {

}

OpenEngine::InputMgr::~InputMgr() {

}