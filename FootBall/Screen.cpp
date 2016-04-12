#include "Screen.h"
#include <windows.h>
#include <stdio.h>
#include "Stage.h"

Screen::Screen()
{
	m_nscreenIndex = 0;
	m_hscreen[0] = 0;
	m_hscreen[1] = 0;
}


Screen::~Screen()
{
	ScreenRelease();
}

// Screen 초기화
void Screen::ScreenInit()
{
	CONSOLE_CURSOR_INFO cci;

	// 가상의 콘솔창 2개룰 만든다.
	m_hscreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	m_hscreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	// 커서 숨기기
	cci.dwSize = 1;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(m_hscreen[0], &cci);
	SetConsoleCursorInfo(m_hscreen[1], &cci);
}


// x , y 좌표에 문자열 출력
void Screen::ScreenPrint(int _x, int _y, char* _string)
{
	DWORD dw;
	COORD CursorPosition = { _x, _y };
	SetConsoleCursorPosition(m_hscreen[m_nscreenIndex], CursorPosition);
	WriteFile(m_hscreen[m_nscreenIndex], _string, strlen(_string), &dw, NULL);
}




// m_hscreen 끼리 바꿔사용(Flipping)
void Screen::ScreenFlipping()
{
	Sleep(10);
	SetConsoleActiveScreenBuffer(m_hscreen[m_nscreenIndex]);
	m_nscreenIndex = !m_nscreenIndex;
}


// Screen을 비워준다
void Screen::ScreenClear()
{
	COORD Coor = { 0, 0 };
	DWORD dw;
	FillConsoleOutputCharacter(m_hscreen[m_nscreenIndex], ' ', 80 * 25, Coor, &dw);
}


// m_hscreen 을 지워준다
void Screen::ScreenRelease()
{
	CloseHandle(m_hscreen[0]);
	CloseHandle(m_hscreen[1]);
}


// 텍스트 색상설정
void Screen::SetColor(unsigned short _color)
{
	SetConsoleTextAttribute(m_hscreen[m_nscreenIndex], _color);
}


// 시작 배경
void Screen::InitScreen()
{
	ScreenPrint(0, 0, "┏━━━━━━━━━━━━━━━━━━━━━┓");
	ScreenPrint(0, 1, "┃                                          ┃");
	ScreenPrint(0, 2, "┃             □━━━□                   ┃");
	ScreenPrint(0, 3, "┃                                          ┃");
	ScreenPrint(0, 4, "┃                        ///.   슛~~~      ┃");
	ScreenPrint(0, 5, "┃                       (^.^)              ┃");
	ScreenPrint(0, 6, "┃                      ┗┫ ┣┓           ┃");
	ScreenPrint(0, 7, "┃                         ┏┛             ┃");
	ScreenPrint(0, 8, "┃                     ⊙  ┛＼             ┃");
	ScreenPrint(0, 9, "┃                                          ┃");
	ScreenPrint(0, 10, "┃                                          ┃");
	ScreenPrint(0, 11, "┃       슛 골인 게임  Go! Go!              ┃");
	ScreenPrint(0, 12, "┃                                          ┃");
	ScreenPrint(0, 13, "┃                                          ┃");
	ScreenPrint(0, 14, "┃       j :왼쪽 l : 오른쪽 k :슛           ┃");
	ScreenPrint(0, 15, "┃                                          ┃");
	ScreenPrint(0, 16, "┃                                          ┃");
	ScreenPrint(0, 17, "┃                                          ┃");
	ScreenPrint(0, 18, "┃        ┗●┛  space 키를 눌러주세요     ┃");
	ScreenPrint(0, 19, "┃                                          ┃");
	ScreenPrint(0, 20, "┃                                          ┃");
	ScreenPrint(0, 21, "┃                                          ┃");
	ScreenPrint(0, 22, "┗━━━━━━━━━━━━━━━━━━━━━┛");
}


