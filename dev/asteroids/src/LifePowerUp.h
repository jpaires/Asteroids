#ifndef LIFEPOWERUP_H_
#define LIFEPOWERUP_H_

#include <string>
#include "cg/cg.h"
#include "PowerUp.h"
#include "glm.h"

namespace asteroids {
	class Physics;
	class PowerUpsManager;

	class LifePowerUp : public PowerUp {
		private:
		public:
			LifePowerUp(std::string id, cg::Vector2d position, bool random);
			~LifePowerUp();
			void init();
			int isColliding(cg::Vector2d position, int radius, Ship *ship);
	};

}	// namespace asteroids


#endif