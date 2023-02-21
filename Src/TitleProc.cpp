//=============================================================================
//      オープニングタイトル・ゲームクリヤー・ゲームオーバーの処理
//=============================================================================
#include "TitleProc.h"
#include "PlaycharProc.h"
#include "MapProc.h"
#include "ForeProc.h"

//============================================================================
// タイトル　プロシージャクラス
//============================================================================

// --------------------------------------------------------------------
// タイトルプロシージャのコンストラクタ
// ---------------------------------------------------------------------------
CTitleProc::CTitleProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	m_pGMain = pGMain;
	m_pImageTitle = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/title.png")); // イメージのロード
	m_pImageSelectBack = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/StageSelect_Back.png"));
	m_pImageSelectIcon = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/StageSelect_Icon.png"));
	m_pSprite = new CSprite(m_pGMain->m_pShader); // スプライトの生成
	m_dwStatusPhase = TITLE_PHASE;
}

// ---------------------------------------------------------------------------
// タイトルタイトルプロシージャのデストラクタ
// ---------------------------------------------------------------------------
CTitleProc::~CTitleProc()
{
	SAFE_DELETE(m_pImageTitle);
	SAFE_DELETE(m_pImageSelectBack);
	SAFE_DELETE(m_pImageSelectIcon);
	SAFE_DELETE(m_pSprite);
}

//------------------------------------------------------------------------
//	タイトル、マップセレクトの表示	
//------------------------------------------------------------------------
void CTitleProc::Title()
{
	float ClearColor[4] = { 0,0,0,1 };// クリア色作成　RGBAの順
	m_pGMain->m_pD3D->ClearRenderTarget(ClearColor); // 画面クリア

	// タイトル、ステージセレクトの遷移
	switch (m_dwStatusPhase) {
	case TITLE_PHASE:
		// タイトルの表示
		if (TitleView())
		{
			// タイトル画面でクリックしたとき
			m_pSprite->m_bFade = true;
			m_pGMain->m_bIsFadeOut = true;
			m_dwStatusPhase = TITLE_BLACKOUT_PHASE;
		}
		break;

	case TITLE_BLACKOUT_PHASE:
		// タイトル画面から暗転
		TitleView();
		if (!m_pGMain->m_bIsFadeOut) {
			// 暗転処理が終了したら遷移
			m_dwStatusPhase = STAGESELECT_PHASE;
		}
		break;

	case STAGESELECT_PHASE:
		// ステージセレクトの表示
		if (Select())
		{
			// ステージボタンを押したとき
			m_pSprite->m_bFade = true;
			m_dwStatusPhase = STAGESELECT_BLACKOUT_PHASE;
		}
		break;

	case STAGESELECT_BLACKOUT_PHASE:
		// ステージセレクトからの暗転
		if (!m_pGMain->m_bIsFadeOut) {
			// 暗転処理が終了したらゲームメインに遷移
			m_pGMain->m_pBgmTitleSelect->Stop();
			m_pGMain->m_dwGameStatus = GAMEMAIN;
			m_pSprite->m_bFade = true;
			m_pGMain->m_bIsFadeOut = true;
			m_pGMain->m_pMapProc->SetMap(m_pGMain->m_dwGameMode - 1);
			m_pGMain->m_pForeProc->SetPhase(1);
			m_dwStatusPhase = STAGESELECT_PHASE;
		}
		Select();
		break;

	default:
		break;
	}
}

//------------------------------------------------------------------------
//	タイトルの表示	
//------------------------------------------------------------------------
BOOL CTitleProc::TitleView()
{
	BOOL bRet = FALSE;
	// フルスクリーンにする(なぜか1度だけだと戻ってしまうので、再度フルスクリーンにする)
	//m_pGMain->ChangeScreenMode(1);

	// 表示
	m_pSprite->Draw(m_pImageTitle, 0, 0, 0, 0, m_pImageTitle->m_dwImageWidth, m_pImageTitle->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);

	// 左右どちらかでクリックすると次のフェーズへ
	if (m_pGMain->m_pDI->CheckMouse(KD_DAT, DIM_LBUTTON) || m_pGMain->m_pDI->CheckMouse(KD_DAT, DIM_RBUTTON))
	{
		bRet = TRUE;
	}
	return bRet;
}

//------------------------------------------------------------------------
//	マップセレクト画面の表示	
//------------------------------------------------------------------------
BOOL CTitleProc::Select()
{
	BOOL bRet = FALSE;
	// マップ画像の下に表示する文字
	TCHAR PName[][20] = {
		_T("Stage 1"),
		_T("Stage 2"),
	};

	// ボタンのサイズ
	const int nNum = sizeof(PName) / sizeof(PName[0]);
	const float fScale = 2.0f;							// カーソルが重なった時の拡大率
	const int nStartX = 219, nStartY = 200;
	const int nWidth = 224, nHeight = 160;

	// 拡大した際のサイズ
	const int nWidthScale = nWidth * fScale;
	const int nHeightScale = nHeight * fScale;

	// 背景の表示
	m_pSprite->Draw(m_pImageSelectBack, 0, 0, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	// ゲームモードセレクト表示
	for (int i = 0; i < nNum; i++)
	{
		if (m_pGMain->m_dwGameMode == i + 1)
		{
			// 選択中のモード
			m_pSprite->Draw(m_pImageSelectIcon, nStartX + (nWidth + 478) * i - (nWidthScale - nWidth) / 2, nStartY - (nHeightScale - nHeight) / 2,
				0 + nWidth * i, 160, nWidth, nHeight, nWidthScale, nHeightScale);
		}
		else {
			// 選択していないモード
			m_pSprite->Draw(m_pImageSelectIcon, nStartX + (nWidth + 478) * i, nStartY, 0 + nWidth * i, 0, nWidth, nHeight);
		}
	}

	// マウスによるゲームモードセレクト
	for (int i = 0; i < nNum; i++)
	{
		if (CheckMousePos(nStartX + (nWidth + 478) * i, nStartY, nWidth, nHeight))
		{
			m_pGMain->m_dwGameMode = i + 1;     // マウスカーソルがゲームモードスプライト内にある
			if (m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))
			{
				bRet = TRUE;  // 終了
			}
		}
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
BOOL CTitleProc::CheckMousePos(int nPosX, int nPosY, int nWidth, int nHeight)
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