#pragma once
#include pointSystem.h 

pointSystem::collidableCollectiableComponent() {
	//Object will be created at the start of the same and will have the animation
	counter = 0; 
}

pointSystem::~collidableCollectiableComponent() {
	//Nothing to add 
}

void pointSystem::getCounter{
	return counter;
}

int pointSystem::setCounter(bool collided) {

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

			//Check if pointer is pointing to water or CO2 

		}
	}
}

