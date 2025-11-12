#include "Sprites.h"
#include "GameConfig.h"
#include <iostream>
#include <QPainter>
#include <QPixmap>
#include <QBitmap>

using namespace MT;

// load image with transparency using the given color as mask
static QPixmap loadImage(const std::string& file, QColor mask_color = Qt::magenta)
{
	QPixmap pixmap(file.c_str());
	pixmap.setMask(pixmap.createMaskFromColor(mask_color));
	return pixmap;
}

// replace color (useful for palette changes)
QPixmap replaceColor(QPixmap pix, QColor old_color, QColor new_color)
{
	QBitmap mask = pix.createMaskFromColor(old_color, Qt::MaskOutColor);
	QPainter p(&pix);
	p.setPen(new_color);
	p.drawPixmap(pix.rect(), mask, mask.rect());
	p.end();
	return pix;
}

// moving within sprite utility function
QRect moveBy(QRect rect, int x, int y, int dx = 16, int dy = 16, int border_x = 1, int border_y = 1)
{
	rect.moveTo(QPoint(rect.x() + x * dx + x * border_x, rect.y() + y * dy + y * border_y));
	return rect;
}

Sprites* Sprites::instance()
{
	static Sprites uniqueInstance;
	return &uniqueInstance;
}

Sprites::Sprites()
{
	_sprites["hud"] = loadImage(":/objects/objects.png", QColor(116, 116, 116));
	_sprites["bullet"] = loadImage(":/player/powersuit.png", QColor(116, 116, 116));
	_sprites["enemies"] = loadImage(":/sprites/enemies.png", QColor(116, 116, 116));
	_sprites["fonts"] = loadImage(":/objects/fonts.png");
	_sprites["items"] = loadImage(":/items/items.png", QColor(116, 116, 116));
	_sprites["player"] = loadImage(":/player/powersuit.png", QColor(116, 116, 116));
	_sprites["title"] = loadImage(":/title/title.png", QColor(116, 116, 116));
	_sprites["spider"] = loadImage(":/player/Spider.png", QColor(116, 116, 116));
	_sprites["boss"] = loadImage(":/player/Boss.png", QColor(116, 116, 116));
	_sprites["bossShot"] = loadImage(":/player/Boss.png", QColor(116, 116, 116));
	_sprites["ripper"] = loadImage(":/player/Ripper.png", QColor(116, 116, 116));
	_sprites["powerup1"] = loadImage(":/items/items.png", QColor(116, 116, 116));
	_sprites["powerup2"] = loadImage(":/items/items.png", QColor(116, 116, 116));
	_sprites["Missile-left"] = loadImage(":/items/items.png", QColor(116, 116, 116));
	_sprites["Missile-right"] = loadImage(":/items/items.png", QColor(116, 116, 116));
	_sprites["Missile-up"] = loadImage(":/items/items.png", QColor(116, 116, 116));
	_sprites["LifeUp"] = loadImage(":/items/items.png", QColor(116, 116, 116));
	_sprites["bat"] = loadImage(":/player/bat.png", QColor(116, 116, 116));
	_sprites["BatShot"] = loadImage(":/player/bat.png", QColor(116, 116, 116));
	_sprites["deathscreen"] = loadImage(":/title/menu.png", QColor(116, 116, 116));

}

QPixmap* Sprites::getSprite(const std::string& id)
{
	if (_sprites.find(id) != _sprites.end())
		return &_sprites[id];

	else
	{
		std::cerr << "Cannot find sprite \"" << id << "\"\n";
		return nullptr;
	}
}

