//=============================================================================
//		ゲームメイン処理
//=============================================================================

#include "GameMain.h"
#include "PlaycharProc.h"
#include "EnemyProc.h"
#include "WeaponProc.h"
#include "Effect.h"
#include "RailProc.h"
#include "ForeProc.h"
#include "MapProc.h"
#include "TitleProc.h"

//------------------------------------------------------------------------
//	ゲームメインクラスのコンストラクタ	
//
//  引数　CMain*	pMain
//------------------------------------------------------------------------
CGameMain::CGameMain(CMain* pMain)
{
	ZeroMemory(this, sizeof(CGameMain));
	m_pMain = pMain;
}

//------------------------------------------------------------------------
//	ゲームメインクラスのデストラクタ	
//------------------------------------------------------------------------
CGameMain::~CGameMain()
{
	SAFE_DELETE(m_pTitleProc);
	SAFE_DELETE(m_pMapProc);
	SAFE_DELETE(m_pForeProc);
	SAFE_DELETE(m_pRailProc);
	SAFE_DELETE(m_pEffectProc);
	SAFE_DELETE(m_pWeaponProc);
	SAFE_DELETE(m_pEnmProc);
	SAFE_DELETE(m_pPcProc);

	SAFE_DELETE(m_pSePower);
	SAFE_DELETE(m_pSeShot);
	SAFE_DELETE(m_pSeHit);
	SAFE_DELETE(m_pBgmTitleSelect);
	SAFE_DELETE(m_pBgmMap1);
	SAFE_DELETE(m_pBgmMap2);
	SAFE_DELETE(m_pSeStart);
	SAFE_DELETE(m_pSeDash);
	SAFE_DELETE(m_pSeClear);
	SAFE_DELETE(m_pSeGameOver);

	SAFE_DELETE(m_pImageUI);
	SAFE_DELETE(m_pImageLava);
	SAFE_DELETE(m_pImageCave);
	SAFE_DELETE(m_pImageSky);
	SAFE_DELETE(m_pImageRail);
	SAFE_DELETE(m_pImageChar);
	SAFE_DELETE(m_pImageSprite);

	SAFE_DELETE(m_pShader);
	SAFE_DELETE(m_pFont);
	SAFE_DELETE(m_pDI);
	SAFE_DELETE(m_pXAudio);
	SAFE_DELETE(m_pD3D);

	CoUninitialize();   // COMの解放
}

