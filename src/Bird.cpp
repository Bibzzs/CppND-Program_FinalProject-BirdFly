#include "Bird.h"
#include <math.h>
#include <random>
#include<iostream>

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


Bird::Bird(float x)
{
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
    _aY = 0;
    _vY = 0;
    _vX = 0;
    _posX = 0;
    _posY = 0;
    
}

Bird::~Bird()
{
    //_numberOfBird--;
}

void Bird::simulate()
{

}

void Bird::fly(float timestep, LeaderBird* leadBird)
{
    while (leadBird->getStatus())
    {
        // sleep at every iteration to reduce CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds((int)(timestep * 1000)));
        if (leadBird->getUpdate())
        {
            std::unique_lock<std::mutex> lock(_mtx); // ensure that the x,y or speed of leadbird are not change during the controller calculation.
            // std::cout << " calculation of bird # " << this->_birdID << std::endl; // DEBUG INFO
            float deltaY = leadBird->getPosY() - _posY;
            float deltaX = leadBird->getPosX() - _posX;
            float deltaVy = leadBird->getVy() - _vY;
            float deltaVx = leadBird->getVx() - _vX;
            lock.unlock();
            _aY = 0.7 * deltaY + 0.9 * deltaVy;
            _aX = 0.7 * deltaX + 0.9 * deltaVx;
            float noiseVX = randomInRange(-0.020, 0.020) * deltaVx;
            float noiseVY = randomInRange(-0.05, 0.05) * deltaVy;
            _vY = _vY + _aY * timestep + noiseVY;
            _vX = _vX + _aX * timestep + noiseVX;
            float noiseX = randomInRange(-0.05, 0.05);
            float noiseY = randomInRange(-0.1, 0.1);
            _posY = 0.5 * _aY * timestep * timestep + _vY * timestep + _posY + noiseY;
            _posX = 0.5 * _aX * timestep * timestep + _vX * timestep + _posX + noiseX;
        }
        else
        {
            if (_posY > _sky.getHeight())
            {
                _vY = 0;
                _aY = 0;
            }
            else
            {
                _vY = _vY + _aY * timestep;
                _posY = 0.5 * _aY * timestep * timestep + _vY * timestep + _posY;
            }
        }
        _hit = targetReached(leadBird);
    }  
}

bool Bird::targetReached(LeaderBird* leadBird)
{
    std::unique_lock<std::mutex>  lock(_mtx);
    double dist = sqrt(pow((this->_posX - leadBird->getPosX()), 2.0) + pow((this->_posY - leadBird->getPosY()), 2.0));
    lock.unlock();

    if (dist < 0.5) 
    {
        std::unique_lock<std::mutex>  lock(_mtx);
        _lifePoint--;
        lock.unlock();
        return true;
    }
    else { return false; }
    
}


