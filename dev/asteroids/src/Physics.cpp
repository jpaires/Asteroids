#include "Physics.h"


namespace asteroids {

	Physics::Physics(cg::Vector2d position, cg::Vector2d velocity, int size, double mass) {
		_position= position;
		_velocity = velocity;
		cg::tWindow win = cg::Manager::instance()->getApp()->getWindow();
		_winWidth = win.width;
		_winHeight = win.height;
		_size = size;
		_angle = 0;
		_mass = mass;
	}

	Physics::~Physics() {}

	cg::Vector2d Physics::getPosition() {
		return _position;
	}
	

	void Physics::setPosition(double xPosition, double yPosition) {
		_position[0] = xPosition;
		_position[1] = yPosition;
	}

	
	void Physics::setVelocity(double xVelocity, double yVelocity) {
		_velocity[0] = xVelocity;
		_velocity[1] = yVelocity;
	}

	void Physics::updatePosition(unsigned long elapsed_millis) {
		_position += _velocity * elapsed_millis / 1000;

		if (_position[0] < -_size)
				_position[0] = _winWidth + _size;
			if (_position[0] > _winWidth + _size)
				_position[0] = -_size;
			if (_position[1] < -_size)
				_position[1] = _winHeight + _size;
			if (_position[1] > _winHeight + _size)
				_position[1] = -_size;
	}

    void Physics::accelerate(double step, double limit) {
        cg::Vector2d velupdate = rotateRad(cg::Vector2d(0, step), _angle);
        if (!(length(_velocity + velupdate) > limit))
		    _velocity += velupdate;
    }
    
    
    void Physics::decelerate(double step, double limit) {
        _velocity = _velocity -  _velocity/step;
		if (length(_velocity) < limit)
            setVelocity(0,0);
    }
    
    void Physics::updateAngle(double step) {
		_angle += PI / step;
		if (_angle > 2 * PI)
			_angle -= 2 * PI;
		if (_angle < 0)
			_angle += 2 * PI;
    }

	void Physics::placeOnWorld(double angx, double angy, double angz) {
		glTranslated(_position[0], _position[1], 0.0);
		if (angx != 0 || angy != 0 || angz != 0)
			glRotated(_angle * RADTODEG + 180, angx, angy, angz);
	}

	bool Physics::isColliding(cg::Vector2d position, int radius) {
		return (length(position - _position) < _size + radius);
	}

	cg::Vector2d Physics::getCollisionPoint(cg::Vector2d position) {
		return cg::Vector2d((_position[0] + position[0])/2, (_position[1] + position[1])/2);
	}

	void Physics::shock(cg::Vector2d collisionPoint, double Force) {
		cg::Vector2d collisionVector = cg::Vector2d(_position[0] - collisionPoint[0], _position[1] - collisionPoint[1]);
			collisionVector /= length(collisionVector);
			setVelocity(Force*collisionVector[0]/_mass + _velocity[0],Force*collisionVector[1]/_mass + _velocity[1]);
	}


} //namespace asteroids
