#ifndef POWERUP_H_
#define POWERUP_H_

#include <string>
#include <cmath>
#include "cg/cg.h"
#include "utils.h"

namespace asteroids {
	class Ship;
	class Physics;
	class PowerUpsManager;

	class PowerUp : public cg::Entity, public cg::IDrawListener, public cg::IUpdateListener {
		protected:
			cg::Vector2d _initPosition;
			Physics* _physics;
			PowerUpsManager* _powerUpsManager;
			GLuint _texture;
			double _life;
			bool _random;
		public:
			PowerUp(std::string id, cg::Vector2d position, bool random);
			~PowerUp();
			void init();
			void draw();
			virtual int isColliding(cg::Vector2d position, int radius, Ship *ship);
			void update(unsigned long elapsed_millis);

	};

}	// namespace asteroids


#endif