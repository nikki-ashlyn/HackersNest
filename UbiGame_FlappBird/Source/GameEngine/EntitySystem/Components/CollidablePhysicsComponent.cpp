#include "CollidablePhysicsComponent.h"

#include "GameEngine/Util/CollisionManager.h"
#include "GameEngine/EntitySystem/Entity.h"
#include <iostream>
#include <vector>

using namespace GameEngine;

CollidablePhysicsComponent::CollidablePhysicsComponent()
{
	counter = 0;
}


CollidablePhysicsComponent::~CollidablePhysicsComponent()
{

}


void CollidablePhysicsComponent::OnAddToWorld()
{
	CollidableComponent::OnAddToWorld();
}


void CollidablePhysicsComponent::OnRemoveFromWorld()
{
	CollidableComponent::OnAddToWorld();
}


void CollidablePhysicsComponent::Update()
{
	//For the time being just a simple intersection check that moves the entity out of all potential intersect boxes
	std::vector<CollidableComponent*>& collidables = CollisionManager::GetInstance()->GetCollidables();

	for (int a = 0; a < collidables.size(); ++a)
	{
		CollidableComponent* colComponent = collidables[a];
		if (colComponent == this)
			continue;

		AABBRect intersection;
		AABBRect myBox = GetWorldAABB();
		AABBRect colideBox = colComponent->GetWorldAABB();
		if (myBox.intersects(colideBox, intersection))
		{
			std::cout << counter << '\n';
			sf::Vector2f pos = sf::Vector2f(0,2000);

			sf::Vector2f waterSize = sf::Vector2f(21, 21);
			sf::Vector2f obstacleSize = sf::Vector2f(20, 20);
			
			//should increment score
			if (colComponent->GetEntity()->GetSize() == waterSize) {
				colComponent->GetEntity()->SetPos(pos);
				counter--;
			}

			//should decrement score
			if (colComponent->GetEntity()->GetSize() == obstacleSize) {
				colComponent->GetEntity()->SetPos(pos);
				counter++;
			}

		}
	}
}