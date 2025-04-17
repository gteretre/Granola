#include <Granola.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../imgui/imgui.h"

#include "Platform/OpenGL/OpenGLShader.h"

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
	ExampleLayer() : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f),
					 m_FigPosition(0.0f, 0.0f, 0.0f)
	{
		// example shaders
		m_VertexArray = Granola::VertexArray::Create();
		constexpr float squareVericies[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // left bottom
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // right bottom
			0.5f, 0.5f, 0.0f, 1.0f, 1.0f, // right top
			-0.5f, 0.5f, 0.0f, 0.0f, 1.0f // left top
		};

		const Granola::Ref<Granola::VertexBuffer> vertexBuffer = Granola::VertexBuffer::Create(
			squareVericies, sizeof(squareVericies));

		const Granola::BufferLayout squareLayout = {
			{Granola::ShaderDataType::Float3, "a_Position"}, {Granola::ShaderDataType::Float2, "a_TexCoord"}
		};

		vertexBuffer->SetLayout(squareLayout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);
		constexpr uint32_t squareIndicies[6] = {0, 1, 2, 2, 3, 0};
		const Granola::Ref<Granola::IndexBuffer> indexBuffer = Granola::IndexBuffer::Create(
			squareIndicies, std::size(squareIndicies));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		const std::string basicShaderVertexSrc = R"(
			#version 410 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		const std::string basicShaderFragmentSrc = R"(
			#version 410 core
			
			layout(location = 0) out vec4 o_Color;
			in vec3 v_Position;
			
			uniform vec3 u_Color;
			
			void main()
			{
				o_Color = vec4(u_Color,1.0);
			}
		)";

		const std::string testShaderVertexSrc = R"(
			#version 410 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
			    v_Color = a_Color;
			    gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}

		)";

		const std::string testShaderFragmentSrc = R"(
			#version 410 core

			in vec3 v_Position;
			in vec4 v_Color;

			uniform float iTime;
			uniform vec2 iResolution;

			out vec4 fragColor;

			vec3 palette( float t ) {
			    vec3 a = vec3(0.5, 0.5, 0.5);
			    vec3 b = vec3(0.5, 0.5, 0.5);
			    vec3 c = vec3(1.0, 1.0, 1.0);
			    vec3 d = vec3(0.263,0.416,0.557);

			    return a + b*cos( 6.28318*(c*t+d) );
			}

			void main() {
			    vec2 uv = (v_Position.xy * 2.0 - iResolution.xy) / iResolution.y;
			    vec2 uv0 = uv;
			    vec3 finalColor = vec3(0.0);
			    
			    for (float i = 0.0; i < 4.0; i++) {
			        uv = fract(uv * 1.5) - 0.5;

			        float d = length(uv) * exp(-length(uv0));

			        vec3 col = palette(length(uv0) + i*.4 + iTime*.4);

			        d = sin(d*8. + iTime)/8.;
			        d = abs(d);

			        d = pow(0.01 / d, 1.2);

			        finalColor += col * d;
			    }
			        
			    fragColor = vec4(finalColor, 1.0) * v_Color;
			}
		)";

		m_BasicShader.reset(Granola::Shader::Create(testShaderVertexSrc, testShaderFragmentSrc));
		m_Texture = Granola::Texture2D::Create("assets/textures/textTex1.png");
		m_TextureShader.reset(Granola::Shader::Create("assets/shaders/Texture.glsl"));
		m_TransparentTexture = Granola::Texture2D::Create("assets/textures/transparentTex.png");
		std::dynamic_pointer_cast<Granola::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Granola::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
	}

	virtual void OnUpdate(const Granola::Timestep timestep) override
	{
		//---Camera Prototype----------------------------------------
		// move left/right
		if (Granola::Input::IsKeyPressed(GRL_KEY_A) or Granola::Input::IsKeyPressed(GRL_KEY_LEFT))
			m_CameraPosition.x -= m_CameraPositionSpeed * timestep;
		else if (Granola::Input::IsKeyPressed(GRL_KEY_D) or Granola::Input::IsKeyPressed(GRL_KEY_RIGHT))
			m_CameraPosition.x += m_CameraPositionSpeed * timestep;

		// Move up/down
		if (Granola::Input::IsKeyPressed(GRL_KEY_S) or Granola::Input::IsKeyPressed(GRL_KEY_DOWN))
			m_CameraPosition.y -= m_CameraPositionSpeed * timestep;
		else if (Granola::Input::IsKeyPressed(GRL_KEY_W) or Granola::Input::IsKeyPressed(GRL_KEY_UP))
			m_CameraPosition.y += m_CameraPositionSpeed * timestep;

		// Rotate left/right
		if (Granola::Input::IsKeyPressed(GRL_KEY_E))
			m_CameraRotation -= m_CameraRotationSpeed * timestep;
		else if (Granola::Input::IsKeyPressed(GRL_KEY_Q))
			m_CameraRotation += m_CameraRotationSpeed * timestep;

		// Reset camera
		if (Granola::Input::IsKeyPressed(GRL_KEY_HOME))
		{
			m_CameraPosition = {0.0f, 0.0f, 0.0f};
			m_CameraRotation = 0.0f;
		}
		//-----------------------------------------------------------


		//---Object Prototype----------------------------------------
		// move left/right
		if (Granola::Input::IsKeyPressed(GRL_KEY_J))
			m_FigPosition.x -= m_CameraPositionSpeed * timestep;
		else if (Granola::Input::IsKeyPressed(GRL_KEY_L))
			m_FigPosition.x += m_CameraPositionSpeed * timestep;

		// move up/down
		if (Granola::Input::IsKeyPressed(GRL_KEY_I))
			m_FigPosition.y += m_CameraPositionSpeed * timestep;
		else if (Granola::Input::IsKeyPressed(GRL_KEY_K))
			m_FigPosition.y -= m_CameraPositionSpeed * timestep;
		//-----------------------------------------------------------


		// Rendering scene
		Granola::RenderCommand::SetClearColor({0.05f, 0.1f, 0.15f, 1.0f});
		Granola::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Granola::Renderer::BeginScene(m_Camera);

		static const glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.3f));

		std::dynamic_pointer_cast<Granola::OpenGLShader>(m_BasicShader)->Bind();
		std::dynamic_pointer_cast<Granola::OpenGLShader>(m_BasicShader)->UploadUniformFloat3("u_Color", m_FigColor);

		for (int x = 0; x < 25; ++x)
			for (int y = 0; y < 15; ++y)
			{
				glm::vec3 pos = {static_cast<float>(x) * 0.13f, static_cast<float>(y) * 0.13f, 0.0f};
				const glm::mat4 transform = translate(glm::mat4(1.0f), pos) * scale;
				Granola::Renderer::Submit(m_BasicShader, m_VertexArray, transform * scale);
			}

		const glm::mat4 transform = translate(glm::mat4(1.0f), m_FigPosition);
		m_Texture->Bind();
		Granola::Renderer::Submit(m_TextureShader, m_VertexArray, transform);
		m_TransparentTexture->Bind();
		Granola::Renderer::Submit(m_TextureShader, m_VertexArray, transform);
		Granola::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");

		ImGui::ColorEdit3("Fig Color", value_ptr(m_FigColor));
		ImGui::DragFloat3("Fig Position", value_ptr(m_FigPosition), 0.1f);
		ImGui::Separator();
		ImGui::DragFloat3("Camera Position", value_ptr(m_CameraPosition), 0.1f);
		ImGui::DragFloat("Camera Rotation", &m_CameraRotation, 0.1f);
		ImGui::Separator();
		ImGui::DragFloat("Camera Rotation Speed", &m_CameraRotationSpeed, 0.1f);
		ImGui::DragFloat("Camera Position Speed", &m_CameraPositionSpeed, 0.1f);
		ImGui::Separator();
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
					ImGui::GetIO().Framerate);
		const Granola::Timestep timestep = ImGui::GetIO().DeltaTime;
		ImGui::Text("Timestep: %.3f ms", timestep.GetTime());

		ImGui::End();

		ImGui::Begin("Debug");
		ImGui::Text("DEBUG");
		ImGui::End();
	}

	virtual void OnEvent(Granola::Event &event) override
	{
	}

private:
	Granola::Ref<Granola::Shader> m_BasicShader;
	Granola::Ref<Granola::Shader> m_TextureShader;
	Granola::Ref<Granola::VertexArray> m_VertexArray;
	Granola::Ref<Granola::Texture2D> m_Texture;
	Granola::Ref<Granola::Texture2D> m_TransparentTexture;

	Granola::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 120.0f;
	float m_CameraPositionSpeed = 3.0f;

	glm::vec3 m_FigPosition;
	glm::vec3 m_FigColor = Granola::RGBColorPallete::Navy;
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
