#pragma once
#include "GameEngine/EntitySystem/Components/CollidableComponent.h"

namespace GameEngine {

	class pointSystem : public CollidableComponent {

	private:
		int counter;

	public:
		pointSystem();
		virtual ~pointSystem();

		int getCounter();
		void setCounter(bool collided);
		virtual void Update() override;




	};
}
