#pragma once

#include "Scene.h"

#include "entt.hpp"

namespace Based
{
  class Entity
  {
    public:
      Entity() = default;
      Entity( entt::entity handle, Scene* scene );
      Entity( const Entity& other ) = default;

      template <typename T, typename... Args> T& AddComponent( Args&&... args )
      {
        BSD_CORE_ASSERT( !HasComponent<T>(), "Entity already contains component" );
        return m_Scene->m_Registry.emplace<T>( m_EntityHandle, std::forward<Args>( args )... );
      }

      template <typename T> T& GetComponent()
      {
        BSD_CORE_ASSERT( HasComponent<T>(), "Entity does not have component!" );
        return m_Scene->m_Registry.get<T>( m_EntityHandle );
      }

      template <typename T> bool HasComponent() { return m_Scene->m_Registry.any_of<T>( m_EntityHandle ); }

      template <typename T> void RemoveComponent()
      {
        BSD_CORE_ASSERT( HasComponent<T>(), "Entity does not have component!" );
        m_Scene->m_Registry.remove<T>( m_EntityHandle );
      }

      // operator bool() const { return m_EntityHandle != 0; }

    private:
      entt::entity m_EntityHandle{ 0 };
      Scene* m_Scene = nullptr;
  };
} // namespace Based
