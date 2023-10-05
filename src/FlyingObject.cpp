#include "FlyingObject.h"
#include <algorithm>

// init static variable
int FlyingObject::_nbBird = 0;
int FlyingObject::_lifePoint = 100;
std::mutex FlyingObject::_mtx;

FlyingObject::FlyingObject()
{

	_id = _nbBird++;
	_posX = 0;
	_posY = 0;
	_type = ObjectType::slowBird; // need to remove this one
	
}

FlyingObject::~FlyingObject()
{
	_nbBird--;
}

void FlyingObject::fly()
{
}

int FlyingObject::getLifePoint()
{
	return std::max(_lifePoint,0);
}

int FlyingObject::getNumberOfBirds() { return _nbBird; }

float FlyingObject::getPosX(){ return _posX;}

float FlyingObject::getPosY(){ return _posY;}