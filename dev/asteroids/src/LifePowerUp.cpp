#include "PowerUp.h"
#include "PowerUpsManager.h"
#include "Physics.h"
#include "Ship.h"
#include "LifePowerUp.h"

namespace asteroids {
	
	LifePowerUp::LifePowerUp(std::string id, cg::Vector2d position, bool random) : PowerUp(id, position, random)  {
			init();
		}

		LifePowerUp::~LifePowerUp() {
		}

		void LifePowerUp::init() {
			PowerUp::init();
			if(_random) {
				_texture = _powerUpsManager->getLifeText();
			} else {
				_texture = _powerUpsManager->getRandomText();
			}
		}

		int LifePowerUp::isColliding(cg::Vector2d position, int radius, Ship *ship) {
			if(PowerUp::isColliding(position, radius, ship)==1) {
				ship->addLife();
				return 1;
			}
			return 0;
		}
} //namespace asteroids