#include "Sky.h"


Sky::Sky(double width, double height): _width(width), _height(height)
{

}
Sky::~Sky()
{

}

// getter / setter
double Sky::getWidth() { return _width; }
double Sky::getHeight() { return _height; }
