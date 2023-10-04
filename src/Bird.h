#ifndef BIRD_H
#define BIRD_H

#include <opencv2/opencv.hpp>
#include "FlyingObject.h"
#include "LeaderBird.h"


class Bird : public FlyingObject
{
    public:
        Bird();
        Bird(int id, float x);
        ~Bird();
        int getBirdID();
        void setBirdID(int id);
        //int getNumberOfBird();
        cv::Point getbirdGraphicPosition();
        float getBirdXpos();
        float getBirdYpos();
        void setbirdGraphicPosition(cv::Point point);
        void fly(float TIMESTEP);
        void fly(float TIMESTEP, float xLead, float yLead);
        void fly(float TIMESTEP, LeaderBird* leadBird);

    private:
        int _birdID;
        cv::Point _birdGraphicPosition; 
        //static int _numberOfBird;
        float _aY;
        float _aX;
        float _vY;
        float _vX;
        //LeaderBird birdChef;
        

};
#endif