void Sprites::getAnimation(const std::string& id, QRect animOutput[])
{

	if (id == "Samus_stand")
	{
		animOutput[0] = QRect(1, 11, TILE, 2*TILE);
		animOutput[1] = QRect(260, 260,TILE, 2 * TILE);
	}

	else if (id == "Samus_walk")
	{
		animOutput[0] = QRect(31, 11, TILE+2, 2 * TILE);
		animOutput[1] = QRect(56, 11, TILE+2, 2 * TILE);
		animOutput[2] = QRect(86, 11, TILE+2, 2 * TILE);
	}

	else if (id == "Samus_roll") {
		animOutput[0] = QRect(58, 118, 14, 14);
		animOutput[1] = QRect(75, 118, 14, 14);
		animOutput[2] = QRect(92, 118, 14, 14);
		animOutput[3] = QRect(109, 118, 14, 14);
	}

	else if (id == "Samus_lookUpStand")
		animOutput[0] = QRect(140, 19, 16, 31);

	else if (id == "Samus_lookUpWalk")
	{
		animOutput[0] = QRect(159, 19, 12, 33);
		animOutput[1] = QRect(182, 21, 17, 32);
		animOutput[2] = QRect(205, 21, 18, 32);
	}

	else if (id == "Samus_lookUpJump")
		animOutput[0] = QRect(230, 12, (2 + TILE), (2 * TILE) + 3);

	else if (id == "Samus_jump")
		animOutput[0] = QRect(112, 14, 21, 30);
	
	else if (id == "Spinning_jump")
	{
		animOutput[0] = QRect(254, 19, TILE, TILE);
		animOutput[1] = QRect(273, 20, TILE, TILE);
		animOutput[2] = QRect(293, 20, TILE, TILE);
		animOutput[3] = QRect(313, 19, TILE, TILE);
	}

	else if (id == "Samus_fall")
		animOutput[0] = QRect(112, 11, TILE + 4, 2 * TILE);
	
	else if (id == "Samus_fire_Idle") //Sparo di samus mentre sta fermo 
		animOutput[0] = QRect(1, 68, TILE, 2 * TILE);

	else if (id == "Samus_fire_Walk") //Sparo di samus mentre corre
	{
		animOutput[0] = QRect(30, 69, TILE+2, 2 * TILE+1);
		animOutput[1] = QRect(60, 69, TILE+2, 2 * TILE+1);
		animOutput[2] = QRect(89, 69, TILE+4, 2 * TILE+1);
	}
	else if (id == "Samus_fire_Aim_Up") //Sparo di samus in alto mentre mira in alto 
		animOutput[0] = QRect(140, 19, 16, 31);
	
	else if (id == "Samus_fire_Aim_Up_Walk") //Sparo di samus in alto mentre corre
	{
		animOutput[0] = QRect(159, 19, 12, 33);
		animOutput[1] = QRect(182, 21, 17, 32);
		animOutput[2] = QRect(205, 21, 18, 32);
	}

	else if (id == "Samus_fire_Aim_Up_Jump") //Sparo di samus in alto mentre salta
		animOutput[0] = QRect(231, 13, 18, 32);
	
	else if (id == "Samus_fire_Aim_Right_Jump") //Sparo di samus verso destra mentre salta
		animOutput[0] = QRect(137, 71, 22, 31);
	
	else if (id == "Death") 
	{
		animOutput[0] = QRect(0, 230, 28, 38);
		animOutput[1] = QRect(28, 230, 28, 38);
		animOutput[2] = QRect(56, 230, 28, 38);
		animOutput[3] = QRect(84, 230, 28, 38);
	}
	else if (id == "Bat")
	{
		animOutput[0] = QRect(5, 5, TILE, TILE);
		animOutput[1] = QRect(26, 5, TILE, TILE);
	}
	else if (id == "bullet") //Proiettile Samus
		animOutput[0] = QRect(2, 168, 6, 7);

	else if (id == "Missile-left") //Missile Samus
		animOutput[0] = QRect(30, 18, 12, 8);
	
	else if (id == "Missile-right") //Missile Samus
		animOutput[0] = QRect(30, 10, 12, 8);
	
	else if (id == "Missile-up") //Missile Samus
		animOutput[0] = QRect(19, 11, 8, 12);
	
	else if (id == "powerup1")
		animOutput[0] = QRect(97, 12, 12, 13);

	else if (id == "powerup2")
		animOutput[0] = QRect(76, 11, TILE, TILE);

	else if (id == "Portal1-left") //Portale blu
	{
		animOutput[0] = QRect(232, 100, 8, 48);
		animOutput[1] = QRect(187, 100, 8, 48);
	}

	else if (id == "Portal1-right") //Portale blu
	{
		animOutput[0] = QRect(178, 100, 8, 48);
		animOutput[1] = QRect(241, 100, 8, 48);
	}

	else if (id == "Portal2-left") //Portale giallo
	{
		animOutput[0] = QRect(204, 100, 8, 48);
		animOutput[1] = QRect(214, 100, 8, 48);
	}

	else if (id == "Portal2-right") //Portale blu
	{
		animOutput[0] = QRect(259, 100, 8, 48);
		animOutput[1] = QRect(268, 100, 8, 48);
	}

	else if (id == "Spider_Down")
	{
		animOutput[0] = QRect(0, 0, 15, 15);
		animOutput[1] = QRect(15, 0, 15, 15);
	}

	else if (id == "Spider_Right")
	{
		animOutput[0] = QRect(30, 0, 15, 15);
		animOutput[1] = QRect(45, 0, 15, 15);
	}

	else if (id == "Spider_Up")
	{
		animOutput[0] = QRect(60, 0, 15, 15);
		animOutput[1] = QRect(75, 0, 15, 15);

	}

	else if (id == "Spider_Left")
	{
		animOutput[0] = QRect(90, 0, 15, 15);
		animOutput[1] = QRect(105, 0, 15, 15);
	}

	else if (id == "Spider_Down_Red")
	{
		animOutput[0] = QRect(0, 15, 15, 15);
		animOutput[1] = QRect(15, 15, 15, 15);
	}

	else if (id == "Spider_Right_Red")
	{
		animOutput[0] = QRect(30, 15, 15, 15);
		animOutput[1] = QRect(45, 15, 15, 15);
	}

	else if (id == "Spider_Up_Red")
	{
		animOutput[0] = QRect(60, 15, 15, 15);
		animOutput[1] = QRect(75, 15, 15, 15);
	}

	else if (id == "Spider_Left_Red")
	{
		animOutput[0] = QRect(90, 15, 15, 15);
		animOutput[1] = QRect(105, 15, 15, 15);
	}

	else if (id == "Spider_Dead")
		animOutput[0] = QRect(120, 0, 36, 36);

	else if (id == "Boss_stand")
	{
		animOutput[0] = QRect(0, 0, 32, 47);
		animOutput[1] = QRect(32, 0, 32, 47);
	}

	else if (id == "Boss_jump")
	{
		animOutput[0] = QRect(64, 0, 32, 47);
		animOutput[1] = QRect(96, 0, 32, 47);
	}

	else if (id == "Boss_stand_red")
	{
		animOutput[0] = QRect(0, 47, 32, 47);
		animOutput[1] = QRect(32, 47, 32, 47);
	}

	else if (id == "Boss_jump_red")
	{
		animOutput[0] = QRect(64, 47, 32, 47);
		animOutput[1] = QRect(96, 47, 32, 47);
	}

	else if (id == "Boss_dead")
		animOutput[0] = QRect(222, 0, 32, 47);

	else if (id == "BossShot")
	{
		animOutput[0] = QRect(198, 0, 8, 8);
		animOutput[1] = QRect(206, 0, 8, 8);
		animOutput[2] = QRect(198, 11, 8, 8);
		animOutput[3] = QRect(206, 11, 8, 8);
	}

	else if (id == "Ripper_Right")
		animOutput[0] = QRect(0, 0, 16, 8);

	else if (id == "Ripper_Left")
		animOutput[0] = QRect(16, 0, 16, 8);
	
	else if (id == "bat_walk")
	{
		animOutput[0] = QRect(2, 14, 21, 32);
		animOutput[1] = QRect(23, 14, 12, 30);
		animOutput[2] = QRect(34, 14, 12, 30);
	}

	else if (id == "bat_injured")
	{
		animOutput[0] = QRect(2, 45, 21, 32);
		animOutput[1] = QRect(23, 45, 12, 30);
		animOutput[2] = QRect(34, 45, 12, 30);
	}

	else if (id == "BatShot")
		animOutput[0] = QRect(47, 17, 8, 8);

	else if (id == "bat_explode")
		animOutput[0] = QRect(57, 18, 32, 32);
	
	else if (id == "LifeUp")
	{
		animOutput[0] = QRect(1, 15, 8, 8);
		animOutput[1] = QRect(10, 15, 8, 8);
	}

	else if (id == "hud_score")
	{
		animOutput[0] = QRect(1, 100, 24, 8);//Scritta EN e Pallini
		animOutput[1] = QRect(1, 100, 24, 17);//Scritta EN con il Power Up 
	}

	else if (id == "title")
	{
		animOutput[0] = QRect(1, 21, 255, 240);
		animOutput[1] = QRect(258, 21, 255, 240);
		animOutput[2] = QRect(515, 21, 255, 240);
		animOutput[3] = QRect(772, 21, 255, 240);
		animOutput[4] = QRect(1029, 21, 255, 240);
		animOutput[5] = QRect(1286, 21, 255, 240);
		animOutput[6] = QRect(1543, 21, 255, 240);
		animOutput[7] = QRect(1800, 21, 255, 240);
		animOutput[8] = QRect(1, 262, 255, 240);
		animOutput[9] = QRect(258, 262, 255, 240);
		animOutput[10] = QRect(515, 262, 255, 240);
		animOutput[11] = QRect(772, 262, 255, 240);
		animOutput[12] = QRect(1029, 262, 255, 240);
		animOutput[13] = QRect(1286, 262, 255, 240);
		animOutput[14] = QRect(1543, 262, 255, 240);
		animOutput[15] = QRect(1800, 262, 255, 240);
	}

	else if (id == "deathscreen")
		animOutput[0] = QRect(523, 56, 255, 224);
	
	else
		std::cerr << "Cannot find animation \"" << id << "\"\n";
}

