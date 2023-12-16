#pragma once

#include "RenderDriver.h"
#include "RenderEnum.h"
#include "Uniformbuffer.h"
#include "Mesh.h"
#include "Material.h"
#include "Time.h"

#include <iostream>

namespace OpenEngine {

	struct DrawCall {
		Mesh* mesh;
		Material* material;
		Mat4 modelMatrix;
	};

	class Renderer {
	public:
		Renderer(RenderDriver& driver) :
			m_driver(driver),
			m_UBO(148, OE_UNIFORM_GLOBALUBO) {}
		void EnableDepthTest() {
			glEnable(GL_DEPTH_TEST);
		}
		void DisableDepthTest() {
			glDisable(GL_DEPTH_TEST);
		}
		void EnableDepthWrite() {
			glDepthMask(GL_TRUE);
		}
		void DisableDepthWrite() {
			glDepthMask(GL_FALSE);
		}
		void SetDepthFunc(TestFunc func) {
			glDepthFunc((GLenum)func);
		}
		void EnableStencilTest() {
			glEnable(GL_STENCIL_TEST);
		}
		void DisableStencilTest() {
			glDisable(GL_STENCIL_TEST);
		}
		void SetStencilMask(uint8_t mask) {
			glStencilMask(mask);
		}
		void SetStencilFunc(TestFunc func, uint8_t ref, uint8_t mask) {
			glStencilFunc(func, ref, mask);
		}
		void SetStencilOperation(TestOperation fail, TestOperation passButDepthTestFail, TestOperation pass) {
			glStencilOp(fail, passButDepthTestFail, pass);
		}
		void EnableBlend() {
			glEnable(GL_BLEND);
		}
		void DisableBlend() {
			glDisable(GL_BLEND);
		}
		void SetBlendFunc(BlendFunc src, BlendFunc dst) {
			glBlendFunc(src, dst);
		}
		void EnableCullFace() {
			glEnable(GL_CULL_FACE);
		}
		void DisableCullFace() {
			glDisable(GL_CULL_FACE);
		}
		void SetCullFaceFront() {
			glCullFace(GL_FRONT);
		}
		void SetCullFaceBack() {
			glCullFace(GL_BACK);
		}
		void SetCullFaceBoth() {
			glCullFace(GL_FRONT_AND_BACK);
		}
		void SetFrontFaceCW() {
			glFrontFace(GL_CW);
		}
		void SetFrontFaceCCW() {
			glFrontFace(GL_CCW);
		}
		void Clear(bool color, bool depth, bool stencil) {
			glClear(
				(color ? GL_COLOR_BUFFER_BIT : 0) |
				(depth ? GL_DEPTH_BUFFER_BIT : 0) |
				(stencil ? GL_STENCIL_BUFFER_BIT : 0)
			);
		}
		void SetViewMatrix(Mat4 view) {
			m_viewMatrix = view;
		}
		void SetProjectionMatrix(Mat4 projection) {
			m_projectionMatrix = projection;
		}
		void SetCameraPosition(Vec3 position) {
			m_cameraPosition = position;
		}
		void DrawMash(Mesh* mesh, Material* material, Mat4 modelMatrix) {
			m_drawcalls.emplace_back(mesh, material, modelMatrix);
		}
		void ExecuteDrawCalls() {
			SetGlobalUBO();
			for (int i = 0;i < m_drawcalls.size();++i) {
				Mesh* mesh = m_drawcalls[i].mesh;
				Material* material = m_drawcalls[i].material;
				material->Use();
				material->m_shader->SetUniform("OE_Model", m_drawcalls[i].modelMatrix);

				if (material->enableDepthTest) {
					EnableDepthTest();
					if (material->enableDepthWrite) EnableDepthWrite();
					else DisableDepthWrite();
					SetDepthFunc(material->depthFunc);
				}
				else DisableDepthTest();
				if (material->enableStencilTest) {
					EnableStencilTest();
					SetStencilFunc(material->stencilFunc, material->stencilFuncRef, material->stencilFuncMask);
					SetStencilOperation(material->stencilFailOperation, material->stencilDeepTestFailOperation, material->stencilPassOperation);
				}
				else DisableStencilTest();
				if (material->enableBlend) {
					EnableBlend();
					SetBlendFunc(material->blendSrcFunc, material->blendDstFunc);
				}
				else DisableBlend();
				if (material->enableCullFace && (material->cullFaceBack || material->cullFaceFront)) {
					EnableCullFace();
					if (material->cullFaceBack && material->cullFaceFront) {
						SetCullFaceBoth();
					}
					else if (material->cullFaceBack) {
						SetCullFaceBack();
					}
					else if (material->cullFaceFront) {
						SetCullFaceFront();
					}
					if (material->frontFaceCCW) {
						SetFrontFaceCCW();
					}
					else {
						SetFrontFaceCW();
					}
				}
				else {
					DisableCullFace();
				}

				mesh->Use();
				glDrawElements(GL_TRIANGLES, mesh->GetIndiceCount(), GL_UNSIGNED_INT, (void*)0);
			}
			m_drawcalls.clear();
		}
	private:
		void SetGlobalUBO() {
			m_UBO.SetSubData<Mat4>(m_viewMatrix, 0);
			m_UBO.SetSubData<Mat4>(m_projectionMatrix, 64);
			m_UBO.SetSubData<Vec3>(m_cameraPosition, 128);
			m_UBO.SetSubData<float>(Time::GetRealtimeSinceStartup(), 144);
		}

		RenderDriver& m_driver;
		Buffer::UniformBuffer m_UBO;
		std::vector<DrawCall> m_drawcalls;
		Mat4 m_viewMatrix;
		Mat4 m_projectionMatrix;
		Vec3 m_cameraPosition;
	};
}