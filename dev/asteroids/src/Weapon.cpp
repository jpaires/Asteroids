#include "Weapon.h"
#include "WeaponsManager.h"
#include "Physics.h"
#include "Ship.h"

namespace asteroids {
	
	Weapon::Weapon(std::string id, int playernumber, cg::Vector2d position, double angle) : cg::Entity(id) {
		_initPosition = position;
		_initAngle = angle;
		_playerNumber = playernumber;
		init();
	}

	Weapon::~Weapon() {
	}

	void Weapon::init() {
		_weaponsManager = (WeaponsManager*)cg::Registry::instance()->get("WeaponsManager");
	}

	cg::Vector2d Weapon::getPosition() {
		return _physics->getPosition();
	}

	double Weapon::getMass() {
		return _physics->getMass();
	}
		
	
	double Weapon::getVelocity() {
		return length(_physics->getVelocity());
	}

	cg::Vector2d Weapon::getCollisionPoint(cg::Vector2d position) {
		return (_physics->getCollisionPoint(position));
	}

	int Weapon::isColliding(cg::Vector2d position, int radius) {
		if (_physics->isColliding(position, radius)) {
			_weaponsManager->removeParticle(cg::Entity::getId());
			return _playerNumber;
		}
		return 0;
	}
	
} //namespace asteroids