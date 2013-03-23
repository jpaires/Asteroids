#ifndef EXPLOSIONMANAGER_H_
#define EXPLOSIONMANAGER_H_

#include <string>
#include "cg/cg.h"
#include "ParticlesManager.h"

namespace asteroids {
	class Explosion;

	class ExplosionManager : public ParticlesManager<Explosion> {
		private:
		public:
			ExplosionManager(std::string id);
			~ExplosionManager();
			void explosion(double posx, double posy);
	};
}//namespace asteroids

#endif
