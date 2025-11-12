#pragma once
#include "Samus.h"
#include <iostream>

namespace MT
{
	class Loader;
	class Samus;
}

class MT::Loader
{
	private: 

		//auxiliary variable used for portals
		bool _position; 

		Samus* _player;

	public:
		
		static DynamicObject* load(int round);
};
