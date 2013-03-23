#ifndef BACKGROUND_H_
#define BACKGROUND_H_

#include <string>
#include <vector>
#include "cg/cg.h"
#include "utils.h"
#include "pixmap.h"


namespace asteroids {
	class Background : public cg::Entity, public cg::IDrawListener {
	private:
		std::vector<cg::Vector2i> _starVector;
		pixmap* _img;
	public:	
		Background();
		~Background();
		void init();
		void draw();
	};

}	// namespace asteroids

#endif
