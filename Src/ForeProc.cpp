//=============================================================================
//		前景・後景処理
//=============================================================================
#include "GameMain.h"
#include "PlaycharProc.h"
#include "ForeProc.h"
#include "TitleProc.h"
#include "EnemyProc.h"
#include "Effect.h"
#include "MapProc.h"

// ========================================================================================
// 前景の処理
// ========================================================================================
//------------------------------------------------------------------------
//	前景プロシージャのコンストラクタ	
//
//  引数　CGameMain* pGMain
//------------------------------------------------------------------------
CForeProc::CForeProc(CGameMain* pGMain)
{
	m_pGMain = pGMain;
	m_dwStatusPhase = 1;
	m_dwPushButton = 0;
	m_pForegrd = new CSprite(m_pGMain->m_pShader);
}

// ---------------------------------------------------------------------------
// 前景プロシージャのデストラクタ
// ---------------------------------------------------------------------------
CForeProc::~CForeProc()
{
	SAFE_DELETE(m_pForegrd);
}

//-----------------------------------------------------------------------------
// 前景プロシージャの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CForeProc::Update()
{
	switch (m_dwStatusPhase) {
	case FORE_GAMEMAIN:
		// ゲームメイン画面
		GameUI();
		break;

	case FORE_GAMECLEAR:
		// クリア画面
		if (ClearUI()) {
			m_dwStatusPhase = FORE_CLICK_BUTTON;
		}
		break;

	case FORE_GAMEOVER:
		// ゲームオーバー画面
		if (OverUI()) {
			m_dwStatusPhase = FORE_CLICK_BUTTON;
		}
		break;

	case FORE_CLICK_BUTTON:
		// ゲームオーバー、ゲームクリア画面で押されたボタンごとの処理
		switch (m_dwPushButton) {
		case 1:
			// ステージセレクト画面への遷移
			m_pForegrd->m_bFade = true;
			m_dwStatusPhase = FORE_BLACKOUT;
			break;

		case 2:
			// ゲーム終了
			m_pGMain->m_dwGameStatus = GAMEEND;
			m_pGMain->m_pEnmProc->SetNonActive();	// 敵を全て消す。敵の発生フラグをリセットする
			m_pGMain->m_pEffectProc->SetNonActive();	// アイテムを全て消す。アイテムの発生フラグをリセットする
			break;

		default:
			break;
		}
		break;

	case FORE_BLACKOUT:
		// フェードアウト終了するまでシーン遷移を待機させる処理
		if (!m_pGMain->m_bIsFadeOut) {
			if (m_pGMain->m_pMapProc->GetMapNo() == 0) {
				m_pGMain->m_pBgmMap1->Stop();
			}
			else {
				m_pGMain->m_pBgmMap2->Stop();
			}
			m_pGMain->m_pBgmTitleSelect->Play(AUDIO_LOOP);
			m_pGMain->m_dwGameStatus = TITLE;
			m_pGMain->m_pPcProc->GetPcObjPtr()->SetActive(FALSE);
			m_pGMain->m_pEnmProc->SetNonActive();	// 敵を全て消す。敵の発生フラグをリセットする
			m_pGMain->m_pEffectProc->SetNonActive();	// アイテムを全て消す。アイテムの発生フラグをリセットする
		}
		break;
	}
}

//-----------------------------------------------------------------------------
// ゲームメイン画面のUI
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void CForeProc::GameUI()
{
	CSpriteImage* pImageFore = m_pGMain->m_pImageSprite; // すでに読み込んであるスプライトイメージを使用する
	float h = 0, m = 0;
	int   DestX, DestY;

	if (m_pGMain->m_pPcProc->GetPcObjPtr()->m_bMovieFlag) {
		// ムービー処理中は上下に黒いバーを重ねる
		m_pForegrd->Draw(pImageFore, 0, 0, 0, 576, WINDOW_WIDTH, 100);
		m_pForegrd->Draw(pImageFore, 0, WINDOW_HEIGHT - 100, 0, 576, WINDOW_WIDTH, 100);
	}
	else {
		// ステータスバーの表示
		h = (float)m_pGMain->m_pPcProc->GetPcObjPtr()->GetHp() / m_pGMain->m_pPcProc->GetPcObjPtr()->GetMaxHp();
		if (h < 0) h = 0;
		m = (float)m_pGMain->m_pPcProc->GetPcObjPtr()->GetMaterial() / m_pGMain->m_pPcProc->GetPcObjPtr()->GetMaxMaterial();
		if (m < 0) m = 0;

		// ＨＰとＰＣ残数の表示
		DestX = 10;
		DestY = 10;
		// バーの左
		m_pForegrd->Draw(pImageFore, DestX, DestY, 0, 96, 48, 48);

		// バー本体の背景
		DestX += 48;
		m_pForegrd->Draw(pImageFore, DestX, DestY, 48, 96, (DWORD)(624 * h), 48);

		// hp
		m_pForegrd->Draw(pImageFore, DestX, DestY + 6, 0, 0, (DWORD)(624 * h), 12);
		// mp
		m_pForegrd->Draw(pImageFore, DestX, DestY + 30, 0, 48, (int)(624 * m), 12);

		// バーの右
		m_pForegrd->Draw(pImageFore, DestX + (int)(DWORD)(624 * h), DestY, 672, 96, 48, 48);
	}
}

