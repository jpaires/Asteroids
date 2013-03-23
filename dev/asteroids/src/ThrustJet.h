#ifndef THRUSTJET_H_
#define THRUSTJET_H_

#include <string>
#include "cg/cg.h"
#include "ParticlesManager.h"

namespace asteroids {
	class ThrustParticle;
	class ThrustManager;

	class ThrustJet : public ParticlesManager<ThrustParticle> {
		private:
			ThrustManager* _thrustManager;
		public:
			ThrustJet(std::string id, cg::Vector2d position, cg::Vector2d velocity, double angle);
			~ThrustJet();
			void postUpdate(unsigned long elapsed_millis);
	};
}//namespace asteroids

#endif
