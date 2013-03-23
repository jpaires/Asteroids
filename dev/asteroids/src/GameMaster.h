#ifndef GAMEMASTER_H
#define GAMEMASTER_H

#define NONE 0
#define SINGLEGAME 1
#define COOPGAME 2
#define DUELGAME 3
#define DRAWCHECKER 4

#include "cg/cg.h"

namespace asteroids {

	class GameMaster : public cg::Entity, public cg::IKeyboardEventListener, public cg::IReshapeEventListener {
	private:
		Entity *_background, *_levelsManager, *_debrisManager, *_explosionManager,
		*_asteroidsManager, *_weaponsManager, *_thrustManager, *_ship1, *_ship2,
		*_powerUpsManager, *_menu;
		int _gameType;
	public:
		GameMaster();
		~GameMaster();
		void init();
		void newSingleGame();
		void newCoopGame();
		void newDuelGame();
        void onKeyPressed(unsigned char key);
        void onKeyReleased(unsigned char key);
        void onSpecialKeyPressed(int key);
        void onSpecialKeyReleased(int key);
		void onReshape(int width, int height);
		void shipDied();
	};
}

#endif