//-----------------------------------------------------------------------------
// ゲームクリア画面のUI
//
//   引数　　　なし
//-----------------------------------------------------------------------------
BOOL CForeProc::ClearUI()
{
	bool bRet = FALSE;
	CSpriteImage* m_pSprite = m_pGMain->m_pImageUI; // すでに読み込んであるスプライトイメージを使用する
	const float fScale = 1.1f;
	const int nStartX = 433, nStartY = 384;
	const int nWidth = 500, nHeight = 150;

	const int nWidthScale = nWidth * fScale;
	const int nHeightScale = nHeight * fScale;

	// 背景の表示
	m_pForegrd->Draw(m_pSprite, 158, 96, 0, 420, 1049, 160);

	// ゲームモードセレクト表示
	for (int i = 0; i < 2; i++)
	{
		if (m_dwPushButton == i + 1)
		{
			// 選択中のモード
			m_pForegrd->Draw(m_pSprite, nStartX - (nWidthScale - nWidth) / 2, nStartY + (nHeight + 42) * i - (nHeightScale - nHeight) / 2,
				0, 0 + nHeight * i, nWidth, nHeight, nWidthScale, nHeightScale);
		}
		else {
			// 選択していないモード
			m_pForegrd->Draw(m_pSprite, nStartX, nStartY + (nHeight + 42) * i, 0, 0 + nHeight * i, nWidth, nHeight, 0.7f);
		}
	}

	// マウスによるゲームモードセレクト(1～4)
	for (int i = 0; i < 2; i++)
	{
		if (CheckMousePos(nStartX, nStartY + (nHeight + 42) * i, nWidth, nHeight))
		{
			m_dwPushButton = i + 1;     // マウスカーソルがゲームモードスプライト内にある
		}
	}

	if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_A) || m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))	//
	{
		bRet = TRUE;  // 終了
	}
	return bRet;
}

//-----------------------------------------------------------------------------
// ゲームオーバーのUI
//
//   引数　　　なし
//-----------------------------------------------------------------------------
BOOL CForeProc::OverUI()
{
	bool bRet = FALSE;
	CSpriteImage* m_pSprite = m_pGMain->m_pImageUI; // すでに読み込んであるスプライトイメージを使用する
	const float fScale = 1.1f;
	const int nStartX = 433, nStartY = 384;
	const int nWidth = 500, nHeight = 150;

	const int nWidthScale = nWidth * fScale;
	const int nHeightScale = nHeight * fScale;

	// 背景の表示
	m_pForegrd->Draw(m_pSprite, 158, 96, 0, 703, 942, 161);

	// ゲームモードセレクト表示
	for (int i = 0; i < 2; i++)
	{
		if (m_dwPushButton == i + 1)
		{
			// 選択中のモード
			m_pForegrd->Draw(m_pSprite, nStartX - (nWidthScale - nWidth) / 2, nStartY + (nHeight + 42) * i - (nHeightScale - nHeight) / 2,
				0, 0 + nHeight * i, nWidth, nHeight, nWidthScale, nHeightScale);
		}
		else {
			// 選択していないモード
			m_pForegrd->Draw(m_pSprite, nStartX, nStartY + (nHeight + 42) * i, 0, 0 + nHeight * i, nWidth, nHeight, 0.7f);
		}
	}

	// マウスによるゲームモードセレクト(1～4)
	for (int i = 0; i < 2; i++)
	{
		if (CheckMousePos(nStartX, nStartY + (nHeight + 42) * i, nWidth, nHeight))
		{
			m_dwPushButton = i + 1;     // マウスカーソルがゲームモードスプライト内にある
		}
	}

	if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_A) || m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))	//
	{
		bRet = TRUE;  // 終了
	}
	return bRet;
}

//------------------------------------------------------------------------
// マウスカーソルが指定した矩形内にあるかどうかを判定する
//
// 引数  int nPosX,  int nPosY     矩形左上座標
//       int nWidth, int nHeight   矩形の幅と高さ
//
// 戻り値  BOOL  TRUE:矩形内にある    FALSE:矩形内に無い
//------------------------------------------------------------------------
BOOL CForeProc::CheckMousePos(int nPosX, int nPosY, int nWidth, int nHeight)
{
	POINT MPos = m_pGMain->m_pDI->GetMousePos();
	if (MPos.x >= nPosX && MPos.x <= nPosX + nWidth &&
		MPos.y >= nPosY && MPos.y <= nPosY + nHeight)
	{
		return TRUE;  // 矩形内にある
	}
	else {
		return FALSE;  // 矩形内に無い
	}
}

//============================================================================
// アクセス関数
//============================================================================
void CForeProc::SetPhase(DWORD phase)
{
	m_dwStatusPhase = phase;
}

DWORD CForeProc::GetPhase()
{
	return m_dwStatusPhase;
}
