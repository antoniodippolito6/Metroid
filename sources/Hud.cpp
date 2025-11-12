#include "Hud.h"
#include "StaticObject.h"
#include "Samus.h"
#include "GameConfig.h"
#include "Game.h"
#include "Sprites.h"
#include "Sounds.h"

using namespace MT;

HUD::HUD(QPointF pos, double w, double h) :
	Object(pos, w, h)
{
	_sprite = Sprites::instance()->getSprite("hud");
	Sprites::instance()->getAnimation("hud_score", &_animEnergy[0]);
	_pos = pos;

	_compenetrable = true;
	_collidable = false;
	_started = true;
	_missile = false;
}

void HUD::advance() 
{
	Samus* player = Game::instance()->player();
	if (player->getMissileFire() && !_missile ) 
	{
		HUD::_boundingRect.adjust(0, 0, 0, +9);
		_missile = true; 
	}

	setX(Game::instance()->viewRect().x()-6.7*TILE);
	setY(Game::instance()->viewRect().y()-5.3*TILE);
}

void HUD::animate() 
{
	Samus* player = Game::instance()->player();

	if (_started) 
	{
		if (player->getMissileFire()) 
			_animRect = &_animEnergy[1];

		else 
			_animRect = &_animEnergy[0];
	}

}

bool HUD::hit(Object* what, Direction fromDir)
{
	if (what->to<Samus*>()) 
		_hitted = true;

	return true;
}

