#include "PowerUp.h"
#include "PowerUpsManager.h"
#include "Physics.h"
#include "Ship.h"
#include "ShotPowerUp.h"

namespace asteroids {
	
	ShotPowerUp::ShotPowerUp(std::string id, cg::Vector2d position, bool random) : PowerUp(id, position, random)  {
			init();
		}

		ShotPowerUp::~ShotPowerUp() {
		}

		void ShotPowerUp::init() {
			PowerUp::init();
			if(_random) {
				_texture = _powerUpsManager->getShotText();
			} else {
				_texture = _powerUpsManager->getRandomText();
			}
		}

		
		int ShotPowerUp::isColliding(cg::Vector2d position, int radius, Ship *ship) {
			if(PowerUp::isColliding(position, radius, ship)==1) {
				ship->shotUpgrade();
				return 1;
			}
			return 0;
		}
} //namespace asteroids