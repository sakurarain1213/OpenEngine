#include "MeshRendererComponent.h"
using namespace OpenEngine;
MeshRendererComponent::MeshRendererComponent(Entity* entity) {
	mOwner = entity;
}
MeshRendererComponent::MeshRendererComponent() {
	mOwner = nullptr;
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