//------------------------------------------------------------------------
//	アプリケーションの初期化処理	
//
//  引数　なし
//
//	戻り値 HRESULT
//		S_OK	= 正常
//		E_FAIL	= 異常
//------------------------------------------------------------------------
HRESULT CGameMain::Init()
{
	// ＣＯＭの初期化
	//CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (FAILED(CoInitialize(NULL))) {
		MessageBox(0, _T("COMの初期化出来ません"), NULL, MB_OK);
		return E_FAIL;
	}

	// Direct3Dの初期化
	m_pD3D = new CDirect3D;
	if (FAILED(m_pD3D->InitD3D(m_pMain->m_hWnd, WINDOW_WIDTH, WINDOW_HEIGHT))) {
		MessageBox(0, _T("Direct3Dを初期化出来ません"), NULL, MB_OK);
		return E_FAIL;
	}

	// シェーダーの初期化
	m_pShader = new CShader(m_pD3D);
	if (FAILED(m_pShader->InitShader())) {
		MessageBox(0, _T("Shaderを生成・初期化出来ません"), NULL, MB_OK);
		return E_FAIL;
	}

	// XAudio2の初期化
	m_pXAudio = new CXAudio;
	if (FAILED(m_pXAudio->InitAudio(m_pMain->m_hWnd))) {
		MessageBox(0, _T("XAudio2を初期化出来ません"), NULL, MB_OK);
		return E_FAIL;
	}

	// DirectInputの初期化
	m_pDI = new CDirectInput;
	if (m_pDI->StartDirectInput(m_pMain->m_hInstance, m_pMain->m_hWnd,
		INIT_KEYBOARD | INIT_MOUSE | INIT_JOYSTICK, WINDOW_WIDTH, WINDOW_HEIGHT) == FALSE) {
		MessageBox(0, _T("DirectInputを初期化出来ません"), NULL, MB_OK);
		return E_FAIL;
	}

	// フォントテクスチャーの初期化
	m_pFont = new CFontTexture(m_pShader);

	// フォント＆スプライト用のシェーダーのセット
	// 最初に1回だけシェーダーのセットをする。途中でシェーダーの変更はないため。
	m_pFont->SetShader();

	// ----------------------------------------------------------------------------------------
	// スプライトイメージのロード
	m_pImageChar = new CSpriteImage(m_pShader, _T("Data/Image/char1.png"));   // キャラクターイメージのロード
	m_pImageSprite = new CSpriteImage(m_pShader, _T("Data/Image/sprite1.png")); // スプライトイメージのロード
	m_pImageRail = new CSpriteImage(m_pShader, _T("Data/Image/rail.png"));		// レールイメージのロード
	m_pImageSky = new CSpriteImage(m_pShader, _T("Data/Image/aozora.png"));
	m_pImageCave = new CSpriteImage(m_pShader, _T("Data/Image/Map2_Back.png"));
	m_pImageLava = new CSpriteImage(m_pShader, _T("Data/Image/lava.png"));
	m_pImageUI = new CSpriteImage(m_pShader, _T("Data/Image/UI.png"));

	// プロシージャの初期化
	m_pPcProc = new CPcProc(this);
	m_pEnmProc = new CEnmProc(this);
	m_pWeaponProc = new CWeaponProc(this);
	m_pEffectProc = new CEffectProc(this);
	m_pRailProc = new CRailProc(this);
	m_pForeProc = new CForeProc(this);
	m_pMapProc = new CMapProc(this);
	m_pTitleProc = new CTitleProc(this);

	// サウンド
	m_pSePower = new CXAudioSource(m_pXAudio, _T("Data/Sound/PowerUp2.wav"));
	m_pSeShot = new CXAudioSource(m_pXAudio, _T("Data/Sound/MainShot.wav"));
	m_pSeHit = new CXAudioSource(m_pXAudio, _T("Data/Sound/Damage.wav"), 5);
	m_pSeStart = new CXAudioSource(m_pXAudio, _T("Data/Sound/Whistle.wav"));
	m_pSeDash = new CXAudioSource(m_pXAudio, _T("Data/Sound/Dash.wav"));
	m_pBgmTitleSelect = new CXAudioSource(m_pXAudio, _T("Data/Sound/TitleSelect.mp3"));
	m_pBgmMap1 = new CXAudioSource(m_pXAudio, _T("Data/Sound/Map1.mp3"));
	m_pBgmMap2 = new CXAudioSource(m_pXAudio, _T("Data/Sound/Map2Bgm.mp3"));
	m_pSeClear = new CXAudioSource(m_pXAudio, _T("Data/Sound/Clear.mp3"));
	m_pSeGameOver = new CXAudioSource(m_pXAudio, _T("Data/Sound/GameOver.mp3"));

	// ゲーム変数の初期化
	m_dwGameStatus = TITLE;

	m_dwGameMode = 0;
	// スクロール座標の初期化
	m_vScroll = VECTOR2(0, 0);

	// 各種フラグの初期化
	m_bIsFadeOut = TRUE;
	// サウンドの再生
	m_pBgmTitleSelect->Play(AUDIO_LOOP);

	return S_OK;
}

