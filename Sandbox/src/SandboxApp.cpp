#include <Granola.h>

/* access violation 0xC0000005 or 0x0000... (nullptr) means problems with GLFW or glad initialization check:
 * 1. Check status and success variables in WindowsWindow.cpp
 * 2. Check if gladLoadGLLoader is called after glfwMakeContextCurrent, glfwInit etc.
 * 3. Check if glad is initialized before any OpenGL call
 * 6/10/23 !Fixed now
 */

// this is a small example of how to use Granola engine
class ExampleLayer final : public Granola::Layer
{
public:
	ExampleLayer() : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		// example shaders
		m_VertexArray = Granola::VertexArray::Create();
		const float squareVericies[6 * 7] = {
			-0.5f, -0.75f, 0.0f, Granola::RGBColorPallete::Red.r, Granola::RGBColorPallete::Red.g,
			Granola::RGBColorPallete::Red.b, 1.0f,
			0.5f, -0.5f, 0.0f, Granola::RGBColorPallete::Blue.r, Granola::RGBColorPallete::Blue.g,
			Granola::RGBColorPallete::Blue.b, 1.0f,
			0.5f, -0.5f, 0.0f, Granola::RGBColorPallete::Purple.r, Granola::RGBColorPallete::Purple.g,
			Granola::RGBColorPallete::Purple.b, 1.0f,
			0.0f, 0.75f, 0.0f, Granola::RGBColorPallete::Orange.r, Granola::RGBColorPallete::Orange.g,
			Granola::RGBColorPallete::Orange.b, 1.0f,
			0.15f, 0.15f, 0.0f, Granola::RGBColorPallete::Yellow.r, Granola::RGBColorPallete::Yellow.g,
			Granola::RGBColorPallete::Yellow.b, 1.0f,
			-0.75f, 0.5f, 0.0f, Granola::RGBColorPallete::Green.r, Granola::RGBColorPallete::Green.g,
			Granola::RGBColorPallete::Green.b, 1.0f
		};

		const Granola::Ref<Granola::VertexBuffer> vertexBuffer = Granola::VertexBuffer::Create(
			squareVericies, sizeof(squareVericies));
		const Granola::BufferLayout squareLayout = {
			{Granola::ShaderDataType::Float3, "a_Position"},
			{Granola::ShaderDataType::Float4, "a_Color"},
		};
		vertexBuffer->SetLayout(squareLayout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);
		constexpr uint32_t squareIndicies[12] = {0, 1, 2, 2, 3, 0, 4, 4, 5, 1, 3, 5};

		const Granola::Ref<Granola::IndexBuffer> indexBuffer = Granola::IndexBuffer::Create(
			squareIndicies, std::size(squareIndicies));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 450 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;
			
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 450 core
			
			layout(location = 0) out vec4 o_Color;
			in vec3 v_Position;
			in vec4 v_Color;
			
			void main()
			{
				o_Color = vec4(v_Position+0.25, 1.0);
				o_Color = v_Color; //* vec4(v_Position+0.25, 1.0);
			}
		)";

		m_Shader = std::make_unique<Granola::Shader>(vertexSrc, fragmentSrc);
	}

	virtual void OnUpdate() override
	{
		// Camera rotatio prototype
		if (Granola::Input::IsKeyPressed(GRL_KEY_A) or Granola::Input::IsKeyPressed(GRL_KEY_LEFT))
			m_CameraPosition.x -= m_CameraPositionSpeed;
		else if (Granola::Input::IsKeyPressed(GRL_KEY_D) or Granola::Input::IsKeyPressed(GRL_KEY_RIGHT))
			m_CameraPosition.x += m_CameraPositionSpeed;
		else if (Granola::Input::IsKeyPressed(GRL_KEY_S) or Granola::Input::IsKeyPressed(GRL_KEY_DOWN))
			m_CameraPosition.y -= m_CameraPositionSpeed;
		else if (Granola::Input::IsKeyPressed(GRL_KEY_W) or Granola::Input::IsKeyPressed(GRL_KEY_UP))
			m_CameraPosition.y += m_CameraPositionSpeed;
		else if (Granola::Input::IsKeyPressed(GRL_KEY_Q))
			m_CameraRotation += m_CameraRotationSpeed;
		else if (Granola::Input::IsKeyPressed(GRL_KEY_E))
			m_CameraRotation -= m_CameraRotationSpeed;
		else if (Granola::Input::IsKeyPressed(GRL_KEY_HOME))
		{
			m_CameraPosition = {0.0f, 0.0f, 0.0f};
			m_CameraRotation = 0.0f;
		}

		// Rendering scene
		Granola::RenderCommand::SetClearColor({0.2f, 0.2f, 0.2f, 1.0f});
		Granola::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Granola::Renderer::BeginScene(m_Camera);
		Granola::Renderer::Submit(m_Shader, m_VertexArray);
		Granola::Renderer::EndScene();
	}

	virtual void OnEvent(Granola::Event &event) override
	{
	}

private:
	Granola::Ref<Granola::Shader> m_Shader;
	Granola::Ref<Granola::VertexArray> m_VertexArray;

	Granola::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition = {0.0f, 0.0f, 0.0f};
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 0.5f;
	float m_CameraPositionSpeed = 0.02f;
};

class Sandbox final : public Granola::App
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	virtual ~Sandbox() override = default;
};

Granola::App *Granola::CreateApp()
{
	return new Sandbox();
}
