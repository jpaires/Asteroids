#ifndef SHIP_H_
#define SHIP_H_

#include <string>
#include <cmath>
#include "glm.h"
#include "cg/cg.h"
#include "utils.h"


namespace asteroids {

	class Physics;
	class WeaponsManager;
	class ThrustManager;
	class ExplosionManager;
	class PowerUpsManager;
	class GameMaster;

	class Ship : public cg::Entity, public cg::IDrawListener, public cg::IDrawOverlayListener, 
				public cg::IKeyboardEventListener, public cg::IUpdateListener, public cg::IMouseEventListener {
	protected:
		Physics* _physics;
		WeaponsManager* _weaponsManager;
		ThrustManager* _thrustManager;
		ExplosionManager* _explosionManager;
		PowerUpsManager* _powerUpsManager;
		GameMaster* _gameMaster;
		Ship* _enemy;
		cg::Vector2d _initialPosition;
		bool _duel;
		double _invincibility, _invlimit, _winWidth, _winHeight, _anglestep, _score, _kills;
		double _astep, _alimit, _dstep, _dlimit, _shieldrad, _shieldbar, _shiprad, _lives, _mass;
		int _mouseControl, _thrust, _rotDirection, _mineAmmo, _isCharging, _chargeTime;
		int _chargeDistance, _chargeMaxTime, _playerNumber, _shotLevel;
		double _energy, _maxEnergy, _chargeConsume, _thrustDisable, _thrustDisableLimit, _shootingDisable, _shootingDisableLimit;
		GLMmodel* _modelShip;
	public:	
		Ship(std::string id);
		~Ship();
		void init();
		void draw();
		void drawOverlay();
		void update(unsigned long elapsed_millis);
		bool isColliding(cg::Vector2d position, int radius);
		void explode();
		void shieldRegen(double bonus);
		void mineReload();
		void energyRecharge();
		bool isInvincible();
		void shotUpgrade();
		void addLife();
		void disableThrust();
		void disableShooting();
		void shotMissile();
		void shock(cg::Vector2d collisionPoint, double Force);
		void onKeyPressed(unsigned char key);
        void onKeyReleased(unsigned char key);
        void onSpecialKeyPressed(int key);
        void onSpecialKeyReleased(int key);
		void onMouse(int button, int state, int x, int y);
        void onMouseMotion(int x, int y);
        void onMousePassiveMotion(int x, int y);
		double getXposition();
		double getYposition();
		cg::Vector2d getPosition();
		double getAngle();
		cg::Vector2d getVelocity();
		double getMass();
		void addScore(double score);
		double getScore();
		void addKill();
		void reset(bool duel);
		bool isAlive();
	};

}	// namespace asteroids


#endif
