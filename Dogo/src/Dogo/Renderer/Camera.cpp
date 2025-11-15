#include "dgpch.h"
#include "Camera.h"
#include "Dogo/Utils/Logger.h"

namespace Dogo
{
	Camera::Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch)
		: m_Front(glm::vec3(0.0f, 0.0f, 1.0f)), m_MovementSpeed(SPEED), m_MouseSensitivity(SENSITIVITY), m_Zoom(ZOOM), m_Position(pos), m_WorldUp(up), m_Yaw(yaw), m_Pitch(pitch)
	{
		UpdateVectors();
	}
	void Camera::UpdateVectors()
	{
		glm::vec3 front{};
		front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		front.y = sin(glm::radians(m_Pitch));
		front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		m_Front = glm::normalize(front);
		m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
		m_Up = glm::normalize(glm::cross(m_Right, m_Front));
	}
}