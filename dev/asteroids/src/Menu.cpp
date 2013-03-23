#include "Menu.h"
#include "GameMaster.h"

namespace asteroids {

	Menu::Menu(std::string id) : cg::Entity(id) {
	}

	Menu::~Menu() {
		delete _background;
		delete _singleUp; delete _singleOver; delete _singleDown;
		delete _multiUp; delete _multiOver; delete _multiDown;
		delete _creditsUp; delete _creditsOver; delete _creditsDown;
		delete _exitUp; delete _exitOver; delete _exitDown;
		delete _cooperativeUp; delete _cooperativeOver; delete _cooperativeDown;
		delete _duelUp; delete _duelOver; delete _duelDown;
		delete _backUp; delete _backOver; delete _backDown;
		delete _howToDown; delete _howToOver; delete _howToUp; delete _howTo; delete _howTo2;
	}

	void Menu::init() {
		_page = MAINPAGE;
		_background = new pixmap("images/menubackground.bmp");
		_credits = new pixmap("images/credits.bmp");
		_singleUp = new pixmap("images/SingleUp.bmp");
		_singleOver = new pixmap("images/SingleOver.bmp");
		_singleDown = new pixmap("images/SingleDown.bmp");
		_singleState = UP;
		_cooperativeUp = new pixmap("images/CooperativeUp.bmp");
		_cooperativeOver = new pixmap("images/CooperativeOver.bmp");
		_cooperativeDown = new pixmap("images/CooperativeDown.bmp");
		_cooperativeState = UP;
		_multiUp = new pixmap("images/MultiUp.bmp");
		_multiOver = new pixmap("images/MultiOver.bmp");
		_multiDown = new pixmap("images/MultiDown.bmp");
		_multiState = UP;
		_duelUp = new pixmap("images/DuelUp.bmp");
		_duelOver = new pixmap("images/DuelOver.bmp");
		_duelDown = new pixmap("images/DuelDown.bmp");
		_duelState = UP;
		_creditsUp = new pixmap("images/CreditsUp.bmp");
		_creditsOver = new pixmap("images/CreditsOver.bmp");
		_creditsDown = new pixmap("images/CreditsDown.bmp");
		_creditsState = UP;
		_exitUp = new pixmap("images/ExitUp.bmp");
		_exitOver = new pixmap("images/ExitOver.bmp");
		_exitDown = new pixmap("images/ExitDown.bmp");
		_exitState = UP;
		_backUp = new pixmap("images/BackUp.bmp");
		_backOver = new pixmap("images/BackOver.bmp");
		_backDown = new pixmap("images/BackDown.bmp");
		_multibackState = UP;
		_credbackState = UP;
		_gameoverbackState = UP;
		_howToDown = new pixmap("images/HowToDown.bmp"); 
		_howToOver = new pixmap("images/HowToOver.bmp");
		_howToUp = new pixmap("images/HowToUp.bmp");
		_howTo = new pixmap("images/HowTo.bmp");
		_howTo2 = new pixmap("images/HowTo2.bmp");
		_howToState = UP;
		_howToBackState = UP;
		_howToNextState = UP;
		_howTo2BackState = UP;
		_nextUp = new pixmap("images/NextUp.bmp");
		_nextOver = new pixmap("images/NextOver.bmp");
		_nextDown = new pixmap("images/NextDown.bmp");
		_backMainDown = new pixmap("images/BackToMainDown.bmp");
		_backMainOver = new pixmap("images/BackToMainOver.bmp");
		_backMainUp = new pixmap("images/BackToMainUp.bmp");
	}

