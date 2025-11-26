#pragma once
#include "Dogo/Physics/DG_Physics.h"
#include "Dogo/Component/Components.h"
namespace Dogo
{
    class GameObject
    {
    public:
        GameObject() = delete;
        GameObject(const glm::vec3& pos);

        virtual inline DogoECS::Entity* GetEntity() const { return m_Entity; }
        virtual inline void Tick(double delta)  {}
        virtual inline void Init() {}

        template<typename ComponentType, typename... Args>
        ComponentType* AddComponent(Args&&... args)
        {
            ComponentType* comp = ECS::AddComponent<ComponentType>(m_Entity, std::forward<Args>(args)...);
            if (!comp) return nullptr;

            m_ComponentCache[typeid(ComponentType)] = comp;
            return comp;
        }


        template<typename ComponentType>
        ComponentType* GetComponent() const
        {
            auto it = m_ComponentCache.find(typeid(ComponentType));
            if (it != m_ComponentCache.end())
            {
                return static_cast<ComponentType*>(it->second);
            }

            ComponentType* comp = ECS::GetComponent<ComponentType>(m_Entity);
            if (comp)
                m_ComponentCache[typeid(ComponentType)] = comp;
            return comp;
        }
    private:
        DogoECS::Entity* m_Entity;
        mutable std::unordered_map<std::type_index, void*> m_ComponentCache;
    };


	class Actor : public GameObject
	{
	public:
		Actor() = delete;
		Actor(const glm::vec3& pos);

	private:

	};

    class Actor2D : public GameObject
    {
    public:
        Actor2D() = delete;
        Actor2D(const glm::vec3& pos);

    private:

    };

	class Snake : public Actor2D
	{
	public:
        Snake() = delete;
        Snake(const glm::vec3& pos);
		
        void Tick(double delta) override;

	private:
	};

    class Apple : public Actor2D
    {
    public:
        Apple() = delete;
        Apple(const glm::vec3& pos);

    private:
    };
}
