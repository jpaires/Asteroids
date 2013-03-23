#ifndef POWERUPS_H_
#define POWERUPS_H_

#include <string>
#include "cg/cg.h"
#include "ParticlesManager.h"

namespace asteroids {
	class PowerUp;
	class ShielPowerUp;
	class MinePowerUp;
	class EnergyPowerUp;
	class ShotPowerUp;
	class LifePowerUp;
	class PeacePowerDown;
	class PinPowerDown;
	class Ship;

	class PowerUpsManager : public ParticlesManager<PowerUp> {
		private:
			double _shieldProb, _mineProb, _energyProb, _shotProb, _lifeProb, _randomProb,
					_peaceProb, _pinProb;
			bool _random;
			GLuint _energyTexture, _shieldTexture, _shotTexture, _mineTexture, _lifeTexture, _randomTexture,
					_peaceTexture, _pinTexture;
		public:
			PowerUpsManager(std::string id);
			~PowerUpsManager();
			void init();
			void addPowerUp(double Width, double Height);
			void addShieldPowerUp(double Width, double Height);
			void addMinePowerUp(double Width, double Height);
			void addEnergyPowerUp(double Width, double Height);
			void addShotPowerUp(double Width, double Height);
			void addLifePowerUp(double Width, double Height);
			void addPeacePowerDown(double Width, double Height);
			void addPinPowerDown(double Width, double Height);
			int isColliding(cg::Vector2d position, int radius, Ship *ship);
			GLuint getEnergyText()													{ return _energyTexture; }
			GLuint getShieldText()													{ return _shieldTexture; }
			GLuint getShotText()													{ return _shotTexture; }
			GLuint getMineText()													{ return _mineTexture; }
			GLuint getLifeText()													{ return _lifeTexture; }
			GLuint getRandomText()													{ return _randomTexture; }
			GLuint getPeaceText()													{ return _peaceTexture; }
			GLuint getPinText()														{ return _pinTexture; }
	};
}//namespace asteroids

#endif
