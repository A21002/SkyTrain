//=============================================================================
//		�Q�[�����C������
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
//	�Q�[�����C���N���X�̃R���X�g���N�^	
//
//  �����@CMain*	pMain
//------------------------------------------------------------------------
CGameMain::CGameMain(CMain* pMain)
{
	ZeroMemory(this, sizeof(CGameMain));
	m_pMain = pMain;
}

//------------------------------------------------------------------------
//	�Q�[�����C���N���X�̃f�X�g���N�^	
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
	SAFE_DELETE(m_pBgmMovie);
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

	CoUninitialize();   // COM�̉��
}

//------------------------------------------------------------------------
//	�A�v���P�[�V�����̏���������	
//
//  �����@�Ȃ�
//
//	�߂�l HRESULT
//		S_OK	= ����
//		E_FAIL	= �ُ�
//------------------------------------------------------------------------
HRESULT CGameMain::Init()
{
	// �b�n�l�̏�����
	//CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (FAILED(CoInitialize(NULL))) {
		MessageBox(0, _T("COM�̏������o���܂���"), NULL, MB_OK);
		return E_FAIL;
	}

	// Direct3D�̏�����
	m_pD3D = new CDirect3D;
	if (FAILED(m_pD3D->InitD3D(m_pMain->m_hWnd, WINDOW_WIDTH, WINDOW_HEIGHT))) {
		MessageBox(0, _T("Direct3D���������o���܂���"), NULL, MB_OK);
		return E_FAIL;
	}

	// �V�F�[�_�[�̏�����
	m_pShader = new CShader(m_pD3D);
	if (FAILED(m_pShader->InitShader())) {
		MessageBox(0, _T("Shader�𐶐��E�������o���܂���"), NULL, MB_OK);
		return E_FAIL;
	}

	// XAudio2�̏�����
	m_pXAudio = new CXAudio;
	if (FAILED(m_pXAudio->InitAudio(m_pMain->m_hWnd))) {
		MessageBox(0, _T("XAudio2���������o���܂���"), NULL, MB_OK);
		return E_FAIL;
	}

	// DirectInput�̏�����
	m_pDI = new CDirectInput;
	if (m_pDI->StartDirectInput(m_pMain->m_hInstance, m_pMain->m_hWnd,
		INIT_KEYBOARD | INIT_MOUSE | INIT_JOYSTICK, WINDOW_WIDTH, WINDOW_HEIGHT) == FALSE) {
		MessageBox(0, _T("DirectInput���������o���܂���"), NULL, MB_OK);
		return E_FAIL;
	}

	// �t�H���g�e�N�X�`���[�̏�����
	m_pFont = new CFontTexture(m_pShader);

	// �t�H���g���X�v���C�g�p�̃V�F�[�_�[�̃Z�b�g
	// �ŏ���1�񂾂��V�F�[�_�[�̃Z�b�g������B�r���ŃV�F�[�_�[�̕ύX�͂Ȃ����߁B
	m_pFont->SetShader();

	// ----------------------------------------------------------------------------------------
	// �X�v���C�g�C���[�W�̃��[�h
	m_pImageChar = new CSpriteImage(m_pShader, _T("Data/Image/char1.png"));   // �L�����N�^�[�C���[�W�̃��[�h
	m_pImageSprite = new CSpriteImage(m_pShader, _T("Data/Image/sprite1.png")); // �X�v���C�g�C���[�W�̃��[�h
	m_pImageRail = new CSpriteImage(m_pShader, _T("Data/Image/rail.png"));		// ���[���C���[�W�̃��[�h
	m_pImageSky = new CSpriteImage(m_pShader, _T("Data/Image/aozora.png"));
	m_pImageCave = new CSpriteImage(m_pShader, _T("Data/Image/Map2_Back.png"));
	m_pImageLava = new CSpriteImage(m_pShader, _T("Data/Image/lava.png"));
	m_pImageUI = new CSpriteImage(m_pShader, _T("Data/Image/UI.png"));

	// �v���V�[�W���̏�����
	m_pPcProc = new CPcProc(this);
	m_pEnmProc = new CEnmProc(this);
	m_pWeaponProc = new CWeaponProc(this);
	m_pEffectProc = new CEffectProc(this);
	m_pRailProc = new CRailProc(this);
	m_pForeProc = new CForeProc(this);
	m_pMapProc = new CMapProc(this);
	m_pTitleProc = new CTitleProc(this);

	// �T�E���h
	m_pSePower = new CXAudioSource(m_pXAudio, _T("Data/Sound/PowerUp2.wav"));
	m_pSeShot = new CXAudioSource(m_pXAudio, _T("Data/Sound/MainShot.wav"));
	m_pSeHit = new CXAudioSource(m_pXAudio, _T("Data/Sound/Damage.wav"), 5);
	m_pSeStart = new CXAudioSource(m_pXAudio, _T("Data/Sound/Start.wav"));
	m_pSeDash = new CXAudioSource(m_pXAudio, _T("Data/Sound/Dash.wav"));
	m_pBgmTitleSelect = new CXAudioSource(m_pXAudio, _T("Data/Sound/TitleSelect.mp3"));
	m_pBgmMovie = new CXAudioSource(m_pXAudio, _T("Data/Sound/Movie.mp3"));
	m_pBgmMap1 = new CXAudioSource(m_pXAudio, _T("Data/Sound/Map1.mp3"));
	m_pBgmMap2 = new CXAudioSource(m_pXAudio, _T("Data/Sound/Map2Bgm.mp3"));
	m_pSeClear = new CXAudioSource(m_pXAudio, _T("Data/Sound/Clear.mp3"));
	m_pSeGameOver = new CXAudioSource(m_pXAudio, _T("Data/Sound/GameOver.mp3"));

	// �Q�[���ϐ��̏�����
	m_dwGameStatus = TITLE;

	m_dwGameMode = 0;
	// �X�N���[�����W�̏�����
	m_vScroll = VECTOR2(0, 0);

	// �e��t���O�̏�����
	m_bIsFadeOut = TRUE;
	// �T�E���h�̍Đ�
	m_pBgmTitleSelect->Play(AUDIO_LOOP);

	return S_OK;
}

