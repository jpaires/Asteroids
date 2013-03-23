#include "PowerUp.h"
#include "PowerUpsManager.h"
#include "Physics.h"
#include "Ship.h"
#include "EnergyPowerUp.h"

namespace asteroids {
	
	EnergyPowerUp::EnergyPowerUp(std::string id, cg::Vector2d position, bool random) : PowerUp(id, position, random)  {
			init();
		}

		EnergyPowerUp::~EnergyPowerUp() {
		}

		void EnergyPowerUp::init() {
			PowerUp::init();
			if(_random) {
				_texture = _powerUpsManager->getEnergyText();
			} else {
				_texture = _powerUpsManager->getRandomText();
			}
		}

		
		int EnergyPowerUp::isColliding(cg::Vector2d position, int radius, Ship *ship) {
			if(PowerUp::isColliding(position, radius, ship)==1) {
				ship->energyRecharge();
				return 1;
			}
			return 0;
		}
} //namespace asteroids