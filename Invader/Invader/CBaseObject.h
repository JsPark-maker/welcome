#pragma once


class CBaseObject
{
public:
	CBaseObject(int X, int Y, ObjectType otf);
	virtual ~CBaseObject();

	virtual bool Action(void) = 0;
	virtual void Draw(void) = 0;
	ObjectType GetObjectType();
	int GetX();
	int GetY();
protected:

	int iX;
	int iY;
	ObjectType ot;
};

