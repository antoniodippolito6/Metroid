#include "LifeUp.h"
#include "GameConfig.h"
#include "Sprites.h"
#include "Samus.h"
#include "Game.h"

using namespace MT;

LifeUp::LifeUp(QPointF pos)
	: StaticObject(pos, 8, 8)
{
	_compenetrable = true;
	_sprite = Sprites::instance()->getSprite("LifeUp");
	Sprites::instance()->getAnimation("LifeUp", &_animLifeUp[0]);
	
	schedule("End_Life_Up",360, [this]{
		setVisible(false);
		setDie();
	});
}

void LifeUp::animate() 
{
	_animRect = &_animLifeUp[(FRAME_COUNT/2)%2];
}

bool LifeUp::hit(Object * what, Direction fromDir)
{ 
	if (what->to<Samus*>())
	{
		setVisible(false);
		setDie();
	}
		
	return true;
}