	void Menu::draw() {
		glDisable(GL_LIGHTING);	
		if (_page == MAINPAGE) {
			glRasterPos2d(490, 370);
			switch (_singleState) {
				case UP:			glDrawPixels(_singleUp->width, _singleUp->height - 1, GL_RGB, GL_UNSIGNED_BYTE, _singleUp->data);
									break;
				case OVER:			glDrawPixels(_singleOver->width, _singleOver->height - 1, GL_RGB, GL_UNSIGNED_BYTE, _singleOver->data);
									break;
				case DOWN:			glDrawPixels(_singleDown->width, _singleDown->height - 1, GL_RGB, GL_UNSIGNED_BYTE, _singleDown->data);
									break;
			}
			glRasterPos2d(490, 300);
			switch (_multiState) {
				case UP:			glDrawPixels(_multiUp->width, _multiUp->height - 1, GL_RGB, GL_UNSIGNED_BYTE, _multiUp->data);
									break;
				case OVER:			glDrawPixels(_multiOver->width, _multiOver->height - 1, GL_RGB, GL_UNSIGNED_BYTE, _multiOver->data);
									break;
				case DOWN:			glDrawPixels(_multiDown->width, _multiDown->height - 1, GL_RGB, GL_UNSIGNED_BYTE, _multiDown->data);
									break;
			}
			glRasterPos2d(490, 230);
			switch (_howToState) {
				case UP:			glDrawPixels(_howToUp->width, _howToUp->height - 1, GL_RGB, GL_UNSIGNED_BYTE, _howToUp->data);
									break;
				case OVER:			glDrawPixels(_howToOver->width, _howToOver->height - 1, GL_RGB, GL_UNSIGNED_BYTE, _howToOver->data);
									break;
				case DOWN:			glDrawPixels(_howToDown->width, _howToDown->height - 1, GL_RGB, GL_UNSIGNED_BYTE, _howToDown->data);
									break;
			}
			glRasterPos2d(490, 160);
			switch (_creditsState) {
				case UP:			glDrawPixels(_creditsUp->width, _creditsUp->height - 1, GL_RGB, GL_UNSIGNED_BYTE, _creditsUp->data);
									break;
				case OVER:			glDrawPixels(_creditsOver->width, _creditsOver->height - 1, GL_RGB, GL_UNSIGNED_BYTE, _creditsOver->data);
									break;
				case DOWN:			glDrawPixels(_creditsDown->width, _creditsDown->height - 1, GL_RGB, GL_UNSIGNED_BYTE, _creditsDown->data);
									break;
			}
			glRasterPos2d(490, 70);
			switch (_exitState) {
				case UP:			glDrawPixels(_exitUp->width, _exitUp->height - 1, GL_RGB, GL_UNSIGNED_BYTE, _exitUp->data);
									break;
				case OVER:			glDrawPixels(_exitOver->width, _exitOver->height - 1, GL_RGB, GL_UNSIGNED_BYTE, _exitOver->data);
									break;
				case DOWN:			glDrawPixels(_exitDown->width, _exitDown->height - 1, GL_RGB, GL_UNSIGNED_BYTE, _exitDown->data);
									break;
			}
			glRasterPos2d(0,0);
			glDrawPixels(_background->width, _background->height, GL_RGB, GL_UNSIGNED_BYTE, _background->data);
		} else if (_page == MULTIPLAYERPAGE) {
			glRasterPos2d(490, 370);
			switch (_cooperativeState) {
				case UP:			glDrawPixels(_cooperativeUp->width, _cooperativeUp->height - 1, GL_RGB, GL_UNSIGNED_BYTE, _cooperativeUp->data);
									break;
				case OVER:			glDrawPixels(_cooperativeOver->width, _cooperativeOver->height - 1, GL_RGB, GL_UNSIGNED_BYTE, _cooperativeOver->data);
									break;
				case DOWN:			glDrawPixels(_cooperativeDown->width, _cooperativeDown->height - 1, GL_RGB, GL_UNSIGNED_BYTE, _cooperativeDown->data);
									break;
			}
			glRasterPos2d(490, 300);
			switch (_duelState) {
				case UP:			glDrawPixels(_duelUp->width, _duelUp->height - 1, GL_RGB, GL_UNSIGNED_BYTE, _duelUp->data);
									break;
				case OVER:			glDrawPixels(_duelOver->width, _duelOver->height - 1, GL_RGB, GL_UNSIGNED_BYTE, _duelOver->data);
									break;
				case DOWN:			glDrawPixels(_duelDown->width, _duelDown->height - 1, GL_RGB, GL_UNSIGNED_BYTE, _duelDown->data);
									break;
			}
			glRasterPos2d(490, 70);
			switch (_multibackState) {
				case UP:			glDrawPixels(_backUp->width, _backUp->height - 1, GL_RGB, GL_UNSIGNED_BYTE, _backUp->data);
									break;
				case OVER:			glDrawPixels(_backOver->width, _backOver->height - 1, GL_RGB, GL_UNSIGNED_BYTE, _backOver->data);
									break;
				case DOWN:			glDrawPixels(_backDown->width, _backDown->height - 1, GL_RGB, GL_UNSIGNED_BYTE, _backDown->data);
									break;
			}
			glRasterPos2d(0,0);
			glDrawPixels(_background->width, _background->height, GL_RGB, GL_UNSIGNED_BYTE, _background->data);
		} else if (_page == HOWTOPAGE) {
			glRasterPos2d(110, 5);
			switch (_howToBackState) {
				case UP:			glDrawPixels(_backUp->width, _backUp->height - 1, GL_RGB, GL_UNSIGNED_BYTE, _backUp->data);
									break;
				case OVER:			glDrawPixels(_backOver->width, _backOver->height - 1, GL_RGB, GL_UNSIGNED_BYTE, _backOver->data);
									break;
				case DOWN:			glDrawPixels(_backDown->width, _backDown->height - 1, GL_RGB, GL_UNSIGNED_BYTE, _backDown->data);
									break;
			}
			glRasterPos2d(490, 5);
			switch (_howToNextState) {
				case UP:			glDrawPixels(_nextUp->width, _nextUp->height - 1, GL_RGB, GL_UNSIGNED_BYTE, _nextUp->data);
									break;
				case OVER:			glDrawPixels(_nextOver->width, _nextOver->height - 1, GL_RGB, GL_UNSIGNED_BYTE, _nextOver->data);
									break;
				case DOWN:			glDrawPixels(_nextDown->width, _nextDown->height - 1, GL_RGB, GL_UNSIGNED_BYTE, _nextDown->data);
									break;
			}
			glRasterPos2d(0,0);
			glDrawPixels(_howTo->width, _howTo->height, GL_RGB, GL_UNSIGNED_BYTE, _howTo->data);
		}else if (_page == HOWTO2PAGE) {
			glRasterPos2d(110, 5);
			switch (_howTo2BackState) {
				case UP:			glDrawPixels(_backUp->width, _backUp->height - 1, GL_RGB, GL_UNSIGNED_BYTE, _backUp->data);
									break;
				case OVER:			glDrawPixels(_backOver->width, _backOver->height - 1, GL_RGB, GL_UNSIGNED_BYTE, _backOver->data);
									break;
				case DOWN:			glDrawPixels(_backDown->width, _backDown->height - 1, GL_RGB, GL_UNSIGNED_BYTE, _backDown->data);
									break;
			}
			glRasterPos2d(490, 5);
			switch (_howToBackMainState) {
				case UP:			glDrawPixels(_backMainUp->width, _backMainUp->height - 1, GL_RGB, GL_UNSIGNED_BYTE, _backMainUp->data);
									break;
				case OVER:			glDrawPixels(_backMainOver->width, _backMainOver->height - 1, GL_RGB, GL_UNSIGNED_BYTE, _backMainOver->data);
									break;
				case DOWN:			glDrawPixels(_backMainDown->width, _backMainDown->height - 1, GL_RGB, GL_UNSIGNED_BYTE, _backMainDown->data);
									break;
			}
			glRasterPos2d(0,0);
			glDrawPixels(_howTo2->width, _howTo2->height, GL_RGB, GL_UNSIGNED_BYTE, _howTo2->data);
		}else if (_page == CREDITSPAGE) {
			glRasterPos2d(490, 70);
			switch (_credbackState) {
				case UP:			glDrawPixels(_backUp->width, _backUp->height - 1, GL_RGB, GL_UNSIGNED_BYTE, _backUp->data);
									break;
				case OVER:			glDrawPixels(_backOver->width, _backOver->height - 1, GL_RGB, GL_UNSIGNED_BYTE, _backOver->data);
									break;
				case DOWN:			glDrawPixels(_backDown->width, _backDown->height - 1, GL_RGB, GL_UNSIGNED_BYTE, _backDown->data);
									break;
			}
			glRasterPos2d(0,0);
			glDrawPixels(_credits->width, _credits->height, GL_RGB, GL_UNSIGNED_BYTE, _credits->data);
		} else if (_page == GAMEOVERPAGE) {
			glColor3d(0.9,0.1,0.1);
			cg::Util::instance()->drawBitmapString("GAME OVER", 575, 370);
			glColor3d(1,1,1);
			std::ostringstream os;
			if (_outcome == 1 || _outcome == 2) {
				os << "Player " << _outcome << " won!";
				std::string str = os.str();
				cg::Util::instance()->drawBitmapString(str, 575, 350);
			} else if (_outcome == -1) {
				os << "Draw!";
				std::string str = os.str();
				cg::Util::instance()->drawBitmapString(str, 590, 350);
			} else {
				os << "Score: " << _outcome;	
				std::string str = os.str();
				cg::Util::instance()->drawBitmapString(str, 575, 350);		
			}
			glRasterPos2d(490, 70);
			switch (_gameoverbackState) {
				case UP:			glDrawPixels(_backUp->width, _backUp->height - 1, GL_RGB, GL_UNSIGNED_BYTE, _backUp->data);
									break;
				case OVER:			glDrawPixels(_backOver->width, _backOver->height - 1, GL_RGB, GL_UNSIGNED_BYTE, _backOver->data);
									break;
				case DOWN:			glDrawPixels(_backDown->width, _backDown->height - 1, GL_RGB, GL_UNSIGNED_BYTE, _backDown->data);
									break;
			}
			glRasterPos2d(0,0);
			glDrawPixels(_background->width, _background->height, GL_RGB, GL_UNSIGNED_BYTE, _background->data);
		}
		glEnable(GL_LIGHTING);
	}

