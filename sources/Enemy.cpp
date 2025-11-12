#include "Enemy.h"
#include "GameConfig.h"
#include "Samus.h"
#include "Sounds.h"
#include "Block.h"

using namespace MT;

Enemy::Enemy(QPointF pos,double width, double height) : DynamicObject(pos,  width, height)
{
	_collider.adjust(0, 2, -2, 0);//A
	_boundingRect.adjust(0, 1, -1, 0);//A
	_dying = false;
	_mirror_x_dir = Direction::RIGHT;
}

bool Enemy::hit(Object* what, Direction fromDir)
{
	if (what->to<Samus*>() && !what->to<Samus*>()->invincible())
		return true;
	
	else if (what->to<Block*>() && fromDir == Direction::DOWN && _dying)
	{
		setVisible(false);
		// spawn item
		return true;
	}

	return false;
}

void Enemy::animate()
{
	if(_dying)
		_animRect = &_animDie[(FRAME_COUNT / 4) % 4];
}

void Enemy::die()
{
	if (_dying)
		return;

	velAdd(Vec2Df(0, -_y_acc_up));

	Sounds::instance()->playSound("enemy_die");
	_dying = true;
}