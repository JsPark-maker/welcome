#include "stdafx.h"
#include "CSceneBase.h"
#include "CSceneGame.h"
#include "CBaseObject.h"
#include "CList.h" 
#include "CObjectManager.h"
#include "Console.h"
CSceneGame::CSceneGame() {
	CObjectManager::GetInstance().InitChar();
}

CSceneGame::~CSceneGame()
{
}

void CSceneGame::Action(void)
{
	CScreenBuffer::GetInstance().Buffer_Clear();

	CObjectManager::GetInstance().Action();

	Draw();

	CScreenBuffer::GetInstance().Buffer_Flip();

}

void CSceneGame::Draw()
{
	for(CList<CBaseObject*>::Iterator itor = CObjectManager::GetInstance().ObjectList.Begin();
	itor != CObjectManager::GetInstance().ObjectList.end(); ++itor){
		(*itor)->Draw();
	}
}

