#ifndef TOP_CAMERA_H
#define TOP_CAMERA_H

#include <string>
#include "cg/cg.h"

namespace asteroids {

    class TopCamera : public cg::Entity, 
		public cg::IDrawListener,
		public cg::IReshapeEventListener
	{
    private:
		double _winWidth, _winHeight;

    public:
        TopCamera();
        virtual ~TopCamera();
        void init();
        void draw();
        void onReshape(int width, int height);
	};
} //namespace asteroids

#endif
