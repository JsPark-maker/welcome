#pragma once
class CPlayerObject : public CBaseObject
{
public:
	CPlayerObject(int iX, int iY, ObjectType ot);
	virtual ~CPlayerObject() {};

	//Action�� �ϴ� ��
	//1.�̵����� �޼���ť�� �ֱ�
	//2.�Ѿ˹߻�޼���
	bool Action(void) override;
	void Draw(void) override;
private:
	void MovementExecution(void);
};

