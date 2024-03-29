#include "Based/Scene/Scene.h"
#include "Based.h"
#include "Based/Scene/Components.h"
#include "Based/Scene/Entity.h"
#include "bsdpch.h"

#include <glm/glm.hpp>

namespace Based
{

  static void OnTransformConstruct( entt::registry& registry, entt::entity entity ) { }

  Scene::Scene()
  {
#if ENTT_EXAMPLE_CODE
    entt::entity entity = m_Registry.create();

    m_Registry.emplace<TransformComponent>( entity, glm::mat4( 1.0f ) );

    m_Registry.on_construct<TransformComponent>().connect<&OnTransformConstruct>();

    if ( m_Registry.has<TransformComponent>( entity ) )
      TransformComponent& transform = m_Registry.get<TransformComponent>( entity );

    auto view = m_Registry.view<TransformComponent>();
    for ( auto entity : view )
    {
      TransformComponent& transform = view.get<TransformComponent>( entity );
    }

    auto group = m_Registry.group<TransformComponent>( entt::get<MeshComponent> );
    for ( auto entity : group )
    {
      auto& [transform, mesh] = group.get<TransformComponent, MeshComponent>( entity );
    }
#endif
  }

  Scene::~Scene() { }

  void Scene::OnUpdate( Timestep ts )
  {

    auto group = m_Registry.group<TransformComponent>( entt::get<SpriteRendererComponent> );
    for ( auto entity : group )
    {
      const auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>( entity );

      Renderer2D::DrawQuad( transform, sprite.Color );
    }
  }

  Entity Scene::CreateEntity( const std::string& name )
  {
    Entity entity = { m_Registry.create(), this };
    entity.AddComponent<TransformComponent>();
    auto& tag = entity.AddComponent<TagComponent>();
    tag.Tag   = tag.Tag.empty() ? "Entity" : tag.Tag;
    return entity;
  }
} // namespace Based
