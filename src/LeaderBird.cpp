#include "LeaderBird.h"

bool LeaderBird::_proceed = true;
LeaderBird::LeaderBird()
{
	_type = ObjectType::leaderBird;
	_posX = 10;
	_posY = 10;
	_newPosX = _posX;
	_newPosY = _posY;
	_prevPosX = _posX;
	_prevPosY = _posY;
	_budpated = false;
}

LeaderBird::~LeaderBird()
{
	
}

void LeaderBird::simulate()
{
	int a = 0;
}

void LeaderBird::fly(double TIMESTEP)
{
	std::lock_guard<std::mutex> lock(_mtx);
	_prevPosX = _posX;
	_prevPosY = _posY;
	_posX = _newPosX;
	_posY = _newPosY;
	_spdX = (_posX - _prevPosX) / TIMESTEP;
	_spdY = (_posY - _prevPosY) / TIMESTEP;
	if (_prevPosY != _posY || _prevPosX != _posX) { _budpated = true; }
	//else { _budpated = false; }
}

bool LeaderBird::getUpdate()
{
	return _budpated;
}


void LeaderBird::update(double x, double y)
{
	_newPosX = x;
	_newPosY = y;
}

double LeaderBird::getVy()
{
	return _spdY;
}
double LeaderBird::getVx()
{
	return _spdX;
}
void LeaderBird::end()
{
	_proceed = false;
}
bool LeaderBird::getStatus()
{
	return _proceed;
}