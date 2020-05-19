#pragma once

class CSceneBase;

enum SceneType { TITLE, GAME, END };
class CSceneManager
{
public:
	void run();
	//�Ű������� ��ȯ ��
	void LoadScene(SceneType st);
	static CSceneManager& GetInstance();
	~CSceneManager();
private:
	//�ʱ� ������ ���� Ÿ��Ʋ�� ������
	CSceneManager();
	CSceneBase* pScene;
};

