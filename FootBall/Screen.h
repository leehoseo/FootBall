#pragma once
#include <time.h>
class Stage;

class Screen
{
public:
	Screen();
	~Screen();

private:
	void* m_hscreen[2];
	int m_nscreenIndex;

public:
	// x , y 좌표에 문자열 출력
	void ScreenPrint(int _x, int _y, char* _string);
	// Screen 초기화
	void ScreenInit();
	// m_hscreen 끼리 바꿔사용(Flipping)
	void ScreenFlipping();
	// Screen을 비워준다
	void ScreenClear();
	// m_hscreen 을 지워준다
	void ScreenRelease();
	// 텍스트 색상설정
	void SetColor(unsigned short _color);
	// 시작 배경
	void InitScreen();
	// 준비 배경
	void ReadyScreen(int _stage);
	// 플레이 배경
	void BackScreen(const Stage& _StageInfo, int _stage, int _ballCount, clock_t _time);


	// 골인 이펙트
	void Screen::GoalMessage(int _x, int _y);
	// Stage 성공 이펙트
	void Screen::SuccessScreen();
	// Stage 실패 이펙트
	void Screen::FailureScreen();
	// 결과 배경
	void Screen::ResultScreen(int _stage);

};

