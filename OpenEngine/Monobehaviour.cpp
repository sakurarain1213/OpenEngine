#include "MonoBehaviour.h"
using namespace OpenEngine;
MonoBehaviour::MonoBehaviour() {
	Initialize();

}

MonoBehaviour::~MonoBehaviour() {
	Finalize();
}

void MonoBehaviour::SetActive(bool state) {
	if (state&&mIsActive==false) {
		OnEnable();
	}
	else if (state==false&&mIsActive==true) {
		OnDisable();
	}
	
	mIsActive = state;
}