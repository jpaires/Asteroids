#ifndef SHIELDPOWERUP_H_
#define SHIELDPOWERUP_H_

#include <string>
#include <cmath>
#include "cg/cg.h"
#include "PowerUp.h"
#include "glm.h"

namespace asteroids {
	class Physics;
	class PowerUpsManager;

	class ShieldPowerUp : public PowerUp {
		private:
		public:
			ShieldPowerUp(std::string id, cg::Vector2d position, bool random);
			~ShieldPowerUp();
			void init();
			int isColliding(cg::Vector2d position, int radius, Ship *ship);
	};

}	// namespace asteroids


#endif