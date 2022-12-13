#pragma once

#include "Based.h"

class ExampleLayer : public Based::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Based::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Based::Event& e) override;
private:
	Based::ShaderLibrary m_ShaderLibrary;
	Based::Ref<Based::Shader> m_Shader;
	Based::Ref<Based::VertexArray> m_VertexArray;

	Based::Ref<Based::Shader> m_FlatColorShader;
	Based::Ref<Based::VertexArray> m_SquareVA;

	Based::Ref<Based::Texture2D> m_Texture, m_ChernoLogoTexture;

	Based::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};
