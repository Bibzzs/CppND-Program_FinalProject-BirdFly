#pragma once
#ifndef SKY_H
#define SKY_H



class Sky
{
public:
	Sky(double width, double height);
	~Sky();
	// getter / setter
	double getWidth();
	double getHeight();
private:
	double _width;
	double _height;
};


#endif  
