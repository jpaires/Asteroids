#ifndef DEBRISMANAGER_H_
#define DEBRISMANAGER_H_

#include <string>
#include "cg/cg.h"
#include "ParticlesManager.h"

namespace asteroids {
	class DebrisCloud;

	class DebrisManager : public ParticlesManager<DebrisCloud> {
		private:
		public:
			DebrisManager(std::string id);
			~DebrisManager();
			void debrisExplosion(double posx, double posy);
	};
}//namespace asteroids

#endif
