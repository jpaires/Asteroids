#ifndef MINEPOWERUP_H_
#define MINEPOWERUP_H_

#include <string>
#include <cmath>
#include "cg/cg.h"
#include "PowerUp.h"
#include "glm.h"

namespace asteroids {
	class Physics;
	class PowerUpsManager;

	class MinePowerUp : public PowerUp {
		private:
		public:
			MinePowerUp(std::string id, cg::Vector2d position, bool random);
			~MinePowerUp();
			void init();
			int isColliding(cg::Vector2d position, int radius, Ship *ship);
	};

}	// namespace asteroids


#endif