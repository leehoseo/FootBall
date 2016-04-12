#pragma once
#include "Stage.h"
class Stage2 : public Stage
{

private:
	virtual void Initialize();

public:
	Stage2();
	~Stage2();

	virtual int GetGoalBall() const { return m_nGoalBall; }
	virtual int GetGPLength() const { return m_nGPLength; }
	virtual int GetResetGPX() const { return m_nResetGPX; }
	virtual int GetResetGPY() const { return m_nResetGPY; }
	virtual int GetGPMoveDistance() const { return m_nGPMoveDistance; }

	virtual clock_t GetLimitTime() const { return  m_LimitTime; }
	virtual clock_t GetMoveTime() const { return m_MoveTime; }
};

