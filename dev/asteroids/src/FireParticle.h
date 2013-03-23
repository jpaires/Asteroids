#ifndef FIREPARTICLE_H_
#define FIREPARTICLE_H_

#include "utils.h"
#include "cg/cg.h"

namespace asteroids {
	class Physics;
	class Explosion;

	class FireParticle : public cg::Entity, public cg::IDrawListener, public cg::IUpdateListener {
		private:
			cg::Vector2d _initialPosition;
			double _life, _maxlife;
			Physics* _physics;
			Explosion* _explosion;
		public:
			FireParticle(std::string str, double posx, double posy, Explosion* explosion);
			~FireParticle();
			void init();
			void draw();
			void update(unsigned long elapsed_millis);
	};
} // namespace asteroids
#endif


