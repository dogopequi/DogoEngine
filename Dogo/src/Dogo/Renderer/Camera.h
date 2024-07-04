#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace Dogo
{
	enum class Movement
	{
		FORWARD, BACKWARD, LEFT, RIGHT
	};

	const float YAW = 90.0f;
	const float PITCH = 0.0f;
	const float SPEED = 0.001f;
	const float SENSITIVITY = 0.1f;
	const float ZOOM = 45.0f;

	class Camera
	{
	public:
		Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

		inline glm::mat4 GetViewMatrix() const { return glm::lookAtRH(m_Position, m_Position + m_Front, m_Up); }
		inline glm::vec3 GetPosition() const { return m_Position; }
		inline glm::vec3 GetFront() const { return m_Front; }
		inline glm::vec3 GetUp() const { return m_Up; }
		inline glm::vec3 GetRight() const { return m_Right; }
		inline glm::vec3 GetWorldUp() const { return m_WorldUp; }

		inline void SetPosition(glm::vec3 pos) { m_Position = pos; }
		inline void SetFront(glm::vec3 front) { m_Front = front; }
		inline void SetUp(glm::vec3 up) { m_Up = up; }
		inline void SetRight(glm::vec3 right) { m_Right = right; }
		inline void SetWorldUp(glm::vec3 worldup) { m_WorldUp = worldup; }

		inline float GetYaw() const { return m_Yaw; }
		inline float GetPitch() const { return m_Pitch; }
		inline float GetSpeed() const { return m_MovementSpeed; }
		inline float GetSensitivity() const { return m_MouseSensitivity; }
		inline float GetZoom() const { return m_Zoom; }

		inline void SetYaw(float yaw) { m_Yaw = yaw; }
		inline void SetPitch(float pitch) { m_Pitch = pitch; }
		inline void SetSpeed(float speed) { m_MovementSpeed = speed; }
		inline void SetSensitivity(float sens) { m_MouseSensitivity = sens; }
		inline void SetZoom(float zoom) { m_Zoom = zoom; }

		void UpdateVectors();

	private:

		glm::vec3 m_Position{};
		glm::vec3 m_Front{};
		glm::vec3 m_Up{};
		glm::vec3 m_Right{};
		glm::vec3 m_WorldUp{};

		float m_Yaw{};
		float m_Pitch{};
		float m_MovementSpeed{};
		float m_MouseSensitivity{};
		float m_Zoom{};

	};
}

