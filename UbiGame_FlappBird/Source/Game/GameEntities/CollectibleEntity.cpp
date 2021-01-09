#include "CollectibleEntity.h"

#include "GameEngine/EntitySystem/Components/CollidableComponent.h"

#include <SFML/Graphics.hpp>

using namespace Game;

CollectibleEntity::CollectibleEntity()
{
	m_renderComponent = AddComponent<GameEngine::SpriteRenderComponent>();
	m_renderComponent->SetFillColor(sf::Color::Red);
	m_renderComponent->SetTexture(GameEngine::eTexture::Particles);
	m_renderComponent->SetZLevel(2);
	m_renderComponent->SetTileIndex(0, 0);

	AddComponent<GameEngine::CollidableComponent>();
}


CollectibleEntity::~CollectibleEntity()
{

}


void CollectibleEntity::OnAddToWorld()
{
	Entity::OnAddToWorld();
}


void CollectibleEntity::OnRemoveFromWorld()
{
	Entity::OnRemoveFromWorld();
}
