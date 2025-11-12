#include "Samus.h"
#include "GameConfig.h"
#include "Block.h"
#include "Sprites.h"
#include "Sounds.h"
#include "Bullet.h"
#include "Portal.h"
#include "PowerUp.h"
#include "Passable.h"
#include <QPainter>
#include "Game.h"
#include "Spider.h"
#include "Bat.h"
#include "Ripper.h"
#include "LifeUp.h"
#include "Hud.h"
#include "BossShot.h"
#include"BatShot.h"
#include"Boss.h"

using namespace MT;

Samus::Samus(QPointF pos)
	: DynamicObject(pos, TILE, 2 * TILE)
{
	_collider.adjust(2,3,-2,-3);
	
	_jump = false;
	_firing = false;
	_roll = false;
	_dying = false;
	_invincible = false;
	_lookUp = false;
	_spinning_jump = false;
	_spinning_jumped = false;
	_bumped = false;
	_stuck = false;
	_rolling = false;
	_missilefire = false;
	_hit = false;
	_burnt = false;

	_prev_x_dir = Direction::RIGHT;

	_mirror_x_dir = Direction::LEFT;

	_sprite = Sprites::instance()->getSprite("player");
   
	Sprites::instance()->getAnimation("Samus_stand", &_animStand[0]);
	Sprites::instance()->getAnimation("Samus_walk", &_animWalk[0]);
	Sprites::instance()->getAnimation("Samus_jump", &_animJump);
	Sprites::instance()->getAnimation("Samus_roll", &_animRoll[0]);
	Sprites::instance()->getAnimation("Samus_fall", &_animFall);
	Sprites::instance()->getAnimation("Samus_lookUpStand", &_animLookUpStand); 
	Sprites::instance()->getAnimation("Samus_lookUpWalk", &_animLookUpWalk[0]);
	Sprites::instance()->getAnimation("Samus_lookUpJump", &_animLookUpJump); 
	Sprites::instance()->getAnimation("Spinning_jump", &_animSpinningJump[0]); 
	Sprites::instance()->getAnimation("Death", &_animDeath[0]);

	Sprites::instance()->getAnimation("Samus_fire_Idle", &_animSamus_fire_Idle);
	Sprites::instance()->getAnimation("Samus_fire_Walk", &_animSamus_fire_Walk[0]);
	Sprites::instance()->getAnimation("Samus_fire_Aim_Up", &_animSamus_fire_Aim_Up); 
	Sprites::instance()->getAnimation("Samus_fire_Aim_Up_Walk", &_animSamus_fire_Aim_Up_Walk[0]);
	Sprites::instance()->getAnimation("Samus_fire_Aim_Up_Jump", &_animSamus_fire_Aim_Up_Jump);
	Sprites::instance()->getAnimation("Samus_fire_Aim_Right_Jump", &_animSamus_fire_Aim_Right_Jump);
}

void Samus::advance()
{
	if (grounded()) 
	{
		_y_vel_max = 3;

		if (_spinning_jumped && _collider.height() == 10) 
		{
			_collider.adjust(0, -TILE, 0, 0);
			_boundingRect.adjust(0, -TILE, 0, 0);
		}
		_spinning_jumped = false;
		_bumped = false;

	}
	else if (falling())
		_y_vel_max = 2,5;

	if (std::abs(_vel.x) > 0 && !midair() && !_spinning_jumped && !_bumped && !_rolling)
		//Sounds::instance()->playSound("Samus_walk");
	
	//SPINNING JUMP 
	if (midair() && _spinning_jumped && _x_dir == Direction::NONE && !_bumped) 
	{
		if (_prev_x_dir == Direction::LEFT)
			_x_dir = Direction::LEFT;

		else if (_prev_x_dir == Direction::RIGHT)
			_x_dir = Direction::RIGHT;
	}

	if (_bumped && _collider.height() == 10 && !_roll) 
	{
		QRectF curRect = qsceneCollider();
		curRect.adjust(1, -1, -1, -22);

		QList<QGraphicsItem*> items_in_rect = Game::instance()->world()->items(curRect);

		for (auto item : items_in_rect)
		{
			Object* obj = dynamic_cast<Object*>(item);
			if (obj->to<Block*>())
				velClip(0,0);
		}

		_spinning_jumped = false;
		_collider.adjust(0, -TILE, 0, 0);
		_boundingRect.adjust(0, -TILE, 0, 0);
		velClip(0,_y_vel_max);
	}
	if (midair())
	{
		_spinning_jump = true;
		//Sounds::instance()->playSound("Samus_jump");
	}
		

	if (_life <= 0)
		die();

	DynamicObject::advance();	
}

