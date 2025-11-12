#pragma once
\
#include <QGraphicsView>
#include <QTimer>
#include <QLabel>
#include "Hud.h"

namespace MT
{
	class Game;
	class Samus;
	class Boss;
	enum class GameState { READY, TITLE_SCREEN, RUNNING, PAUSED, GAME_OVER };
}

class MT::Game : public QGraphicsView
{ 
	Q_OBJECT 

	private:

		// game attributes
		QTimer			_engine;
		GameState		_state;
		QGraphicsScene* _world;
		QGraphicsScene* _hud;
		std::string		_music;

		// I store in a pointer variable the main character instance,
		// which is essential for managing game dynamics 
		Samus*			_player;
		// I store the boss instance in a pointer variable,
		// so that I can access its attributes and handle the boss kill
		Boss *			_boss;
		
		// camera
		QRectF			_view_rect;
		qreal			_margin;


		// per-frame controls flags
		bool			_up_pressed;
		bool			_left_pressed;
		bool			_right_pressed;
		bool			_jump_pressed;
		bool			_fire_pressed;
		bool			_roll_pressed;
		bool			_spinning_jump;
		bool			_invincibility;
;
		

		// singleton
		static Game* _uniqueInstance;
		Game();

	public: 
		
		static Game* instance();

		// getters 
		QGraphicsScene* world()  { return _world; }
		Samus* player() { return _player; }
		Boss* boss() { return _boss; }
		double aspectRatio() { return 16 * 1.14 / 15; }
		QRectF viewRect() { return _view_rect; }

		//camera
		void moveView(QPointF p) { _view_rect.moveTopLeft(p); }
		void setViewLeftMargin(int m) { _margin = m; }
		void centerView();
		void restoreDefaultView();

		// event handlers
		virtual void keyPressEvent(QKeyEvent* e) override;		
		virtual void keyReleaseEvent(QKeyEvent* e) override;
		virtual void wheelEvent(QWheelEvent* e) override;
		virtual void resizeEvent(QResizeEvent* event) override;
		virtual void keyRefresh();

	public slots:

		void reset();
		void welcome();
		void start();
		void gameOver();
		void freeze();
		void nextFrame();
		void togglePause();
		 
};