#include "MeshRenderComponent.h"
using namespace OpenEngine;
MeshRenderComponent::MeshRenderComponent(Entity* entity) {
	mOwner = entity;
}
MeshRenderComponent::MeshRenderComponent() {
	mOwner = nullptr;
}
int MeshRenderComponent::Initialize() {
	return 0;
}
void MeshRenderComponent::Finalize() {

}
void MeshRenderComponent::SetMaterial(Material* m) {
	mMaterial = m;
}

void MeshRenderComponent::SetMesh(Mesh* m) {
	mMesh = m;
}