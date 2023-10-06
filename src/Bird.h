#ifndef BIRD_H
#define BIRD_H

#include <opencv2/opencv.hpp>
#include "FlyingObject.h"
#include "LeaderBird.h"


class Bird : public FlyingObject, public std::enable_shared_from_this<Bird>
{
    public:
        Bird();
        Bird(double x);
        ~Bird();
        
        void simulate();
        void fly(double TIMESTEP, LeaderBird* leadBird);

        // miscellaneous
        std::shared_ptr<Bird> get_shared_this() { return shared_from_this(); }
    
private:
        double _aY;
        double _aX;
        double _vY;
        double _vX;
        bool _hit = false;
        bool targetReached(LeaderBird* leadBird);
        
};
#endif