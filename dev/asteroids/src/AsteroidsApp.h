#ifndef ASTEROIDS_APP_H
#define ASTEROIDS_APP_H

#include "cg/cg.h"
#include "TopCamera.h"
#include "Background.h"
#include "Ship.h"
#include "Ship2.h"
#include "AsteroidsManager.h"
#include "WeaponsManager.h"
#include "LevelsManager.h"
#include "DebrisManager.h"
#include "ExplosionManager.h"
#include "ThrustManager.h"
#include "GameMaster.h"
#include "PowerUpsManager.h"
#include "Menu.h"

namespace asteroids {

	class AsteroidsApp : public cg::Application {
	public:
		AsteroidsApp();
		~AsteroidsApp();
		void createEntities();
	};
} //namespace asteroids

#endif
