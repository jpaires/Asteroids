#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include <string>
#include "cg/cg.h"
#include "ParticlesManager.h"

namespace asteroids {
	class FireParticle;
	class ExplosionManager;

	class Explosion : public ParticlesManager<FireParticle> {
		private:
			ExplosionManager* _explosionManager;
		public:
			Explosion(std::string id, double posx, double posy);
			~Explosion();
			void postUpdate(unsigned long elapsed_millis);
	};
}//namespace asteroids

#endif
