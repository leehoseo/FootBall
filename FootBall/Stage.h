#pragma once
#include <time.h>

// GP : GoalPost
class Stage
{
public:
	Stage();
	~Stage();
protected:
	int m_nGoalBall;
	int m_nGPLength;
	int m_nResetGPX;
	int m_nResetGPY;
	int m_nGPMoveDistance;

	clock_t m_LimitTime;
	clock_t m_MoveTime;
	
protected:
	virtual void Initialize() = 0;

public:
	virtual int GetGoalBall() const = 0;
	virtual int GetGPLength() const = 0;
	virtual int GetResetGPX() const = 0;
	virtual int GetResetGPY() const = 0;
	virtual int GetGPMoveDistance() const =0;
	virtual clock_t GetLimitTime() const =0;
	virtual clock_t GetMoveTime() const =0;
};