//------------------------------------------------------------------------
//	アプリケーションのメインループ処理	
//
//  引数　なし
//
//	戻り値 なし
//------------------------------------------------------------------------
void CGameMain::Loop()
{

	m_pDI->GetInput();			// 入力情報の取得
	m_pFont->Refresh();         // フォント情報のリフレッシュ

	if (m_pDI->CheckKey(KD_TRG, DIK_F4))  ChangeScreenMode();   // フルスクリーンの切り替え       // -- 2018.12.14

	switch (m_dwGameStatus)
	{
	case TITLE:				// ゲーム開始タイトル
		m_pTitleProc->Title();
		break;

	case GAMEMAIN:			// ゲーム主処理
		GameMain();
		break;

	case GAMEEND:			// ゲーム終了
		PostQuitMessage(0);
		break;
	}

	// 暗転処理
	if (CSprite::m_bFade) {
		Fade();
	}

	//画面更新（バックバッファをフロントバッファに）
	m_pD3D->m_pSwapChain->Present(0, 0);                   // Vsyncなし
}

//------------------------------------------------------------------------
//	ゲームのメイン処理	
//
//  引数　なし
//
//	戻り値 なし
//------------------------------------------------------------------------
void CGameMain::GameMain()
{

	//画面クリア（実際は単色で画面を塗りつぶす処理）
	float ClearColor[4] = { 0,0,0,1 };// クリア色作成　RGBAの順
	m_pD3D->ClearRenderTarget(ClearColor); // 画面クリア

	// プロシージャの更新
	m_pMapProc->Update();		// マッププロシージャの更新
	m_pPcProc->UpdateAll();		// ＰＣプロシージャの更新
	m_pEnmProc->UpdateAll();	// 敵プロシージャの更新
	m_pWeaponProc->UpdateAll();	// 武器プロシージャの更新
	m_pEffectProc->UpdateAll();	// 映像効果プロシージャの更新
	m_pRailProc->UpdateAll();

	m_pMapProc->Update2();		// マッププロシージャの更新2
	m_pForeProc->Update();		// 前景プロシージャの更新
}

//------------------------------------------------------------------------
//	アプリケーションの終了処理	
//
//  引数　なし
//
//	戻り値 なし
//------------------------------------------------------------------------
void CGameMain::Quit()
{

}

//------------------------------------------------------------------------
//	各シーン移動時の暗転の処理	
//
//  引数　なし
//
//	戻り値 なし
//------------------------------------------------------------------------
void CGameMain::Fade()
{
	if (CSprite::m_fFadeDiffuse > 0.00f && m_bIsFadeOut) {
		CSprite::m_fFadeDiffuse -= 0.05f;
	}
	else {
		m_bIsFadeOut = FALSE;
		CSprite::m_fFadeDiffuse += 0.05f;
		if (CSprite::m_fFadeDiffuse >= 1.00f) {
			CSprite::m_fFadeDiffuse = 1.0f;
			CSprite::m_bFade = false;
			m_bIsFadeOut = TRUE;
		}
	}
}

//------------------------------------------------------------------------    // -- 2018.12.14
//	ウィンドウモードとフルスクリーンモードを切り替える処理	
//
//  引数　モード  0:ウインドウモード　1:フルスクリーン　-1:モード切り替え（省略値）
//
//	戻り値 なし
//------------------------------------------------------------------------
HRESULT CGameMain::ChangeScreenMode(int nMode)
{
	HRESULT Ret = S_OK;
	BOOL bFullScreen;  // フルスクリーンモードか？

	//	現在のスクリーンモードを得る
	m_pD3D->m_pSwapChain->GetFullscreenState(&bFullScreen, NULL);

	switch (nMode)
	{
	case 0:    // ウインドウモードにする
		if (bFullScreen) Ret = m_pD3D->m_pSwapChain->SetFullscreenState(false, NULL);
		break;
	case 1:    // フルスクリーンモードにする
		if (!bFullScreen) Ret = m_pD3D->m_pSwapChain->SetFullscreenState(true, NULL);
		break;
	default:   // 現在のモードを切り替える
		if (bFullScreen)
		{
			Ret = m_pD3D->m_pSwapChain->SetFullscreenState(false, NULL);
		}
		else {
			Ret = m_pD3D->m_pSwapChain->SetFullscreenState(true, NULL);
		}
	}

	return Ret;
}