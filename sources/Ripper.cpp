#include "Ripper.h"
#include "Sprites.h"
#include "Game.h"
#include "GameConfig.h"
#include "Block.h"
#include "Samus.h"

using namespace MT;

Ripper::Ripper(QPointF pos)
	: Enemy(pos, TILE, 8)
{
	_right = false;
	_left = false;
	
	_x_dir = Direction::RIGHT;

	_sprite = Sprites::instance()->getSprite("ripper");

	Sprites::instance()->getAnimation("Ripper_Right", &_animRight);
	Sprites::instance()->getAnimation("Ripper_Left", &_animLeft);

	_x_vel_max = 0.7;
	_x_acc = 1;
	_y_gravity = 0;
}

void Ripper::advance()
{
	if (_x_dir == Direction::RIGHT)
	{
		velAdd(Vec2Df(_x_acc, 0));
	}

	else if (_x_dir == Direction::LEFT)
	{
		velAdd(Vec2Df(-_x_acc, 0));
	}

	resolveCollisions();

	setX(x() + _vel.x);
	setY(y() + _vel.y);
}


void Ripper::animate()
{
	if (_x_dir == Direction::RIGHT)
		_animRect = &_animRight;

	else if (_x_dir == Direction::LEFT)
		_animRect = &_animLeft;
}

bool Ripper::hit(Object* what, Direction fromDir)
{

	if (what->to<Block*>() &&  fromDir == Direction::RIGHT )
		_x_dir = Direction::LEFT;

	if (what->to<Block*>() && fromDir == Direction::LEFT)
		_x_dir = Direction::RIGHT;
	
	return true;
}