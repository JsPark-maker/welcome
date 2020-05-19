#pragma once
class CPlayerObject : public CBaseObject
{
public:
	CPlayerObject(int iX, int iY, ObjectType ot);
	virtual ~CPlayerObject() {};

	//Action이 하는 일
	//1.이동방향 메세지큐에 넣기
	//2.총알발사메세지
	bool Action(void) override;
	void Draw(void) override;
private:
	void MovementExecution(void);
};

