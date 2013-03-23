#ifndef ASTEROID_H_
#define ASTEROID_H_

#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include "cg/cg.h"
#include "utils.h"


namespace asteroids {
	class Physics;
	class Ship;
	class Ship2;
	class AsteroidsManager;
	class WeaponsManager;
	class DebrisManager;
	class ExplosionManager;
	class PowerUpsManager;
	
	class Asteroid : public cg::Entity, public cg::IDrawListener, public cg::IUpdateListener {
		private:
			Physics* _physics;
			int _minradius, _maxradius, _medradius, _topVertex, _downVertex;
			double _posx, _posy, _mass;
			double _anglestep, _rotx, _roty, _rotz;
			std::vector<cg::Vector3d> _points;
			Ship* _ship1;
			Ship2* _ship2;
			AsteroidsManager* _asteroidsManager;
			WeaponsManager* _weaponsManager;
			DebrisManager* _debrisManager;
			ExplosionManager* _explosionManager;
			PowerUpsManager* _powerUpsManager;
		public:
			Asteroid(std::string id, int minradius, int maxradius);
			Asteroid(std::string id, int minradius, int maxradius, double posx, double posy);
			~Asteroid();
			void init();
			void draw();
			void update(unsigned long elapsed_millis);
			void explode();
			double getScore();
			void shock(cg::Vector2d collisionPoint);
			double getXPosition();
			double getYPosition();
	};
} //namespace asteroid

#endif
