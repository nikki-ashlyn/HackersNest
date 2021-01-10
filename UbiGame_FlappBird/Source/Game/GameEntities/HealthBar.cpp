#include "HealthBar.h"

#include "GameEngine/EntitySystem/Components/CollidableComponent.h"

#include <SFML/Graphics.hpp>

using namespace Game;

HealthBar::HealthBar()
{
	m_renderComponent = AddComponent<GameEngine::SpriteRenderComponent>();
	m_renderComponent->SetFillColor(sf::Color::Red);
	m_renderComponent->SetTexture(GameEngine::eTexture::Tileset);
	m_renderComponent->SetZLevel(2);
	m_renderComponent->SetTileIndex(0, 0);

	AddComponent<GameEngine::CollidableComponent>();
}


HealthBar::~HealthBar()
{

}


void HealthBar::OnAddToWorld()
{
	Entity::OnAddToWorld();
}


void HealthBar::OnRemoveFromWorld()
{
	Entity::OnRemoveFromWorld();
}
