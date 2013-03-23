#ifndef LEVELSMANAGER_H_
#define LEVELSMANAGER_H_

#include <string>
#include "utils.h"
#include "cg/cg.h"

namespace asteroids {
	class AsteroidsManager;
	class Ship;
	class Ship2;

	class LevelsManager : public cg::Entity, public cg::IDrawOverlayListener, public cg::IUpdateListener {
		private:
			AsteroidsManager* _asteroidsManager;
			bool _duel;
			int _level;
			Ship* _ship1;
			Ship2* _ship2;
			double _winHeight, _winWidth;
			void makeAsteroid(double minrad, double maxrad);
			bool _changeLevel;
			unsigned int _maxDelay, _currentDelay;
		public:
			LevelsManager(std::string id);
			~LevelsManager();
			void init();
			void drawOverlay();
			void update(unsigned long elapsed_millis);
			void reset(bool duel);
			void nextLevel();
	};
}//namespace asteroids

#endif
