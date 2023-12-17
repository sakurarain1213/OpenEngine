#include "Move.h"
#include"Entity.h"
#include"ServiceLocator.h"

#include"Input.h"
#include<iostream>
using namespace OpenEngine;

Move::Move(Entity* entity) :MonoBehaviour(entity) {
	
}

int Move::Initialize()
{
	return 0;
}
void Move::Update() {
	TransformComponent* trans = GetOwner()->GetComponent<TransformComponent>();
	Vec3 temp = { 0,0,0 };
	Vec3 Zerovec = { 0,0,0 };
	if (OESERVICE(Input).GetKeyDown(EKey::KEY_J)) {
		temp(0) += -0.1;
	}
	if (OESERVICE(Input).GetKeyDown(EKey::KEY_L)) {
		temp(0) += 0.1;
	}
	if (OESERVICE(Input).GetKeyDown(EKey::KEY_I)) {
		temp(1) += 0.1;
	}
	if (OESERVICE(Input).GetKeyDown(EKey::KEY_K)) {
		temp(1) = -0.1;
	}
	Vec3 oldposi= trans->GetPosition();
	trans->SetPosition(oldposi + temp);

}