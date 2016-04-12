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

// Screen �ʱ�ȭ
void Screen::ScreenInit()
{
	CONSOLE_CURSOR_INFO cci;

	// ������ �ܼ�â 2���� �����.
	m_hscreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	m_hscreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	// Ŀ�� �����
	cci.dwSize = 1;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(m_hscreen[0], &cci);
	SetConsoleCursorInfo(m_hscreen[1], &cci);
}


// x , y ��ǥ�� ���ڿ� ���
void Screen::ScreenPrint(int _x, int _y, char* _string)
{
	DWORD dw;
	COORD CursorPosition = { _x, _y };
	SetConsoleCursorPosition(m_hscreen[m_nscreenIndex], CursorPosition);
	WriteFile(m_hscreen[m_nscreenIndex], _string, strlen(_string), &dw, NULL);
}




// m_hscreen ���� �ٲ���(Flipping)
void Screen::ScreenFlipping()
{
	Sleep(10);
	SetConsoleActiveScreenBuffer(m_hscreen[m_nscreenIndex]);
	m_nscreenIndex = !m_nscreenIndex;
}


// Screen�� ����ش�
void Screen::ScreenClear()
{
	COORD Coor = { 0, 0 };
	DWORD dw;
	FillConsoleOutputCharacter(m_hscreen[m_nscreenIndex], ' ', 80 * 25, Coor, &dw);
}


// m_hscreen �� �����ش�
void Screen::ScreenRelease()
{
	CloseHandle(m_hscreen[0]);
	CloseHandle(m_hscreen[1]);
}


// �ؽ�Ʈ ������
void Screen::SetColor(unsigned short _color)
{
	SetConsoleTextAttribute(m_hscreen[m_nscreenIndex], _color);
}


// ���� ���
void Screen::InitScreen()
{
	ScreenPrint(0, 0, "����������������������������������������������");
	ScreenPrint(0, 1, "��                                          ��");
	ScreenPrint(0, 2, "��             �ব������                   ��");
	ScreenPrint(0, 3, "��                                          ��");
	ScreenPrint(0, 4, "��                        ///.   ��~~~      ��");
	ScreenPrint(0, 5, "��                       (^.^)              ��");
	ScreenPrint(0, 6, "��                      ���� ����           ��");
	ScreenPrint(0, 7, "��                         ����             ��");
	ScreenPrint(0, 8, "��                     ��  ����             ��");
	ScreenPrint(0, 9, "��                                          ��");
	ScreenPrint(0, 10, "��                                          ��");
	ScreenPrint(0, 11, "��       �� ���� ����  Go! Go!              ��");
	ScreenPrint(0, 12, "��                                          ��");
	ScreenPrint(0, 13, "��                                          ��");
	ScreenPrint(0, 14, "��       j :���� l : ������ k :��           ��");
	ScreenPrint(0, 15, "��                                          ��");
	ScreenPrint(0, 16, "��                                          ��");
	ScreenPrint(0, 17, "��                                          ��");
	ScreenPrint(0, 18, "��        ���ܦ�  space Ű�� �����ּ���     ��");
	ScreenPrint(0, 19, "��                                          ��");
	ScreenPrint(0, 20, "��                                          ��");
	ScreenPrint(0, 21, "��                                          ��");
	ScreenPrint(0, 22, "����������������������������������������������");
}


