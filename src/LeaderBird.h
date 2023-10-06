#ifndef LEADERBIRD_H
#define LEADERBIRD_H
#include "FlyingObject.h"

class LeaderBird : public FlyingObject 
{
public:
	LeaderBird();
	~LeaderBird();
	void simulate();
	void fly(double TIMESTEP);
	void update(double x, double y);
	bool getUpdate();
	double getVy();
	double getVx();
	bool getStatus();
	void end();
	
	
private:	
	double _spdX;
	double _spdY;
	double _prevPosX;
	double _prevPosY;
	double _newPosX;
	double _newPosY;
	bool _budpated;
	static bool _proceed;

};

#endif