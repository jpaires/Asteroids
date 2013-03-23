#include "WeaponsManager.h"
#include "Weapon.h"
#include "Missile.h"
#include "ChargeGun.h"
#include "Mine.h"

namespace asteroids {
	WeaponsManager::WeaponsManager(std::string id) : ParticlesManager<Weapon>(id, "Weapon") {
		_modelMissile = glmReadOBJ("models/missile.obj");
		glmScale(_modelMissile, cg::Properties::instance()->getDouble("SHOTSCALE"));
		_modelMine = glmReadOBJ("models/mine.obj");
		glmScale(_modelMine, cg::Properties::instance()->getDouble("MINESCALE"));
		_modelCharge = glmReadOBJ("models/chargegun.obj");
		glmScale(_modelCharge, cg::Properties::instance()->getDouble("CHARGESCALE"));
	}
	
	WeaponsManager::~WeaponsManager() {
		glmDelete(_modelMissile);
		glmDelete(_modelMine);
		glmDelete(_modelCharge);
	}
	
	void WeaponsManager::addMissile(int playernumber, cg::Vector2d position, double angle) {
		addParticle(new Missile(getNewId(), playernumber, position, angle));
	}

	void WeaponsManager::addMine(int playernumber, cg::Vector2d position, double angle) {
		addParticle(new Mine(getNewId(), playernumber, position, angle));
	}

	void WeaponsManager::addChargeShot(int playernumber, cg::Vector2d position, double angle) {
		addParticle(new ChargeGun(getNewId(), playernumber, position, angle));
	}

	int WeaponsManager::isColliding(cg::Vector2d position, int radius) {
		unsigned int i;
		int player;
		for (i=0; i < _entities.size(); i++) {
			player = ((Weapon*)_entities[i])->isColliding(position, radius);
			if (player != 0) {
				return player;
			}
		}
		return 0;
	}

	cg::Vector2d WeaponsManager::getCollisionPoint(cg::Vector2d position, int radius) {
		unsigned int i;
		int player;
		for (i=0; i < _entities.size(); i++) {
			player = ((Weapon*)_entities[i])->isColliding(position, radius);
			if (player != 0) {
				break;
			}
		}
		return ((Weapon*)_entities[i])->getCollisionPoint(position);
	}

	double WeaponsManager::getCollisionForce(cg::Vector2d position, int radius) {
		unsigned int i;
		int player;
		for (i=0; i < _entities.size(); i++) {
			player = ((Weapon*)_entities[i])->isColliding(position, radius);
			if (player != 0) {
				break;
			}
		}
		return (((Weapon*)_entities[i])->getMass())*(((Weapon*)_entities[i])->getVelocity());
	}

	GLMmodel* WeaponsManager::getModelMissile() {
		return _modelMissile;
	}

	GLMmodel* WeaponsManager::getModelMine() {
		return _modelMine;
	}
	GLMmodel* WeaponsManager::getModelCharge() {
		return _modelCharge;
	}
} //namespace asteroids