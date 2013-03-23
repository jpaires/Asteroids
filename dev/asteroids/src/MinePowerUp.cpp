#include "PowerUp.h"
#include "PowerUpsManager.h"
#include "Physics.h"
#include "Ship.h"
#include "MinePowerUp.h"

namespace asteroids {
	
	MinePowerUp::MinePowerUp(std::string id, cg::Vector2d position, bool random) : PowerUp(id, position, random)  {
			init();
		}

		MinePowerUp::~MinePowerUp() {
		}

		void MinePowerUp::init() {
			PowerUp::init();
			if(_random) {
				_texture = _powerUpsManager->getMineText();
			} else {
				_texture = _powerUpsManager->getRandomText();
			}
		}

		int MinePowerUp::isColliding(cg::Vector2d position, int radius, Ship *ship) {
			if(PowerUp::isColliding(position, radius, ship)==1) {
				ship->mineReload();
				return 1;
			}
			return 0;
		}
} //namespace asteroids