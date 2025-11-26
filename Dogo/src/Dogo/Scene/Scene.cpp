#include "dgpch.h"
#include "Scene.h"


namespace Dogo
{
	void Scene::UpdateGameObjects(double delta)
	{
		for (std::shared_ptr<GameObject> obj : m_GameObjects)
		{
			if (obj)
				obj->Tick(delta);
			else
				DG_TRACE("Object has expired and Tick() was called.");
		}
	}

	void Scene::Init()
	{

	}
}