// 준비 배경
void Screen::ReadyScreen(int _stage)
{
	char string[100];

	ScreenPrint(0, 0, "┏━━━━━━━━━━━━━━━━━━━━━┓");
	ScreenPrint(0, 1, "┃■■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 2, "┃■■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 3, "┃■■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 4, "┃■■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 5, "┃■■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 6, "┃■■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 7, "┃■■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 8, "┃■■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 9, "┃■■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 10, "┃■■■■■                    ■■■■■■┃");
	sprintf_s(string, "┃■■■■■     %d   스테이지   ■■■■■■┃", _stage + 1);
	ScreenPrint(0, 11, string);
	ScreenPrint(0, 12, "┃■■■■■                    ■■■■■■┃");
	ScreenPrint(0, 13, "┃■■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 14, "┃■■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 15, "┃■■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 16, "┃■■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 17, "┃■■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 18, "┃■■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 19, "┃■■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 20, "┃■■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 21, "┃■■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 22, "┃■■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 23, "┗━━━━━━━━━━━━━━━━━━━━━┛");
}


// 플레이 배경
void Screen::BackScreen(const Stage& _StageInfo , int _stage , int _ballCount , clock_t _time)
{
	char string[100];

	ScreenPrint(0, 0, "┏━━━━━━━━━━━━━━━━━━━━━┓");
	ScreenPrint(0, 1, "┃                                          ┃");
	ScreenPrint(0, 2, "┃                                          ┃");
	ScreenPrint(0, 3, "┃                                          ┃");
	sprintf_s(string, "┃                                          ┃스테이지: %d", _stage + 1);
	ScreenPrint(0, 4, string);
	ScreenPrint(0, 5, "┃                                          ┃");
	sprintf_s(string, "┣━━━━━━━━━━━━━━━━━━━━━┫제한 시간: %d", _StageInfo.GetLimitTime() / 1000);
	ScreenPrint(0, 6, string);
	ScreenPrint(0, 7, "┃                                          ┃");
	sprintf_s(string, "┃                                          ┃현재 시간: %d", (clock() - _time) / 1000);
	ScreenPrint(0, 8, string);
	ScreenPrint(0, 9, "┃                                          ┃");
	sprintf_s(string, "┃                                          ┃목표 골인: %d ", _StageInfo.GetGoalBall());
	ScreenPrint(0, 10, string);
	ScreenPrint(0, 11, "┃                                          ┃");
	sprintf_s(string, "┃                                          ┃골인 공 개수: %d ", _ballCount);
	ScreenPrint(0, 12, string);

	ScreenPrint(0, 13, "┃                                          ┃");
	sprintf_s(string, "┃                                          ┃");
	ScreenPrint(0, 14, string);
	ScreenPrint(0, 15, "┃                                          ┃");
	sprintf_s(string, "┃                                          ┃");
	ScreenPrint(0, 16, string);
	ScreenPrint(0, 17, "┃                                          ┃");
	ScreenPrint(0, 18, "┃                                          ┃");
	ScreenPrint(0, 19, "┃                                          ┃");
	ScreenPrint(0, 20, "┃                                          ┃");
	ScreenPrint(0, 21, "┃                                          ┃");
	ScreenPrint(0, 22, "┃                                          ┃");
	ScreenPrint(0, 23, "┗━━━━━━━━━━━━━━━━━━━━━┛");
}

// 골인 이펙트
void Screen::GoalMessage(int _x, int _y)
{
	ScreenPrint(_x, _y, "☆ )) 골인 (( ★");
	ScreenPrint(_x, _y + 1, "＼(^^')/ ＼(\"*')/");
	ScreenPrint(_x, _y + 2, "   ■       ■");
	ScreenPrint(_x, _y + 3, "  ┘┐    ┌└");
}


// Stage 성공 이펙트
void Screen::SuccessScreen()
{
	ScreenPrint(0, 0, "┏━━━━━━━━━━━━━━━━━━━━━┓");
	ScreenPrint(0, 1, "┃                                          ┃");
	ScreenPrint(0, 2, "┃                                          ┃");
	ScreenPrint(0, 3, "┃                                          ┃");
	ScreenPrint(0, 4, "┃                                          ┃");
	ScreenPrint(0, 5, "┃                                          ┃");
	ScreenPrint(0, 6, "┃                ////＼＼                  ┃");
	ScreenPrint(0, 7, "┃               q ∧  ∧ p                 ┃");
	ScreenPrint(0, 8, "┃               (└──┘)                 ┃");
	ScreenPrint(0, 9, "┃             ♬ 미션 성공 ♪              ┃");
	ScreenPrint(0, 10, "┃                                          ┃");
	ScreenPrint(0, 11, "┃                                          ┃");
	ScreenPrint(0, 12, "┃                                          ┃");
	ScreenPrint(0, 13, "┃                                          ┃");
	ScreenPrint(0, 14, "┃                                          ┃");
	ScreenPrint(0, 15, "┃                                          ┃");
	ScreenPrint(0, 16, "┃                                          ┃");
	ScreenPrint(0, 17, "┃                                          ┃");
	ScreenPrint(0, 18, "┃                                          ┃");
	ScreenPrint(0, 19, "┃                                          ┃");
	ScreenPrint(0, 20, "┃                                          ┃");
	ScreenPrint(0, 21, "┃                                          ┃");
	ScreenPrint(0, 22, "┃                                          ┃");
	ScreenPrint(0, 23, "┗━━━━━━━━━━━━━━━━━━━━━┛");
}


// Stage 실패 이펙트
void Screen::FailureScreen()
{
	ScreenPrint(0, 0, "┏━━━━━━━━━━━━━━━━━━━━━┓");
	ScreenPrint(0, 1, "┃                                          ┃");
	ScreenPrint(0, 2, "┃                                          ┃");
	ScreenPrint(0, 3, "┃                                          ┃");
	ScreenPrint(0, 4, "┃                                          ┃");
	ScreenPrint(0, 5, "┃                                          ┃");
	ScreenPrint(0, 6, "┃                                          ┃");
	ScreenPrint(0, 7, "┃                                          ┃");
	ScreenPrint(0, 8, "┃                                          ┃");
	ScreenPrint(0, 9, "┃                                          ┃");
	ScreenPrint(0, 10, "┃                                          ┃");
	ScreenPrint(0, 11, "┃                    미션 실패 !!!!        ┃");
	ScreenPrint(0, 12, "┃                                          ┃");
	ScreenPrint(0, 13, "┃                                          ┃");
	ScreenPrint(0, 14, "┃                 ●┳━┓                 ┃");
	ScreenPrint(0, 15, "┃                   ┛  ┗                 ┃");
	ScreenPrint(0, 16, "┃                  ■■■■                ┃");
	ScreenPrint(0, 17, "┃                                          ┃");
	ScreenPrint(0, 18, "┃        다시 하시겠습니까? (y/n)          ┃");
	ScreenPrint(0, 19, "┃                                          ┃");
	ScreenPrint(0, 20, "┃                                          ┃");
	ScreenPrint(0, 21, "┃                                          ┃");
	ScreenPrint(0, 22, "┗━━━━━━━━━━━━━━━━━━━━━┛");
}


// 결과 배경
void Screen::ResultScreen(int _stage)
{
	char string[100];
	ScreenPrint(0, 0, "┏━━━━━━━━━━━━━━━━━━━━━┓");
	ScreenPrint(0, 1, "┃                                          ┃");
	ScreenPrint(0, 2, "┃                                          ┃");
	ScreenPrint(0, 3, "┃             □━━━□                   ┃");
	ScreenPrint(0, 4, "┃                                          ┃");
	ScreenPrint(0, 5, "┃                                          ┃");
	ScreenPrint(0, 6, "┃                                          ┃");
	ScreenPrint(0, 7, "┃                                          ┃");
	sprintf_s(string, "┃      성공한 스테이지 :  %2d               ┃", _stage + 1);
	ScreenPrint(0, 8, string);
	ScreenPrint(0, 9, "┃                                          ┃");
	ScreenPrint(0, 10, "┃                                          ┃");
	ScreenPrint(0, 11, "┃   ___▒▒▒___                           ┃");
	ScreenPrint(0, 12, "┃     (*^  ^*)                             ┃");
	ScreenPrint(0, 13, "┃ =====○==○=====                         ┃");
	ScreenPrint(0, 14, "┃                                          ┃");
	ScreenPrint(0, 15, "┃                                          ┃");
	ScreenPrint(0, 16, "┃                                          ┃");
	ScreenPrint(0, 17, "┃                                          ┃");
	ScreenPrint(0, 18, "┃                      ┗●┛              ┃");
	ScreenPrint(0, 19, "┃                                          ┃");
	ScreenPrint(0, 20, "┃                                          ┃");
	ScreenPrint(0, 21, "┃                                          ┃");
	ScreenPrint(0, 22, "┗━━━━━━━━━━━━━━━━━━━━━┛");
}
