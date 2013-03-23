#ifndef SHIP2_H_
#define SHIP2_H_

#include <string>
#include <cmath>
#include "cg/cg.h"
#include "utils.h"
#include "Ship.h"

namespace asteroids {
	
	class Physics;

	class Ship2 : public Ship{
		Ship* _ship1;
	public:	
		Ship2(std::string id);
		~Ship2();
		void init();
		void draw();
		void drawOverlay();
		void update(unsigned long elapsed_millis);
		void onKeyPressed(unsigned char key);
		void onKeyReleased(unsigned char key);
		void onSpecialKeyPressed(int key) {}
		void onSpecialKeyReleased(int key) {}
		void onMouse(int button, int state, int x, int y) {}
		void onMouseMotion(int x, int y) {}
		void onMousePassiveMotion(int x, int y) {}
	};

}	// namespace asteroids


#endif
