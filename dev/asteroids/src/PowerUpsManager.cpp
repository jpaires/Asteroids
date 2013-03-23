#include "PowerUpsManager.h"
#include "PowerUp.h"
#include "ShieldPowerUp.h"
#include "MinePowerUp.h"
#include "EnergyPowerUp.h"
#include "ShotPowerUp.h"
#include "LifePowerUp.h"
#include "PeacePowerDown.h"
#include "PinPowerDown.h"
#include "Ship.h"

namespace asteroids {
	PowerUpsManager::PowerUpsManager(std::string id) : ParticlesManager<PowerUp>(id, "PowerUp") {
		init();
	}
	
	PowerUpsManager::~PowerUpsManager() {
		FreeTexture(_energyTexture);
		FreeTexture(_shieldTexture);
		FreeTexture(_shotTexture);
		FreeTexture(_mineTexture);
		FreeTexture(_lifeTexture);
		FreeTexture(_randomTexture);
		FreeTexture(_peaceTexture);
		FreeTexture(_pinTexture);
	}
	
	void PowerUpsManager::init() {
		_shieldProb = cg::Properties::instance()->getInt("SHIELDPROB");
		_mineProb = cg::Properties::instance()->getInt("MINEPROB");
		_energyProb = cg::Properties::instance()->getInt("ENERGYPROB");
		_shotProb = cg::Properties::instance()->getInt("SHOTPROB");
		_lifeProb = cg::Properties::instance()->getInt("LIFEPROB");
		_peaceProb = cg::Properties::instance()->getInt("PEACEPROB");
		_pinProb = cg::Properties::instance()->getInt("PINPROB");
		_random = false;
		_randomProb = 50;
		_energyTexture = LoadTexture( "textures/energyPUP.raw", 64, 64 );
		_shieldTexture = LoadTexture( "textures/shieldPUP.raw", 64, 64 );
		_shotTexture = LoadTexture( "textures/shotPUP.raw", 64, 64 );
		_mineTexture = LoadTexture( "textures/minePUP.raw", 64, 64 ); 
		_lifeTexture = LoadTexture( "textures/lifePUP.raw", 64, 64 );
		_randomTexture = LoadTexture( "textures/randomPUP.raw", 64, 64 );
		_peaceTexture = LoadTexture( "textures/peacePD.raw", 64, 64 );
		_pinTexture = LoadTexture( "textures/pinPD.raw", 64, 64 );
	}

	void PowerUpsManager::addPowerUp(double Width, double Height) {

		int randomN = randomBetween(0, 100);
		if( randomN <= _randomProb) {
			_random = true;
		} else {
			_random = false;
		}
		double prob = randomBetween(0, 100);
		if(prob <= _shieldProb) {
			addShieldPowerUp(Width, Height);
			return;
		}
		if(prob <= _shieldProb + _energyProb) {
			addEnergyPowerUp(Width, Height);
			return;
		}
		if(prob <= _shieldProb + _energyProb + _mineProb) {
			addMinePowerUp(Width, Height);
			return;
		}
		if(prob <= _shieldProb + _energyProb + _mineProb + _shotProb) {
			addShotPowerUp(Width, Height);
			return;
		}
		if(prob <= _shieldProb + _energyProb + _mineProb + _shotProb + _lifeProb) {
			addLifePowerUp(Width, Height);
			return;
		}
		if(prob <= _shieldProb + _energyProb + _mineProb + _shotProb + _lifeProb + _peaceProb) {
			addPeacePowerDown(Width, Height);
			return;
		}
		if(prob <= _shieldProb + _energyProb + _mineProb + _shotProb + _lifeProb + _peaceProb + _pinProb) {
			addPinPowerDown(Width, Height);
			return;
		}
	}

	void PowerUpsManager::addShieldPowerUp(double Width, double Height) {
		addParticle(new ShieldPowerUp(getNewId(), cg::Vector2d(Width, Height), _random));
	}

	void PowerUpsManager::addMinePowerUp(double Width, double Height) {
		addParticle(new MinePowerUp(getNewId(), cg::Vector2d(Width, Height), _random));
	}

	void PowerUpsManager::addEnergyPowerUp(double Width, double Height) {
		addParticle(new EnergyPowerUp(getNewId(), cg::Vector2d(Width, Height), _random));
	}

	void PowerUpsManager::addShotPowerUp(double Width, double Height) {
		addParticle(new ShotPowerUp(getNewId(), cg::Vector2d(Width, Height), _random));
	}

	void PowerUpsManager::addLifePowerUp(double Width, double Height) {
		addParticle(new LifePowerUp(getNewId(), cg::Vector2d(Width, Height), _random));
	}

	void PowerUpsManager::addPeacePowerDown(double Width, double Height) {
		addParticle(new PeacePowerDown(getNewId(), cg::Vector2d(Width, Height), _random));
	}

	void PowerUpsManager::addPinPowerDown(double Width, double Height) {
		addParticle(new PinPowerDown(getNewId(), cg::Vector2d(Width, Height), _random));
	}

	int PowerUpsManager::isColliding(cg::Vector2d position, int radius, Ship *ship) {
		unsigned int i;
		int player;
		for (i=0; i < _entities.size(); i++) {
			player = ((PowerUp*)_entities[i])->isColliding(position, radius, ship);
			if (player != 0) {
				return player;
			}
		}
		return 0;
	}

} //namespace asteroids


