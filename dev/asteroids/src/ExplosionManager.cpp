#include "ExplosionManager.h"
#include "Explosion.h"

namespace asteroids {
	ExplosionManager::ExplosionManager(std::string id) : ParticlesManager<Explosion>(id, "Explosion") {
	}
	
	ExplosionManager::~ExplosionManager() {}
	
	void ExplosionManager::explosion(double posx, double posy) {
		addParticle(new Explosion(getNewId(), posx, posy));
	}

} //namespace asteroids