// �غ� ���
void Screen::ReadyScreen(int _stage)
{
	char string[100];

	ScreenPrint(0, 0, "����������������������������������������������");
	ScreenPrint(0, 1, "�����������������������᦭");
	ScreenPrint(0, 2, "�����������������������᦭");
	ScreenPrint(0, 3, "�����������������������᦭");
	ScreenPrint(0, 4, "�����������������������᦭");
	ScreenPrint(0, 5, "�����������������������᦭");
	ScreenPrint(0, 6, "�����������������������᦭");
	ScreenPrint(0, 7, "�����������������������᦭");
	ScreenPrint(0, 8, "�����������������������᦭");
	ScreenPrint(0, 9, "�����������������������᦭");
	ScreenPrint(0, 10, "��������                    ������᦭");
	sprintf_s(string, "��������     %d   ��������   ������᦭", _stage + 1);
	ScreenPrint(0, 11, string);
	ScreenPrint(0, 12, "��������                    ������᦭");
	ScreenPrint(0, 13, "�����������������������᦭");
	ScreenPrint(0, 14, "�����������������������᦭");
	ScreenPrint(0, 15, "�����������������������᦭");
	ScreenPrint(0, 16, "�����������������������᦭");
	ScreenPrint(0, 17, "�����������������������᦭");
	ScreenPrint(0, 18, "�����������������������᦭");
	ScreenPrint(0, 19, "�����������������������᦭");
	ScreenPrint(0, 20, "�����������������������᦭");
	ScreenPrint(0, 21, "�����������������������᦭");
	ScreenPrint(0, 22, "�����������������������᦭");
	ScreenPrint(0, 23, "����������������������������������������������");
}


// �÷��� ���
void Screen::BackScreen(const Stage& _StageInfo , int _stage , int _ballCount , clock_t _time)
{
	char string[100];

	ScreenPrint(0, 0, "����������������������������������������������");
	ScreenPrint(0, 1, "��                                          ��");
	ScreenPrint(0, 2, "��                                          ��");
	ScreenPrint(0, 3, "��                                          ��");
	sprintf_s(string, "��                                          ����������: %d", _stage + 1);
	ScreenPrint(0, 4, string);
	ScreenPrint(0, 5, "��                                          ��");
	sprintf_s(string, "�������������������������������������������������� �ð�: %d", _StageInfo.GetLimitTime() / 1000);
	ScreenPrint(0, 6, string);
	ScreenPrint(0, 7, "��                                          ��");
	sprintf_s(string, "��                                          ������ �ð�: %d", (clock() - _time) / 1000);
	ScreenPrint(0, 8, string);
	ScreenPrint(0, 9, "��                                          ��");
	sprintf_s(string, "��                                          ����ǥ ����: %d ", _StageInfo.GetGoalBall());
	ScreenPrint(0, 10, string);
	ScreenPrint(0, 11, "��                                          ��");
	sprintf_s(string, "��                                          ������ �� ����: %d ", _ballCount);
	ScreenPrint(0, 12, string);

	ScreenPrint(0, 13, "��                                          ��");
	sprintf_s(string, "��                                          ��");
	ScreenPrint(0, 14, string);
	ScreenPrint(0, 15, "��                                          ��");
	sprintf_s(string, "��                                          ��");
	ScreenPrint(0, 16, string);
	ScreenPrint(0, 17, "��                                          ��");
	ScreenPrint(0, 18, "��                                          ��");
	ScreenPrint(0, 19, "��                                          ��");
	ScreenPrint(0, 20, "��                                          ��");
	ScreenPrint(0, 21, "��                                          ��");
	ScreenPrint(0, 22, "��                                          ��");
	ScreenPrint(0, 23, "����������������������������������������������");
}

// ���� ����Ʈ
void Screen::GoalMessage(int _x, int _y)
{
	ScreenPrint(_x, _y, "�� )) ���� (( ��");
	ScreenPrint(_x, _y + 1, "��(^^')/ ��(\"*')/");
	ScreenPrint(_x, _y + 2, "   ��       ��");
	ScreenPrint(_x, _y + 3, "  ����    ����");
}


