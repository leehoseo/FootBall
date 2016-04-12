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


// GameEntitiy들을 그린다
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

		// Note: 효과 출력  	
		if (m_IsGoal == 1)
		{
			m_pScreen->GoalMessage(10, 10);
		}

		//// Note: 2 컬럼씩 클리핑 
		//if (g_sPlayer.nX < 2)  //  왼쪽 클리핑 처리  g_nLength : Player
		//	m_Screen.ScreenPrint(2, g_sPlayer.nMoveY, &g_strPlayer[(g_sPlayer.nX - 2)*-1]);	 // 좌표를 배열 인덱스 
		//else if (g_sPlayer.nMoveX + (g_nLength - g_sPlayer.nCenterX + 1) > 43) // 오른쪽 클리핑 처리
		//{
		//	strncat(string, g_strPlayer, g_nLength - ((g_sPlayer.nMoveX + g_sPlayer.nCenterX + 1) - 43));
		//	m_Screen.ScreenPrint(g_sPlayer.nX, g_sPlayer.nMoveY, string);
		//}
		//else { // 1 컬럼씩 이동
		//	m_Screen.ScreenPrint(g_sPlayer.nX, g_sPlayer.nMoveY, g_strPlayer);
		//}

		//m_Screen.ScreenPrint(g_sBall.nMoveX, g_sBall.nMoveY, "⊙");
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

	// Note: 렌더링 끝 
	m_pScreen->ScreenFlipping();
}


