#ifndef FLYINGOBJECT_H
#define FLYINGOBJECT_H

#include "Sky.h"
#include <vector>
#include <thread>
#include <mutex>
#include <memory>

enum ObjectType
{
	leaderBird,
	slowBird,
	fastBird,
};

class FlyingObject
{
public:
	// Constructor / desttructor
	FlyingObject();
	~FlyingObject();
	// getter and setter
	int getNumberOfBirds();
	float getPosX();
	float getPosY();
	// typical behavior methods
	virtual void fly();
	virtual void simulate() {};
	

protected:
	int _id;
	float _posX, _posY;
	ObjectType _type;
	std::vector<std::thread> threads; // holds all threads that have been launched within this object
	static std::mutex _mtx;
	static Sky _sky;
	static std::shared_ptr<std::vector<float>> _targetPos;

private:
	static int _nbBird;
	
	
};

#endif