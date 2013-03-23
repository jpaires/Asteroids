#include "PowerUp.h"
#include "PowerUpsManager.h"
#include "Physics.h"
#include "Ship.h"
#include "PinPowerDown.h"

namespace asteroids {
	
	PinPowerDown::PinPowerDown(std::string id, cg::Vector2d position, bool random) : PowerUp(id, position, random)  {
			init();
		}

		PinPowerDown::~PinPowerDown() {
		}

		void PinPowerDown::init() {
			PowerUp::init();
			if(_random) {
				_texture = _powerUpsManager->getPinText();
			} else {
				_texture = _powerUpsManager->getRandomText();
			}
		}

		int PinPowerDown::isColliding(cg::Vector2d position, int radius, Ship *ship) {
			if(PowerUp::isColliding(position, radius, ship)==1) {
				ship->disableThrust();
				return 1;
			}
			return 0;
		}
} //namespace asteroids