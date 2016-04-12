#include "Game.h"
#include "Stage1.h"
#include "Stage2.h"
#include <conio.h>
#include <string.h>
#include <iostream>


Game::Game()
{
	m_pStage = new Stage1();

	m_pScreen = new Screen();
	m_pScreen->ScreenInit();
	
	m_pGoalPost = new GoalPost();

	m_eGameStage = GAME_STATE::INIT;

	m_LimitTime = 0;
	m_UpdateOldTime = 0;
	m_curTime = 0;
	m_GameStartTime = 0;

	m_nGoalBallCount = 0;
	m_nGoal = 0;
	m_nBallCount = 0;
	m_nCurStage = 0;

	m_IsGoal = false;
}


Game::~Game()
{
	SAFE_DELETE(m_pStage);
	SAFE_DELETE(m_pScreen);
}


// GameEntitiy���� �׸���
void Game::Render()
{
	char string[100] = { 0, };
	int nLength, i;

	m_pScreen->ScreenClear();

	switch (m_eGameStage)
	{
	case INIT:
		//if (g_nStage == 0)
		m_pScreen->InitScreen();
		break;
	case READY:
		m_pScreen->ReadyScreen(m_nCurStage);
		break;
	case RUNNING:
		m_pScreen->BackScreen(*m_pStage , m_nCurStage, m_nBallCount , m_GameStartTime);
		m_pGoalPost->Render();

		// Note: ȿ�� ���  	
		if (m_IsGoal == 1)
		{
			m_pScreen->GoalMessage(10, 10);
		}

		//// Note: 2 �÷��� Ŭ���� 
		//if (g_sPlayer.nX < 2)  //  ���� Ŭ���� ó��  g_nLength : Player
		//	m_Screen.ScreenPrint(2, g_sPlayer.nMoveY, &g_strPlayer[(g_sPlayer.nX - 2)*-1]);	 // ��ǥ�� �迭 �ε��� 
		//else if (g_sPlayer.nMoveX + (g_nLength - g_sPlayer.nCenterX + 1) > 43) // ������ Ŭ���� ó��
		//{
		//	strncat(string, g_strPlayer, g_nLength - ((g_sPlayer.nMoveX + g_sPlayer.nCenterX + 1) - 43));
		//	m_Screen.ScreenPrint(g_sPlayer.nX, g_sPlayer.nMoveY, string);
		//}
		//else { // 1 �÷��� �̵�
		//	m_Screen.ScreenPrint(g_sPlayer.nX, g_sPlayer.nMoveY, g_strPlayer);
		//}

		//m_Screen.ScreenPrint(g_sBall.nMoveX, g_sBall.nMoveY, "��");
		break;
	case SUCCESS:
		m_pScreen->SuccessScreen();
		break;
	case FAILED:
		m_pScreen->FailureScreen();
		break;
	case RESULT:
		m_pScreen->ResultScreen(m_nCurStage);
		break;
	}

	// Note: ������ �� 
	m_pScreen->ScreenFlipping();
}


