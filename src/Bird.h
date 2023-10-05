#ifndef BIRD_H
#define BIRD_H

#include <opencv2/opencv.hpp>
#include "FlyingObject.h"
#include "LeaderBird.h"


class Bird : public FlyingObject, public std::enable_shared_from_this<Bird>
{
    public:
        Bird();
        Bird(float x);
        ~Bird();
        
        void simulate();
        void fly(float TIMESTEP, LeaderBird* leadBird);

        // miscellaneous
        std::shared_ptr<Bird> get_shared_this() { return shared_from_this(); }
    
private:
        float _aY;
        float _aX;
        float _vY;
        float _vX;
        bool _hit;
        bool targetReached(LeaderBird* leadBird);
        
};
#endif