	void Menu::onMouse(int button, int state, int x, int y) {
		if (button != GLUT_LEFT_BUTTON) return;
		if (state == GLUT_DOWN) {
			if ( (x > 490) && ( (unsigned) x < 490 + _singleUp->width) &&
				(y < (600-370)) && ( (unsigned) y > (600-370) - _singleUp->height)) {
					if (_page == MAINPAGE) { _button = SINGLE; _singleState = DOWN; }
					if (_page == MULTIPLAYERPAGE) { _button = COOP; _cooperativeState = DOWN; }
			}
			if ( (x > 490) && ( (unsigned) x < 490 + _multiUp->width) &&
				(y < (600-300)) && ( (unsigned) y > (600-300) - _multiUp->height)) {
					if (_page == MAINPAGE) { _button = MULTI; _multiState = DOWN; }
					if (_page == MULTIPLAYERPAGE) { _button = DUEL; _duelState = DOWN; }
			}
			if ( (x > 490) && ( (unsigned) x < 490 + _howToUp->width) &&
				(y < (600-230)) && ( (unsigned) y > (600-230) - _howToUp->height)) {
					if (_page == MAINPAGE) { _button = HOWTO; _howToState = DOWN; }
			}
			if ( (x > 490) && ( (unsigned) x < 490 + _creditsUp->width) &&
				(y < (600-160)) && ( (unsigned) y > (600-160) - _creditsUp->height)) {
					if (_page == MAINPAGE) { _button = CREDITS; _creditsState = DOWN; }
			}
			if ( (x > 490) && ( (unsigned) x < 490 + _exitUp->width) &&
				(y < (600-70)) && ( (unsigned) y > (600-70) - _exitUp->height)) {
					if (_page == MAINPAGE) { _button = EXIT; _exitState = DOWN; }
			}
			if ( (x > 490) && ( (unsigned) x < 490 + _singleUp->width) &&
				(y < (600-70)) && ( (unsigned) y > (600-70) - _singleUp->height)) {
					if (_page == MULTIPLAYERPAGE) { _button = MULTIBACK; _multibackState = DOWN; }
					if (_page == CREDITSPAGE) { _button = CREDBACK; _credbackState = DOWN; }
					if (_page == GAMEOVERPAGE) { _button = GAMEOVERBACK; _gameoverbackState = DOWN; }
			}
			if ( (x > 110) && ( (unsigned) x < 110 + _backUp->width) &&
				(y < (600-5)) && ( (unsigned) y > (600-5) - _backUp->height)) {
					if (_page == HOWTOPAGE) { _button = HOWTOBACK; _howToBackState = DOWN; }
					if (_page == HOWTO2PAGE) { _button = HOWTO2BACK; _howTo2BackState = DOWN; }
			}
			if ( (x > 490) && ( (unsigned) x < 490 + _backUp->width) &&
				(y < (600-5)) && ( (unsigned) y > (600-5) - _backUp->height)) {
					if (_page == HOWTOPAGE) { _button = HOWTONEXT; _howToNextState = DOWN; }
					if (_page == HOWTO2PAGE) { _button = HOWTOBACKMAIN; _howToBackMainState = DOWN; }
			}
		} else {
			_singleState = UP;
			_multiState = UP;
			_creditsState = UP;
			_exitState = UP;
			_cooperativeState = UP;
			_duelState = UP;
			_multibackState = UP;
			_howToState = UP;
			_credbackState = UP;
			_gameoverbackState = UP;
			_howToBackState = UP;
			_howToNextState = UP;
			_howTo2BackState = UP;
			_howToBackMainState = UP;
			if ( (x > 490) && ( (unsigned) x < 490 + _singleUp->width) &&
				(y < (600-370)) && ( (unsigned) y > (600-370) - _singleUp->height)) {
				if (_button == SINGLE) ((GameMaster*) cg::Registry::instance()->get("GameMaster"))->newSingleGame();
				if (_button == COOP) ((GameMaster*) cg::Registry::instance()->get("GameMaster"))->newCoopGame();
			}
			if ( (x > 490) && ( (unsigned) x < 490 + _multiUp->width) &&
				(y < (600-300)) && ( (unsigned) y > (600-300) - _multiUp->height)) {
				if (_button == MULTI) _page = MULTIPLAYERPAGE;
				if (_button == DUEL) ((GameMaster*) cg::Registry::instance()->get("GameMaster"))->newDuelGame();
			}
			if ( (x > 490) && ( (unsigned) x < 490 + _howToUp->width) &&
				(y < (600-230)) && ( (unsigned) y > (600-230) - _howToUp->height)) {
				if (_button == HOWTO) _page = HOWTOPAGE;
			}
			if ( (x > 490) && ( (unsigned) x < 490 + _creditsUp->width) &&
				(y < (600-160)) && ( (unsigned) y > (600-160) - _creditsUp->height)) {
				if (_button == CREDITS) _page = CREDITSPAGE;
			}
			if ( (x > 490) && ( (unsigned) x < 490 + _exitUp->width) &&
				(y < (600-70)) && ( (unsigned) y > (600-70) - _exitUp->height)) {
				if (_button == MULTIBACK) _page = MAINPAGE;
				if (_button == CREDBACK) _page = MAINPAGE;
				if (_button == GAMEOVERBACK) _page = MAINPAGE;
				if (_button == EXIT) cg::Manager::instance()->shutdownApp();
			}
			if ( (x > 110) && ( (unsigned) x < 110 + _backUp->width) &&
				(y < (600-5)) && ( (unsigned) y > (600-5) - _backUp->height)) {
					if (_button == HOWTOBACK) _page = MAINPAGE;
					if (_button == HOWTO2BACK) _page = HOWTOPAGE;
			}
			if ( (x > 490) && ( (unsigned) x < 490 + _backUp->width) &&
				(y < (600-5)) && ( (unsigned) y > (600-5) - _backUp->height)) {
					if (_button == HOWTONEXT) _page = HOWTO2PAGE;
					if (_button == HOWTOBACKMAIN) _page = MAINPAGE;
			}
			_button = NONE;
		}

	}

