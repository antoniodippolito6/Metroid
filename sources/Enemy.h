#pragma once

#include "DynamicObject.h"

namespace MT
{
	class Enemy;
}

class MT::Enemy: public DynamicObject
{
	protected:

		// state flags
		bool _dying;

		// animations
		QRect _animWalk[2][2];
		QRect _animBubble[2][2];
		QRect _animDie[4];

	public:

		Enemy(QPointF pos, double width, double height);

		// getters
		QPixmap* sprite() { return _sprite; }
		bool dying() { return _dying; }

		// implemented abstract methods
		virtual bool hit(Object* what, Direction fromDir) override;
		virtual void animate() override;

		// nonimplemented abstract methods
		virtual std::string name() override = 0;

		// actions
		virtual void die();
};