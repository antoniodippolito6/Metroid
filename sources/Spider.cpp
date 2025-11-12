#include "Spider.h"
#include "Sprites.h"
#include "Game.h"
#include "GameConfig.h"
#include "Block.h"
#include "Samus.h"
#include "Bullet.h"
#include "Portal.h"
#include "Passable.h"
#include "LifeUp.h"

using namespace MT;

Spider::Spider(QPointF pos, bool clockwise)
	: Enemy(pos, TILE, TILE)
{
	_collider.adjust(0,1,-1,0);

	_right = false;
	_left = false;
	_up = false;
	_down = false;
	_hit = false;

	_sprite = Sprites::instance()->getSprite("spider");

	
	_x_dir = Direction::RIGHT;

	_clockwise = clockwise;

	Sprites::instance()->getAnimation("Spider_Right", &_animRight[0][0]);
	Sprites::instance()->getAnimation("Spider_Left", &_animLeft[0][0]);
	Sprites::instance()->getAnimation("Spider_Up", &_animUp[0][0]);
	Sprites::instance()->getAnimation("Spider_Down", &_animDown[0][0]);
	Sprites::instance()->getAnimation("Spider_Right_Red", &_animRight[1][0]);
	Sprites::instance()->getAnimation("Spider_Left_Red", &_animLeft[1][0]);
	Sprites::instance()->getAnimation("Spider_Up_Red", &_animUp[1][0]);
	Sprites::instance()->getAnimation("Spider_Down_Red", &_animDown[1][0]);
	Sprites::instance()->getAnimation("Spider_Dead", &_animDead);

	if (_clockwise) 
	{
		_x_gravity = -1;
		_y_gravity = 1;
	}

	else 
	{
		_x_gravity = 1;
		_y_gravity = 1;
	}

	_x_vel_max = 0.8;
	_y_vel_max = 0.8;

}

void Spider::advance()
{
	_right = _left = _up = _down = false;

	velClip(0, 0);

	velAdd(Vec2Df(_x_gravity, _y_gravity));
	resolveCollisions();

	if(_clockwise)
	{
		if (_down)
			_x_dir = Direction::LEFT;

		if (_right)
			_x_dir = Direction::DOWN;

		if (_left)
			_x_dir = Direction::UP;

		if (_up)
			_x_dir = Direction::RIGHT;

		if ((_down && _right)) 
		{
			_y_gravity = 1;
			_x_gravity = -1;
		}

		else if (_down && _left) 
		{
			_y_gravity = -1;
			_x_gravity = -1;
		}

		else if (_up && _right) 
		{
			_y_gravity = 1;
			_x_gravity = 1;
		}

		else if (_up && _left) 
		{
			_y_gravity = -1;
			_x_gravity = 1;
		}

		else if (!_up && !_right && !_down && !_left && _x_dir == Direction::LEFT)
		{
			_y_gravity = 1;
			_x_gravity = 1;
		}

		else if (!_up && !_right && !_down && !_left && _x_dir == Direction::UP)
		{
			_y_gravity = 1;
			_x_gravity = -1;
		}

		else if (!_up && !_right && !_down && !_left && _x_dir == Direction::RIGHT)
		{
			_y_gravity = -1;
			_x_gravity = -1;
		}

		else if (!_up && !_right && !_down && !_left && _x_dir == Direction::DOWN)
		{
			_y_gravity = -1;
			_x_gravity = 1;
		}
	}
	else {

		if (_down)
			_x_dir = Direction::RIGHT;

		if (_right)
			_x_dir = Direction::UP;

		if (_left)
			_x_dir = Direction::DOWN;

		if (_up)
			_x_dir = Direction::LEFT;

		if ((_down && _right)) 
		{
			_y_gravity = -1;
			_x_gravity = 1;
		}

		else if (_down && _left) 
		{
			_y_gravity = 1;
			_x_gravity = 1;
		}

		else if (_up && _right) 
		{
			_y_gravity = -1;
			_x_gravity = -1;
		}

		else if (_up && _left) 
		{
			_y_gravity = 1;
			_x_gravity = -1;
		}

		else if (!_up && !_right && !_down && !_left && _x_dir == Direction::LEFT)
		{
			_y_gravity = -1;
			_x_gravity = 1;
		}

		else if (!_up && !_right && !_down && !_left && _x_dir == Direction::UP)
		{
			_y_gravity = 1;
			_x_gravity = 1;
		}

		else if (!_up && !_right && !_down && !_left && _x_dir == Direction::RIGHT)
		{
			_y_gravity = 1;
			_x_gravity = -1;
		}

		else if (!_up && !_right && !_down && !_left && _x_dir == Direction::DOWN)
		{
			_y_gravity = -1;
			_x_gravity = -1;
		}
	}

	if (_hit) {
		velClip(0, 0);
	}

	if (_life == 0) {
		_life--;
		_boundingRect.adjust(-8, -8, 9, 9);
		schedule("Dead", 10, [this]() {
			srand(time(0) + _id);
			if (rand()%3==0) 
			{
				new LifeUp(QPointF(x() + 6, y() + 8));
			}
			setVisible(false);
			setDie();
			});

	}

	setX(x() + _vel.x);
	setY(y() + _vel.y);
}


void Spider::animate()
{
	if (_life <0) 
			_animRect = &_animDead;
	
	else if (_hit) {

		if (_left)
			_animRect = &_animRight[1][(FRAME_COUNT / 4) % 2];

		if (_right)
			_animRect = &_animLeft[1][(FRAME_COUNT / 4) % 2];

		if (_up)
			_animRect = &_animUp[1][(FRAME_COUNT / 4) % 2];

		if (_down)
			_animRect = &_animDown[1][(FRAME_COUNT / 4) % 2];
	}
	else {
		if (_left)
			_animRect = &_animRight[0][(FRAME_COUNT / 4) % 2];

		if (_right)
			_animRect = &_animLeft[0][(FRAME_COUNT / 4) % 2];

		if (_up)
			_animRect = &_animUp[0][(FRAME_COUNT / 4) % 2];

		if (_down)
			_animRect = &_animDown[0][(FRAME_COUNT / 4) % 2];
	}

}

bool Spider::hit(Object* what, Direction fromDir)
{

	Samus* player = Game::instance()->player();

	if ((what->to<Block*>() || what->to<Portal*>() || what->to<Passable*>()) &&  fromDir == Direction::RIGHT )
		_right = true;

	if ((what->to<Block*>() || what->to<Portal*>() || what->to<Passable*>()) && fromDir == Direction::UP)
		_up = true;
	
	if ((what->to<Block*>() || what->to<Portal*>() || what->to<Passable*>()) && fromDir == Direction::DOWN)
		_down = true;

	if ((what->to<Block*>() || what->to<Portal*>() || what->to<Passable*>()) && fromDir == Direction::LEFT)
		_left = true;
	
	if (what->to<Bullet*>()) {
		_hit = true;

		if (player->getMissileFire()) {
			_life = _life - 2;
		}
		else _life--;

		schedule("Hit", 10, [this]() {
			_hit = false;
			});
	}

	return true;
}