#include "DebrisCloud.h"
#include "DebrisManager.h"
#include "Debris.h"

namespace asteroids {
	DebrisCloud::DebrisCloud(std::string id, double posx, double posy) : ParticlesManager<Debris>(id, "Debris") {
		_debrisManager = (DebrisManager*)cg::Registry::instance()->get("DebrisManager");
		int i = 0;
		for (i = 0; i < 25; i++)
			addParticle(new Debris(getNewId(), posx, posy, this));
	}
	
	DebrisCloud::~DebrisCloud() {}
	
	void DebrisCloud::postUpdate(unsigned long elapsed_millis) {
		ParticlesManager::postUpdate(elapsed_millis);
		if ( _entities.size() == 0)
			_debrisManager->removeParticle(cg::Entity::getId());
	}
} //namespace asteroids


