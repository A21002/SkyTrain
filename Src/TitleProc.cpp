//=============================================================================
//      �I�[�v�j���O�^�C�g���E�Q�[���N�����[�E�Q�[���I�[�o�[�̏���
//=============================================================================
#include "TitleProc.h"
#include "PlaycharProc.h"
#include "MapProc.h"
#include "ForeProc.h"

//============================================================================
// �^�C�g���@�v���V�[�W���N���X
//============================================================================

// --------------------------------------------------------------------
// �^�C�g���v���V�[�W���̃R���X�g���N�^
// ---------------------------------------------------------------------------
CTitleProc::CTitleProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	m_pGMain = pGMain;
	m_pImageTitle = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/title.png")); // �C���[�W�̃��[�h
	m_pImageSelectBack = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/StageSelect_Back.png"));
	m_pImageSelectIcon = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/StageSelect_Icon.png"));
	m_pSprite = new CSprite(m_pGMain->m_pShader); // �X�v���C�g�̐���
	m_dwStatusPhase = TITLE_PHASE;
}

// ---------------------------------------------------------------------------
// �^�C�g���^�C�g���v���V�[�W���̃f�X�g���N�^
// ---------------------------------------------------------------------------
CTitleProc::~CTitleProc()
{
	SAFE_DELETE(m_pImageTitle);
	SAFE_DELETE(m_pImageSelectBack);
	SAFE_DELETE(m_pImageSelectIcon);
	SAFE_DELETE(m_pSprite);
}

//------------------------------------------------------------------------
//	�^�C�g���A�}�b�v�Z���N�g�̕\��	
//------------------------------------------------------------------------
void CTitleProc::Title()
{
	float ClearColor[4] = { 0,0,0,1 };// �N���A�F�쐬�@RGBA�̏�
	m_pGMain->m_pD3D->ClearRenderTarget(ClearColor); // ��ʃN���A

	// �^�C�g���A�X�e�[�W�Z���N�g�̑J��
	switch (m_dwStatusPhase) {
	case TITLE_PHASE:
		// �^�C�g���̕\��
		if (TitleView())
		{
			// �^�C�g����ʂŃN���b�N�����Ƃ�
			m_pSprite->m_bFade = true;
			m_pGMain->m_bIsFadeOut = true;
			m_dwStatusPhase = TITLE_BLACKOUT_PHASE;
		}
		break;

	case TITLE_BLACKOUT_PHASE:
		// �^�C�g����ʂ���Ó]
		TitleView();
		if (!m_pGMain->m_bIsFadeOut) {
			// �Ó]�������I��������J��
			m_dwStatusPhase = STAGESELECT_PHASE;
		}
		break;

	case STAGESELECT_PHASE:
		// �X�e�[�W�Z���N�g�̕\��
		if (Select())
		{
			// �X�e�[�W�{�^�����������Ƃ�
			m_pSprite->m_bFade = true;
			m_dwStatusPhase = STAGESELECT_BLACKOUT_PHASE;
		}
		break;

	case STAGESELECT_BLACKOUT_PHASE:
		// �X�e�[�W�Z���N�g����̈Ó]
		if (!m_pGMain->m_bIsFadeOut) {
			// �Ó]�������I��������Q�[�����C���ɑJ��
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
//	�^�C�g���̕\��	
//------------------------------------------------------------------------
BOOL CTitleProc::TitleView()
{
	BOOL bRet = FALSE;
	// �t���X�N���[���ɂ���(�Ȃ���1�x�������Ɩ߂��Ă��܂��̂ŁA�ēx�t���X�N���[���ɂ���)
	//m_pGMain->ChangeScreenMode(1);

	// �\��
	m_pSprite->Draw(m_pImageTitle, 0, 0, 0, 0, m_pImageTitle->m_dwImageWidth, m_pImageTitle->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);

	// ���E�ǂ��炩�ŃN���b�N����Ǝ��̃t�F�[�Y��
	if (m_pGMain->m_pDI->CheckMouse(KD_DAT, DIM_LBUTTON) || m_pGMain->m_pDI->CheckMouse(KD_DAT, DIM_RBUTTON))
	{
		bRet = TRUE;
	}
	return bRet;
}

//------------------------------------------------------------------------
//	�}�b�v�Z���N�g��ʂ̕\��	
//------------------------------------------------------------------------
BOOL CTitleProc::Select()
{
	BOOL bRet = FALSE;
	// �}�b�v�摜�̉��ɕ\�����镶��
	TCHAR PName[][20] = {
		_T("Stage 1"),
		_T("Stage 2"),
	};

	// �{�^���̃T�C�Y
	const int nNum = sizeof(PName) / sizeof(PName[0]);
	const float fScale = 2.0f;							// �J�[�\�����d�Ȃ������̊g�嗦
	const int nStartX = 219, nStartY = 200;
	const int nWidth = 224, nHeight = 160;

	// �g�債���ۂ̃T�C�Y
	const int nWidthScale = nWidth * fScale;
	const int nHeightScale = nHeight * fScale;

	// �w�i�̕\��
	m_pSprite->Draw(m_pImageSelectBack, 0, 0, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	// �Q�[�����[�h�Z���N�g�\��
	for (int i = 0; i < nNum; i++)
	{
		if (m_pGMain->m_dwGameMode == i + 1)
		{
			// �I�𒆂̃��[�h
			m_pSprite->Draw(m_pImageSelectIcon, nStartX + (nWidth + 478) * i - (nWidthScale - nWidth) / 2, nStartY - (nHeightScale - nHeight) / 2,
				0 + nWidth * i, 160, nWidth, nHeight, nWidthScale, nHeightScale);
		}
		else {
			// �I�����Ă��Ȃ����[�h
			m_pSprite->Draw(m_pImageSelectIcon, nStartX + (nWidth + 478) * i, nStartY, 0 + nWidth * i, 0, nWidth, nHeight);
		}
	}

	// �}�E�X�ɂ��Q�[�����[�h�Z���N�g
	for (int i = 0; i < nNum; i++)
	{
		if (CheckMousePos(nStartX + (nWidth + 478) * i, nStartY, nWidth, nHeight))
		{
			m_pGMain->m_dwGameMode = i + 1;     // �}�E�X�J�[�\�����Q�[�����[�h�X�v���C�g���ɂ���
			if (m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))
			{
				bRet = TRUE;  // �I��
			}
		}
	}

	return bRet;
}

//------------------------------------------------------------------------
// �}�E�X�J�[�\�����w�肵����`���ɂ��邩�ǂ����𔻒肷��
//
// ����  int nPosX,  int nPosY     ��`������W
//       int nWidth, int nHeight   ��`�̕��ƍ���
//
// �߂�l  BOOL  TRUE:��`���ɂ���    FALSE:��`���ɖ���
//------------------------------------------------------------------------
BOOL CTitleProc::CheckMousePos(int nPosX, int nPosY, int nWidth, int nHeight)
{
	POINT MPos = m_pGMain->m_pDI->GetMousePos();
	if (MPos.x >= nPosX && MPos.x <= nPosX + nWidth &&
		MPos.y >= nPosY && MPos.y <= nPosY + nHeight)
	{
		return TRUE;  // ��`���ɂ���
	}
	else {
		return FALSE;  // ��`���ɖ���
	}
}