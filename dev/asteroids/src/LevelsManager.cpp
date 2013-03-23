#include "LevelsManager.h"
#include "AsteroidsManager.h"
#include "Ship.h"
#include "Ship2.h"

namespace asteroids {
	LevelsManager::LevelsManager(std::string id) : Entity(id) {
		init();
	}
	
	LevelsManager::~LevelsManager() {
	}

	void LevelsManager::init() {
		_asteroidsManager = (AsteroidsManager*)cg::Registry::instance()->get("AsteroidsManager");
		_level = 0;
		_ship1 = (Ship*)cg::Registry::instance()->get("Ship");
		_ship2 = (Ship2*)cg::Registry::instance()->get("ShipTwo");

		cg::tWindow win = cg::Manager::instance()->getApp()->getWindow();
		_winWidth = win.width;
		_winHeight = win.height;
		_changeLevel = false;
		_maxDelay = 3000;
		_currentDelay = 0;
	}

	void LevelsManager::makeAsteroid(double minrad, double maxrad) {
		double posx = randomBetween(0, _winWidth);
		double posy;
		double limit = 80;
		if ((posx > _winWidth/2 - limit) && (posx < _winWidth/2 + limit)) {
			if (randomBetween(0,9) < 5) {
				posy = randomBetween(0, _winHeight/2 - limit);
			} else {
				posy = randomBetween(_winHeight/2 + limit, _winHeight);
			}
		}
		else posy = randomBetween(0, _winHeight);
		_asteroidsManager->addAst(minrad, maxrad, (int) posx, (int) posy);
	}


	void LevelsManager::drawOverlay() {
		glDisable(GL_LIGHTING);
		glColor3d(1,1,1);
		std::ostringstream os;
		if (!_duel) {
			os << "Level " << _level;
			std::string str = os.str();
			cg::Util::instance()->drawBitmapString(str, _winWidth/2 - 15, _winHeight - 20);
		}
		if(_changeLevel) {
			os.str("");
			if (!_duel) {
				os << "Get ready for level " << _level+1;
				std::string str = os.str();
				cg::Util::instance()->drawBitmapString(str, _winWidth/2 - 45, _winHeight - 70);
			} else {
				os << "Get ready for more asteroids!";
				std::string str = os.str();
				cg::Util::instance()->drawBitmapString(str, _winWidth/2 - 60, _winHeight - 70);
			}
		}
	}

	void LevelsManager::update(unsigned long elapsed_millis) {
		if (_changeLevel) {
			_currentDelay += elapsed_millis;
			if(_currentDelay < _maxDelay)
				return;
			_level++;
			if (_duel) {
				if (_level == 1) {
					makeAsteroid(30, 40);
					makeAsteroid(30, 40);
					makeAsteroid(30, 40);
					makeAsteroid(30, 40);
					makeAsteroid(30, 40);
				} else if (_level == 2) {
					makeAsteroid(50, 60);
					makeAsteroid(50, 60);
					makeAsteroid(50, 60);
					makeAsteroid(50, 60);
					_level = 0;
				}
			} else if (_level == 1) {
				makeAsteroid(30, 40);
				makeAsteroid(30, 40);
				makeAsteroid(30, 40);
				makeAsteroid(30, 40);
				makeAsteroid(30, 40);
				makeAsteroid(30, 40);
			}
			else if (_level == 2) {
				makeAsteroid(30, 40);
				makeAsteroid(30, 40);
				makeAsteroid(30, 40);
				makeAsteroid(30, 40);
				makeAsteroid(40, 50);
				makeAsteroid(40, 50);
			}
			else if (_level == 3) {
				makeAsteroid(30, 40);
				makeAsteroid(30, 40);
				makeAsteroid(30, 40);
				makeAsteroid(30, 40);
				makeAsteroid(30, 40);
				makeAsteroid(40, 50);
				makeAsteroid(40, 50);
			}
			else if (_level == 4) {
				makeAsteroid(30, 40);
				makeAsteroid(30, 40);
				makeAsteroid(30, 40);
				makeAsteroid(30, 40);
				makeAsteroid(30, 40);
				makeAsteroid(30, 40);
				makeAsteroid(30, 40);
				makeAsteroid(30, 40);
			}
			else if (_level == 5) {
				makeAsteroid(30, 40);
				makeAsteroid(30, 40);
				makeAsteroid(30, 40);
				makeAsteroid(30, 40);
				makeAsteroid(30, 40);
				makeAsteroid(40, 50);
				makeAsteroid(40, 50);
				makeAsteroid(40, 50);
			}
			else if (_level == 6) {
				makeAsteroid(30, 40);
				makeAsteroid(30, 40);
				makeAsteroid(30, 40);
				makeAsteroid(30, 40);
				makeAsteroid(30, 40);
				makeAsteroid(40, 50);
				makeAsteroid(40, 50);
				makeAsteroid(40, 50);
			}
			else if (_level == 7) {
				makeAsteroid(30, 40);
				makeAsteroid(30, 40);
				makeAsteroid(30, 40);
				makeAsteroid(30, 40);
				makeAsteroid(30, 40);
				makeAsteroid(40, 50);
				makeAsteroid(50, 60);
				makeAsteroid(50, 60);
			}
			else if (_level == 8) {
				makeAsteroid(30, 40);
				makeAsteroid(40, 50);
				makeAsteroid(40, 50);
				makeAsteroid(40, 50);
				makeAsteroid(50, 60);
				makeAsteroid(50, 60);
				makeAsteroid(50, 60);
			}
			else if (_level == 9) {
				makeAsteroid(30, 40);
				makeAsteroid(30, 40);
				makeAsteroid(30, 40);
				makeAsteroid(40, 50);
				makeAsteroid(40, 50);
				makeAsteroid(40, 50);
				makeAsteroid(50, 60);
				makeAsteroid(50, 60);
				makeAsteroid(50, 60);
			}
			else {
				makeAsteroid(30, 40);
				makeAsteroid(30, 40);
				makeAsteroid(30, 40);
				makeAsteroid(30, 40);
				makeAsteroid(30, 40);
				makeAsteroid(40, 50);
				makeAsteroid(40, 50);
				makeAsteroid(40, 50);
				makeAsteroid(50, 60);
				makeAsteroid(50, 60);
				makeAsteroid(50, 60);
			}
			_changeLevel = false;
			_currentDelay = 0;
		}
	}

	void LevelsManager::reset(bool duel) {
		_duel = duel;
		_level = 0;
	}


	void LevelsManager::nextLevel() {
		if (_changeLevel == true )
			return;
		_changeLevel = true;
		_ship1->shieldRegen(_maxDelay);
		_ship2->shieldRegen(_maxDelay);
	}

} // namespace asteroids 