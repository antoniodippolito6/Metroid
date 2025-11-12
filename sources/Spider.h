#pragma once

#include "Enemy.h"

namespace MT
{
	class Spider;
}

class MT::Spider : public Enemy
{
	private:
		// state flags
		bool _left;
		bool _right;
		bool _up;
		bool _down;
		bool _clockwise;
		bool _hit;

		// reimplemented physics parameters 
		double _x_gravity;

		// animations
		QRect _animRight[2][2];
		QRect _animLeft[2][2];
		QRect _animUp[2][2];
		QRect _animDown[2][2];
		QRect _animDead;

		int _life=2;

	public:

		Spider(QPointF pos, bool clockwise);

		// implemented abstract methods
		virtual std::string name() override { return "Spider[" + std::to_string(_id) + "]"; }

		// reimplemented abstract methods
		virtual bool hit(Object* what, Direction fromDir) override;
		// reimplemented game physics
		virtual void advance() override;
		virtual void animate() override;
};