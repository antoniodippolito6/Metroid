#pragma once

#include "StaticObject.h"

namespace MT
{
	class Block;
	class DamagingBlock;
}

// Object used to build the levels
class MT::Block : public StaticObject
{
	public:

		Block(QPointF pos, QColor color, double width, double height, bool state = false) :
			StaticObject(pos, width, height) {}

		// implemented abstract methods
		virtual bool hit(Object* what, Direction fromDir) override { return true; }
		virtual std::string name() override { return "Block[" + std::to_string(_id) + "]"; }
};

// Special block to implement lava
class MT::DamagingBlock : public StaticObject
{
public:

	DamagingBlock(QPointF pos, QColor color, double width, double height) :
		StaticObject(pos, width, height) 
	{
		_compenetrable = true;
	}

	// implemented abstract methods
	virtual bool hit(Object* what, Direction fromDir) override { return true; }
	virtual std::string name() override { return "Block[" + std::to_string(_id) + "]"; }
};
