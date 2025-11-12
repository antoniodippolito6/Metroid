#pragma once

#include "DynamicObject.h"
#include "Enemy.h"

namespace MT
{
	class BossShot;
}

class MT::BossShot : public DynamicObject
{
	private:

		// state flags
		bool _firing;
		bool _up;

		// animations
		QRect _animFire[4];

	public:

		BossShot(QPointF pos);

		// implemented abstract methods
		virtual void animate() override;
		virtual bool hit(Object* what, Direction fromDir) override;
		virtual std::string name() override { return "BossShot[" + std::to_string(_id) + "]"; }

		// reimplemented abstract methods
		virtual void advance() override;
		virtual void defaultPhysics() override;
};