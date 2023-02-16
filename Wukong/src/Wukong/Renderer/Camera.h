#pragma once

#include <glm/glm.hpp>


#include "Wukong/Event/Event.h"
#include "Wukong/Event/MouseEvent.h"
#include "Wukong/Event/KeyEvent.h"

namespace Wukong
{

	class Camera
	{
	public:
		virtual ~Camera() = default;

		virtual void OnEvent(Event& e) = 0;
		
		virtual void SetScreenParam(float width, float height) = 0;
		virtual const glm::mat4& GetProjectionMatrix() const = 0;
		virtual const glm::mat4& GetViewMatrix() const = 0;
		virtual const glm::mat4& GetViewProjectionMatrix() const = 0;
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
		PrespectiveCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
		virtual ~PrespectiveCamera();

		virtual void OnEvent(Event& e) override;

		virtual void SetScreenParam(float width, float height) override
		{
			m_ScreenHeight = height;
			m_ScreenWidth = width;
		}
		virtual const glm::mat4& GetProjectionMatrix()const override { return m_ProjectionMatrix; }
		virtual const glm::mat4& GetViewMatrix()const override { return m_ViewMatrix; }
		virtual const glm::mat4& GetViewProjectionMatrix()const override
		{
			return GetProjectionMatrix() * GetViewMatrix();
		}
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
	};

	class OrthographicCamera :public Camera
	{
	public:
		OrthographicCamera();
		OrthographicCamera(float left, float right, float bottom, float top);
		virtual ~OrthographicCamera();

		virtual void OnEvent(Event& e) override;

		virtual void SetScreenParam(float width, float height) override;
		virtual const glm::mat4& GetProjectionMatrix()const override { return m_ProjectionMatrix; }
		virtual const glm::mat4& GetViewMatrix()const override { return m_ViewMatrix; }
		virtual const glm::mat4& GetViewProjectionMatrix()const override
		{
			return GetProjectionMatrix() * GetViewMatrix();
		}
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
		float m_MovementSpeed = 2.5f, m_RotationSpeed = 30.0f, m_MouseSensitivity = 0.1f;
		float m_ScreenWidth = 800, m_ScreenHeight = 600;
	};
}


