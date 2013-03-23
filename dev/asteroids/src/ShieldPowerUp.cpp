#include "PowerUp.h"
#include "PowerUpsManager.h"
#include "Physics.h"
#include "Ship.h"
#include "ShieldPowerUp.h"

namespace asteroids {
	
	ShieldPowerUp::ShieldPowerUp(std::string id, cg::Vector2d position, bool random) : PowerUp(id, position, random)  {
			init();
		}

		ShieldPowerUp::~ShieldPowerUp() {
		}

		void ShieldPowerUp::init() {
			PowerUp::init();
			if(_random) {
				_texture = _powerUpsManager->getShieldText();
			} else {
				_texture = _powerUpsManager->getRandomText();
			}
		}

		int ShieldPowerUp::isColliding(cg::Vector2d position, int radius, Ship *ship) {
			if(PowerUp::isColliding(position, radius, ship)==1) {
				ship->shieldRegen(0);
				return 1;
			}
			return 0;
		}
} //namespace asteroids