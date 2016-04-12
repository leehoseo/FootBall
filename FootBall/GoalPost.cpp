#include "GoalPost.h"
#include "Stage.h"


GoalPost::GoalPost()
{
}


GoalPost::~GoalPost()
{
}

void GoalPost::Initialize(const Stage & _stageInfo, Screen& _screen)
{
	m_pScreen = &_screen;
	m_nX = _stageInfo.GetResetGPX();
	m_nY = _stageInfo.GetResetGPY();
	m_nLength = _stageInfo.GetGPLength();
	m_nDistance = _stageInfo.GetGPMoveDistance();
	m_MoveTime = _stageInfo.GetMoveTime();
	m_OldTime = clock();
	m_nMaxLength = m_nLength * 2 + 1;
	for (int index = 0; index < m_nMaxLength; index++)
	{
		m_nArrLineX[index] = m_nX + 2 * (index + 1);
	}
}

void GoalPost::Update()
{
	for (int index = 0; index < m_nMaxLength; index++)
	{
		m_nArrLineX[index] = m_nX + 2 * (index + 1);
	}
}

void GoalPost::Render()
{
	m_pScreen->ScreenPrint(m_nX, m_nY, "□");

	for (int index = 0; index < m_nMaxLength; index++)
		m_pScreen->ScreenPrint(m_nArrLineX[index], m_nY, "━");

	m_pScreen->ScreenPrint(m_nArrLineX[m_nMaxLength - 1 ] + 2, m_nY, "□");
}

void GoalPost::MoveGoalPost(clock_t _time)
{
	if (_time - m_OldTime > m_MoveTime)
	{
		m_OldTime = _time;
		if (m_nX + m_nDistance >= 2 && ((m_nArrLineX[m_nMaxLength - 1] + 3) + m_nDistance) <= 43)
		{
			m_nX += m_nDistance;
		}
		else {
			m_nDistance = m_nDistance * -1; // -1 이 방향을 바꾸어 줌.
		}
	}
}
