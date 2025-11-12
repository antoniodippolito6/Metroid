#include "DeathScreen.h"
#include "GameConfig.h"
#include "Sprites.h"

#include <QPainter>

using namespace MT;

DeathScreen::DeathScreen() : Object(QPoint(0, 0), TILE * 16, TILE * 16)
{
	_sprite = Sprites::instance()->getSprite("deathscreen");
	Sprites::instance()->getAnimation("deathscreen", &_animDeathScreen);
}


void DeathScreen::animate()
{
	setZValue(2);
	_animRect = &_animDeathScreen;
}


