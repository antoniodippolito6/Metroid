#pragma once

#include "Object.h"

namespace MT
{
	class Title;
	class Text;
}

class MT::Title : public Object
{
	private:

		// state flags
		bool _moving;
		//animations
		QRect _animTitle[21];
	

	public:

		Title();

		// implemented abstract methods
		virtual void advance() override;
		virtual void animate() override;
		virtual bool hit(Object* what, Direction fromDir) override { return true; }
		virtual std::string name() override { return "Title"; }
};

class MT::Text : public Object
{
private:

	QPixmap _pixText;
	QRect _animText;

public:

	Text();

	// implemented abstract methods
	virtual void advance() override;
	virtual void animate() override;
	virtual bool hit(Object* what, Direction fromDir) override { return true; }
	virtual std::string name() override { return "Text"; }
};


