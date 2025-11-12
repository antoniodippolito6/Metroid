#pragma once

#include "StaticObject.h"
#include "Samus.h"

namespace MT
{
	class PowerUp;
}

class MT::PowerUp : public StaticObject
{
	private:

		PowerUp* power;
		bool _taken=false;

		// animations
		bool _type=false;
		QRect _animRolling;
		QRect _animMissile;

	public:

		PowerUp(QPointF pos,bool type);

		//getters
		bool getType() { return _type; }
		bool getTaken() { return _taken; }
		
		// reimplemented abstract methods
		virtual bool hit(Object* what, Direction fromDir) override;
		virtual std::string name() override { return "PowerUp[" + std::to_string(_id) + "]"; }

};