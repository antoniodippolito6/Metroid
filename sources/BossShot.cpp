#include "BossShot.h"
#include "GameConfig.h"
#include "Sprites.h"
#include "Samus.h"
#include "Game.h"
#include <QPainter>
#include "Block.h"
using namespace MT;

BossShot::BossShot(QPointF pos)
	: DynamicObject(pos, 8, 8)
{
	_collider.adjust(2, 2, -2, -2);

	_compenetrable = false;
	_firing = true;
	
	defaultPhysics();

	_sprite = Sprites::instance()->getSprite("bossShot");

	Sprites::instance()->getAnimation("BossShot", &_animFire[0]);
	
	_y_gravity = 0.1;

	srand(time(0) + _id);
	_x_vel_max = ((rand() % 100) / (float)40 + 0.5);
	_y_vel_max = 2;

	velAdd(Vec2Df(0, -6));
}



void BossShot::defaultPhysics()
{
	_y_acc_up = 0;
	_y_vel_min = 0.01;
	_x_vel_min = 0.01;

	// no accelerations / decelerations along x
	_x_acc = 0.8;
	_x_dec_rel = 0;
	_x_dec_skd = 0;
}

void BossShot::advance()
{
	velAdd(Vec2Df(-0.3, 0));

	DynamicObject::advance();
}

void BossShot::animate()
{
	_animRect = &_animFire[(FRAME_COUNT/9)%4];
}

bool BossShot::hit(Object* what, Direction fromDir)
{
	if (what->to<Block*>()) 
	{
		setVisible(false);
		setDie();
	}	
	return true;
}
