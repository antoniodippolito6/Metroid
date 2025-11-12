#include <QApplication>
#include <QPainter>
#include <QKeyEvent>
#include <QIcon>
#include <QOpenGLWidget>
#include <QGraphicsPixmapItem>
#include <QBrush>
#include <QTimer>
#include "Game.h"
#include "GameConfig.h"
#include "Loader.h"
#include "Samus.h"
#include "Sprites.h"
#include "Object.h"
#include "PowerUp.h"
#include "Sounds.h"
#include "Hud.h"
#include"Boss.h"
#include"DeathScreen.h"

using namespace MT;

// singleton
Game* Game::_uniqueInstance = 0;
Game* Game::instance()
{
	if (_uniqueInstance == 0)
		_uniqueInstance = new Game();

	return _uniqueInstance;
}

Game::Game() : QGraphicsView()
{
	// setup world
	_world = new QGraphicsScene();
	_world->setSceneRect(0, 0, TILE * 300, TILE * 200);
	setScene(_world);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setInteractive(false);

	// setup game engine
	QObject::connect(&_engine, SIGNAL(timeout()), this, SLOT(nextFrame()));
	_engine.setTimerType(Qt::PreciseTimer);
	_engine.setInterval(1000 / FPS);

	// enable OpenGL rendering
	QOpenGLWidget* gl = new QOpenGLWidget();
	setViewport(gl);

	reset();
}

void Game::reset()
{
	_state = GameState::READY;
	_engine.stop();
	_world->clear();
	_world->setBackgroundBrush(QBrush(Qt::black));
	_player = 0;
	_boss = 0;

	// per-frame controls flags reset
	_up_pressed = false;
	_left_pressed = false;
	_right_pressed = false;
	_jump_pressed = false;
	_fire_pressed = false;
	_roll_pressed = false;
	_spinning_jump = false;
	_invincibility = false;

	restoreDefaultView();
	Sounds::instance()->stopMusic("Brinstar");
	setSceneRect(QRectF());
	centerOn(44 * TILE, 149 * TILE);

	QTimer::singleShot(0, this, &Game::welcome);
}

void Game::welcome()
{
	if (_state == GameState::READY)
	{
		_state = GameState::TITLE_SCREEN;
		_world->clear();
		Loader::load(0);
		_engine.start();
		centerOn(0, 0);
		Sounds::instance()->playMusic("Title", true);
	}
}

void Game::start()
{
	if (_state == GameState::TITLE_SCREEN)
	{
		_state = GameState::RUNNING;
		_world->clear();
		_engine.start();
		Sounds::instance()->stopMusic("Title");

		//loading level 1 and main character
		_player = (Samus*)Loader::load(1);
		// loading level 1 boss
		_boss = (Boss*)Loader::load(4);

		Sounds::instance()->playMusic("Brinstar", true);
		//camera
		centerView();
		centerOn(44 * TILE, 149 * TILE);
	}
}

void Game::gameOver()
{
	if (_state == GameState::RUNNING)
	{
		_state = GameState::GAME_OVER;
		_world->clear();
		_engine.stop();
		// loading deathScreen 
		_player = (Samus*)Loader::load(3);
		Sounds::instance()->stopMusic("Title");
		Sounds::instance()->stopMusic("Brinstar");
		Sounds::instance()->stopMusic("Item_Obtainment_Jingle");
		//camera
		centerView();
		centerOn(0, 0);
	}
}

void Game::togglePause()
{
	if (_state == GameState::RUNNING)
	{
		_engine.stop();
		keyRefresh();
		Sounds::instance()->stopMusic(_music);
		_state = GameState::PAUSED;
	}

	else if (_state == GameState::PAUSED )
	{
		_engine.start();
		Sounds::instance()->playMusic(_music);
		_state = GameState::RUNNING;
	}
}

void Game::freeze()
{
	// WARNING
	/*	this function is called if Samus takes a powerUp
		in this case the game is frozen for 5 seconds
		if the Pause button is pressed you will exit the freeze state but the counter will continue to run
		and	when the 5 seconds expires the togglePause function will be called and you will be back in the pause state 
	*/
	togglePause();
	QTimer::singleShot(5000, [this] {togglePause(); Sounds::instance()->playMusic("Brinstar"); });
} 

