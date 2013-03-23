#ifndef SHOTPOWERUP_H_
#define SHOTPOWERUP_H_

#include <string>
#include "cg/cg.h"
#include "PowerUp.h"
#include "glm.h"

namespace asteroids {
	class Physics;
	class PowerUpsManager;

	class ShotPowerUp : public PowerUp {
		private:
		public:
			ShotPowerUp(std::string id, cg::Vector2d position, bool random);
			~ShotPowerUp();
			void init();
			int isColliding(cg::Vector2d position, int radius, Ship *ship);
	};

}	// namespace asteroids


#endif