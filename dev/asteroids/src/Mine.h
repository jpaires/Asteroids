#ifndef MINE_H_
#define MINE_H_

#include <string>
#include <cmath>
#include "cg/cg.h"
#include "glm.h"
#include "utils.h"
#include "Weapon.h"

namespace asteroids {
	class Ship;
	class Physics;
	class WeaponsManager;

	class Mine : public Weapon {
		private:
			int _mineInit, _shotColliding;
			GLMmodel* _modelMine;
		public:
			Mine(std::string id, int playernumber, cg::Vector2d position, double angle);
			~Mine();
			void init();
			void draw();
			void update(unsigned long elapsed_millis);
			void explode();
	};

}	// namespace asteroids


#endif