//------------------------------------------------------------------------
//	�A�v���P�[�V�����̃��C�����[�v����	
//
//  �����@�Ȃ�
//
//	�߂�l �Ȃ�
//------------------------------------------------------------------------
void CGameMain::Loop()
{

	m_pDI->GetInput();			// ���͏��̎擾
	m_pFont->Refresh();         // �t�H���g���̃��t���b�V��

	if (m_pDI->CheckKey(KD_TRG, DIK_F4))  ChangeScreenMode();   // �t���X�N���[���̐؂�ւ�       // -- 2018.12.14

	switch (m_dwGameStatus)
	{
	case TITLE:				// �Q�[���J�n�^�C�g��
		m_pTitleProc->Title();
		break;

	case GAMEMAIN:			// �Q�[���又��
		GameMain();
		break;

	case GAMEEND:			// �Q�[���I��
		PostQuitMessage(0);
		break;
	}

	// �Ó]����
	if (CSprite::m_bFade) {
		Fade();
	}

	//��ʍX�V�i�o�b�N�o�b�t�@���t�����g�o�b�t�@�Ɂj
	m_pD3D->m_pSwapChain->Present(0, 0);                   // Vsync�Ȃ�
}

//------------------------------------------------------------------------
//	�Q�[���̃��C������	
//
//  �����@�Ȃ�
//
//	�߂�l �Ȃ�
//------------------------------------------------------------------------
void CGameMain::GameMain()
{

	//��ʃN���A�i���ۂ͒P�F�ŉ�ʂ�h��Ԃ������j
	float ClearColor[4] = { 0,0,0,1 };// �N���A�F�쐬�@RGBA�̏�
	m_pD3D->ClearRenderTarget(ClearColor); // ��ʃN���A

	// �v���V�[�W���̍X�V
	m_pMapProc->Update();		// �}�b�v�v���V�[�W���̍X�V
	m_pPcProc->UpdateAll();		// �o�b�v���V�[�W���̍X�V
	m_pEnmProc->UpdateAll();	// �G�v���V�[�W���̍X�V
	m_pWeaponProc->UpdateAll();	// ����v���V�[�W���̍X�V
	m_pEffectProc->UpdateAll();	// �f�����ʃv���V�[�W���̍X�V
	m_pRailProc->UpdateAll();

	m_pMapProc->Update2();		// �}�b�v�v���V�[�W���̍X�V2
	m_pForeProc->Update();		// �O�i�v���V�[�W���̍X�V
}

//------------------------------------------------------------------------
//	�A�v���P�[�V�����̏I������	
//
//  �����@�Ȃ�
//
//	�߂�l �Ȃ�
//------------------------------------------------------------------------
void CGameMain::Quit()
{

}

//------------------------------------------------------------------------
//	�e�V�[���ړ����̈Ó]�̏���	
//
//  �����@�Ȃ�
//
//	�߂�l �Ȃ�
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
//	�E�B���h�E���[�h�ƃt���X�N���[�����[�h��؂�ւ��鏈��	
//
//  �����@���[�h  0:�E�C���h�E���[�h�@1:�t���X�N���[���@-1:���[�h�؂�ւ��i�ȗ��l�j
//
//	�߂�l �Ȃ�
//------------------------------------------------------------------------
HRESULT CGameMain::ChangeScreenMode(int nMode)
{
	HRESULT Ret = S_OK;
	BOOL bFullScreen;  // �t���X�N���[�����[�h���H

	//	���݂̃X�N���[�����[�h�𓾂�
	m_pD3D->m_pSwapChain->GetFullscreenState(&bFullScreen, NULL);

	switch (nMode)
	{
	case 0:    // �E�C���h�E���[�h�ɂ���
		if (bFullScreen) Ret = m_pD3D->m_pSwapChain->SetFullscreenState(false, NULL);
		break;
	case 1:    // �t���X�N���[�����[�h�ɂ���
		if (!bFullScreen) Ret = m_pD3D->m_pSwapChain->SetFullscreenState(true, NULL);
		break;
	default:   // ���݂̃��[�h��؂�ւ���
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