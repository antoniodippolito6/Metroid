#pragma once
#include "StaticObject.h"
#include"GameConfig.h"

namespace MT
{
	class Passable;
}

class MT::Passable : public StaticObject
{
	private:
		//bool _hitted;

	public:

		Passable(QPointF pos) : StaticObject(pos, 2 * TILE, 3 * TILE)
		{
			_collider.adjust(1, 1, -1, -1);
			_compenetrable = false;
		}

		// reimplemented abstract methods
		virtual bool hit(Object* what, Direction fromDir) override { return true; };
		virtual std::string name() override { return "Portal[" + std::to_string(_id) + "]"; }

};