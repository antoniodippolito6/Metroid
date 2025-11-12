#pragma once

#include "DynamicObject.h"
#include "Enemy.h"

namespace MT
{
	class BatShot;
}

class MT::BatShot : public DynamicObject
{
	private:

		//coordinate per spawn
		qreal x_spawn;
		qreal y_spawn;

		// state flags
		bool _up;

		// animations
		QRect _animShot;


	public:

		BatShot(QPointF pos, Direction _dir, bool up);

		// implemented abstract methods
		virtual void animate() override;
		virtual bool hit(Object* what, Direction fromDir) override;
		virtual std::string name() override { return "BatShot[" + std::to_string(_id) + "]"; }
		
		// reimplemented game physics
		virtual void advance() override;
		virtual void defaultPhysics() override;
};