#include "ObstacleEntity.h"

#include "GameEngine/EntitySystem/Components/CollidableComponent.h"

#include <SFML/Graphics.hpp>

using namespace Game;

ObstacleEntity::ObstacleEntity()	
{
	m_renderComponent = AddComponent<GameEngine::SpriteRenderComponent>();
	m_renderComponent->SetFillColor(sf::Color::Red);
	m_renderComponent->SetTexture(GameEngine::eTexture::Bad);
	m_renderComponent->SetZLevel(2);
	m_renderComponent->SetTileIndex(0, 0);

	GameEngine::CollidableComponent* waterDrop = AddComponent<GameEngine::CollidableComponent>();
	waterDrop->isWaterDrop = true;
}


ObstacleEntity::~ObstacleEntity()
{

}


void ObstacleEntity::OnAddToWorld()
{
	Entity::OnAddToWorld();
}


void ObstacleEntity::OnRemoveFromWorld()
{
	Entity::OnRemoveFromWorld();
}
