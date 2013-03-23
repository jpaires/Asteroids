#ifndef ENERGYPOWERUP_H_
#define ENERGYPOWERUP_H_

#include <string>
#include <cmath>
#include "cg/cg.h"
#include "PowerUp.h"
#include "glm.h"

namespace asteroids {
	class Physics;
	class PowerUpsManager;

	class EnergyPowerUp : public PowerUp {
		private:
		public:
			EnergyPowerUp(std::string id, cg::Vector2d position, bool random);
			~EnergyPowerUp();
			void init();
			int isColliding(cg::Vector2d position, int radius, Ship *ship);
	};

}	// namespace asteroids


#endif