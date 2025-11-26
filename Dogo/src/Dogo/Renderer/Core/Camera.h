#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "Dogo/Renderer/Core/FrameBuffer.h"
namespace Dogo
{

    enum class Movement
    {
        FORWARD, BACKWARD, LEFT, RIGHT
    };

    enum class CameraType
    {
        PERSPECTIVE,
        ORTHOGRAPHIC
    };

    class Camera
    {
    public:
        static Camera Perspective(float fov, float aspect, float nearPlane, float farPlane)
        {
            Camera cam;
            cam.SetType(CameraType::PERSPECTIVE);
            cam.Init(fov, aspect, nearPlane, farPlane);
            return cam;
        }

        static Camera Orthographic(float width, float height, float nearPlane, float farPlane)
        {
            Camera cam;
            cam.SetType(CameraType::ORTHOGRAPHIC);
            cam.Init(width, height, nearPlane, farPlane);
            return cam;
        }
    private:
        Camera() = default;

    public:
        glm::mat4 GetViewMatrix() const;
        glm::mat4 GetProjectionMatrix() const;

        void Move(Movement dir, float deltaTime);
        void Rotate(float deltaYaw, float deltaPitch);

        inline CameraType GetType() const { return m_Type; }
        inline glm::vec3 GetPosition() const { return m_Position; }
        inline glm::quat GetOrientation() const { return m_Orientation; }
        inline glm::vec3 GetFront() const { return m_Front; }
        inline glm::vec3 GetRight() const { return m_Right; }
        inline glm::vec3 GetUp() const { return m_Up; }
        inline float GetZoom() const { return m_Zoom; }

        inline void BindTarget() const { m_RenderTarget->Bind(); }
        inline void UnbindTarget() const { m_RenderTarget->Unbind(); }
        inline void SetRenderTargetSize(uint32_t width, uint32_t height) { m_RenderTarget->Resize(width, height); }
        inline std::pair<uint32_t, uint32_t> GetRenderTargetSize() const
        {
            return std::make_pair(m_RenderTarget->GetWidth(), m_RenderTarget->GetHeight());
        }
        inline uint32_t GetRenderTargetID() const { return m_RenderTarget->GetColorAttachmentID(); }

        void SetPerspective(float fov, float aspect, float nearPlane, float farPlane);
        void SetOrthographic(float width, float height, float nearPlane, float farPlane);

        void SetPosition(const glm::vec3& pos) { m_Position = pos; UpdateVectors(); }

    private:
        void UpdateVectors();
        void UpdateViewMatrix();
        void Init(float a, float b, float c, float d);
        inline void SetType(CameraType type) { m_Type = type; }

    private:

        glm::vec3 m_Position{ 0.0f, 0.0f, 10.0f };
        glm::quat m_Orientation{ 1,0,0,0 };

        glm::vec3 m_Front{ 0.0f, 0.0f, -1.0f };
        glm::vec3 m_Right{ 1.0f, 0.0f, 0.0f };
        glm::vec3 m_Up{ 0.0f, 1.0f, 0.0f };
        glm::vec3 m_WorldUp{ 0.0f, 1.0f, 0.0f };

        glm::mat4 m_ViewMatrix{ 1.0f };
        glm::mat4 m_ProjectionMatrix{ 1.0f };

        CameraType m_Type;
        float m_FOV{ 45.0f };
        float m_Aspect{ 16.0f / 9.0f };
        float m_NearPlane{ 0.1f };
        float m_FarPlane{ 1000.0f };
        float m_OrthoWidth{ 10.0f };
        float m_OrthoHeight{ 10.0f };
        float m_MoveSpeed{ 5.0f };
        float m_MouseSensitivity{ 0.1f };
        float m_Zoom{ 1.0f };

        std::unique_ptr<Framebuffer> m_RenderTarget;
    };

}

