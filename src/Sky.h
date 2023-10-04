#pragma once
#ifndef SKY_H
#define SKY_H



class Sky
{
public:
	Sky(int width, int height);
	~Sky();
	// getter / setter
	int getWidth();
	int getHeight();
private:
	int _width;
	int _height;
};


#endif  
