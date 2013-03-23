#ifndef MISSILE_H_
#define MISSILE_H_

#include <string>
#include <cmath>
#include "cg/cg.h"
#include "utils.h"
#include "Weapon.h"
#include "glm.h"

namespace asteroids {
	class Ship;
	class Physics;
	class WeaponsManager;

	class Missile : public Weapon {
		private:
			double _life, _vfactor;
			GLMmodel* _modelMissile;
		public:
			Missile(std::string id, int playernumber, cg::Vector2d position, double angle);
			~Missile();
			void init();
			void draw();
			void update(unsigned long elapsed_millis);
	};

}	// namespace asteroids


#endif