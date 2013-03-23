#include "DebrisManager.h"
#include "DebrisCloud.h"

namespace asteroids {
	DebrisManager::DebrisManager(std::string id) : ParticlesManager<DebrisCloud>(id, "Cloud") {
	}
	
	DebrisManager::~DebrisManager() {}
	
	void DebrisManager::debrisExplosion(double posx, double posy) {
		addParticle(new DebrisCloud(getNewId(), posx, posy));
	}

} //namespace asteroids


