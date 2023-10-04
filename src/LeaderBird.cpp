#include "LeaderBird.h"

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
	//**_targetPos[0] = _posX;
	//&_targetPos[1] = _posY;

}

LeaderBird::~LeaderBird()
{
}

void LeaderBird::fly(float TIMESTEP)
{
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


void LeaderBird::update(float x, float y)
{
	_newPosX = x;
	_newPosY = y;
}

float LeaderBird::getBirdXpos()
{
	return 0.0f;
}

float LeaderBird::getBirdYpos()
{
	return 0.0f;
}

float LeaderBird::getVy()
{
	return _spdY;
}
float LeaderBird::getVx()
{
	return _spdX;
}
