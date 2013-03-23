#include "ThrustManager.h"
#include "ThrustJet.h"

namespace asteroids {
	ThrustManager::ThrustManager(std::string id) : ParticlesManager<ThrustJet>(id, "Jet") {
	}
	
	ThrustManager::~ThrustManager() {}
	
	void ThrustManager::thrust(cg::Vector2d position, cg::Vector2d velocity, double angle) {
			addParticle(new ThrustJet(getNewId(), position, velocity, angle));
	}

} //namespace asteroids


