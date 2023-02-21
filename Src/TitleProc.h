//=============================================================================
//      オープニングタイトル・ゲームクリヤー・ゲームオーバーの処理
//=============================================================================
#pragma once

#include "GameMain.h"

#define TITLE_PHASE 0
#define TITLE_BLACKOUT_PHASE 1
#define STAGESELECT_PHASE 2
#define STAGESELECT_BLACKOUT_PHASE 3

// --------------------------------------------------------------------
// タイトル　プロシージャクラス
// --------------------------------------------------------------------
class CTitleProc : public CBaseProc
{
protected:
	CGameMain* m_pGMain;

	CSpriteImage* m_pImageTitle;			// タイトル画面のイラスト
	CSpriteImage* m_pImageSelectBack;		// ステージセレクトの背景
	CSpriteImage* m_pImageSelectIcon;		// ステージセレクト時のボタン
	CSprite* m_pSprite;

	DWORD			m_dwStatusPhase;

public:
	void Title();
	BOOL TitleView();
	BOOL Select();

	BOOL CheckMousePos(int, int, int, int);
	CTitleProc(CGameMain* pGMain);	// コンストラクタ
	~CTitleProc();
};