// main game loop
void Game::nextFrame() 
{
	if (_state != GameState::RUNNING && _state != GameState::TITLE_SCREEN)
		return;

	//process inputs	 (PLAYER CONTROLS)
	if (_state == GameState::RUNNING && !_player->dying())
	{
		if (_left_pressed && _right_pressed)
			_player->move(Direction::NONE);

		else if (_left_pressed)
			_player->move(Direction::LEFT);

		else if (_right_pressed)
			_player->move(Direction::RIGHT);

		else
			_player->move(Direction::NONE);

		if (!(_jump_pressed && (_right_pressed || _left_pressed))) 
		{
			_player->jump(_jump_pressed);
			_player->spinning_jump(false);
		}
		else 
		{
			if (_player->stuck())
				_player->jump(_jump_pressed);

			else if (!_player->get_spinning_jump())
				_player->spinning_jump(true);
		}

		if (_fire_pressed)
			_player->fire();

		if (_roll_pressed && !_jump_pressed)
		{
			_player->roll();
			_roll_pressed = false;
		}

		if (_up_pressed)
			_player->lookUp(_up_pressed);

		if (!_up_pressed)
			_player->lookUp(_up_pressed);
	}

	if (_player)
	{
		//FIX CAMERA
		// first portal
		if (_player->x() >= 19 * TILE && _player->x() <= 83 * TILE)  
		{
			centerOn(std::min(_player->x(), _margin * 76), 145.7 * TILE);
			_view_rect.moveTopLeft(QPointF(std::min(_player->x(), _margin * 76), 145.7 * TILE));
		}
		// second portal
		else if (_player->x() >= 84 * TILE && _player->x() <= 99 * TILE && _player->y() >= 138 * TILE && _player->y() <= 151 * TILE) 
		{
			centerOn(92 * TILE, 145.7 * TILE);
			_view_rect.moveTopLeft(QPointF(92 * TILE, 145.7 * TILE));
		}
		// third portal sx
		else if (_player->x() >= 108 * TILE && _player->x() <= 163 * TILE && _player->y() >= 138 * TILE && _player->y() <= 151 * TILE) //TERZO PORTALE dx
		{
			centerOn(std::min(_player->x(), _margin * 156), 145.7 * TILE);
			_view_rect.moveTopLeft(QPointF(std::min(_player->x(), _margin * 156), 145.7 * TILE));
		}
		// third portal dx
		else if (_player->x() >= 100 * TILE && _player->x() <= 155 * TILE && _player->y() >= 138 * TILE && _player->y() <= 151 * TILE) //TERZO PORTALE sx
		{
			centerOn(std::max(_player->x(), _margin * 108), 145.7 * TILE);
			_view_rect.moveTopLeft(QPointF(std::max(_player->x(), _margin * 108), 145.7 * TILE));
		}
		// blu vertical zone 
		else if ((_player->x() >= 164 * TILE) && (_player->x() <= 179 * TILE)) 
		{
			centerOn(172 * TILE, std::max(_player->y(), _margin * 10.7));
			_view_rect.moveTopLeft(QPointF(172 * TILE, std::max(_player->y(), _margin * 10.7)));
		}
		// upper zone dx 
		else if (_player->x() >= 124 * TILE && _player->x() <= 163 * TILE && _player->y() <= 17 * TILE) 
		{
			centerOn(std::min(_player->x(), _margin * 156), 10.7 * TILE);
			_view_rect.moveTopLeft(QPointF(std::min(_player->x(), _margin * 156), 10.7 * TILE));
		}
		// upper zone sx
		else if (_player->x() >= 116 * TILE && _player->x() <= 155 * TILE && _player->y() <= 17 * TILE) 
		{
			centerOn(std::max(_player->x(), _margin * 124), 10.7 * TILE);
			_view_rect.moveTopLeft(QPointF(std::max(_player->x(), _margin * 124), 10.7 * TILE));
		}
		// power up 
		else if (_player->x() >= 100 * TILE && _player->x() <= 115 * TILE && _player->y() <= 17 * TILE) 
		{
			centerOn(108 * TILE, 10.7 * TILE);
			_view_rect.moveTopLeft(QPointF(108 * TILE, 10.7 * TILE));
		}
		// bridge
		else if (_player->x() >= 180 * TILE && _player->x() <= 195 * TILE && _player->y() >= 37 * TILE && _player->y() <= 41 * TILE) 
		{
			centerOn(188 * TILE, 39.7 * TILE);
			_view_rect.moveTopLeft(QPointF(188 * TILE, 39.7 * TILE));
		}
		// yellow vertical zone  
		else if (_player->x() >= 196 * TILE && _player->x() <= 211 * TILE)
		{
			centerOn(204 * TILE, std::max(_player->y(), _margin * 41.7));
			_view_rect.moveTopLeft(QPointF(204 * TILE, std::max(_player->y(), _margin * 41.7)));
		}
		// boss room dx
		else if (_player->x() >= 222 * TILE && _player->x() <= 236 * TILE) 
		{
			centerOn(std::min(_player->x(), _margin * 229), 100.7 * TILE);
			_view_rect.moveTopLeft(QPointF(std::min(_player->x(), _margin * 229), 100.7 * TILE));
		}
		// boss room sx
		else if (_player->x() >= 212 * TILE && _player->x() <= 222 * TILE) 
		{
			centerOn(std::max(_player->x(), _margin * 220), 100.7 * TILE);
			_view_rect.moveTopLeft(QPointF(std::max(_player->x(), _margin * 220), 100.7 * TILE));
		}

		//Game over for samus's dead or boss's dead
		if (_player->life() <= 0 || _boss->life() <= 0)
		{
			/*
				the call to the gameOver function is delayed by singleShot so that the character death animation is seen;
				in this way the words 'game over' are not read. 
				on the other hand, if I do not use singleShot because of the delay the words 'game over' are displayed
				but the death of the character or boss is not visible 
			*/

			//QTimer::singleShot(1000, [this] {gameOver();});
			gameOver();
		}
	}

	// advance game
	for (auto item : _world->items())
	{
		Object* obj = dynamic_cast<Object*>(item);

		if (obj && !obj->getDie())
		{
			obj->advance();			 // physics, collision detection and resolution, game logic
			obj->animate();			 // animation
			obj->updateSchedulers(); // game logic
			//obj->paint();			 // graphics, automatically called by Qt
		}
	}

	// @TODO update game state (game over, level cleared, etc.)

	update();

	FRAME_COUNT++;
}

