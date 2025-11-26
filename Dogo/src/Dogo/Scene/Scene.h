#pragma once
#include "Dogo/Actors/Actor.h"
#include "Dogo/Renderer/Core/Camera.h"
namespace Dogo
{
	class Scene
	{
	public:
		Scene() = default;
		~Scene() = default;
		inline void SetMainCamera(const std::weak_ptr<Camera>& cam) { m_MainCamera = cam; }
		inline std::weak_ptr<Camera> GetMainCamera() const { return m_MainCamera; }
		inline std::vector<std::weak_ptr<Camera>> GetCameras() const { return m_Cameras; }
		inline void AddCamera(const std::weak_ptr<Camera>& cam) { m_Cameras.push_back(cam); }
		void UpdateGameObjects(double delta);
		inline void AddGameObject(std::shared_ptr<GameObject> obj) { m_GameObjects.push_back(obj); }
		inline void RemoveGameObject(std::shared_ptr<GameObject> obj)
		{
			auto it = std::remove_if(m_GameObjects.begin(), m_GameObjects.end(),
				[&](const std::shared_ptr<GameObject>& g) {
					return g == obj;
				});
			m_GameObjects.erase(it, m_GameObjects.end());
		}
		void Init();
	private:
		std::vector<std::shared_ptr<GameObject>> m_GameObjects;
		std::vector<std::weak_ptr<Camera>> m_Cameras;
		std::weak_ptr<Camera> m_MainCamera;
	};
}