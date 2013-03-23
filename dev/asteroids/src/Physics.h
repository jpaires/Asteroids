#ifndef PHYSICS_H_
#define PHYSICS_H_

#include "cg/cg.h"
#include "utils.h"

namespace asteroids {
	class Physics {
		private:
			double _winWidth, _winHeight, _angle, _mass;
			cg::Vector2d _position, _velocity;
			int _size;
		public:
			Physics(cg::Vector2d position, cg::Vector2d velocity, int size, double mass);
			~Physics();
			cg::Vector2d getPosition();
			double getMass()									{ return _mass; }
			void setSize(double newSize)						{ _size = newSize; }
			double getXPosition()                               { return _position[0]; }
			double getYPosition()                               { return _position[1]; }
			void setPosition(cg::Vector2d position)             { _position = position; }
			void setPosition(double xPosition, double yPosition);
			cg::Vector2d getVelocity()                          { return _velocity; }
			double getXVelocity()                               { return _velocity[0]; }
			double getYVelocity()                               { return _velocity[1]; }
			void setVelocity(cg::Vector2d velocity)             { _velocity = velocity; }
			void setVelocity(double xVelocity, double yVelocity);
			void setXVelocity(double xVelocity)                 { _velocity[0] = xVelocity; }
			void setYVelocity(double yVelocity)                 { _velocity[1] = yVelocity; }
			void updatePosition(unsigned long elapsed_millis);
            void accelerate(double step, double limit);
            void decelerate(double step, double limit);
            void setAngle(double angle)                         { _angle = angle; }
            double getAngle()                                   { return _angle; }
            void updateAngle(double step);
			void placeOnWorld(double angx, double angy, double angz);
			bool isColliding(cg::Vector2d position, int radius);
			cg::Vector2d getCollisionPoint(cg::Vector2d position);
			void shock(cg::Vector2d collisionPoint, double Force);
	};


} //namespace asteroids

#endif