// Stage ���� ����Ʈ
void Screen::SuccessScreen()
{
	ScreenPrint(0, 0, "����������������������������������������������");
	ScreenPrint(0, 1, "��                                          ��");
	ScreenPrint(0, 2, "��                                          ��");
	ScreenPrint(0, 3, "��                                          ��");
	ScreenPrint(0, 4, "��                                          ��");
	ScreenPrint(0, 5, "��                                          ��");
	ScreenPrint(0, 6, "��                ////����                  ��");
	ScreenPrint(0, 7, "��               q ��  �� p                 ��");
	ScreenPrint(0, 8, "��               (��������)                 ��");
	ScreenPrint(0, 9, "��             �� �̼� ���� ��              ��");
	ScreenPrint(0, 10, "��                                          ��");
	ScreenPrint(0, 11, "��                                          ��");
	ScreenPrint(0, 12, "��                                          ��");
	ScreenPrint(0, 13, "��                                          ��");
	ScreenPrint(0, 14, "��                                          ��");
	ScreenPrint(0, 15, "��                                          ��");
	ScreenPrint(0, 16, "��                                          ��");
	ScreenPrint(0, 17, "��                                          ��");
	ScreenPrint(0, 18, "��                                          ��");
	ScreenPrint(0, 19, "��                                          ��");
	ScreenPrint(0, 20, "��                                          ��");
	ScreenPrint(0, 21, "��                                          ��");
	ScreenPrint(0, 22, "��                                          ��");
	ScreenPrint(0, 23, "����������������������������������������������");
}


// Stage ���� ����Ʈ
void Screen::FailureScreen()
{
	ScreenPrint(0, 0, "����������������������������������������������");
	ScreenPrint(0, 1, "��                                          ��");
	ScreenPrint(0, 2, "��                                          ��");
	ScreenPrint(0, 3, "��                                          ��");
	ScreenPrint(0, 4, "��                                          ��");
	ScreenPrint(0, 5, "��                                          ��");
	ScreenPrint(0, 6, "��                                          ��");
	ScreenPrint(0, 7, "��                                          ��");
	ScreenPrint(0, 8, "��                                          ��");
	ScreenPrint(0, 9, "��                                          ��");
	ScreenPrint(0, 10, "��                                          ��");
	ScreenPrint(0, 11, "��                    �̼� ���� !!!!        ��");
	ScreenPrint(0, 12, "��                                          ��");
	ScreenPrint(0, 13, "��                                          ��");
	ScreenPrint(0, 14, "��                 �ܦ�����                 ��");
	ScreenPrint(0, 15, "��                   ��  ��                 ��");
	ScreenPrint(0, 16, "��                  �����                ��");
	ScreenPrint(0, 17, "��                                          ��");
	ScreenPrint(0, 18, "��        �ٽ� �Ͻðڽ��ϱ�? (y/n)          ��");
	ScreenPrint(0, 19, "��                                          ��");
	ScreenPrint(0, 20, "��                                          ��");
	ScreenPrint(0, 21, "��                                          ��");
	ScreenPrint(0, 22, "����������������������������������������������");
}


// ��� ���
void Screen::ResultScreen(int _stage)
{
	char string[100];
	ScreenPrint(0, 0, "����������������������������������������������");
	ScreenPrint(0, 1, "��                                          ��");
	ScreenPrint(0, 2, "��                                          ��");
	ScreenPrint(0, 3, "��             �ব������                   ��");
	ScreenPrint(0, 4, "��                                          ��");
	ScreenPrint(0, 5, "��                                          ��");
	ScreenPrint(0, 6, "��                                          ��");
	ScreenPrint(0, 7, "��                                          ��");
	sprintf_s(string, "��      ������ �������� :  %2d               ��", _stage + 1);
	ScreenPrint(0, 8, string);
	ScreenPrint(0, 9, "��                                          ��");
	ScreenPrint(0, 10, "��                                          ��");
	ScreenPrint(0, 11, "��   ___�ƢƢ�___                           ��");
	ScreenPrint(0, 12, "��     (*^  ^*)                             ��");
	ScreenPrint(0, 13, "�� =====��==��=====                         ��");
	ScreenPrint(0, 14, "��                                          ��");
	ScreenPrint(0, 15, "��                                          ��");
	ScreenPrint(0, 16, "��                                          ��");
	ScreenPrint(0, 17, "��                                          ��");
	ScreenPrint(0, 18, "��                      ���ܦ�              ��");
	ScreenPrint(0, 19, "��                                          ��");
	ScreenPrint(0, 20, "��                                          ��");
	ScreenPrint(0, 21, "��                                          ��");
	ScreenPrint(0, 22, "����������������������������������������������");
}
