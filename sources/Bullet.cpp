#include "Bullet.h"
#include "GameConfig.h"
#include "Sprites.h"
#include "Bat.h"
#include "Samus.h"
#include "Game.h"
#include "Passable.h"
#include "Portal.h"
#include <QPainter>
#include "Block.h"
#include "PowerUp.h"

using namespace MT;

Bullet::Bullet(QPointF pos, Direction _fireDir, bool up)
	: DynamicObject(pos, 5, 6)
{
	_collider.adjust(2, 2, -2, -2);

	_compenetrable = false;
	_firing = true;
	_up = up;
	
	_x_dir = _fireDir; //Direzione del proiettile sull'asse x 
	
	defaultPhysics();

	_animRect = &_animFire;	
}

void Bullet::defaultPhysics()
{
	_y_gravity = 0;
	_y_acc_up = 0;

	_y_vel_max = 3;
	_y_vel_min = 0.01;

	_x_vel_max = 3;
	_x_vel_min = 0.01;

	// no accelerations / decelerations along x
	_x_acc = 0.8;
	_x_dec_rel = 0;
	_x_dec_skd = 0;
}

void Bullet::advance()
{
	srand(time(0) + _id);

	if (y() < (3 * TILE + rand()%20))
	{
		_vel.y = 0;
		_x_vel_max = 0.3;
		_x_dir = x() < 7.5 * TILE + rand()%TILE ? Direction::RIGHT : Direction::LEFT;
	}

	Samus* player = Game::instance()->player();

	if ( ((x() - player->x()) >= 3* TILE) || (( x()- player->x( )) <= (- 3 * TILE) ) || ((y() - player->y()) <= (-3 * TILE))  )
	{
		setVisible(false);
		setDie();
	}

	if (_up) 
	{
		_y_gravity = -1;
		_y_acc_up = -1;
	}
	DynamicObject::advance();
}

void Bullet::animate()
{
	Samus* player = Game::instance()->player();

	if (_firing && !player->getMissileFire())
	{
		_sprite = Sprites::instance()->getSprite("bullet");
		Sprites::instance()->getAnimation("bullet", &_animFire);
		_animRect = &_animFire;
	}

	else if (_firing && player->getMissileFire() && player->getLookUp())
	{
		_sprite = Sprites::instance()->getSprite("Missile-up");
		Sprites::instance()->getAnimation("Missile-up", &_animMissFire);
		_animRect = &_animMissFire;
	}

	else if (_firing && player->getMissileFire() && _x_dir == Direction::RIGHT)
	{
		_sprite = Sprites::instance()->getSprite("Missile-right");
		Sprites::instance()->getAnimation("Missile-right", &_animMissFire);
		_animRect = &_animMissFire;
	}

	else if (_firing && player->getMissileFire() && _x_dir==Direction::LEFT)
	{
		_sprite = Sprites::instance()->getSprite("Missile-left");
		Sprites::instance()->getAnimation("Missile-left", &_animMissFire);
		_animRect = &_animMissFire;
	}
}

	bool Bullet::hit(Object * what, Direction fromDir)
	{
		if (what->to<Block*>()) 
		{
			setVisible(false);
			setDie();
		}

		if (what->to<Passable*>())
		{
			setVisible(false);
			setDie();
		}

		if (what->to<Portal*>()) 
		{
			setVisible(false);
			setDie();
		}

		if (what->to<Enemy*>()) 
		{
			_compenetrable = true; 
			setVisible(false);
			setDie();
		}
		return true;
	}