	void Menu::onMouseMotion(int x, int y) {
		if ( (x > 490) && ( (unsigned) x < 490 + _singleUp->width) &&
			(y < (600-370)) && ( (unsigned) y > (600-370) - _singleUp->height)) {
			if (_button == SINGLE && _page == MAINPAGE) _singleState = DOWN;
			if (_button == COOP && _page == MULTIPLAYERPAGE) _cooperativeState = DOWN;
		}
		else { _singleState = UP; _cooperativeState = UP; }
		if ( (x > 490) && ( (unsigned) x < 490 + _multiUp->width) &&
			(y < (600-300)) && ( (unsigned) y > (600-300) - _multiUp->height)) {
			if (_page == MAINPAGE && _button == MULTI) _multiState = DOWN;
			if (_page == MULTIPLAYERPAGE && _button == DUEL) _duelState = DOWN;
		}
		else { _multiState = UP; _duelState = UP; }
		if ( (x > 490) && ( (unsigned) x < 490 + _howToUp->width) &&
			(y < (600-230)) && ( (unsigned) y > (600-230) - _howToUp->height)) {
			if (_page == MAINPAGE && _button == HOWTO) _howToState = DOWN;
		}
		else _howToState = UP;
		if ( (x > 490) && ( (unsigned) x < 490 + _creditsUp->width) &&
			(y < (600-160)) && ( (unsigned) y > (600-160) - _creditsUp->height)) {
			if (_page == MAINPAGE && _button == CREDITS) _creditsState = DOWN;
		}
		else _creditsState = UP;
		if ( (x > 490) && ( (unsigned) x < 490 + _backUp->width) &&
			(y < (600-70)) && ( (unsigned) y > (600-70) - _backUp->height)) {
			if (_page == MAINPAGE && _button == EXIT) _exitState = DOWN;
			if (_page == MULTIPLAYERPAGE && _button == MULTIBACK) _multibackState = DOWN;
			if (_page == CREDITSPAGE && _button == CREDBACK) _credbackState = DOWN;
			if (_page == GAMEOVERPAGE && _button == GAMEOVERBACK) _gameoverbackState = DOWN;
		}
		else { _exitState = UP; _multibackState = UP; _credbackState = UP; _gameoverbackState = UP; }
		if ( (x > 110) && ( (unsigned) x < 110 + _backUp->width) &&
			(y < (600-5)) && ( (unsigned) y > (600-5) - _backUp->height)) {
				if (_page == HOWTOPAGE && _button == HOWTOBACK) _howToBackState = DOWN;
				if (_page == HOWTO2PAGE && _button == HOWTO2BACK) _howTo2BackState = DOWN;
		}
		else {_howToBackState = UP; _howToBackMainState = UP;}
		if ( (x > 490) && ( (unsigned) x < 490 + _backUp->width) &&
			(y < (600-5)) && ( (unsigned) y > (600-5) - _backUp->height)) {
				if (_page == HOWTOPAGE && _button == HOWTONEXT) _howToNextState = DOWN;
				if (_page == HOWTO2PAGE && _button == HOWTOBACKMAIN) _howToBackMainState = DOWN;
		}
		else {_howToNextState = UP; _howToBackMainState;}
	}

