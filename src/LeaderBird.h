#ifndef LEADERBIRD_H
#define LEADERBIRD_H
#include "FlyingObject.h"

class LeaderBird : public FlyingObject 
{
public:
	LeaderBird();
	~LeaderBird();
	void simulate();
	void fly(float TIMESTEP);
	void update(float x, float y);
	bool getUpdate();
	float getVy();
	float getVx();
	bool getStatus();
	void end();
	
	
private:	
	float _spdX;
	float _spdY;
	float _prevPosX;
	float _prevPosY;
	float _newPosX;
	float _newPosY;
	bool _budpated;
	static bool _proceed;

};

#endif