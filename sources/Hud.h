#pragma once

#include <QGraphicsView>
#include "Object.h"
#include "StaticObject.h"
#include "Samus.h"

namespace MT
{
	class HUD;
	class Text;
}

class MT::HUD : public Object
{

private:
	
	// state flags
	bool _started; 
	bool _hud;
	bool _hitted;
	bool _missile;
	// animations
	QRect _animEnergy[2];
	QPointF _pos;

public:

	HUD(QPointF pos, double w, double h);
	
	// reimplemented abstract methods 
	virtual void advance() override;
	virtual void animate() override;
	virtual bool hit(Object* what, Direction fromDir) override;
	virtual std::string name() override { return "Hud[" + std::to_string(_id) + "]"; }
	

	
	
};

