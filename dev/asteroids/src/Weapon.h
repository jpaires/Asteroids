#ifndef WEAPON_H_
#define WEAPON_H_

#include <string>
#include <cmath>
#include "cg/cg.h"
#include "utils.h"

namespace asteroids {
	class Ship;
	class Physics;
	class WeaponsManager;

	class Weapon : public cg::Entity, public cg::IDrawListener, public cg::IUpdateListener {
		protected:
			int _playerNumber;
			cg::Vector2d _initPosition;
			double _initAngle, _mass;
			Physics* _physics;
			WeaponsManager* _weaponsManager;
		public:
			Weapon(std::string id, int playernumber, cg::Vector2d position, double angle);
			~Weapon();
			void init();
			virtual void draw() = 0;
			virtual void update(unsigned long elapsed_millis) = 0;
			cg::Vector2d getPosition();
			double getMass();
			double getVelocity();
			cg::Vector2d getCollisionPoint(cg::Vector2d position);
			virtual int isColliding(cg::Vector2d position, int radius);
	};

}	// namespace asteroids


#endif