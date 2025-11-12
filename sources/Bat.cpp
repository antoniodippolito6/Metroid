#include "Bat.h"
#include "Sprites.h"
#include "Game.h"
#include "GameConfig.h"
#include "Block.h"
#include "Samus.h"
#include "Spider.h"
#include "Bullet.h"
#include "BatShot.h"
#include "LifeUp.h"

using namespace MT;

Bat::Bat(QPointF pos)
	: Enemy(pos, TILE, TILE + 8)
{
	_sprite = Sprites::instance()->getSprite("bat");

	_collider.adjust(2, 3, -2, -3);

	// Variable used to handle the bat explosion (batShot) 
	_dying = false;

	_hunting = false;
	_injured = false;
	_died = false;
	_compenetrable = false;

	Sprites::instance()->getAnimation("bat_walk", &_batWalk[0]);
	Sprites::instance()->getAnimation("bat_injured", &_batInjured[0]);
	Sprites::instance()->getAnimation("bat_explode", &_batExplode);

	defaultPhysics();
}

void Bat::defaultPhysics()
{
	_y_gravity = -0.18;
	_y_acc_up = 1.5;

	_y_vel_max = 1.5;
	_y_vel_min = 0.1;

	_x_vel_max = 1;
	_x_vel_min = 0.1;
}

void Bat::advance()
{
	// variable used to know the position of the player
	Samus* player = Game::instance()->player();

	resolveCollisions();
	
	if (!grounded() && _x_dir == Direction::NONE)
	{
		// condition for which, if verified, the tracking begins 
		if (std::abs(player->x() - x()) < 2 * TILE && !_dying && !_died)
		{
			_y_gravity = 0.12;
			move(Direction::DOWN);
			_hunting = true;
		}
	}
	// check current position of samus and correct the direction of the chase
	else if (!_dying && !_died)
	{
		if (player->x() < x() - TILE)
			move(Direction::LEFT);
		else if (player->x() > x() + TILE)
			move(Direction::RIGHT);
		// if injured, bat is frozen for a short time 
		if (_injured)
			velClip(0, 0);
	}
	// condition for the death of bat
	if (_life <= 0 || _dying)
		die();

	Enemy::advance();
}

bool Bat::hit(Object* what, Direction fromDir)
{
	Samus* player = Game::instance()->player();

	if (Enemy::hit(what, fromDir))
		return true;

	if (what->to<Block*>() && !midair() && (fromDir == Direction::RIGHT || fromDir == Direction::LEFT))
		move(inverse(_x_dir));
	else if ((what->to<Block*>() && (fromDir == Direction::DOWN)) || what->to<Samus*>() )
		_dying = true;
	//management of damage sustained
	else if (what->to<Bullet*>())
	{
		_injured = true;
		if (player->getMissileFire()) {
			_life = _life - 2;
		}
		else --_life;

		schedule("Injured", 5, [this]() {
			_injured = false;
			});
	}
	else if (what->to<Spider*>()) 
		_compenetrable = true;

	return false;
}

void Bat::animate()
{
	if (_hunting)
		_animRect = &_batWalk[(FRAME_COUNT / 6) % 3];

	if (_injured)
		_animRect = &_batInjured[(FRAME_COUNT / 6) % 3];

	if (_life <= 0)
		_animRect = &_batExplode;

	else
		_animRect = &_batWalk[(FRAME_COUNT / 12) % 3];
}

void Bat::die()
{
	if (_died)
		return;

	// If the bat is not killed and reaches the floor, it explodes creating 4 shots
	if (_dying && _life > 0)
	{
		move(Direction::DOWN);
		if (grounded())
		{
			velAdd(Vec2Df(0, 0));

			new BatShot(QPointF((x()), (y()+8)), Direction::LEFT, false);
			new BatShot(QPointF((x()), (y()+8)), Direction::RIGHT, false);
			new BatShot(QPointF((x()), (y()+8)), Direction::LEFT, true);
			new BatShot(QPointF((x()), (y()+8)), Direction::RIGHT, true);

			setVisible(false);
			setDie();
		}
	}
	// case in which the bat is killed (life = 0 ) 
	// if killed the bat randomly releases a lifeup
	else
	{
		velAdd(Vec2Df(0, 0));
		_y_gravity = 0;
		_x_dir = Direction::NONE;
		schedule("Dead", 10, [this]() {
			srand(time(0) + _id);
			if (rand() % 3 == 0)
				new LifeUp(QPointF(x() + 6, y() + 8));
			setVisible(false);
			setDie();
			});

		_died = true;

	}

}