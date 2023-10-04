#include "FlyingObject.h"

// init static variable
int FlyingObject::_nbBird = 0;

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

int FlyingObject::getNumberOfBirds() { return _nbBird; }

float FlyingObject::getPosX(){ return _posX;}

float FlyingObject::getPosY(){ return _posY;}