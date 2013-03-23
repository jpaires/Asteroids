#ifndef DEBRIS_H_
#define DEBRIS_H_

#include "utils.h"
#include "cg/cg.h"

namespace asteroids {
	class Physics;
	class DebrisCloud;

	class Debris : public cg::Entity, public cg::IDrawListener, public cg::IUpdateListener {
		private:
			cg::Vector2d _initialPosition;
			double _life;
			Physics* _physics;
			DebrisCloud* _debrisCloud;
		public:
			Debris(std::string str, double posx, double posy, DebrisCloud* debrisCloud);
			~Debris();
			void init();
			void draw();
			void update(unsigned long elapsed_millis);
	};
} // namespace asteroids
#endif


