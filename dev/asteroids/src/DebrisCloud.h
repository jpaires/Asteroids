#ifndef DEBRISCLOUD_H_
#define DEBRISCLOUD_H_

#include <string>
#include "cg/cg.h"
#include "ParticlesManager.h"

namespace asteroids {
	class Debris;
	class DebrisManager;

	class DebrisCloud : public ParticlesManager<Debris> {
		private:
			DebrisManager* _debrisManager;
		public:
			DebrisCloud(std::string id, double posx, double posy);
			~DebrisCloud();
			void postUpdate(unsigned long elapsed_millis);
	};
}//namespace asteroids

#endif
