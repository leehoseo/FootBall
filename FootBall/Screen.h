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
	// x , y ��ǥ�� ���ڿ� ���
	void ScreenPrint(int _x, int _y, char* _string);
	// Screen �ʱ�ȭ
	void ScreenInit();
	// m_hscreen ���� �ٲ���(Flipping)
	void ScreenFlipping();
	// Screen�� ����ش�
	void ScreenClear();
	// m_hscreen �� �����ش�
	void ScreenRelease();
	// �ؽ�Ʈ ������
	void SetColor(unsigned short _color);
	// ���� ���
	void InitScreen();
	// �غ� ���
	void ReadyScreen(int _stage);
	// �÷��� ���
	void BackScreen(const Stage& _StageInfo, int _stage, int _ballCount, clock_t _time);


	// ���� ����Ʈ
	void Screen::GoalMessage(int _x, int _y);
	// Stage ���� ����Ʈ
	void Screen::SuccessScreen();
	// Stage ���� ����Ʈ
	void Screen::FailureScreen();
	// ��� ���
	void Screen::ResultScreen(int _stage);

};