// GameEntity 들을 Update시킨다
void Game::Update()
{
	m_curTime = clock();
	InputKey();
	int * pGPLineInfo = m_pGoalPost->GetLineX();

	switch (m_eGameStage)
	{
	case READY:
		if (m_curTime - m_UpdateOldTime > 2000)  // 2초
		{
			m_eGameStage = GAME_STATE::RUNNING;
			m_GameStartTime = m_curTime;

			//FMOD_Channel_Stop( g_Channel[3] );  // ready 사운드 중지
			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[1], 0, &g_Channel[1]); // running 배경음
		}
		break;
	case RUNNING:
		if (m_curTime - m_GameStartTime > m_LimitTime) // Note: 제한 시간
		{
			m_eGameStage = GAME_STATE::STOP;
			return;
		}
		else {
			 //Note: 골대
			m_pGoalPost->MoveGoalPost(m_curTime);
			m_pGoalPost->Update();
			//if (g_sBall.nIsReady == 0) // 이동 중일 때 
			//{	// 이동 시간 간격에 의한 이동
			//	if ((m_curTime - g_sBall.OldTime) > g_sBall.MoveTime)
			//	{
			//		if (g_sBall.nMoveY - 1 > 0)
			//		{
			//			g_sBall.nMoveY--;
			//			g_sBall.OldTime = m_curTime; // 다음 이동 시각과 비교하기 위해 현재 시간을 이전 시간 변수에 저장

			//									   // 골대 라인 충돌
			//			if (g_sBall.nMoveX >= g_sGoalDae.nLineX[0] && g_sBall.nMoveX + 1 <= g_sGoalDae.nLineX[nLength - 1] + 1)
			//			{
			//				if (g_sBall.nMoveY <= g_sGoalDae.nMoveY)
			//				{   // 공 초기화
			//					g_sBall.nIsReady = 1;
			//					g_sBall.nMoveX = g_sPlayer.nMoveX;
			//					g_sBall.nMoveY = g_sPlayer.nMoveY - 1;
			//					g_nBallCount++;  // 골인한 공의 개수										

			//					if (g_nBallCount == g_nGoalBallCount) // 공과 목표 공과의 개수가 같으면 SUCCESS
			//					{
			//						m_eGameStage = GAME_STATE::STOP;
			//						g_nGoal = 1;
			//						return;
			//					}

			//					// 효과 출력
			//					if (g_nIsGoal == 0)
			//					{
			//						g_nIsGoal = 1;
			//						g_sEffect.StratTime = m_curTime;
			//					}

			//					// 골인 사운드 출력
			//					//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[6], 0, &g_Channel[6]); // 골인 사운드 와우~
			//				}
			//				// 골대 충돌 
			//			}
			//			else if ((g_sBall.nMoveX >= g_sGoalDae.nLineX[0] - 2 && g_sBall.nMoveX <= g_sGoalDae.nLineX[0] - 1) ||
			//				(g_sBall.nMoveX + 1 >= g_sGoalDae.nLineX[0] - 2 && g_sBall.nMoveX + 1 <= g_sGoalDae.nLineX[0] - 1) ||
			//				(g_sBall.nMoveX >= g_sGoalDae.nLineX[nLength - 1] + 2 && g_sBall.nMoveX <= g_sGoalDae.nLineX[nLength - 1] + 3) ||
			//				(g_sBall.nMoveX + 1 >= g_sGoalDae.nLineX[nLength - 1] + 2 && g_sBall.nMoveX + 1 <= g_sGoalDae.nLineX[nLength - 1] + 3))
			//			{
			//				if (g_sBall.nMoveY <= g_sGoalDae.nMoveY)
			//				{   // 공 초기화
			//					g_sBall.nIsReady = 1;
			//					g_sBall.nMoveX = g_sPlayer.nMoveX;
			//					g_sBall.nMoveY = g_sPlayer.nMoveY - 1;
			//				}
			//			}
			//		}
			//		else { // 공 초기화
			//			g_sBall.nIsReady = 1;
			//			g_sBall.nMoveX = g_sPlayer.nMoveX;
			//			g_sBall.nMoveY = g_sPlayer.nMoveY - 1;
			//		}
			//	}
			//}
			//else {
			//	g_sBall.nMoveX = g_sPlayer.nMoveX;
			//}

			// 효과 
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
			//FMOD_Channel_Stop( g_Channel[1] );  // running 사운드 중지
			//FMOD_Channel_Stop( g_Channel[1] );  // running 사운드 중지

			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[4], 0, &g_Channel[4]); // 미션 성공 사운드
		}
		else {
			m_eGameStage = GAME_STATE::FAILED;
			//FMOD_Channel_Stop( g_Channel[1] );  // running 사운드 중지
			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[2], 0, &g_Channel[2]); // 미션 실패 사운드
		}
		break;
	case SUCCESS:
		if (m_curTime - m_UpdateOldTime > 3000)
		{
			m_UpdateOldTime = m_curTime;
			/*++g_nStage;
			Init();*/			// Stage 변경 부분
			m_eGameStage = GAME_STATE::READY;
			//FMOD_Channel_Stop( g_Channel[4] );  // 미션 성공 사운드 출력 중지					
			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[3], 0, &g_Channel[3]); //READY 사운드 
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
			//if (g_sPlayer.nMoveX > 2) // 왼쪽 충돌 경계 좌표 체크
			//{
			//	g_sPlayer.nMoveX--;
			//	nRemain = g_nLength - g_sPlayer.nCenterX + 1; // 전체 길이 - ( 중심 좌표 + 1 )은 남은 길이
			//												  // Note: 2컬럼씩 이동하기 위한 부분 ( 팔이 걸친 경우 ) 
			//	if (g_sPlayer.nMoveX - g_sPlayer.nCenterX < 2 || g_sPlayer.nMoveX + nRemain > 43)
			//		g_sPlayer.nMoveX--;

			//	g_sPlayer.nX = g_sPlayer.nMoveX - g_sPlayer.nCenterX;
			//}
			break;
		case 'l':
			//if (g_sPlayer.nMoveX + 1 < 43) // 오른쪽 충돌 경계 좌표 체크
			//{
			//	g_sPlayer.nMoveX++;
			//	nRemain = g_nLength - g_sPlayer.nCenterX + 1; // 전체 길이 - ( 중심 좌표 + 1 )은 남은 길이
			//												  // Note: 2컬럼씩 이동하기 위한 부분 ( 팔이 걸친 경우 )
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
			//	//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[5], 0, &g_Channel[5]); // 슛 동작 소리 출력
			//}
			break;

		case 'y':
		case 'Y':
			if (m_eGameStage == GAME_STATE::FAILED)
			{
				Initialize();
				m_eGameStage = GAME_STATE::READY;
			//	//FMOD_Channel_Stop( g_Channel[2] );  // 미션 실패 사운드 출력 중지 
			//	//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[3], 0, &g_Channel[3]);
			}
			break;
		case 'n':
		case 'N':
			if (m_eGameStage == GAME_STATE::FAILED)
			{
				m_eGameStage = GAME_STATE::RESULT;
				//FMOD_Channel_Stop( g_Channel[2] );  // 미션 실패 사운드 출력 중지							
			}
			break;

		case ' ':
			if (m_eGameStage == GAME_STATE::INIT && m_nCurStage == 0)
			{
				m_eGameStage = GAME_STATE::READY;
				//FMOD_Channel_Stop( g_Channel[0] ); // 배경음 중지
				//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[3], 0, &g_Channel[3]); // ready 사운드
				m_UpdateOldTime = clock();  // ready를 일정시간 지속해 주기 위해 							
			}
			break;
		}
	}
}
// Game 처음과 Stage 바뀔때 꼭 하자 , Player , Ball , GoalPost 초기화도 넣기
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