// GameEntity ���� Update��Ų��
void Game::Update()
{
	m_curTime = clock();
	InputKey();
	int * pGPLineInfo = m_pGoalPost->GetLineX();

	switch (m_eGameStage)
	{
	case READY:
		if (m_curTime - m_UpdateOldTime > 2000)  // 2��
		{
			m_eGameStage = GAME_STATE::RUNNING;
			m_GameStartTime = m_curTime;

			//FMOD_Channel_Stop( g_Channel[3] );  // ready ���� ����
			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[1], 0, &g_Channel[1]); // running �����
		}
		break;
	case RUNNING:
		if (m_curTime - m_GameStartTime > m_LimitTime) // Note: ���� �ð�
		{
			m_eGameStage = GAME_STATE::STOP;
			return;
		}
		else {
			 //Note: ���
			m_pGoalPost->MoveGoalPost(m_curTime);
			m_pGoalPost->Update();
			//if (g_sBall.nIsReady == 0) // �̵� ���� �� 
			//{	// �̵� �ð� ���ݿ� ���� �̵�
			//	if ((m_curTime - g_sBall.OldTime) > g_sBall.MoveTime)
			//	{
			//		if (g_sBall.nMoveY - 1 > 0)
			//		{
			//			g_sBall.nMoveY--;
			//			g_sBall.OldTime = m_curTime; // ���� �̵� �ð��� ���ϱ� ���� ���� �ð��� ���� �ð� ������ ����

			//									   // ��� ���� �浹
			//			if (g_sBall.nMoveX >= g_sGoalDae.nLineX[0] && g_sBall.nMoveX + 1 <= g_sGoalDae.nLineX[nLength - 1] + 1)
			//			{
			//				if (g_sBall.nMoveY <= g_sGoalDae.nMoveY)
			//				{   // �� �ʱ�ȭ
			//					g_sBall.nIsReady = 1;
			//					g_sBall.nMoveX = g_sPlayer.nMoveX;
			//					g_sBall.nMoveY = g_sPlayer.nMoveY - 1;
			//					g_nBallCount++;  // ������ ���� ����										

			//					if (g_nBallCount == g_nGoalBallCount) // ���� ��ǥ ������ ������ ������ SUCCESS
			//					{
			//						m_eGameStage = GAME_STATE::STOP;
			//						g_nGoal = 1;
			//						return;
			//					}

			//					// ȿ�� ���
			//					if (g_nIsGoal == 0)
			//					{
			//						g_nIsGoal = 1;
			//						g_sEffect.StratTime = m_curTime;
			//					}

			//					// ���� ���� ���
			//					//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[6], 0, &g_Channel[6]); // ���� ���� �Ϳ�~
			//				}
			//				// ��� �浹 
			//			}
			//			else if ((g_sBall.nMoveX >= g_sGoalDae.nLineX[0] - 2 && g_sBall.nMoveX <= g_sGoalDae.nLineX[0] - 1) ||
			//				(g_sBall.nMoveX + 1 >= g_sGoalDae.nLineX[0] - 2 && g_sBall.nMoveX + 1 <= g_sGoalDae.nLineX[0] - 1) ||
			//				(g_sBall.nMoveX >= g_sGoalDae.nLineX[nLength - 1] + 2 && g_sBall.nMoveX <= g_sGoalDae.nLineX[nLength - 1] + 3) ||
			//				(g_sBall.nMoveX + 1 >= g_sGoalDae.nLineX[nLength - 1] + 2 && g_sBall.nMoveX + 1 <= g_sGoalDae.nLineX[nLength - 1] + 3))
			//			{
			//				if (g_sBall.nMoveY <= g_sGoalDae.nMoveY)
			//				{   // �� �ʱ�ȭ
			//					g_sBall.nIsReady = 1;
			//					g_sBall.nMoveX = g_sPlayer.nMoveX;
			//					g_sBall.nMoveY = g_sPlayer.nMoveY - 1;
			//				}
			//			}
			//		}
			//		else { // �� �ʱ�ȭ
			//			g_sBall.nIsReady = 1;
			//			g_sBall.nMoveX = g_sPlayer.nMoveX;
			//			g_sBall.nMoveY = g_sPlayer.nMoveY - 1;
			//		}
			//	}
			//}
			//else {
			//	g_sBall.nMoveX = g_sPlayer.nMoveX;
			//}

			// ȿ�� 
			if (true == m_IsGoal )
			{
				/*if (m_curTime - g_sEffect.StratTime > g_sEffect.StayTime)
					m_IsGoal = false;*/
			}
		}
		break;
	case STOP:
		if ( true == m_IsGoal )
		{
			m_eGameStage = GAME_STATE::SUCCESS;
			m_UpdateOldTime = m_curTime;
			//FMOD_Channel_Stop( g_Channel[1] );  // running ���� ����
			//FMOD_Channel_Stop( g_Channel[1] );  // running ���� ����

			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[4], 0, &g_Channel[4]); // �̼� ���� ����
		}
		else {
			m_eGameStage = GAME_STATE::FAILED;
			//FMOD_Channel_Stop( g_Channel[1] );  // running ���� ����
			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[2], 0, &g_Channel[2]); // �̼� ���� ����
		}
		break;
	case SUCCESS:
		if (m_curTime - m_UpdateOldTime > 3000)
		{
			m_UpdateOldTime = m_curTime;
			/*++g_nStage;
			Init();*/			// Stage ���� �κ�
			m_eGameStage = GAME_STATE::READY;
			//FMOD_Channel_Stop( g_Channel[4] );  // �̼� ���� ���� ��� ����					
			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[3], 0, &g_Channel[3]); //READY ���� 
		}
		break;
	}

}
void Game::InputKey()
{
	int nKey, nRemain;

	if (_kbhit())
	{
		if (m_eGameStage == GAME_STATE::RESULT)
			return;;

		nKey = _getch();

		switch (nKey)
		{
		case 'j':
			//if (g_sPlayer.nMoveX > 2) // ���� �浹 ��� ��ǥ üũ
			//{
			//	g_sPlayer.nMoveX--;
			//	nRemain = g_nLength - g_sPlayer.nCenterX + 1; // ��ü ���� - ( �߽� ��ǥ + 1 )�� ���� ����
			//												  // Note: 2�÷��� �̵��ϱ� ���� �κ� ( ���� ��ģ ��� ) 
			//	if (g_sPlayer.nMoveX - g_sPlayer.nCenterX < 2 || g_sPlayer.nMoveX + nRemain > 43)
			//		g_sPlayer.nMoveX--;

			//	g_sPlayer.nX = g_sPlayer.nMoveX - g_sPlayer.nCenterX;
			//}
			break;
		case 'l':
			//if (g_sPlayer.nMoveX + 1 < 43) // ������ �浹 ��� ��ǥ üũ
			//{
			//	g_sPlayer.nMoveX++;
			//	nRemain = g_nLength - g_sPlayer.nCenterX + 1; // ��ü ���� - ( �߽� ��ǥ + 1 )�� ���� ����
			//												  // Note: 2�÷��� �̵��ϱ� ���� �κ� ( ���� ��ģ ��� )
			//	if (g_sPlayer.nMoveX + nRemain > 43 || (g_sPlayer.nMoveX - g_sPlayer.nCenterX < 2))
			//		g_sPlayer.nMoveX++;

			//	g_sPlayer.nX = g_sPlayer.nMoveX - g_sPlayer.nCenterX;
			//}
			break;
		case 'k':
			//if (g_sBall.nIsReady && m_eGameStage == GAME_STATE::RUNNING)
			//{
			//	g_sBall.nMoveX = g_sPlayer.nMoveX;
			//	g_sBall.nMoveY = g_sPlayer.nMoveY - 1;
			//	g_sBall.OldTime = clock();
			//	g_sBall.nIsReady = 0;
			//	//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[5], 0, &g_Channel[5]); // �� ���� �Ҹ� ���
			//}
			break;

		case 'y':
		case 'Y':
			if (m_eGameStage == GAME_STATE::FAILED)
			{
				Initialize();
				m_eGameStage = GAME_STATE::READY;
			//	//FMOD_Channel_Stop( g_Channel[2] );  // �̼� ���� ���� ��� ���� 
			//	//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[3], 0, &g_Channel[3]);
			}
			break;
		case 'n':
		case 'N':
			if (m_eGameStage == GAME_STATE::FAILED)
			{
				m_eGameStage = GAME_STATE::RESULT;
				//FMOD_Channel_Stop( g_Channel[2] );  // �̼� ���� ���� ��� ����							
			}
			break;

		case ' ':
			if (m_eGameStage == GAME_STATE::INIT && m_nCurStage == 0)
			{
				m_eGameStage = GAME_STATE::READY;
				//FMOD_Channel_Stop( g_Channel[0] ); // ����� ����
				//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[3], 0, &g_Channel[3]); // ready ����
				m_UpdateOldTime = clock();  // ready�� �����ð� ������ �ֱ� ���� 							
			}
			break;
		}
	}
}
// Game ó���� Stage �ٲ� �� ���� , Player , Ball , GoalPost �ʱ�ȭ�� �ֱ�
void Game::Initialize()
{
	m_nGoalBallCount = m_pStage->GetGoalBall();
	m_LimitTime = m_pStage->GetLimitTime();
	//g_sEffect.StayTime = 2000;
	m_nGoal = 0;
	m_nBallCount = 0;
	m_UpdateOldTime = clock();
	m_IsGoal = false;

	m_pGoalPost->Initialize(*m_pStage, *m_pScreen);
}
