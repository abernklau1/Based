#include "Entity.h"
#include "bsdpch.h"

namespace Based
{
  Entity::Entity( entt::entity handle, Scene* scene ) : m_EntityHandle( handle ), m_Scene( scene ) { }

} // namespace Based
