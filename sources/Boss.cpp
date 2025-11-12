#include "Boss.h"
#include "Sprites.h"
#include "Game.h"
#include "GameConfig.h"
#include "Block.h"
#include "Samus.h"
#include "BossShot.h"
#include "Bullet.h"

using namespace MT;

Boss::Boss(QPointF pos)
	: Enemy(pos, 32, 47)
{
	_sprite = Sprites::instance()->getSprite("boss");

	_hit = false;
	_fire = false;

	Sprites::instance()->getAnimation("Boss_stand", &_animStand[0][0]);
	Sprites::instance()->getAnimation("Boss_jump", &_animJump[0][0]);
	Sprites::instance()->getAnimation("Boss_stand_red", &_animStand[1][0]);
	Sprites::instance()->getAnimation("Boss_jump_red", &_animJump[1][0]);
	Sprites::instance()->getAnimation("Boss_dead", &_animDead);

	_x_vel_max = 0.1;
	_y_vel_max = 8;
}

void Boss::advance()
{
	Samus* player = Game::instance()->player();

	srand(time(0) + _id);

	// random jump 
	if (grounded())
	{
		_jump = false;
		schedule("jump", rand() % 30 + 40, [this]() {jump(true); _jump = true; }, false);
	}

	// automatic shot
	if (!_fire)
	{
		_fire = true;

		new BossShot(QPoint(x(), y()));
		schedule("Not_fire", 30, [this]() {
			_fire = false;
			});
	}

	if (_life == 0)
		die();

	Enemy::advance();
}


void Boss::animate()
{
	if (_hit) 
	{
		_animRect = &_animStand[1][(FRAME_COUNT / 9) % 2];
		if (_jump)
			_animRect = &_animJump[1][(FRAME_COUNT / 9) % 2];
	}
	else 
	{
		_animRect = &_animStand[0][(FRAME_COUNT / 9) % 2];
		if (_jump)
			_animRect = &_animJump[0][(FRAME_COUNT / 9) % 2];
	}

	if (_life < 0)
		_animRect = &_animDead;
}

bool Boss::hit(Object* what, Direction fromDir)
{
	Samus* player = Game::instance()->player();
	//management of damage sustained
	if (what->to<Bullet*>()) 
	{
		_hit = true;
		
		if (player->getMissileFire()) {
			_life = _life - 2;
		}
		else _life--;

		schedule("Hit", 5, [this]() {
			_hit = false;
			});
		return true;
	}
	return false;
}

void Boss::die()
{
	if (_dying)
		return;

	_dying = true;
	_x_dir = Direction::NONE;
	velAdd(Vec2Df(0, 0));

	setVisible(false);
	setDie();
}