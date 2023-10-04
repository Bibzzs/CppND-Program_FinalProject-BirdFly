#include "Bird.h"
#include <random>


template <class T>
T randomInRange(const T min, const T max)
{
    // Create a random number generator engine
    std::random_device rd;  // Seed the random number generator
    std::mt19937 gen(rd()); // Mersenne Twister engine
    std::uniform_real_distribution<T> distribution(min, max); // Uniform distribution between a and b

    // Generate a random number within the specified range
    return distribution(gen);
}

//int Bird::_numberOfBird = 0;

Bird::Bird(int ID, float x): _birdID(ID)
{
    setbirdGraphicPosition(cv::Point(x, 0));
    _type = ObjectType::fastBird;
    _aY = 9.810;
    _vY = 0;
    _vX = 0;
    _posX = x;
    _posY = 0;
    
}

Bird::Bird()
{
    //_numberOfBird++;
    setbirdGraphicPosition(cv::Point(0, 0));
}

Bird::~Bird()
{
    //_numberOfBird--;
}


int Bird::getBirdID()
{
    return _birdID;
}

void Bird::setBirdID(int id)
{
}

//int Bird::getNumberOfBird()
//{
//    return _numberOfBird;
//}

void Bird::setbirdGraphicPosition(cv::Point point)
{
    _birdGraphicPosition = point;
}

void Bird::fly(float timestep)
{
    if (_posY > _sky.getHeight() )
    {
        _vY = 0;
        _aY = 0;
    }
    else
    {
        _vY = _vY + _aY * timestep;
        _posY = 0.5 * _aY * timestep * timestep + _vY * timestep + _posY;
    }
    
    //setbirdGraphicPosition(cv::Point(0, _Y));
}

void Bird::fly(float timestep, float xLead, float yLead)
{
    float deltaY = yLead - _posY;
    float deltaVy = (5) * timestep;
    _aY = 0.2 * deltaY;
    _vY = _vY + _aY * timestep;
    _posY = 0.5 * _aY * timestep * timestep + _vY * timestep + _posY;
}
void Bird::fly(float timestep, LeaderBird* leadBird)
{
    float deltaY = leadBird->getPosY() - _posY;
    float deltaX = leadBird->getPosX() - _posX;
    float deltaVy = leadBird->getVy() - _vY;
    float deltaVx = leadBird->getVx() - _vX;
    _aY = 0.7 * deltaY + 0.9 * deltaVy;
    _aX = 0.7 * deltaX + 0.9 * deltaVx;
    float noiseVX = randomInRange(-0.020, 0.020)* deltaVx;
    float noiseVY = randomInRange(-0.05, 0.05)* deltaVy;
    _vY = _vY + _aY * timestep + noiseVY;
    _vX = _vX + _aX * timestep + noiseVX;
    float noiseX = randomInRange(-0.05, 0.05);
    float noiseY = randomInRange(-0.1, 0.1);
    _posY = 0.5 * _aY * timestep * timestep + _vY * timestep + _posY + noiseY;
    _posX = 0.5 * _aX * timestep * timestep + _vX * timestep + _posX + noiseX;

}


cv::Point Bird::getbirdGraphicPosition()
{
    return _birdGraphicPosition;
}

float Bird::getBirdXpos()
{
    return _posX;
}

float Bird::getBirdYpos()
{
    return _posY;
}

