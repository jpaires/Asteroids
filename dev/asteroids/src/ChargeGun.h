#ifndef CHARGEGUN_H_
#define CHARGEGUN_H_

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

	class ChargeGun : public Weapon {
		private:
			double _life, _vfactor;
			GLMmodel* _modelCharge;
		public:
			ChargeGun(std::string id, int playernumber, cg::Vector2d position, double angle);
			~ChargeGun();
			void init();
			void draw();
			void update(unsigned long elapsed_millis);			
			int isColliding(cg::Vector2d position, int radius);
	};

}	// namespace asteroids


#endif