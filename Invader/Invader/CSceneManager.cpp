#include "stdafx.h"
#include "CSceneTitle.h"
#include "CSceneGame.h"
#include "CSceneOver.h"
#include "CSceneManager.h"
#include "CObjectManager.h"

CSceneManager::~CSceneManager()
{
	delete pScene;
}

CSceneManager::CSceneManager() {
	LoadScene(SceneType(TITLE));
}

void CSceneManager::run()
{
	pScene->Action();
}

void CSceneManager::LoadScene(SceneType st)
{
	switch (st) {
	case TITLE:
		if (pScene != nullptr)
			delete pScene;
		pScene = new CSceneTitle();
		break;
	case GAME:
		if(pScene != nullptr)
			delete pScene;
		pScene = new CSceneGame();
		break;
	case END:
		if (pScene != nullptr)
			delete pScene;
		CObjectManager::GetInstance().~CObjectManager();
		pScene = new CSceneOver();
		break;
	}
}

CSceneManager& CSceneManager::GetInstance()
{
	static CSceneManager sm;
	return sm;
}
