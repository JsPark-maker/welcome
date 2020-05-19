#include "stdafx.h"
#include "CBaseObject.h"
CBaseObject::CBaseObject(int X, int Y, ObjectType otf) 
	:iX(X), iY(Y), ot(otf)
{
}

CBaseObject::~CBaseObject()
{
}

ObjectType CBaseObject::GetObjectType()
{
	return ot;
}

int CBaseObject::GetX()
{
	return iX;
}

int CBaseObject::GetY()
{
	return iY;
}
