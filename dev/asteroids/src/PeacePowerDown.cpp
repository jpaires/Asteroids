#include "PowerUp.h"
#include "PowerUpsManager.h"
#include "Physics.h"
#include "Ship.h"
#include "PeacePowerDown.h"

namespace asteroids {
	
	PeacePowerDown::PeacePowerDown(std::string id, cg::Vector2d position, bool random) : PowerUp(id, position, random)  {
			init();
		}

		PeacePowerDown::~PeacePowerDown() {
		}

		void PeacePowerDown::init() {
			PowerUp::init();
			if(_random) {
				_texture = _powerUpsManager->getPeaceText();
			} else {
				_texture = _powerUpsManager->getRandomText();
			}
		}

		int PeacePowerDown::isColliding(cg::Vector2d position, int radius, Ship *ship) {
			if(PowerUp::isColliding(position, radius, ship)==1) {
				ship->disableShooting();
				return 1;
			}
			return 0;
		}
} //namespace asteroids