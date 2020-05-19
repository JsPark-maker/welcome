#pragma once
class CBulletObject : public CBaseObject
{
public:
	CBulletObject(int X, int Y, ObjectType ot);
	~CBulletObject();
	bool Action() override;
	void Draw() override;
	void Collision(CBaseObject* = nullptr);
private:
	void BulletMovement(void);
	void EnemyBulletMovement(void);
};

