#ifndef ASTEROIDSMANAGER_H_
#define ASTEROIDSMANAGER_H_

#include <string>
#include "cg/cg.h"
#include "ParticlesManager.h"

namespace asteroids {
	class Asteroid;
	class LevelsManager;

	class AsteroidsManager : public ParticlesManager<Asteroid>, public cg::IDrawOverlayListener {
		private:
			LevelsManager* _levelsManager;
			double _winWidth, _winHeight;
			int _minimap;
		public:
			AsteroidsManager(std::string id);
			~AsteroidsManager();
			void addAst(int min, int max);
			void addAst(int min, int max, double posx, double posy);
			void postUpdate(unsigned long elapsed_millis);
			void drawOverlay();
			void draw();
	};
}//namespace asteroids

#endif
