#pragma once
#include "Game/GameComponents/PointSystem.h"
#include <vector>
#include <iostream>

#include "GameEngine/Util/CollisionManager.h"	
using namespace GameEngine;
pointSystem::pointSystem() {
	//Object will be created at the start of the same and will have the animation
	counter = 0; 
}

pointSystem::~pointSystem() {
	//Nothing to add 
}

int pointSystem::getCounter(){
	return counter;
}

void pointSystem::setCounter(bool collided) {

	if (collided == true) {
		counter++;
	}

}

void pointSystem::Update()
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
			//Check if pointer is pointing to water or CO2 
			
			//If it is a water drop 
			if (colComponent->isWaterDrop) {
				if (counter == 2) {
					
				}

				counter++; 
				
			}

			//If it is smoke 
			else {

				if (counter == 0) {
					break; 
				}

				counter--; 

			}
	

		}
	}
}

