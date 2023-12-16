
//未投入使用
#include "InputComponent.h"
using namespace OpenEngine;

InputComponent::InputComponent() {

}
int InputComponent::Initialize()noexcept {
	return 0;
}
void InputComponent::Finalize()noexcept {

}

void InputComponent::BindAction(auto fun,auto obj) {
	actions.AddListener(std::bind(fun, obj, std::placeholders::_1, std::placeholders::_2));
}