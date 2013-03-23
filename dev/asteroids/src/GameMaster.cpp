#include "GameMaster.h"
#include "Ship.h"
#include "ParticlesManager.h"
#include "LevelsManager.h"
#include "Menu.h"

namespace asteroids {

	GameMaster::GameMaster() : cg::Entity("GameMaster") {

	}
	GameMaster::~GameMaster() {
	}

	void GameMaster::init() {
		_background = cg::Registry::instance()->get("Background");
		_levelsManager = cg::Registry::instance()->get("LevelsManager");
		_debrisManager = cg::Registry::instance()->get("DebrisManager");
		_explosionManager = cg::Registry::instance()->get("ExplosionManager");
		_asteroidsManager = cg::Registry::instance()->get("AsteroidsManager");
		_thrustManager = cg::Registry::instance()->get("ThrustManager");
		_weaponsManager = cg::Registry::instance()->get("WeaponsManager");
		_powerUpsManager = cg::Registry::instance()->get("PowerUpsManager");
		_menu = cg::Registry::instance()->get("Menu");
		_ship1 = cg::Registry::instance()->get("Ship");
		_ship2 = cg::Registry::instance()->get("ShipTwo");

		_gameType = NONE;

		_background->state.disable();
		_levelsManager->state.disable();
		_debrisManager->state.disable();
		_explosionManager->state.disable();
		_asteroidsManager->state.disable();
		_weaponsManager->state.disable();
		_powerUpsManager->state.disable();
		_ship1->state.disable();
		_ship2->state.disable();

	}

	void GameMaster::newSingleGame() {
		_gameType = SINGLEGAME;
		_background->state.enable();
		_levelsManager->state.enable();
		((LevelsManager*)_levelsManager)->reset(false);
		_debrisManager->state.enable();
		((ParticlesManager<class P>*)_debrisManager)->reset();
		_explosionManager->state.enable();
		((ParticlesManager<class P>*)_explosionManager)->reset();
		_asteroidsManager->state.enable();
		((ParticlesManager<class P>*)_asteroidsManager)->reset();
		_weaponsManager->state.enable();
		((ParticlesManager<class P>*)_weaponsManager)->reset();
		_powerUpsManager->state.enable();
		((ParticlesManager<class P>*)_powerUpsManager)->reset();
		_ship1->state.enable();
		((Ship*)_ship1)->reset(false);
		((Ship*)_ship2)->reset(false);
		_menu->state.disable();
	}

	void GameMaster::newCoopGame() {
		newSingleGame();
		_gameType = COOPGAME;
		_ship2->state.enable();
	}

	void GameMaster::newDuelGame() {
		newCoopGame();
		((Ship*)_ship1)->reset(true);
		((Ship*)_ship2)->reset(true);
		((LevelsManager*)_levelsManager)->reset(true);
		_gameType = DUELGAME;
	}

	void GameMaster::shipDied() {
		if (_gameType == NONE) return;
		double outcome = 0;
		bool ended = false;
		if ( ((_gameType == SINGLEGAME) || (_gameType == COOPGAME)) && !_ship1->state.isEnabled() && !_ship2->state.isEnabled()) {
			outcome = ((Ship*)_ship1)->getScore() + ((Ship*)_ship2)->getScore();
			_gameType = NONE;
			ended = true;
		} else if (_gameType == DUELGAME) {
			_gameType = DRAWCHECKER;
			ended = true;
		} else if (_gameType == DRAWCHECKER) {
			ended = true;
		}
		if (ended) {
			_menu->state.enable();
			_background->state.disable();
			_levelsManager->state.disable();
			_debrisManager->state.disable();
			_explosionManager->state.disable();
			_asteroidsManager->state.disable();
			_weaponsManager->state.disable();
			_powerUpsManager->state.disable();
			if (_gameType == DRAWCHECKER) {
				if (_ship1->state.isEnabled()) outcome = 1;
				else {
					if (_ship2->state.isEnabled()) outcome = 2;
					else outcome = -1;
				}
			}
			_ship1->state.disable();
			_ship2->state.disable();
			((Menu*)_menu)->gameOver(outcome);
		}
	}

	void GameMaster::onKeyPressed(unsigned char key) {
        if (key == 27) {
			if (_gameType == NONE || _gameType == DRAWCHECKER) return;
			_menu->state.toggle();
			_background->state.toggle();
			_levelsManager->state.toggle();
			_debrisManager->state.toggle();
			_explosionManager->state.toggle();
			_asteroidsManager->state.toggle();
			_weaponsManager->state.toggle();
			_powerUpsManager->state.toggle();
			if(_menu->state.isEnabled()) {
				_ship1->state.disable();
				_ship2->state.disable();
			} else {
				if (((Ship*)_ship1)->isAlive()) _ship1->state.enable();
				if (((Ship*)_ship2)->isAlive() && _gameType > SINGLEGAME) _ship2->state.enable();
			}
        }
	}

	void GameMaster::onKeyReleased(unsigned char key) {
	}

	void GameMaster::onSpecialKeyPressed(int key) {
	}

	void GameMaster::onSpecialKeyReleased(int key) {
	}

	void GameMaster::onReshape(int width, int height) {
		glutReshapeWindow(800,600);
	}
}