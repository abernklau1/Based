#include "Application.h"
#include "Based/Log.h"
#include "bsdpch.h"

#include "Renderer/Renderer.h"

#include "Input.h"

namespace Based {

Application *Application::s_Instance = nullptr;

Application::Application() {
  BSD_CORE_ASSERT(s_Instance, "Application already exists");

  s_Instance = this;

  m_Window = std::unique_ptr<Window>(Window::Create());
  m_Window->SetEventCallback(BSD_BIND_EVENT_FN(Application::OnEvent));

  m_ImGuiLayer = new ImGuiLayer();
  PushOverlay(m_ImGuiLayer);

  // Vertex Array
  // Vertex Buffer
  // Index Buffer
  // For MacOSX -- Shader

  // Vertex Array and Vertex Buffer
  m_VertexArray.reset(VertexArray::Create());

  float vertices[3 * 7] = {
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
     0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
     0.0f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
 };

  std::shared_ptr<VertexBuffer> vertexBuffer;
  vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));


    BufferLayout layout = {
      { ShaderDataType::Float3, "a_Position" },
      { ShaderDataType::Float4, "a_Color"}
    };
    vertexBuffer->SetLayout(layout);


    m_VertexArray->AddVertexBuffer(vertexBuffer);

  // Index Buffer
  uint32_t indices[3] = {
    0, 1, 2
  };

  std::shared_ptr<IndexBuffer> indexBuffer;
  indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
  m_VertexArray->SetIndexBuffer(indexBuffer);

  // Shader
  std::string vertexSrc = R"(
    #version 410 core

    layout(location = 0) in vec4 a_Position;
    layout(location = 1) in vec4 a_Color;

    out vec4 v_Position;
    out vec4 v_Color;

    void main() {
      v_Position = a_Position;
      v_Color = a_Color;
      gl_Position = a_Position;
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

  m_Shader.reset(new Shader(vertexSrc, fragmentSrc));

 }

Application::~Application() {}

void Application::PushLayer(Layer *layer) {
  m_LayerStack.PushLayer(layer);
  layer->OnAttach();
}

void Application::PushOverlay(Layer *layer) {
  m_LayerStack.PushOverlay(layer);
  layer->OnAttach();
}

void Application::OnEvent(Event &e) {
  EventDispatcher dispatcher(e);
  dispatcher.Dispatch<WindowCloseEvent>(
      BSD_BIND_EVENT_FN(Application::OnWindowClose));
  BSD_CORE_TRACE("{0}", e);
  for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {

    (*--it)->OnEvent(e);
    if (e.Handled)
      break;
  }
}

void Application::Run() {
  while (m_Running) {

    RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    RenderCommand::Clear();

    Renderer::BeginScene();

    m_Shader->Bind();
    Renderer::Submit(m_VertexArray);
    Renderer::EndScene();

    for (Layer *layer : m_LayerStack)
      layer->OnUpdate();

    m_ImGuiLayer->Begin();
    for (Layer *layer : m_LayerStack)
      layer->OnImGuiRender();

    m_ImGuiLayer->End();

    m_Window->OnUpdate();
  }
}

bool Application::OnWindowClose(WindowCloseEvent &e) {
  m_Running = false;
  return true;
}

} // namespace Based
