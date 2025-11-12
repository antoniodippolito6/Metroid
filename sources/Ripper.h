#pragma once

#include "Enemy.h"

namespace MT
{
	class Ripper;
}

class MT::Ripper : public Enemy
{
	private:
		//state flags
		bool _left;
		bool _right;

		// reimplemented physics parameters 
		double _x_gravity;
		
		//animation
		QRect _animRight;
		QRect _animLeft;
		
	public:

		Ripper(QPointF pos);

		// implemented abstract methods
		virtual std::string name() override { return "ripper[" + std::to_string(_id) + "]"; }

		// reimplemented abstract methods
		virtual bool hit(Object* what, Direction fromDir) override;
		// reimplemented game physics
		virtual void advance() override;
		virtual void animate() override;
};