	void Menu::onMousePassiveMotion(int x, int y) {
		if ( (x > 490) && ( (unsigned) x < 490 + _singleUp->width) &&
			(y < (600-370)) && ( (unsigned) y > (600-370) - _singleUp->height)) {
			if (_page == MAINPAGE) _singleState = OVER;
			if (_page == MULTIPLAYERPAGE) _cooperativeState = OVER;
		}
		else { _singleState = UP; _cooperativeState = UP; }
		if ( (x > 490) && ( (unsigned) x < 490 + _multiUp->width) &&
			(y < (600-300)) && ( (unsigned) y > (600-300) - _multiUp->height)) {
			if (_page == MAINPAGE) _multiState = OVER;
			if (_page == MULTIPLAYERPAGE) _duelState = OVER;
		}
		else { _multiState = UP; _duelState = UP; }
		if ( (x > 490) && ( (unsigned) x < 490 + _howToUp->width) &&
			(y < (600-230)) && ( (unsigned) y > (600-230) - _howToUp->height)) {
			if (_page == MAINPAGE) _howToState = OVER;
		}
		else _howToState = UP;
		if ( (x > 490) && ( (unsigned) x < 490 + _creditsUp->width) &&
			(y < (600-160)) && ( (unsigned) y > (600-160) - _creditsUp->height)) {
			if (_page == MAINPAGE) _creditsState = OVER;
		}
		else _creditsState = UP;
		if ( (x > 490) && ( (unsigned) x < 490 + _backUp->width) &&
			(y < (600-70)) && ( (unsigned) y > (600-70) - _backUp->height)) {
			if (_page == MAINPAGE) _exitState = OVER;
			if (_page == MULTIPLAYERPAGE) _multibackState = OVER;
			if (_page == CREDITSPAGE) _credbackState = OVER;
			if (_page == GAMEOVERPAGE) _gameoverbackState = OVER;
		}
		else { _exitState = UP; _multibackState = UP; _credbackState = UP; _gameoverbackState = UP; }
		if ( (x > 110) && ( (unsigned) x < 110 + _backUp->width) &&
			(y < (600-5)) && ( (unsigned) y > (600-5) - _backUp->height)) {
				if (_page == HOWTOPAGE) _howToBackState = OVER;
				if (_page == HOWTO2PAGE) _howTo2BackState = OVER;
		}
		else {_howToBackState = UP; _howTo2BackState = UP;}
		if ( (x > 490) && ( (unsigned) x < 490 + _backUp->width) &&
			(y < (600-5)) && ( (unsigned) y > (600-5) - _backUp->height)) {
				if (_page == HOWTOPAGE) _howToNextState = OVER;
				if (_page == HOWTO2PAGE) _howToBackMainState = OVER;
		}
		else {_howToNextState = UP; _howToBackMainState = UP;}
	}

	void Menu::gameOver(double outcome) {
		_outcome = outcome;
		_page = GAMEOVERPAGE;
	}

} // namespace asteroids