#ifndef PEACEPOWERUP_H_
#define PEACEPOWERUP_H_

#include <string>
#include "cg/cg.h"
#include "PowerUp.h"
#include "glm.h"

namespace asteroids {
	class Ship;

	class PeacePowerDown : public PowerUp {
		private:
		public:
			PeacePowerDown(std::string id, cg::Vector2d position, bool random);
			~PeacePowerDown();
			void init();
			int isColliding(cg::Vector2d position, int radius, Ship *ship);
	};

}	// namespace asteroids


#endif