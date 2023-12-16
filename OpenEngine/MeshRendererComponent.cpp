#include "MeshRendererComponent.h"
#include"ServiceLocator.h"
#include"Renderer.h"
#include"Entity.h"
using namespace OpenEngine;
MeshRendererComponent::MeshRendererComponent(Entity* entity) {
	mOwner = entity;
	mMaterial = nullptr;
	mMesh = nullptr;
	Visible = true;
}
MeshRendererComponent::MeshRendererComponent() {
	mOwner = nullptr;
	mMaterial = nullptr;
	mMesh = nullptr;
	Visible = true;
}
int MeshRendererComponent::Initialize() {
	return 0;
}
void MeshRendererComponent::Finalize() {

}
void MeshRendererComponent::SetMaterial(Material* m) {
	mMaterial = m;
}

void MeshRendererComponent::SetMesh(Mesh* m) {
	mMesh = m;
}

void MeshRendererComponent::DrawMesh() {
	Mat4 ModelMatrix=this->GetOwner()->GetComponent<TransformComponent>()->GetModelMatrix();
	OESERVICE(Renderer).DrawMash(mMesh, mMaterial, ModelMatrix);
	
}