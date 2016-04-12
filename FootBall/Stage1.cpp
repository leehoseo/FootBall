#include "Stage1.h"



Stage1::Stage1()
{
	Initialize();
}


Stage1::~Stage1()
{
}

void Stage1::Initialize()
{
	m_nGoalBall = 3;
	m_nGPLength = 1;
	m_nResetGPX = 20;
	m_nResetGPY = 3;
	m_nGPMoveDistance = 1;

	m_LimitTime = 1000 * 20;
	m_MoveTime = 300;
}
