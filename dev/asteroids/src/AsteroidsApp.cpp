#include "AsteroidsApp.h"

namespace asteroids {

	AsteroidsApp::AsteroidsApp() : cg::Application("config.ini") {
		_window.caption = "Asteroids";
		_window.width = 800;
		_window.height = 600;
	}
	AsteroidsApp::~AsteroidsApp() {
	}
	void AsteroidsApp::createEntities() {

		addEntity(new TopCamera());
		addEntity(new GameMaster());
		addEntity(new Background());
		addEntity(new LevelsManager("LevelsManager"));
		addEntity(new DebrisManager("DebrisManager"));
		addEntity(new ThrustManager("ThrustManager"));
		addEntity(new ExplosionManager("ExplosionManager"));
		addEntity(new AsteroidsManager("AsteroidsManager"));
		addEntity(new WeaponsManager("WeaponsManager"));
		addEntity(new PowerUpsManager("PowerUpsManager"));
		addEntity(new Menu("Menu"));
		addEntity(new Ship2("ShipTwo"));
		addEntity(new Ship("Ship"));

	}
} //namespace asteroids
