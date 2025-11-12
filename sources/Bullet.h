#pragma once

#include "DynamicObject.h"
#include "Enemy.h"

namespace MT
{
	class Bullet;
}

class MT::Bullet : public DynamicObject
{
	private:

		// state flags
		bool _firing;
		bool _up; 

		// animations
		QRect _animFire;
		QRect _animMissFire;

	public:

		Bullet(QPointF pos, Direction _fireDir, bool up);

		// implemented abstract methods
		virtual void animate() override;
		virtual bool hit(Object* what, Direction fromDir) override;
		virtual std::string name() override { return "Bullet[" + std::to_string(_id) + "]"; }
		
		// reimplemented game physics
		virtual void advance() override;
		virtual void defaultPhysics() override;
};