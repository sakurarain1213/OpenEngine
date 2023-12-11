#pragma once

#include "Object.h"
#include "Math.h"
#include <vector>
#include "VertexArray.h"
#include "Logger.h"

namespace OpenEngine {

	struct Vertex {
		Vec3 position;
		Vec3 normal;
		Vec3 tangent;
		Vec2 texCoords;
	};

	class Mesh : Object{
		friend class Renderer;
	public:
		Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, std::string name = "New Mesh") :
			vertices(vertices),
			indices(indices),
			m_vertexBuffer(),
			m_elementBuffer(),
			m_vertexArray(m_vertexBuffer, m_elementBuffer),
			Object(name) {
			SetupVertexAttribPoint();
			UploadMeshData();
		}
		void UploadMeshData() {
			m_vertexBuffer.Upload(&vertices[0], sizeof(Vertex) * vertices.size());
			m_elementBuffer.Upload(&indices[0], sizeof(uint32_t) * indices.size());
			m_vertice_count = (uint32_t)vertices.size();
			m_indice_count = (uint32_t)indices.size();
			OE_INFO("[Mesh] " + name + " : Upload " + std::to_string(vertices.size()) + " vertices and " + std::to_string(indices.size() / 3) + " faces with total memory " + std::to_string(vertices.size() * sizeof(Vertex) + indices.size() * sizeof(uint32_t)));
		}
		uint32_t GetIndiceCount() {
			return m_indice_count;
		}
		uint32_t GetVerticeCount() {
			return m_vertice_count;
		}
		std::string GetType() {
			return "Mesh";
		}
		static std::string ClassType() {
			return "Mesh";
		}
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
	private:
		void Use() {
			m_vertexArray.Bind();
		}
		void SetupVertexAttribPoint() {
			m_vertexArray.Bind();
			m_vertexArray.BindAttribute(0, 3, sizeof(Vertex), offsetof(Vertex, position));
			m_vertexArray.BindAttribute(1, 3, sizeof(Vertex), offsetof(Vertex, normal));
			m_vertexArray.BindAttribute(2, 3, sizeof(Vertex), offsetof(Vertex, tangent));
			m_vertexArray.BindAttribute(3, 2, sizeof(Vertex), offsetof(Vertex, texCoords));
			m_vertexArray.Unbind();
		}
		Buffer::VertexBuffer m_vertexBuffer;
		Buffer::ElementBuffer m_elementBuffer;
		Buffer::VertexArray m_vertexArray;
		uint32_t m_vertice_count;
		uint32_t m_indice_count;
	};
}