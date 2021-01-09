#pragma once
#include "GameEngine/EntitySystem/Components/CollidableComponent.h"

	class pointSystem : public CollidableComponent {

	private:
		int counter;

	public:
		pointSystem();
		virtual ~pointSystem();

		void getcounter();
		int setCounter(bool collided);
		virtual void Update() override;




	};
