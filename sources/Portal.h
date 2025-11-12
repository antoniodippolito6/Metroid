#pragma once
#include "StaticObject.h"
#include "Samus.h"

namespace MT
{
	class Portal;
}

class MT::Portal : public StaticObject
{
	private:

		//state flags
		bool _hitted;
		bool _position; // if position is true then portal is turned to dx, else to sx
		bool _color;	// if color is true then portal is orange, else it'
		bool _animHitted;

		// animations
		QRect _animPortalBlueLeft[2];
		QRect _animPortalBlueRight[2];
		QRect _animPortalOrangeLeft[2];
		QRect _animPortalOrangeRight[2];

	public:

		Portal(QPointF pos, bool _position, bool _color);

		// reimplemented abstract methods
		virtual bool hit(Object* what, Direction fromDir) override;
		virtual std::string name() override { return "Portal[" + std::to_string(_id) + "]"; }
		virtual void advance() override;
		virtual void animate() override;
};