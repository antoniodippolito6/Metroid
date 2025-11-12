#pragma once

#include "Object.h"

namespace MT
{
	class StaticObject;
}

class MT::StaticObject : public Object
{
	public:

		StaticObject(QPointF pos, double width, double height) :
			Object(pos, width, height){}

		// implemented abstract methods
		virtual void advance() override {}
		virtual void animate() override {}

		// nonimplemented abstract methods
		virtual bool hit(Object* what, Direction fromDir) override = 0;
		virtual std::string name() override = 0;
};