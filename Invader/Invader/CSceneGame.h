#pragma once

#include "CSceneBase.h"

class CSceneGame : public CSceneBase
{
public:
	CSceneGame();
	~CSceneGame();
	void Action(void) override;
	void Draw();
};

