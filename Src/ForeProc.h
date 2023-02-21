//=============================================================================
//		前景・後景処理
//=============================================================================
#pragma once

//警告非表示
#pragma warning(disable : 4005)
#pragma warning(disable : 4244)
#pragma warning(disable : 4018)

//ヘッダーファイルのインクルード
#include <stdio.h>
#include <windows.h>

#include "Main.h"
#include "Direct3D.h"
#include "XAudio.h"
#include "Dinput.h"
#include "Sprite.h"

#define FORE_GAMEMAIN 1
#define FORE_GAMECLEAR 2
#define FORE_GAMEOVER 3
#define FORE_CLICK_BUTTON 4
#define FORE_BLACKOUT 5

//======================================================================
// バッククラウンド　プロシージャクラス
//======================================================================
class CBackProc
{
protected:
	CGameMain* m_pGMain;
	CSpriteImage* m_pImageBk;
	CSprite* m_pBackgrd;
	VECTOR2			m_vScroll;
};

//======================================================================
// フォアクラウンド　プロシージャクラス
// (注意)基本プロシージャクラスは継承していない
//======================================================================
class CForeProc
{
protected:
	CGameMain* m_pGMain;
	CSprite* m_pForegrd;
	DWORD			m_dwStatusPhase;
	DWORD			m_dwPushButton;

public:
	void Update();		// 更新処理

	void GameUI();		// ゲームUIの表示
	BOOL ClearUI();		// クリア文字、ボタンの表示
	BOOL OverUI();		// ゲームオーバー文字、ボタンの表示
	BOOL CheckMousePos(int, int, int, int);

	// アクセス関数
	void SetPhase(DWORD phase);
	DWORD GetPhase();

	CForeProc(CGameMain* pGMain);	// コンストラクタ
	~CForeProc();

};
