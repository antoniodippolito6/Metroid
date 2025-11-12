#pragma once

#include "StaticObject.h"
#include "Samus.h"

namespace MT
{
	class LifeUp;
}

class MT::LifeUp : public StaticObject
{
	private:

		// animations
		QRect _animLifeUp[2];

	public:

		LifeUp(QPointF pos);

		// implemented abstract methods
		virtual void animate() override;
		virtual bool hit(Object* what, Direction fromDir) override;
		virtual std::string name() override { return "PowerUp[" + std::to_string(_id) + "]"; }
};