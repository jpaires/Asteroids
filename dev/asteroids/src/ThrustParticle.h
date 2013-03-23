#ifndef THRUSTPARTICLE_H_
#define THRUSTPARTICLE_H_

#include "utils.h"
#include "cg/cg.h"

namespace asteroids {
	class Physics;
	class ThrustJet;

	class ThrustParticle : public cg::Entity, public cg::IDrawListener, public cg::IUpdateListener {
		private:
			cg::Vector2d _initialPosition, _velocity;
			double _life, _maxlife, _angle;
			Physics* _physics;
			ThrustJet* _thrustJet;
		public:
			ThrustParticle(std::string str, cg::Vector2d position, cg::Vector2d velocity, double angle, ThrustJet* thrustJet);
			~ThrustParticle();
			void init();
			void draw();
			void update(unsigned long elapsed_millis);
	};
} // namespace asteroids
#endif