void Samus::animate()
{
	// animation step is implemented with division (/step)
	// animation cycle is implemented with modular division (%cycle size)
	
	if (_dying)
		_animRect = &_animDeath[(FRAME_COUNT / 3) % 4];
	// still
	else if (_vel.x == 0 && !_roll && !_lookUp && !_firing) 
		_animRect = &_animStand[0];
	// rolling
	else if (_roll) 
		_animRect = &_animRoll[(FRAME_COUNT / 3) % 4];
	// fire while stationary
	else if (_firing && _vel.x == 0 && !_roll && !_lookUp) 
		_animRect = &_animSamus_fire_Idle;
	// fire while running
	else if (_firing && _vel.x != 0 && !_roll && !midair() && !_lookUp)
		_animRect = &_animSamus_fire_Walk[(FRAME_COUNT / 3) % 3];
	// fire up 
	else if (_firing && _vel.x == 0 && _lookUp && !_roll && !midair()) 
		_animRect = &_animSamus_fire_Aim_Up;
	// fire up while running
	else if (_firing && _vel.x != 0 && _lookUp && !_roll && !midair()) 
		_animRect = &_animSamus_fire_Aim_Up_Walk[(FRAME_COUNT / 3) % 3];
	
	else if (midair() && !_roll)
	{	
		//jump
		if (_vel.y < 0 && !_lookUp && !_spinning_jumped&& !_firing)  
			_animRect = &_animJump;
		//Spinning Jump
		else if (_spinning_jumped) 
			_animRect = &_animSpinningJump[(FRAME_COUNT / 4) % 4];
		// fall
		else if (_vel.y > 0 && !_lookUp && !_spinning_jump && !_firing) 
			_animRect = &_animFall;
		// look up and jump
		else if (_lookUp && _vel.y != 0 or _lookUp && !_firing && !_spinning_jumped) 
			_animRect = &_animLookUpJump;
		// fire up while jump
		else if (_firing && _lookUp && _jump && !_spinning_jumped) 
			_animRect = &_animSamus_fire_Aim_Up_Jump;
		// fire right while jump
		else if (_firing && _jump && !_lookUp && !_spinning_jumped) 
			_animRect = &_animSamus_fire_Aim_Right_Jump;
	}
	//walk
	else if (!_roll && !_lookUp && _vel.x != 0 && !_firing && !_spinning_jumped) 
		_animRect = &_animWalk[(FRAME_COUNT / 3) % 3];
	// look up and running
	else if (_lookUp && _vel.x != 0 && !midair()) 
		_animRect = &_animLookUpWalk[(FRAME_COUNT / 3) % 3];
	// look up and still
	else if (_lookUp && _vel.x == 0 && _vel.y == 0) 
		_animRect = &_animLookUpStand;
	
	else if (!_invincible && _hit ) 
	{
		if ((FRAME_COUNT / 2) % 2) 
			_animRect = &_animStand[1];
	}
}

bool Samus::hit(Object* what, Direction fromDir)
{
	if ((what->to<Block*>() || what->to<Portal*>()) && _spinning_jumped && (fromDir == Direction::LEFT || fromDir == Direction::RIGHT))
	{
		_bumped = true;
		return true;
	}

	if ((what->to<Block*>() || what->to<Portal*>()) && (fromDir == Direction::LEFT || fromDir == Direction::RIGHT)) 
	{
		_stuck = true;
		return true;
	}

	if (what->to<Passable*>() && (fromDir == Direction::RIGHT)) 
		setX(x() + 4 * TILE);

	if (what->to<Passable*>() && (fromDir == Direction::LEFT)) 
		setX(x() - 4 * TILE);

	if (what->to<PowerUp*>() && what->to<PowerUp*>()->getType()) 
	{
		_rolling = true;
		return true;
	}

	if (what->to<PowerUp*>() && !what->to<PowerUp*>()->getType()) 
	{
		_missilefire = true;
		return true;
	}

	if (!_invincible) {

		if (what->to<Spider*>() || what->to<Ripper*>()) 
		{
			_life = _life - 8;
			jump();
			_hit = true;
			schedule("Hit", 20, [this]() {
			_hit = false;
				});
		}

		if (what->to<Bat*>()) 
		{
			_life = _life-8;
			jump();
			_hit = true;
			_invincible = true;
			schedule("Hit", 5, [this]() {
				_hit = false;
				_invincible = false;
				});
		}

		if (what->to<BatShot*>()) 
		{
			_life = _life - 4;
			jump();
			_hit = true;
			schedule("Hit", 50, [this]() {
				_hit = false;
				});
		}

		if (what->to<BossShot*>() || what->to<Boss*>())
		{
			_life = _life - 10;
			jump();
			_hit = true;
			schedule("Hit", 50, [this]() {
				_hit = false;
				});
		}

		if (what->to<DamagingBlock*>())
		{
			burnt();
			_burnt = false;
		}

		if (what->to<LifeUp*>()) 
		{
			_life = _life + 5;
				return true;
		}
	}

	return false; 
}

void Samus::burnt()
{
	//function that causes you to take periodic damage
	if (_burnt)
		return;
	else
	{
		QObject* obj = new QObject();
		QTimer* timer = new QTimer();
		QObject::connect(timer, &QTimer::timeout, obj, [&]() { this->updateHealth(); });
		timer->setInterval(1000);
		timer->start();
		_burnt = true;
	}
}


