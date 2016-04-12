#include "Stage2.h"



Stage2::Stage2()
{
	Initialize();
}


Stage2::~Stage2()
{
}

void Stage2::Initialize()
{
	m_nGoalBall = 10;
	m_nGPLength = 2;
	m_nResetGPX = 20;
	m_nResetGPY = 5;
	m_nGPMoveDistance = 1;

	m_LimitTime = 1000 * 30;
	m_MoveTime = 300;
}
