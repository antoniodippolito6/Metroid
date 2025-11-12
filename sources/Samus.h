#pragma once

#include "DynamicObject.h"

namespace MT
{
	class Samus;
}

class MT::Samus : public DynamicObject
{
private:

	// state flags
	bool _lookUp;
	bool _jump;
	bool _spinning_jump;
	bool _spinning_jumped;
	bool _firing;
	bool _dying;
	bool _roll;
	bool _invincible;
	bool _bumped;
	bool _stuck;
	bool _rolling;
	bool _missilefire;
	bool _hit;
	bool _burnt;

	// animations
	QRect _animspawn;
	QRect _animStand[2];
	QRect _animWalk[3];
	QRect _animJump;
	QRect _animRoll[4];
	QRect _animFall;
	QRect _animSamus_fire_Idle;
	QRect _animSamus_fire_Walk[3];
	QRect _animSamus_fire_Aim_Up;
	QRect _animSamus_fire_Aim_Up_Walk[4];
	QRect _animSamus_fire_Aim_Up_Jump;
	QRect _animSamus_fire_Aim_Right_Jump;
	QRect _animDeath[4];

	QRect _animLookUpStand;
	QRect _animLookUpWalk[3];
	QRect _animLookUpJump;
	QRect _animSpinningJump[4];
	QRect _animMissile;

	int _life = 30;

public:

	Samus(QPointF pos);

	// getters
	bool dying() { return _dying; }
	bool invincible() { return _invincible; }
	bool stuck() { return _stuck; }
	bool get_spinning_jump() { return _spinning_jump; }
	bool getMissileFire() { return _missilefire; }
	bool getLookUp() { return _lookUp; }
	int life() { return _life; }

	//setters
	void setInvincibile(bool invincibile) { _invincible = invincibile; }
	void updateHealth() { _life -= 1; };

	// implemented abstract methods
	virtual void animate() override;
	virtual bool hit(Object* what, Direction fromDir) override;
	virtual std::string name() override { return "Player"; }

	// reimplemented game physics
	virtual void advance() override;
	virtual void jump(bool on = true) override;

	// player actions
	void lookUp(bool _up_pressed);
	void roll();
	void fire();
	void spinning_jump(bool on = true);
	void die();

	// Auxiliary function used to suffer damage every second 
	void burnt();
};