#pragma once

#include "Object.h"

namespace MT
{
	class DeathScreen;

}

class MT::DeathScreen : public Object
{
	private:

		QRect _animDeathScreen;


	public:

		DeathScreen();

		// implemented abstract methods
		virtual void advance() {};
		virtual void animate() override;
		virtual bool hit(Object* what, Direction fromDir) override { return true; }
		virtual std::string name() override { return "deathscreen"; }
};

