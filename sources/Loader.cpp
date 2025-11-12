#include "Loader.h"
#include "WelcomeScreen.h"
#include "Samus.h"
#include "Bat.h"
#include "Spider.h"
#include "Ripper.h"
#include "Boss.h"
#include "Block.h"
#include "Game.h"
#include "GameConfig.h"
#include "Portal.h"
#include "PowerUp.h"
#include "Passable.h"
#include "Hud.h"
#include <QBrush>
#include "DeathScreen.h"

using namespace MT;

DynamicObject* Loader::load(int round)
{
	if (round == 0)
	{
		new Title();

		return nullptr;
	}

	else if (round == 1)
	{
		Game::instance()->world()->addPixmap(QPixmap(":/levels/level1.png"));

		// HUD energy
		new HUD(QPointF(39 * TILE, 142 * TILE), 24, 8);
		new Text();


		new Block(QPointF(19 * TILE, 151 * TILE), Qt::transparent, 63 * TILE, TILE);
		new Block(QPointF(19 * TILE, 138 * TILE), Qt::transparent, 145 * TILE, TILE);
		new Block(QPointF(19 * TILE, 139 * TILE), Qt::transparent, TILE, 12 * TILE);

		new Block(QPointF(23 * TILE, 150 * TILE), Qt::transparent, 2 * TILE, TILE);
		new Block(QPointF(23 * TILE, 149 * TILE), Qt::transparent, TILE, TILE);
		new Block(QPointF(26 * TILE, 148 * TILE), Qt::transparent, TILE, 3 * TILE);
		new Block(QPointF(28 * TILE, 150 * TILE), Qt::transparent, 2 * TILE, TILE);
		new Block(QPointF(29 * TILE, 149 * TILE), Qt::transparent, TILE, TILE);

		new Block(QPointF(30 * TILE, 142 * TILE), Qt::transparent, 1 * TILE, 4 * TILE);
		new Block(QPointF(31 * TILE, 142 * TILE), Qt::transparent, 1 * TILE, 6 * TILE);
		new Block(QPointF(32 * TILE, 142 * TILE), Qt::transparent, 2 * TILE, 8 * TILE);
		new Block(QPointF(34 * TILE, 144 * TILE), Qt::transparent, 1 * TILE, 6 * TILE);
		new Block(QPointF(35 * TILE, 146 * TILE), Qt::transparent, 1 * TILE, 4 * TILE);
		new Block(QPointF(30 * TILE, 144 * TILE), Qt::transparent, 1 * TILE, 1 * TILE);
		new Block(QPointF(31 * TILE, 146 * TILE), Qt::transparent, 1 * TILE, 1 * TILE);

		new Block(QPointF(41 * TILE, 141 * TILE), Qt::transparent, TILE, 7 * TILE);
		new Block(QPointF(42 * TILE, 143 * TILE), Qt::transparent, TILE, 5 * TILE);
		new Block(QPointF(46 * TILE, 143 * TILE), Qt::transparent, TILE, 5 * TILE);
		new Block(QPointF(47 * TILE, 141 * TILE), Qt::transparent, TILE, 7 * TILE);
		new Block(QPointF(41 * TILE, 150 * TILE), Qt::transparent, 7 * TILE, TILE);

		new Block(QPointF(20 * TILE, 139 * TILE), Qt::transparent, 4 * TILE, TILE);
		new Block(QPointF(26 * TILE, 139 * TILE), Qt::transparent, 14 * TILE, TILE);
		new Block(QPointF(42 * TILE, 139 * TILE), Qt::transparent, 6 * TILE, TILE);
		new Block(QPointF(50 * TILE, 139 * TILE), Qt::transparent, 6 * TILE, TILE);
		new Block(QPointF(58 * TILE, 139 * TILE), Qt::transparent, 6 * TILE, TILE);
		new Block(QPointF(66 * TILE, 139 * TILE), Qt::transparent, 6 * TILE, TILE);
		new Block(QPointF(74 * TILE, 139 * TILE), Qt::transparent, 8 * TILE, TILE);

		new Block(QPointF(20 * TILE, 140 * TILE), Qt::transparent, TILE, TILE);
		new Block(QPointF(36 * TILE, 140 * TILE), Qt::transparent, TILE, TILE);
		new Block(QPointF(44 * TILE, 140 * TILE), Qt::transparent, TILE, TILE);
		new Block(QPointF(52 * TILE, 140 * TILE), Qt::transparent, TILE, TILE);
		new Block(QPointF(60 * TILE, 140 * TILE), Qt::transparent, TILE, TILE);
		new Block(QPointF(68 * TILE, 140 * TILE), Qt::transparent, TILE, TILE);

		new Block(QPointF(78 * TILE, 146 * TILE), Qt::transparent, 4 * TILE, TILE);
		new Block(QPointF(82 * TILE, 146 * TILE), Qt::transparent, 6 * TILE, 5 * TILE);
		new Block(QPointF(82 * TILE, 139 * TILE), Qt::transparent, 4 * TILE, 4 * TILE);

		new Block(QPointF(88 * TILE, 150 * TILE), Qt::transparent, 8 * TILE, TILE);
		new Block(QPointF(88 * TILE, 148 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(88 * TILE, 144 * TILE), Qt::transparent, 8 * TILE, TILE);
		new Block(QPointF(86 * TILE, 139 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(91 * TILE, 139 * TILE), Qt::transparent, 6 * TILE, TILE);
		new Block(QPointF(96 * TILE, 146 * TILE), Qt::transparent, 6 * TILE, 5 * TILE);
		new Block(QPointF(98 * TILE, 139 * TILE), Qt::transparent, 4 * TILE, 4 * TILE);

		new Block(QPointF(102 * TILE, 151 * TILE), Qt::transparent, 60 * TILE, TILE);
		new Block(QPointF(102 * TILE, 146 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(82 * TILE, 139 * TILE), Qt::transparent, 4 * TILE, 4 * TILE);
		new Block(QPointF(93 * TILE, 140 * TILE), Qt::transparent, TILE, TILE);
		new Block(QPointF(136 * TILE, 140 * TILE), Qt::transparent, 8 * TILE, 10 * TILE);

		new Block(QPointF(102 * TILE, 139 * TILE), Qt::transparent, 4 * TILE, TILE);
		new Block(QPointF(102 * TILE, 140 * TILE), Qt::transparent, TILE, TILE);
		new Block(QPointF(108 * TILE, 139 * TILE), Qt::transparent, 6 * TILE, TILE);
		new Block(QPointF(110 * TILE, 140 * TILE), Qt::transparent, TILE, TILE);
		new Block(QPointF(116 * TILE, 139 * TILE), Qt::transparent, 4 * TILE, TILE);
		new Block(QPointF(116 * TILE, 140 * TILE), Qt::transparent, TILE, TILE);
		new Block(QPointF(122 * TILE, 139 * TILE), Qt::transparent, 6 * TILE, TILE);
		new Block(QPointF(124 * TILE, 140 * TILE), Qt::transparent, TILE, TILE);
		new Block(QPointF(130 * TILE, 139 * TILE), Qt::transparent, 22 * TILE, TILE);
		new Block(QPointF(144 * TILE, 140 * TILE), Qt::transparent, TILE, TILE);
		new Block(QPointF(148 * TILE, 140 * TILE), Qt::transparent, TILE, TILE);
		new Block(QPointF(154 * TILE, 139 * TILE), Qt::transparent, 10 * TILE, TILE);
		new Block(QPointF(158 * TILE, 146 * TILE), Qt::transparent, 11 * TILE, TILE);
		new Block(QPointF(162 * TILE, 147 * TILE), Qt::transparent, 4 * TILE, 6 * TILE);
		new Block(QPointF(162 * TILE, 140 * TILE), Qt::transparent, 4 * TILE, 3 * TILE);

		//Vertical Room 1 
		new Block(QPointF(165 * TILE, 153 * TILE), Qt::transparent, 13 * TILE, TILE);
		new Block(QPointF(164 * TILE, 11 * TILE), Qt::transparent, 2 * TILE, 129 * TILE);
		new Block(QPointF(178 * TILE, 3 * TILE), Qt::transparent, 2 * TILE, 35 * TILE);
		new Block(QPointF(178 * TILE, 41 * TILE), Qt::transparent, 2 * TILE, 113 * TILE);
		new Block(QPointF(163 * TILE, 4 * TILE), Qt::transparent, 3 * TILE, 4 * TILE);

		new Block(QPointF(170 * TILE, 149 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(176 * TILE, 147 * TILE), Qt::transparent, 2 * TILE, TILE);
		new Block(QPointF(171 * TILE, 142 * TILE), Qt::transparent, 4 * TILE, TILE);
		new Block(QPointF(168 * TILE, 138 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(170 * TILE, 134 * TILE), Qt::transparent, 4 * TILE, TILE);
		new Block(QPointF(174 * TILE, 131 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(167 * TILE, 130 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(171 * TILE, 126 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(166 * TILE, 124 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(170 * TILE, 119 * TILE), Qt::transparent, 4 * TILE, TILE);	
		new Block(QPointF(174 * TILE, 116 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(167 * TILE, 115 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(171 * TILE, 111 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(166 * TILE, 109 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(170 * TILE, 104 * TILE), Qt::transparent, 4 * TILE, TILE);
		new Block(QPointF(174 * TILE, 101 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(167 * TILE, 100 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(171 * TILE, 96 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(166 * TILE, 94 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(170 * TILE, 89 * TILE), Qt::transparent, 4 * TILE, TILE);
		new Block(QPointF(174 * TILE, 86 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(167 * TILE, 85 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(171 * TILE, 81 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(166 * TILE, 79 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(170 * TILE, 74 * TILE), Qt::transparent, 4 * TILE, TILE);
		new Block(QPointF(174 * TILE, 71 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(167 * TILE, 70 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(171 * TILE, 66 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(166 * TILE, 64 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(170 * TILE, 59 * TILE), Qt::transparent, 4 * TILE, TILE);
		new Block(QPointF(174 * TILE, 56 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(167 * TILE, 55 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(171 * TILE, 51 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(166 * TILE, 49 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(171 * TILE, 45 * TILE), Qt::transparent, 4 * TILE, TILE);
		new Block(QPointF(166 * TILE, 42 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(175 * TILE, 41 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(170 * TILE, 38 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(175 * TILE, 35 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(166 * TILE, 33 * TILE), Qt::transparent, 4 * TILE, TILE);
		new Block(QPointF(170 * TILE, 29 * TILE), Qt::transparent, 4 * TILE, TILE);
		new Block(QPointF(174 * TILE, 26 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(167 * TILE, 25 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(171 * TILE, 21 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(166 * TILE, 19 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(170 * TILE, 14 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(176 * TILE, 12 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(166 * TILE, 11 * TILE), Qt::transparent, 3 * TILE, TILE);

		//PowerUp Room
		new Block(QPointF(100 * TILE, 3 * TILE), Qt::transparent, 78 * TILE, TILE);
		new Block(QPointF(115 * TILE, 4 * TILE), Qt::transparent, 48 * TILE, TILE);
		new Block(QPointF(155 * TILE, 11 * TILE), Qt::transparent, 9 * TILE, TILE);
		new Block(QPointF(158 * TILE, 12 * TILE), Qt::transparent, TILE, 4 * TILE);
		new Block(QPointF(121 * TILE, 16 * TILE), Qt::transparent, 38 * TILE, TILE);
		new Block(QPointF(121 * TILE, 12 * TILE), Qt::transparent, TILE, 4 * TILE);
		new Block(QPointF(107 * TILE, 11 * TILE), Qt::transparent, 18 * TILE, TILE);
		new Block(QPointF(104 * TILE, 9 * TILE), Qt::transparent, 4 * TILE, 2 * TILE);
		new Block(QPointF(104 * TILE, 8 * TILE), Qt::transparent, 6 * TILE, TILE);
		new Block(QPointF(104 * TILE, 4 * TILE), Qt::transparent, TILE, 4 * TILE);
		new Block(QPointF(115 * TILE, 5 * TILE), Qt::transparent, 2 * TILE, 3 * TILE);
		new Block(QPointF(134 * TILE, 15 * TILE), Qt::transparent, 2 * TILE, TILE);
		new Block(QPointF(139 * TILE, 15 * TILE), Qt::transparent, 4 * TILE, TILE);
		new Block(QPointF(151 * TILE, 15 * TILE), Qt::transparent, 2 * TILE, TILE);

		//Bridge
		new Block(QPointF(180 * TILE, 41 * TILE), Qt::transparent, 16 * TILE, TILE);
		new Block(QPointF(180 * TILE, 37 * TILE), Qt::transparent, 16 * TILE, TILE);

		//Vertical Room 2
		new Block(QPointF(198 * TILE, 34 * TILE), Qt::transparent, 12 * TILE, TILE);
		new Block(QPointF(196 * TILE, 34 * TILE), Qt::transparent, 2 * TILE, 4 * TILE);
		new Block(QPointF(196 * TILE, 41 * TILE), Qt::transparent, 2 * TILE, 67 * TILE);
		new Block(QPointF(210 * TILE, 34 * TILE), Qt::transparent, 2 * TILE, 59 * TILE);
		new Block(QPointF(210 * TILE, 93 * TILE), Qt::transparent, 4 * TILE, 5 * TILE);
		new Block(QPointF(210 * TILE, 101 * TILE), Qt::transparent, 4 * TILE, 7 * TILE);
		new Block(QPointF(198 * TILE, 108 * TILE), Qt::transparent, 12 * TILE, TILE);

		new Block(QPointF(203 * TILE, 105 * TILE), Qt::transparent, 4 * TILE, TILE);
		new Block(QPointF(198 * TILE, 102 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(207 * TILE, 101 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(202 * TILE, 98 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(198 * TILE, 93 * TILE), Qt::transparent, 4 * TILE, TILE);
		new Block(QPointF(202 * TILE, 89 * TILE), Qt::transparent, 4 * TILE, TILE);
		new Block(QPointF(206 * TILE, 86 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(199 * TILE, 85 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(203 * TILE, 81 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(198 * TILE, 79 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(202 * TILE, 74 * TILE), Qt::transparent, 4 * TILE, TILE);
		new Block(QPointF(206 * TILE, 71 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(199 * TILE, 70 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(203 * TILE, 66 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(198 * TILE, 64 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(202 * TILE, 59 * TILE), Qt::transparent, 4 * TILE, TILE);
		new Block(QPointF(206 * TILE, 56 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(199 * TILE, 55 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(203 * TILE, 51 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(198 * TILE, 49 * TILE), Qt::transparent, 3 * TILE, TILE);
		new Block(QPointF(202 * TILE, 45 * TILE), Qt::transparent, 4 * TILE, TILE);
		new Block(QPointF(198 * TILE, 41 * TILE), Qt::transparent, 3 * TILE, TILE);

		//Boss Room
		new Block(QPointF(214 * TILE, 93 * TILE), Qt::transparent, 22 * TILE, TILE);
		new Block(QPointF(214 * TILE, 107 * TILE), Qt::transparent, 22 * TILE, TILE);
		new Block(QPointF(236 * TILE, 93 * TILE), Qt::transparent, TILE, 15 * TILE);
		new Block(QPointF(214 * TILE, 101 * TILE), Qt::transparent, (3 * TILE) - 1.5, TILE);
		new Block(QPointF(218 * TILE, 101 * TILE), Qt::transparent, TILE, TILE);
		new Block(QPointF(233 * TILE, 101 * TILE), Qt::transparent, TILE, TILE);
		new Block(QPointF(219 * TILE, 102 * TILE), Qt::transparent, 14 * TILE, 5 * TILE);
		new DamagingBlock(QPointF((214 * TILE), (103 * TILE) + 8), Qt::transparent, 5 * TILE, (4 * TILE) - 8);
		new DamagingBlock(QPointF((233 * TILE), (103 * TILE) + 8), Qt::transparent, 3 * TILE, (4 * TILE) - 8);

		//Portals 
		new Portal(QPointF(82 * TILE, 143 * TILE), false, false);
		new Portal(QPointF(85 * TILE, 143 * TILE), true, false);
		new Portal(QPointF(98 * TILE, 143 * TILE), false, false);
		new Portal(QPointF(101 * TILE, 143 * TILE), true, false);
		new Portal(QPointF(162 * TILE, 143 * TILE), false, false);
		new Portal(QPointF(165 * TILE, 143 * TILE), true, false);
		new Portal(QPointF(114 * TILE, 8 * TILE), false, true);
		new Portal(QPointF(117 * TILE, 8 * TILE), true, true);
		new Portal(QPointF(162 * TILE, 8 * TILE), false, false);
		new Portal(QPointF(165 * TILE, 8 * TILE), true, false);
		new Portal(QPointF(178 * TILE, 38 * TILE), false, false);
		new Portal(QPointF(181 * TILE, 38 * TILE), true, false);
		new Portal(QPointF(194 * TILE, 38 * TILE), false, false);
		new Portal(QPointF(197 * TILE, 38 * TILE), true, false);
		new Portal(QPointF(210 * TILE, 98 * TILE), false, false);
		new Portal(QPointF(213 * TILE, 98 * TILE), true, false);

		//Blocks between portals
		new Passable(QPointF(83 * TILE, 143 * TILE));
		new Passable(QPointF(99 * TILE, 143 * TILE));
		new Passable(QPointF(163 * TILE, 143 * TILE));
		new Passable(QPointF(115 * TILE, 8 * TILE));
		new Passable(QPointF(163 * TILE, 8 * TILE));
		new Passable(QPointF(179 * TILE, 38 * TILE));
		new Passable(QPointF(195 * TILE, 38 * TILE));
		new Passable(QPointF(211 * TILE, 98 * TILE));

		//spiders
		new Spider(QPointF(24 * TILE, 149 * TILE), true);
		new Spider(QPointF(41 * TILE, 140 * TILE), false);
		new Spider(QPointF(46 * TILE, 142 * TILE), true);
		new Spider(QPointF(77 * TILE, 150 * TILE), false);
		new Spider(QPointF(80 * TILE, 145 * TILE), true);
		new Spider(QPointF(89 * TILE, 143 * TILE), false);
		new Spider(QPointF(94 * TILE, 143 * TILE), false);
		new Spider(QPointF(107 * TILE, 150 * TILE), true);
		new Spider(QPointF(110 * TILE, 150 * TILE), true);
		new Spider(QPointF(133 * TILE, 150 * TILE), true);
		new Spider(QPointF(143 * TILE, 150 * TILE), false);
		new Spider(QPointF(158 * TILE, 150 * TILE), false);
		new Spider(QPointF(162 * TILE, 145 * TILE), false);

		new Spider(QPointF(170 * TILE, 148 * TILE), false);
		new Spider(QPointF(171 * TILE, 141 * TILE), true);
		new Spider(QPointF(168 * TILE, 137 * TILE), false);
		new Spider(QPointF(170 * TILE, 133 * TILE), true);
		new Spider(QPointF(174 * TILE, 130 * TILE), false);
		new Spider(QPointF(167 * TILE, 129 * TILE), false);
		new Spider(QPointF(171 * TILE, 125 * TILE), false);
		new Spider(QPointF(170 * TILE, 118 * TILE), true);
		new Spider(QPointF(174 * TILE, 115 * TILE), false);
		new Spider(QPointF(167 * TILE, 114 * TILE), false);
		new Spider(QPointF(171 * TILE, 110 * TILE), false);
		new Spider(QPointF(170 * TILE, 103 * TILE), true);
		new Spider(QPointF(174 * TILE, 100 * TILE), false);
		new Spider(QPointF(167 * TILE, 99 * TILE), false);
		new Spider(QPointF(171 * TILE, 95 * TILE), false);
		new Spider(QPointF(170 * TILE, 88 * TILE), true);
		new Spider(QPointF(174 * TILE, 85 * TILE), false);
		new Spider(QPointF(167 * TILE, 84 * TILE), false);
		new Spider(QPointF(171 * TILE, 80 * TILE), false);
		new Spider(QPointF(170 * TILE, 73 * TILE), true);
		new Spider(QPointF(174 * TILE, 70 * TILE), false);
		new Spider(QPointF(167 * TILE, 69 * TILE), false);
		new Spider(QPointF(171 * TILE, 65 * TILE), false);
		new Spider(QPointF(174 * TILE, 55 * TILE), false);
		new Spider(QPointF(167 * TILE, 54 * TILE), false);
		new Spider(QPointF(171 * TILE, 50 * TILE), false);
		new Spider(QPointF(171 * TILE, 44 * TILE), true);
		new Spider(QPointF(170 * TILE, 37 * TILE), false);
		new Spider(QPointF(170 * TILE, 28 * TILE), true);
		new Spider(QPointF(174 * TILE, 25 * TILE), false);
		new Spider(QPointF(167 * TILE, 24 * TILE), false);
		new Spider(QPointF(171 * TILE, 20 * TILE), false);

		new Spider(QPointF(203 * TILE, 104 * TILE), true);
		new Spider(QPointF(202 * TILE, 97 * TILE), true);
		new Spider(QPointF(202 * TILE, 88 * TILE), true);
		new Spider(QPointF(206 * TILE, 85 * TILE), true);
		new Spider(QPointF(199 * TILE, 84 * TILE), true);
		new Spider(QPointF(203 * TILE, 80 * TILE), true);
		new Spider(QPointF(202 * TILE, 73 * TILE), true);
		new Spider(QPointF(206 * TILE, 70 * TILE), true);
		new Spider(QPointF(199 * TILE, 69 * TILE), true);
		new Spider(QPointF(203 * TILE, 65 * TILE), true);
		new Spider(QPointF(202 * TILE, 58 * TILE), true);
		new Spider(QPointF(206 * TILE, 55 * TILE), true);
		new Spider(QPointF(199 * TILE, 54 * TILE), true);
		new Spider(QPointF(203 * TILE, 50 * TILE), true);
		new Spider(QPointF(202 * TILE, 44 * TILE), true);

		new Spider(QPointF(127 * TILE, 15 * TILE), false);
		new Spider(QPointF(137 * TILE, 15 * TILE), false);
		new Spider(QPointF(147 * TILE, 15 * TILE), false);


		//rippers
		new Ripper(QPointF(166 * TILE, 149 * TILE));
		new Ripper(QPointF(177 * TILE, 142 * TILE));
		new Ripper(QPointF(166 * TILE, 134 * TILE));
		new Ripper(QPointF(177 * TILE, 126 * TILE));
		new Ripper(QPointF(166 * TILE, 119 * TILE));
		new Ripper(QPointF(177 * TILE, 111 * TILE));
		new Ripper(QPointF(166 * TILE, 104 * TILE));
		new Ripper(QPointF(177 * TILE, 96 * TILE));
		new Ripper(QPointF(166 * TILE, 89 * TILE));
		new Ripper(QPointF(177 * TILE, 81 * TILE));
		new Ripper(QPointF(166 * TILE, 74 * TILE));
		new Ripper(QPointF(177 * TILE, 66 * TILE));
		new Ripper(QPointF(166 * TILE, 59 * TILE));
		new Ripper(QPointF(177 * TILE, 51 * TILE));
		new Ripper(QPointF(177 * TILE, 45 * TILE));
		new Ripper(QPointF(166 * TILE, 38 * TILE));
		new Ripper(QPointF(166 * TILE, 29 * TILE));
		new Ripper(QPointF(177 * TILE, 21 * TILE));
		new Ripper(QPointF(166 * TILE, 14 * TILE));

		new Ripper(QPointF(209 * TILE, 105 * TILE));
		new Ripper(QPointF(198 * TILE, 98 * TILE));
		new Ripper(QPointF(198 * TILE, 89 * TILE));
		new Ripper(QPointF(209 * TILE, 81 * TILE));
		new Ripper(QPointF(198 * TILE, 74 * TILE));
		new Ripper(QPointF(209 * TILE, 66 * TILE));
		new Ripper(QPointF(198 * TILE, 59 * TILE));
		new Ripper(QPointF(209 * TILE, 51 * TILE));
		new Ripper(QPointF(198 * TILE, 45 * TILE));

		//PowerUp
		new PowerUp(QPointF(26 * TILE, 147 * TILE), true);
		new PowerUp(QPointF(107 * TILE, 6 * TILE), false);

		//bats
		new Bat(QPointF(55 * TILE, 140 * TILE));
		new Bat(QPointF(61 * TILE, 140 * TILE));
		new Bat(QPointF(66 * TILE, 140 * TILE));

		new Bat(QPointF(113 * TILE, 140 * TILE));
		new Bat(QPointF(119 * TILE, 140 * TILE));
		new Bat(QPointF(127 * TILE, 140 * TILE));
		new Bat(QPointF(150 * TILE, 140 * TILE));

		new Bat(QPointF(133 * TILE, 5 * TILE));
		new Bat(QPointF(142 * TILE, 5 * TILE));

		return new Samus(QPointF(44 * TILE, 148 * TILE));

	}

	else if (round == 3)
	{
		new DeathScreen();
		return nullptr;
	}
	// returns the boss instance
	else if (round == 4)
		return new Boss(QPointF(230 * TILE, 99 * TILE));
	
	else
	{
		std::cerr << "Level \"" << round << "\" not yet implemented\n";
		return nullptr;
	}
}