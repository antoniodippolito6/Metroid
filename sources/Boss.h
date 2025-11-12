#pragma once

#include "Enemy.h"

namespace MT
{
	class Boss;
}

class MT::Boss : public Enemy
{
private:

	// state flags
	bool _fire;
	bool _jump;
	bool _hit;

	// reimplemented of physics parameters
	double _x_gravity;

	// animations
	QRect _animStand[2][2];
	QRect _animJump[2][2];
	QRect _animDead;

	int _life = 20;

public:

	Boss(QPointF pos);

	// implemented abstract methods
	virtual std::string name() override { return "Boss[" + std::to_string(_id) + "]"; }

	// getter
	int life() { return _life; }

	// reimplemented abstract methods
	virtual bool hit(Object* what, Direction fromDir) override;
	virtual void advance() override;
	virtual void animate() override;
	virtual void die() override;
};