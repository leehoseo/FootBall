#pragma once
#include "Resource.h"
#include "Stage.h"
#include "Screen.h"
#include "GoalPost.h"
#include <time.h>

class Game
{
private:
	Stage * m_pStage;
	Screen * m_pScreen;
	GoalPost * m_pGoalPost;

	GAME_STATE m_eGameStage;
	clock_t m_LimitTime;
	clock_t m_UpdateOldTime;
	clock_t m_curTime;
	clock_t m_GameStartTime;
	int m_nGoalBallCount;
	int m_nGoal;
	int m_nBallCount;
	int m_nCurStage;
	bool m_IsGoal;
	
public:
	Game();
	~Game();
	// GameEntitiy들을 그린다
	void Render();
	// GameEntity 들을 Update시킨다
	void Update();
	void InputKey();
	void Initialize();
};