void Samus::lookUp(bool _up_pressed) {

	if (_up_pressed) 
	{
		_lookUp = true;

		if (_roll) 
		{
			QRectF curRect = qsceneCollider();
			curRect.adjust(1, -1, -1, -22);

			QList<QGraphicsItem*> items_in_rect = Game::instance()->world()->items(curRect);

			for (auto item : items_in_rect)
			{
				Object* obj = dynamic_cast<Object*>(item);
				if (obj->to<Block*>())
				return;
			}

			setY(y() - TILE);
			_collider.adjust(0, 0, 0, +TILE);
			_boundingRect.adjust(0, 0, 0, +TILE);
			_roll = false;
		}
	}
	else if(!_up_pressed) 
		_lookUp = false;
}

void Samus::jump(bool on)
{
	if (on)
	{
		if (_roll && _collider.height() == 10) 
		{
			QRectF curRect = qsceneCollider();
			curRect.adjust(1, -1, -1, -22);

			QList<QGraphicsItem*> items_in_rect = Game::instance()->world()->items(curRect);
			for (auto item : items_in_rect)
			{
				Object* obj = dynamic_cast<Object*>(item);
				if (obj->to<Block*>())
					return;
					
			}

			setY(y() - TILE);
			_collider.adjust(0, 0, 0, +TILE);
			_boundingRect.adjust(0, 0, 0, +TILE);
			_roll = false;
			_spinning_jump = true;
			_jump = true;
			Sounds::instance()->playSound("Samus_jump");
		}

		else if (!midair() && !_jump && !_roll && !_spinning_jump)
		{
			if (std::abs(_vel.x) <= 2.3123)
			{
				velAdd(Vec2Df(0, -10));
				_y_gravity = 0.054;
			}
			else
			{
				velAdd(Vec2Df(0, -5));
				_y_gravity = 0.0938;
			}
			_jump = true;
		}
	}
	else 
	{
		_y_gravity = 0.4375;
		_stuck = false;
	}

	_jump = on;
}

void Samus::spinning_jump(bool on)
{
	if (on)
	{
		if (_roll && _collider.height() == 10) 
		{
			QRectF curRect = qsceneCollider();
			curRect.adjust(1, -1, -1, -22);

			QList<QGraphicsItem*> items_in_rect = Game::instance()->world()->items(curRect);
			for (auto item : items_in_rect)
			{
				Object* obj = dynamic_cast<Object*>(item);
				if (obj->to<Block*>())
					return;
			}

			setY(y() - TILE);
			_collider.adjust(0, 0, 0, +TILE);
			_boundingRect.adjust(0, 0, 0, +TILE);
			_roll = false;
			_spinning_jump = true;
			_jump = true;
		}

		else if (!midair() && !_spinning_jump && !_roll && !_jump)
		{
			if(_collider.height() == 26) 
			{
				_collider.adjust(0, TILE, 0, 0);
				_boundingRect.adjust(0, TILE, 0, 0);
			}

			if (std::abs(_vel.x) <= 2.3123)
			{
				velAdd(Vec2Df(0, -4));
				_y_gravity = 0.054;
			}

			else
			{
				velAdd(Vec2Df(0, -5));
				_y_gravity = 0.00038;
			}

			_spinning_jump = true;
			_spinning_jumped = true;
		}

	}
	
	else
		_spinning_jump = on;
}

void Samus::roll()
{

	if (!_rolling)
		return;

	if (!_roll && !midair() && _rolling)
	{
		_collider.adjust(0, 0, 0, -TILE);
		_boundingRect.adjust(0, 0, 0, -TILE);
		_roll = true;
	}
}

void Samus::fire()
{
	if (_firing || _roll || _spinning_jumped)
		return;
		

	_firing = true;

	Sounds::instance()->playSound("Samus_beam");

	if (_lookUp) 
		new Bullet(QPoint(x()+ 8, y() ), Direction::UP, _lookUp);
		
	else if ((_x_dir==Direction::RIGHT || _x_dir == Direction::NONE &&  _prev_x_dir == Direction::RIGHT))
		new Bullet(QPoint(x() + TILE, y() + 8), Direction::RIGHT, _lookUp);
		
	else if ((_x_dir == Direction::LEFT || _x_dir == Direction::NONE && _prev_x_dir == Direction::LEFT))
		new Bullet(QPoint(x() , y() + 8), Direction::LEFT, _lookUp);
		

	schedule("firing_disable", 8, [this]() {
			_firing = false;
		});

}

void Samus::die()
{
	if (_dying)
		return;

	_x_dir = Direction::NONE;
	_dying = true;
	_life = 0;

	_boundingRect.adjust(-6, -3, 6, 3);
	schedule("Dead", 12, [this]() {
		setVisible(false);
		});

}