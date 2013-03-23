#ifndef THRUSTMANAGER_H_
#define THRUSTMANAGER_H_

#include <string>
#include "cg/cg.h"
#include "ParticlesManager.h"

namespace asteroids {
	class ThrustJet;

	class ThrustManager : public ParticlesManager<ThrustJet> {
		private:
		public:
			ThrustManager(std::string id);
			~ThrustManager();
			void thrust(cg::Vector2d position, cg::Vector2d velocity, double angle);
	};
}//namespace asteroids

#endif
