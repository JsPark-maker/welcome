#pragma once
class CEnemyObject : public CBaseObject
{
public:
	CEnemyObject(int X, int Y, ObjectType ot);
	~CEnemyObject();
	bool Action() override;
	void Draw() override;
private:
	void EnemyMovement();
	void ShootEnemyBullet();
	bool isLeft = true;

};

