#include "WelcomeScreen.h"
#include "GameConfig.h"
#include "Sprites.h"
#include "Game.h"
#include <QPainter>

using namespace MT;

Title::Title() : Object(QPoint(0, 0), TILE * 16, TILE * 16)
{
	_sprite = Sprites::instance()->getSprite("title");
	Sprites::instance()->getAnimation("title", &_animTitle[0]);
	
	new Text();
}

void Title::advance()
{
	setY(y() + 1);
	setY(y() - 1);
}

void Title::animate()
{
	_animRect = &_animTitle[(FRAME_COUNT / 10) % 16];
}

Text::Text() : Object(QPoint(4*TILE, 14*TILE), TILE * 8, TILE)
{
	_sprite = &_pixText;
	_animText = QRect(0, 0, TILE * 8, TILE);
	_animRect = &_animText;

	_compenetrable = true;
	_collidable = false;
	setZValue(1);
}

void Text::advance() 
{
	setX(Game::instance()->viewRect().x() - 5 * TILE);
	setY(Game::instance()->viewRect().y() - 5.3 * TILE);
}


void Text::animate() 
{
	Samus* player = Game::instance()->player();
	if (player)
		_pixText = Sprites::instance()->getText(std::to_string(player->life()), 0, QColor(255, 110, 204));
	
}