QPixmap Sprites::getTexture(const std::string& id)
{
	if (id.rfind("char-", 0) == 0)
	{
		char c = id[5];
		int xDist = c - '0', yDist = 0;

		if (c >= 'A' && c - 'A' < 13)
		{
			xDist = c - 'A';
			yDist = 1;
		}

		else if (c >= 'A' && c - 'A' < 26)
		{
			xDist = c - 'N';
			yDist = 2;
		}
		
		return _sprites["fonts"].copy(moveBy(QRect(8, 7, 7, 7), xDist, yDist, 7, 7, 3, 3));
	}

	else
	{
		std::cerr << "Cannot find sprite texture \"" << id << "\"\n";
		return QPixmap();
	}
}

QPixmap Sprites::getText(std::string text, int fill, QColor color)
{
	// fill with 0s on the left
	if (fill)
		while (text.size() != fill)
			text = ' ' + text;

	// create collage texture
	QPixmap collage(8 * int(text.size()), 7);
	QPainter painter(&collage);
	painter.setPen(Qt::NoPen);
	painter.setBrush(Qt::black);
	painter.drawRect(0, 0, collage.width(), collage.height());

	// add letters
	for (int i = 0; i < text.size(); i++)
		if (text[i] != ' ')
			painter.drawPixmap(8 * i, 0, Sprites::instance()->getTexture(std::string("char-") + text[i]));

	// end painting (necessary for setMask)
	painter.end();

	// make background transparent
	collage.setMask(collage.createMaskFromColor(QColor(116, 116, 116)));

	// apply color
	//if (color != Qt::white)
	//	collage = replaceColor(collage, QColor(252, 254, 252), color);

	return collage;
}

// score composite from sprite single score pieces

QPixmap Sprites::getNumber(int n, int fill)
{
	std::string text = std::to_string(n);

	// fill with 0s on the left
	if (fill)
		while (text.size() != fill)
			text = '0' + text;

	// create collage texture
	QPixmap collage(8 * int(text.size()), 8);
	QPainter painter(&collage);


	// end painting (necessary for setMask)
	painter.end();

	// make background transparent
	collage.setMask(collage.createMaskFromColor(QColor(147, 187, 236)));

	return collage;
}
