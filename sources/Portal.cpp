#include "Portal.h"
#include "GameConfig.h"
#include "Sprites.h"
#include "Samus.h"
#include "Game.h"
#include "Block.h"
#include "Bullet.h"
using namespace MT;

Portal::Portal(QPointF pos, bool position, bool color)
	: StaticObject(pos, TILE/2, 3*TILE )
{
	if (!position) 
		setX(x() + 8);

	_collider.adjust(1, 1, -1, -1);

	_compenetrable = false;
	_sprite = Sprites::instance()->getSprite("items");

	Sprites::instance()->getAnimation("Portal1-left", &_animPortalBlueLeft[0]);
	Sprites::instance()->getAnimation("Portal1-right", &_animPortalBlueRight[0]);
	Sprites::instance()->getAnimation("Portal2-left", &_animPortalOrangeLeft[0]);
	Sprites::instance()->getAnimation("Portal2-right", &_animPortalOrangeRight[0]);
		
	_position = position;
	_color = color;
	_animHitted=false;
	_hitted = false;
}

void Portal::advance() 
{
	Samus* player = Game::instance()->player();

	// after the portal is hit, if samus moves 2 tiles away,
	// the portal will regenerate 
	if (player->x() > (2 * TILE + x()) && !_position) 
	{
		_hitted = false;
		setVisible(true); 
	}
	if (player->x() < (-2 * TILE + x()) && _position) 
	{
		_hitted = false;
		setVisible(true);
	}

	if (_hitted) 
	{
		_hitted = false;
		schedule("Portal_anim", 10, [this]() {
			_animHitted = false;
			setVisible(false);
			
			});
		schedule("Portal", 180, [this]() {
			setVisible(true);
			});
	}
}

bool Portal::hit(Object* what, Direction fromDir)
{
	if (what->to<Bullet*>() &&  !_animHitted) 
	{
		_hitted = true;
		_animHitted = true;
	}
	
	return true;
}

void Portal::animate() 
{
	if (_position == false && _color == false) // Blue portal sx
		_animRect = &_animPortalBlueLeft[0];
	
	else if (_position == true && _color == false) // Blue portal dx
		_animRect = &_animPortalBlueRight[0];
	
	else if (_position == false && _color == true) // Orange portal sx
		_animRect = &_animPortalOrangeLeft[0];
	
	else if (_position == true && _color == true) //Orange portal dx
		_animRect = &_animPortalOrangeRight[0];
	
	if (_animHitted) 
	{
		if (_position == true && _color == false) // Blue portal sx
			_animRect = &_animPortalBlueLeft[1];
		
		else if (_position == false && _color == false)  // Blue portal dx
			_animRect = &_animPortalBlueRight[1];
		
		else if (_position == false && _color == true) // Orange portal sx
			_animRect = &_animPortalOrangeLeft[1];
		
		else if (_position == true && _color == true) //Orange portal dx
			_animRect = &_animPortalOrangeRight[1];
		
	}
}