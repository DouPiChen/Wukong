#pragma once

#include <glm/glm.hpp>

#include "Wukong/Core/TimeStep.h"
#include "Wukong/Event/Event.h"
#include "Wukong/Event/MouseEvent.h"
#include "Wukong/Event/KeyEvent.h"

namespace Wukong
{

	class Camera
	{
	public:
		virtual ~Camera() = default;

		virtual void OnUpdate(TimeStep ts) = 0;
		virtual void OnEvent(Event& e) = 0;
		
		virtual const glm::mat4& GetProjectionMatrix() const = 0;
		virtual const glm::mat4& GetViewMatrix() const = 0;
		virtual const float GetZoom() const = 0;

		virtual bool OnKeyboard(KeyPressedEvent& e) = 0;
		virtual bool OnMouseMovement(MouseMovedEvent& e) = 0;
		virtual bool OnMouseScroll(MouseScrolledEvent& e) = 0;

	private:
		virtual void UpdateCameraVectors() = 0;
	};

	class PrespectiveCamera :public Camera
	{
	public:
		PrespectiveCamera();
		PrespectiveCamera(float posX, float posY, float posZ,
			float upX, float upY, float upZ, float yaw, float pitch,
			float screenWidth = 800.0f, float screenHeight = 600.0f);
		virtual ~PrespectiveCamera();

		virtual void OnUpdate(TimeStep ts) override;
		virtual void OnEvent(Event& e) override;

		virtual const glm::mat4& GetProjectionMatrix()const override { return m_ProjectionMatrix; }
		virtual const glm::mat4& GetViewMatrix()const override { return m_ViewMatrix; }
		virtual const float GetZoom() const override { return m_Zoom; }

		virtual bool OnKeyboard(KeyPressedEvent& e) override;
		virtual bool OnMouseMovement(MouseMovedEvent& e) override;
		virtual bool OnMouseScroll(MouseScrolledEvent& e) override;

	private:
		virtual void UpdateCameraVectors() override;

		glm::vec3 m_Position = { 0.0f,0.0f,0.0f };
		glm::vec3 m_Right, m_Up, m_Front;
		glm::vec3 m_WorldUp;
		glm::mat4 m_ProjectionMatrix, m_ViewMatrix;
		float m_Yaw, m_Pitch;
		float m_Zoom = 45.0f, m_MovementSpeed = 2.5f, m_MouseSensitivity = 0.1f;
		float m_ScreenWidth = 800, m_ScreenHeight = 600;
		bool m_FirstMouse = true;
		float m_LastX = m_ScreenWidth / 2, m_LastY = m_ScreenHeight / 2;
		float m_DeltaTime = 0.03f;
	};

	class OrthographicCamera :public Camera
	{
	public:
		OrthographicCamera();
		OrthographicCamera(float left, float right, float bottom, float top, 
			float screenWidth = 800.0f, float screenHeight = 600.0f);
		virtual ~OrthographicCamera();

		virtual void OnUpdate(TimeStep ts) override;
		virtual void OnEvent(Event& e) override;

		virtual const glm::mat4& GetProjectionMatrix()const override { return m_ProjectionMatrix; }
		virtual const glm::mat4& GetViewMatrix()const override { return m_ViewMatrix; }
		virtual const float GetZoom() const override { return m_Zoom; }

		virtual bool OnKeyboard(KeyPressedEvent& e) override;
		virtual bool OnMouseMovement(MouseMovedEvent& e) override;
		virtual bool OnMouseScroll(MouseScrolledEvent& e) override;

	private:
		virtual void UpdateCameraVectors() override;

		glm::vec3 m_Position = { 0.0f,0.0f,0.0f };
		float m_Rotation = 0.0f;
		glm::mat4 m_ProjectionMatrix, m_ViewMatrix;
		float m_Zoom = 1.0f, m_AspectRatio;
		float m_ScreenWidth = 800, m_ScreenHeight = 600;
		float m_MovementSpeed = 2.5f, m_RotationSpeed = 30.0f, m_MouseSensitivity = 0.1f;
		float m_DeltaTime = 0.03f;
	};
}


