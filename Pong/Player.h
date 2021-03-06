#pragma once
#include "Object.h"
#include "SDL.h"
#include "SerialInterface.h"

class Player : public Object
{
public:
	void virtual init();
	void virtual Move();
	
	enum Side{Side_Undefined,Side_Left,Side_Right};
	void SetSide(Side eSide);

	void SetPosY(float newPosY);
	float GetPosY();

private:
	Side mySide;
	int speed;
};
