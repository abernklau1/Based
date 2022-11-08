#include "Based.h"

#include "Based/Events/KeyEvent.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include <imgui/imgui.h>

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class ExampleLayer : public Based::Layer {
public:
  ExampleLayer() : Layer("Example"), m_CameraController(1280.0f / 720.0f) {
  // Vertex Array
  // Vertex Buffer
  // Index Buffer
  // For MacOSX -- Shader

 //  // --- Triangle -----------------------------------------------------------------------

 //  // Vertex Array and Vertex Buffer
 //  m_VertexArray.reset(Based::VertexArray::Create());

 //  float vertices[3 * 7] = {
 //    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
 //     0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
 //     0.0f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
 // };

 //  Based::Ref<Based::VertexBuffer> vertexBuffer;
 //  vertexBuffer.reset(Based::VertexBuffer::Create(vertices, sizeof(vertices)));


 //    Based::BufferLayout layout = {
 //      { Based::ShaderDataType::Float3, "a_Position" },
 //      { Based::ShaderDataType::Float4, "a_Color"}
 //    };
 //    vertexBuffer->SetLayout(layout);

 //    m_VertexArray->AddVertexBuffer(vertexBuffer);

 //  // Index Buffer
 //  uint32_t indices[3] = {
 //    0, 1, 2
 //  };

 //  Based::Ref<Based::IndexBuffer> indexBuffer;
 //  indexBuffer.reset(Based::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
 //  m_VertexArray->SetIndexBuffer(indexBuffer);

 //  // Shader
 //  std::string vertexSrc = R"(
 //    #version 410 core

 //    layout(location = 0) in vec4 a_Position;
 //    layout(location = 1) in vec4 a_Color;

 //    uniform mat4 u_ViewProjection;
 //    uniform mat4 u_Transform;

 //    out vec4 v_Position;
 //    out vec4 v_Color;

 //    void main() {
 //      v_Position = a_Position;
 //      v_Color = a_Color;
 //      gl_Position = u_ViewProjection * u_Transform * a_Position;
 //    })";

 //  std::string fragmentSrc = R"(
 //    #version 410 core

 //    layout(location = 0) out vec4 color;

 //    in vec4 v_Position;
 //    in vec4 v_Color;

 //    void main() {
 //      color = vec4(v_Position * 0.5 + 0.5);
 //      color = v_Color;
 //    })";

 //  m_Shader.reset(Based::Shader::Create(vertexSrc, fragmentSrc));


  // ------------------------------------------------------------------------------------

  // --- Square -------------------------------------------------------------------------

  // Vertex Array and Vertex Buffer
  m_SquareVA.reset(Based::VertexArray::Create());

  float squareVertices[5 * 4] = {
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
    -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
 };

    Based::Ref<Based::VertexBuffer> squareVB;
  squareVB.reset(Based::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

  squareVB->SetLayout({
      { Based::ShaderDataType::Float3, "a_Position" },
      { Based::ShaderDataType::Float2, "a_TextCoord"}
    });


    m_SquareVA->AddVertexBuffer(squareVB);

  // Index Buffer
  uint32_t squareIndices[6] = {
    0, 1, 2, 2, 3, 0
  };

  Based::Ref<Based::IndexBuffer> squareIB;
  squareIB.reset(Based::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
  m_SquareVA->SetIndexBuffer(squareIB);

  // Shader
  std::string squareVSrc = R"(
    #version 410 core

    layout(location = 0) in vec4 a_Position;

    uniform mat4 u_ViewProjection;
    uniform mat4 u_Transform;

    out vec4 v_Position;

    void main() {
      v_Position = a_Position;
      gl_Position = u_ViewProjection * u_Transform * a_Position;
    })";

  std::string squareFSrc = R"(
    #version 410 core

    layout(location = 0) out vec4 color;

    in vec4 v_Position;

    uniform vec3 u_Color;

    void main() {
      color = vec4(u_Color, 1.0);
    })";

  m_SquareShader = Based::Shader::Create("FlatColorShader", squareVSrc, squareFSrc);

  // Texture Shader

  auto textureShader = m_ShaderLibrary.Load("Sandbox/assets/shaders/Texture.glsl");

  m_Texture = Based::Texture2D::Create("Sandbox/assets/textures/Checkerboard.png");

  std::dynamic_pointer_cast<Based::OpenGLShader>(textureShader)->Bind();

  std::dynamic_pointer_cast<Based::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);

  }

  void OnUpdate(Based::Timestep ts) override {

    // Update
    m_CameraController.OnUpdate(ts);

    // Renderer 
    Based::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    Based::RenderCommand::Clear();

    Based::Renderer::BeginScene(m_CameraController.GetCamera());


    static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

    std::dynamic_pointer_cast<Based::OpenGLShader>(m_SquareShader)->Bind();
    std::dynamic_pointer_cast<Based::OpenGLShader>(m_SquareShader)->UploadUniformFloat3("u_Color", m_SquareColor);

    for (int y = 0; y < 20; y++) {
      for (int x = 0; x < 20; x++) {
        glm::vec3 pos(x * 0.11f,y * 0.11f, 0.0f);
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
        Based::Renderer::Submit(m_SquareShader, m_SquareVA, transform);
      }
    }

    auto textureShader = m_ShaderLibrary.Get("Texture");

    m_Texture->Bind();
    Based::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));


    // Triangle
    // Based::Renderer::Submit(m_Shader, m_VertexArray);

    Based::Renderer::EndScene();
  }

  void OnImGuiRender() override {
    ImGui::Begin("Settings");
    ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
  }

  void OnEvent(Based::Event &e) override {
    m_CameraController.OnEvent(e);
  }

private:
  Based::ShaderLibrary m_ShaderLibrary;
  Based::Ref<Based::Shader> m_Shader;
  Based::Ref<Based::VertexArray> m_VertexArray;

  Based::Ref<Based::Shader> m_SquareShader;
  Based::Ref<Based::VertexArray> m_SquareVA;

  Based::Ref<Based::Texture2D> m_Texture;

  Based::OrthographicCameraController m_CameraController;

  glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Based::Application {
public:
  Sandbox() { PushLayer(new ExampleLayer()); }

  ~Sandbox() {}
};

Based::Application *Based::CreateApplication() { return new Sandbox(); }
