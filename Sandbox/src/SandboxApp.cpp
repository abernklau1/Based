#include "Based.h"

#include "Based/Events/KeyEvent.h"
#include "imgui/imgui.h"


class ExampleLayer : public Based::Layer {
public:
  ExampleLayer() : Layer("Example"), m_Camera(-1.0f, 1.0f, -1.0f, 1.0f), m_CameraPosition(0.0f) {
// Vertex Array
  // Vertex Buffer
  // Index Buffer
  // For MacOSX -- Shader

  // Vertex Array and Vertex Buffer
  m_VertexArray.reset(Based::VertexArray::Create());

  float vertices[3 * 7] = {
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
     0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
     0.0f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
 };

  std::shared_ptr<Based::VertexBuffer> vertexBuffer;
  vertexBuffer.reset(Based::VertexBuffer::Create(vertices, sizeof(vertices)));


    Based::BufferLayout layout = {
      { Based::ShaderDataType::Float3, "a_Position" },
      { Based::ShaderDataType::Float4, "a_Color"}
    };
    vertexBuffer->SetLayout(layout);


    m_VertexArray->AddVertexBuffer(vertexBuffer);

  // Index Buffer
  uint32_t indices[3] = {
    0, 1, 2
  };

  std::shared_ptr<Based::IndexBuffer> indexBuffer;
  indexBuffer.reset(Based::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
  m_VertexArray->SetIndexBuffer(indexBuffer);

  // Shader
  std::string vertexSrc = R"(
    #version 410 core

    layout(location = 0) in vec4 a_Position;
    layout(location = 1) in vec4 a_Color;

    uniform mat4 u_ViewProjection;

    out vec4 v_Position;
    out vec4 v_Color;

    void main() {
      v_Position = a_Position;
      v_Color = a_Color;
      gl_Position = u_ViewProjection * a_Position;
    })";

  std::string fragmentSrc = R"(
    #version 410 core

    layout(location = 0) out vec4 color;

    in vec4 v_Position;
    in vec4 v_Color;

    void main() {
      color = vec4(v_Position * 0.5 + 0.5);
      color = v_Color;
    })";

  m_Shader.reset(new Based::Shader(vertexSrc, fragmentSrc));


  }

  void OnUpdate() override {


    if (Based::Input::IsKeyPressed(BSD_KEY_LEFT))
      m_CameraPosition.x += m_CameraMovementSpeed;

    else if (Based::Input::IsKeyPressed(BSD_KEY_RIGHT))
      m_CameraPosition.x -= m_CameraMovementSpeed;

    if (Based::Input::IsKeyPressed(BSD_KEY_UP))
      m_CameraPosition.y -= m_CameraMovementSpeed;

    else if (Based::Input::IsKeyPressed(BSD_KEY_DOWN))
      m_CameraPosition.y += m_CameraMovementSpeed;

    if (Based::Input::IsKeyPressed(BSD_KEY_A))
      m_CameraRotation -= m_CameraRotationSpeed;

    if (Based::Input::IsKeyPressed(BSD_KEY_D))
      m_CameraRotation += m_CameraRotationSpeed;

    Based::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    Based::RenderCommand::Clear();

    m_Camera.SetPosition(m_CameraPosition);
    m_Camera.SetRotation(m_CameraRotation);

    Based::Renderer::BeginScene(m_Camera);

    Based::Renderer::Submit(m_Shader, m_VertexArray);
    Based::Renderer::EndScene();
  }

  void OnImGuiRender() override {
  }

  void OnEvent(Based::Event &event) override {
  }

private:
  std::shared_ptr<Based::Shader> m_Shader;
  std::shared_ptr<Based::VertexArray> m_VertexArray;
  Based::OrthographicCamera m_Camera;
  glm::vec3 m_CameraPosition;
  float m_CameraRotation = 0;
  float m_CameraMovementSpeed = 0.1f;
  float m_CameraRotationSpeed = 0.5f;
};

class Sandbox : public Based::Application {
public:
  Sandbox() { PushLayer(new ExampleLayer()); }

  ~Sandbox() {}
};

Based::Application *Based::CreateApplication() { return new Sandbox(); }
