#ifndef MENU_H_
#define MENU_H_

#include "cg/cg.h"
#include "pixmap.h"

#define UP 0
#define OVER 1
#define DOWN 2

#define MAINPAGE 0
#define MULTIPLAYERPAGE 1
#define CREDITSPAGE 2
#define GAMEOVERPAGE 3
#define HOWTOPAGE 4
#define HOWTO2PAGE 5

#define NONE 0
#define SINGLE 1
#define MULTI 2
#define	CREDITS 3
#define COOP 4
#define DUEL 5
#define MULTIBACK 6
#define CREDBACK 7
#define GAMEOVERBACK 8
#define EXIT 9
#define HOWTO 10
#define HOWTONEXT 11
#define HOWTOBACK 12
#define HOWTO2 13
#define HOWTO2BACK 14
#define HOWTOBACKMAIN 15

namespace asteroids {
	class Menu : public cg::Entity, public cg::IDrawListener, public cg::IMouseEventListener {
	private:
		unsigned int _page, _button, _singleState, _multiState, _creditsState, _exitState, _cooperativeState, 
					_duelState, _multibackState, _credbackState, _gameoverbackState, _howToState, _howToBackState,
					_howToNextState, _howTo2BackState, _howToBackMainState;
		double _outcome;
		pixmap *_background, *_singleUp, *_singleOver, *_singleDown, *_multiUp, *_multiOver, *_multiDown,
				*_creditsUp, *_creditsOver, *_creditsDown, *_exitUp, *_exitOver, *_exitDown, *_credits,
				*_cooperativeUp, *_cooperativeOver, *_cooperativeDown, *_duelUp, *_duelOver, *_duelDown,
				*_backDown, *_backOver, *_backUp, *_howToDown, *_howToOver, *_howToUp, *_howTo, *_howTo2,
				*_nextDown, *_nextOver, *_nextUp, *_backMainDown, *_backMainOver, *_backMainUp;
	public:
		Menu(std::string id);
		~Menu();
		void init();
		void draw();
		void onMouse(int button, int state, int x, int y);
		void onMouseMotion(int x, int y);
		void onMousePassiveMotion(int x, int y);
		void gameOver(double outcome);
	};

} // namespace asteroids
#endif