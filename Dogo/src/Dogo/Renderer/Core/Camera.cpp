#include "dgpch.h"
#include "Camera.h"

namespace Dogo
{
    void Camera::Init(float a, float b, float c, float d, const glm::vec3& pos)
    {
        SetPosition(pos);
        if (m_Type == CameraType::PERSPECTIVE)
            SetPerspective(a, b, c, d);
        else
            SetOrthographic(a, b, c, d);
        m_RenderTarget = std::unique_ptr<Framebuffer>(Framebuffer::Create(800, 600));
    }

    void Camera::UpdateVectors()
    {
        m_Front = glm::normalize(m_Orientation * glm::vec3(0.0f, 0.0f, -1.0f));
        m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
        m_Up = glm::normalize(glm::cross(m_Right, m_Front));

        UpdateViewMatrix();
    }

    void Camera::UpdateViewMatrix()
    {
        m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
    }

    glm::mat4 Camera::GetViewMatrix() const
    {
        return m_ViewMatrix;
    }

    glm::mat4 Camera::GetProjectionMatrix() const
    {
        return m_ProjectionMatrix;
    }

    void Camera::Move(Movement dir, float deltaTime)
    {
        float velocity = m_MoveSpeed * deltaTime;
        if (dir == Movement::FORWARD)  m_Position += m_Front * velocity;
        if (dir == Movement::BACKWARD) m_Position -= m_Front * velocity;
        if (dir == Movement::LEFT)     m_Position -= m_Right * velocity;
        if (dir == Movement::RIGHT)    m_Position += m_Right * velocity;

        UpdateViewMatrix();
    }

    void Camera::Rotate(float deltaYaw, float deltaPitch)
    {
        deltaYaw *= m_MouseSensitivity;
        deltaPitch *= m_MouseSensitivity;

        glm::quat yawQ = glm::angleAxis(glm::radians(deltaYaw), m_WorldUp);
        glm::quat pitchQ = glm::angleAxis(glm::radians(deltaPitch), m_Right);

        m_Orientation = glm::normalize(yawQ * pitchQ * m_Orientation);
        UpdateVectors();
    }

    void Camera::SetPerspective(float fov, float aspect, float nearPlane, float farPlane)
    {
        m_Type = CameraType::PERSPECTIVE;
        m_FOV = fov;
        m_Aspect = aspect;
        m_NearPlane = nearPlane;
        m_FarPlane = farPlane;

        m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), m_Aspect, m_NearPlane, m_FarPlane);
    }

    void Camera::SetOrthographic(float width, float height, float nearPlane, float farPlane)
    {
        m_Type = CameraType::ORTHOGRAPHIC;
        m_OrthoWidth = width;
        m_OrthoHeight = height;
        m_NearPlane = nearPlane;
        m_FarPlane = farPlane;
        m_ProjectionMatrix = glm::ortho(
            0.0f,
            width,
            0.0f,
            height,
            nearPlane,
            farPlane);
    }
}
