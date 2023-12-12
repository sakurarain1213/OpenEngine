#pragma once
#include"IComponent.h"
#include"Mesh.h"
#include"Material.h"
namespace OpenEngine {
	class MeshRendererComponent : public IComponent
	{
	public:
		MeshRendererComponent(Entity* entity);
		MeshRendererComponent();

		virtual int Initialize();
		virtual void Finalize();

		void SetVisible(bool v) { Visible = v; }
		bool IsVisible() { return Visible; }

		void SetMesh(Mesh* mesh);
		void SetMaterial(Material* m);
	private:
		bool Visible;
		Mesh* mMesh;
		Material* mMaterial;
	};
}

