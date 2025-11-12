#include "BatShot.h"
#include "GameConfig.h"
#include "Sprites.h"
#include "Samus.h"
#include "Game.h"
#include "Bat.h"
#include "Block.h"
#include <QPainter>

using namespace MT;

BatShot::BatShot(QPointF pos, Direction dir, bool up)
	:DynamicObject(pos, 8, 8)
{
	_collider.adjust(1, 1, -1, -1);
	_boundingRect.adjust(1, 1, -1, -1);

	_compenetrable = true;

	_sprite = Sprites::instance()->getSprite("BatShot");
	Sprites::instance()->getAnimation("BatShot", &_animShot);

	// If up is true the shot will have a direction incident to the floor, otherwise parallel 
	_up = up;
	_x_dir = dir;

	// storage of spawn coordinates 
	// used to determine the range of the batShot
	x_spawn = pos.x();
	y_spawn = pos.y();

	defaultPhysics();

	if (_up)
		_y_gravity = -0.3;
	else
		_y_gravity = 0;
}

void BatShot::defaultPhysics()
{
	_y_acc_up = 1;

	_y_vel_max = 1.5;
	_y_vel_min = 0.01;

	_x_vel_max = 2.5;
	_x_vel_min = 0.1;

	_x_acc = 0.8;
	_x_dec_rel = 0;
	_x_dec_skd = 0;
}

void BatShot::advance()
{

	if (_x_dir == Direction::LEFT)
		move(Direction::LEFT);

	else if (_x_dir == Direction::RIGHT) 
		move(Direction::RIGHT);

	// Batshot range check, must be 2 tiles along x and y axis
	// I use x_spawn and y_spawn for comparison 
	if (((x() - x_spawn) >= 2 * TILE) || ((x() - x_spawn) <= (-2 * TILE)) || ((y() - y_spawn) <= (-2 * TILE)))
	{
		setVisible(false);
		setDie();
	}
	DynamicObject::advance();
	resolveCollisions();
}

void BatShot::animate()
{
	_animRect = &_animShot;
}

bool BatShot::hit(Object* what, Direction fromDir)
{
	// collision control, even if the projectile has not exceeded the range 
	// if it hits samus or a block should disappear
	if (what->to<Block*>())
	{
		setVisible(false);
		setDie();
		return true;
	}
	else if (what->to<Samus*>())
	{
		setVisible(false);
		setDie();
		return true;
	}
		
	return false;
}