void Game::keyPressEvent(QKeyEvent* e)
{
	if (e->isAutoRepeat())
		return;

	// game controls
	if (e->key() == Qt::Key_S)
		start();

	else if (e->key() == Qt::Key_R)
		reset();

	else if (e->key() == Qt::Key_P)
		togglePause();

	else if (e->key() == Qt::Key_Minus)
		_engine.setInterval(250);

	else if (e->key() == Qt::Key_Plus)
		_engine.setInterval(1000 / FPS);

	else if (e->key() == Qt::Key_C)
	{
		for (auto item : _world->items())
			if (dynamic_cast<Object*>(item))
				dynamic_cast<Object*>(item)->toggleCollider();
	}

	// player controls
	if (_state == GameState::RUNNING && _player)
	{
		if (e->key() == Qt::Key_Left)
			_left_pressed = true;

		else if (e->key() == Qt::Key_Right)
			_right_pressed = true;

		else if (e->key() == Qt::Key_Space)
			_jump_pressed = true;

		else if (e->key() == Qt::Key_F)
			_fire_pressed = true;

		else if (e->key() == Qt::Key_Down)
			_roll_pressed = true;

		else if (e->key() == Qt::Key_Up)
			_up_pressed = true;

		// cheats
		else if (e->key() == Qt::Key_I)
		{
			if (_invincibility == true) 
			{
				_invincibility = false; // invincibility
				_player->setInvincibile(false);
			}

			else if(_invincibility==false)
			{
				_invincibility = true;
				_player->setInvincibile(true);
			}
		}
	}
}

void Game::keyReleaseEvent(QKeyEvent* e)
{
	if (e->isAutoRepeat())
		return;

	// player controls
	if (_state == GameState::RUNNING && _player)
	{
		if (e->key() == Qt::Key_Left)
			_left_pressed = false;

		else if (e->key() == Qt::Key_Right)
			_right_pressed = false;

		else if (e->key() == Qt::Key_Space)
			_jump_pressed = false;

		else if (e->key() == Qt::Key_F)
			_fire_pressed = false;

		else if (e->key() == Qt::Key_Up)
			_up_pressed = false;
	}
}

void Game::keyRefresh()
{
	_left_pressed = false;
	_right_pressed = false;
	_jump_pressed = false;
	_fire_pressed = false;
	_up_pressed = false;
}

void Game::wheelEvent(QWheelEvent* e)
{
	if (e->angleDelta().y() > 0)
		scale(1.1, 1.1);
	else
		scale(1 / 1.1, 1 / 1.1);
}

void Game::resizeEvent(QResizeEvent* evt)
{
	fitInView(0, 0, TILE * 16, TILE * 15);
}

//camera
void Game::centerView()
{
	setSceneRect(_view_rect);
}

void Game::restoreDefaultView()
{
	_margin = TILE;
}