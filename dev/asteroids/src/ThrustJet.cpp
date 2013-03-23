#include "ThrustJet.h"
#include "ThrustParticle.h"
#include "ThrustManager.h"

namespace asteroids {
	ThrustJet::ThrustJet(std::string id, cg::Vector2d position, cg::Vector2d velocity, double angle) : ParticlesManager<ThrustParticle>(id, "Thrust") {
		_thrustManager = (ThrustManager*)cg::Registry::instance()->get("ThrustManager");
		int i = 0;
		for (i = 0; i < 10; i++)
			addParticle(new ThrustParticle(getNewId(), position, velocity, angle, this));
	}
	
	ThrustJet::~ThrustJet() {}
	
	void ThrustJet::postUpdate(unsigned long elapsed_millis) {
		ParticlesManager::postUpdate(elapsed_millis);
		if ( _entities.size() == 0)
			_thrustManager->removeParticle(cg::Entity::getId());
	}
} //namespace asteroids


