#include "PowerUp.h"
#include "GameConfig.h"
#include "Sprites.h"
#include "Samus.h"
#include "Game.h"
#include "Block.h"
#include "Sounds.h"
using namespace MT;

PowerUp::PowerUp(QPointF pos, bool type)
	: StaticObject(pos, TILE, TILE)
{
	_type = type;
	_collider.adjust(1, 1, -1, -1);
	_compenetrable = true;

	// power up for rolling
	if (_type) 
	{
		_sprite = Sprites::instance()->getSprite("powerup1");
		Sprites::instance()->getAnimation("powerup1", &_animRolling);
		_animRect = &_animRolling;
	}
	// power up for missile
	else 
	{
		_sprite = Sprites::instance()->getSprite("powerup2");
		Sprites::instance()->getAnimation("powerup2", &_animMissile);
		_animRect = &_animMissile;
	}

}

bool PowerUp::hit(Object * what, Direction fromDir)
{ 
	Samus* player = Game::instance()->player();

	if (what->to<Samus*>())
	{
		Game::instance()->freeze();
		setVisible(false);
		setDie();
		Sounds::instance()->stopMusic("Brinstar");
		Sounds::instance()->playMusic("Item_Obtainment_Jingle",false);
	}
		
	return true;
}


