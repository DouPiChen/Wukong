#include "Wupch.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "Wukong/Core/KeyCodes.h"
#include "Wukong/Core/Input.h"

namespace Wukong
{
	PrespectiveCamera::PrespectiveCamera(float posX, float posY,
		float posZ, float upX, float upY, float upZ, float yaw, float pitch)
	{
		m_Position = glm::vec3(posX, posY, posZ);
		m_WorldUp = glm::vec3(upX, upY, upZ);
		m_Yaw = yaw;
		m_Pitch = pitch;

		UpdateCameraVectors();
        m_ProjectionMatrix = glm::perspective(glm::radians(m_Zoom), m_ScreenWidth / m_ScreenHeight, 0.1f, 100.0f);
        m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	}

    PrespectiveCamera::PrespectiveCamera()
    {
        PrespectiveCamera(0.0f, 0.0f, 3.0f, 0.0f, 1.0f, 0.0f, -90.0f, 0.0f); 
	}

	PrespectiveCamera::~PrespectiveCamera()
	{}

    void PrespectiveCamera::OnUpdate(TimeStep ts)
    {
        m_DeltaTime = ts;
    }

    void PrespectiveCamera::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(PrespectiveCamera::OnMouseScroll));
        dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(PrespectiveCamera::OnMouseMovement));
        dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(PrespectiveCamera::OnKeyboard));
    }

	void PrespectiveCamera::UpdateCameraVectors()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		front.y = sin(glm::radians(m_Pitch));
		front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		m_Front = glm::normalize(front);

		m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
		m_Up = glm::normalize(glm::cross(m_Right, m_Front));
	}

    bool PrespectiveCamera::OnKeyboard(KeyPressedEvent& e)
    {
        float velocity = m_MovementSpeed * m_DeltaTime;
        if (Input::IsKeyPressed(Key::W)) //forward
            m_Position += m_Front * velocity;
        if (Input::IsKeyPressed(Key::S)) //backward
            m_Position -= m_Front * velocity;
        if (Input::IsKeyPressed(Key::A)) //left
            m_Position -= m_Right * velocity;
        if (Input::IsKeyPressed(Key::D)) //right
            m_Position += m_Right * velocity;

        m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
        return false;
    }

    bool PrespectiveCamera::OnMouseMovement(MouseMovedEvent& e)
    {
        auto [xpos, ypos] = Input::GetMousePosition();

        if (m_FirstMouse)
        {
            m_LastX = xpos;
            m_LastY = ypos;
            m_FirstMouse = false;
        }

        float xoffset = xpos - m_LastX;
        float yoffset = m_LastY - ypos;

        m_LastX = xpos;
        m_LastY = ypos;

        xoffset *= m_MouseSensitivity;
        yoffset *= m_MouseSensitivity;

        m_Yaw += xoffset;
        m_Pitch += yoffset;

        if (m_Pitch > 89.0f)
            m_Pitch = 89.0f;
        if (m_Pitch < -89.0f)
            m_Pitch = -89.0f;

        UpdateCameraVectors();
        m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
        return false;
    }

    bool PrespectiveCamera::OnMouseScroll(MouseScrolledEvent& e)
    {
        m_Zoom -= (float)e.GetYOffset();
        if (m_Zoom < 1.0f)
            m_Zoom = 1.0f;
        if (m_Zoom > 80.0f)
            m_Zoom = 80.0f;

        m_ProjectionMatrix = glm::perspective(glm::radians(m_Zoom), m_ScreenWidth / m_ScreenHeight, 0.1f, 100.0f);
        return false;
    }

    void PrespectiveCamera::SetScreenParam(float width, float height)
    {
        m_ScreenHeight = height;
        m_ScreenWidth = width;
        m_LastX = m_ScreenWidth / 2;
        m_LastY = m_ScreenHeight / 2;
    }


    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
    {
        m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -10.0f, 10.0f);
        UpdateCameraVectors();
    }
    
    OrthographicCamera::OrthographicCamera()
    {
        m_AspectRatio = m_ScreenWidth / m_ScreenHeight;
        OrthographicCamera(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom);
    }

    OrthographicCamera::~OrthographicCamera()
    {
    }


    void OrthographicCamera::UpdateCameraVectors()
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
            glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));
        m_ViewMatrix = glm::inverse(transform);
    }

    void OrthographicCamera::SetScreenParam(float width, float height)
    {
        m_ScreenHeight = height;
        m_ScreenWidth = width;
        m_AspectRatio = m_ScreenWidth / m_ScreenHeight;
        m_ProjectionMatrix = glm::ortho(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom, -10.0f, 10.0f);
        UpdateCameraVectors();
    }

    void OrthographicCamera::OnUpdate(TimeStep ts)
    {
        m_DeltaTime = ts;
    }

    void OrthographicCamera::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(OrthographicCamera::OnMouseScroll));
        dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(OrthographicCamera::OnKeyboard));
    }

    bool OrthographicCamera::OnKeyboard(KeyPressedEvent& e)
    {

        float velocity = m_MovementSpeed * m_DeltaTime;
        float rotate_velocity = m_RotationSpeed * m_DeltaTime;
        if (Input::IsKeyPressed(Key::W)) //forward
        {
            m_Position.x += -sin(glm::radians(m_Rotation)) * velocity;
            m_Position.y += cos(glm::radians(m_Rotation)) * velocity;
        }
        if (Input::IsKeyPressed(Key::S)) //backward
        {
            m_Position.x -= -sin(glm::radians(m_Rotation)) * velocity;
            m_Position.y -= cos(glm::radians(m_Rotation)) * velocity;
        }
        if (Input::IsKeyPressed(Key::A)) //left
        {
            m_Position.x -= cos(glm::radians(m_Rotation)) * velocity;
            m_Position.y -= sin(glm::radians(m_Rotation)) * velocity;
        }
        if (Input::IsKeyPressed(Key::D)) //right
        {
            m_Position.x += cos(glm::radians(m_Rotation)) * velocity;
            m_Position.y += sin(glm::radians(m_Rotation)) * velocity;
        }

        if (Input::IsKeyPressed(Key::Q)) //left rotation
            m_Rotation -= rotate_velocity;
        if (Input::IsKeyPressed(Key::E)) //right rotation
            m_Rotation += rotate_velocity;
        if (m_Rotation > 180.0f)
        {
            m_Rotation -= 360.0f;
        }
        else if (m_Rotation <= -180.0f)
        {
            m_Rotation += 360.0f;
        }

        UpdateCameraVectors();
        return false;
    }

    bool OrthographicCamera::OnMouseMovement(MouseMovedEvent& e)
    {
        return false;
    }

    bool OrthographicCamera::OnMouseScroll(MouseScrolledEvent& e)
    {
        m_Zoom -= (float)e.GetYOffset();
        m_ProjectionMatrix = glm::ortho(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom, -10.0f, 10.0f);
        UpdateCameraVectors();
        return false;
    }

}
