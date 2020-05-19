#pragma once

class CSceneBase;

enum SceneType { TITLE, GAME, END };
class CSceneManager
{
public:
	void run();
	//매개변수로 전환 신
	void LoadScene(SceneType st);
	static CSceneManager& GetInstance();
	~CSceneManager();
private:
	//초기 생성시 씬을 타이틀로 만들어둠
	CSceneManager();
	CSceneBase* pScene;
};

