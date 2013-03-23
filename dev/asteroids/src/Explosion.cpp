#include "Explosion.h"				
#include "FireParticle.h"
#include "ExplosionManager.h"

namespace asteroids {
	Explosion::Explosion(std::string id, double posx, double posy) : ParticlesManager<FireParticle>(id, "Fire") {
		_explosionManager = (ExplosionManager*)cg::Registry::instance()->get("ExplosionManager");
		int i = 0;
		for (i = 0; i < 35; i++)
			addParticle(new FireParticle(getNewId(), posx, posy, this));
	}
	
	Explosion::~Explosion() {}

	void Explosion::postUpdate(unsigned long elapsed_millis) {
		ParticlesManager::postUpdate(elapsed_millis);
		if ( _entities.size() == 0)
			_explosionManager->removeParticle(cg::Entity::getId());
	}
} //namespace asteroids


