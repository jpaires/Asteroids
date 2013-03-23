#ifndef PINPOWERUP_H_
#define PINPOWERUP_H_

#include <string>
#include "cg/cg.h"
#include "PowerUp.h"
#include "glm.h"

namespace asteroids {
	class Ship;

	class PinPowerDown : public PowerUp {
		private:
		public:
			PinPowerDown(std::string id, cg::Vector2d position, bool random);
			~PinPowerDown();
			void init();
			int isColliding(cg::Vector2d position, int radius, Ship *ship);
	};

}	// namespace asteroids


#endif