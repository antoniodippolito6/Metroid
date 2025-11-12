#pragma once

#include "Enemy.h"

namespace MT
{
	class Bat;
}

class MT::Bat : public Enemy
{
private:

	// state flags
	bool _hunting;
	bool _injured;
	bool _died;

	// animations
	QRect _batWalk[3];
	QRect _batInjured[3];
	QRect _batExplode;

	int _life = 3;

public:

	Bat(QPointF pos);

	// implemented abstract methods
	virtual std::string name() override { return "Bat[" + std::to_string(_id) + "]"; }
	virtual bool hit(Object* what, Direction fromDir) override;

	// reimplemented game physics
	virtual void defaultPhysics() override;
	virtual void advance() override;

	// reimplemented abstract methods
	virtual void animate() override;
	virtual void die() override;
};