//=============================================================================
//		�O�i�E��i����
//=============================================================================
#include "GameMain.h"
#include "PlaycharProc.h"
#include "ForeProc.h"
#include "TitleProc.h"
#include "EnemyProc.h"
#include "Effect.h"
#include "MapProc.h"

// ========================================================================================
// �O�i�̏���
// ========================================================================================
//------------------------------------------------------------------------
//	�O�i�v���V�[�W���̃R���X�g���N�^	
//
//  �����@CGameMain* pGMain
//------------------------------------------------------------------------
CForeProc::CForeProc(CGameMain* pGMain)
{
	m_pGMain = pGMain;
	m_dwStatusPhase = 1;
	m_dwPushButton = 0;
	m_pForegrd = new CSprite(m_pGMain->m_pShader);
}

// ---------------------------------------------------------------------------
// �O�i�v���V�[�W���̃f�X�g���N�^
// ---------------------------------------------------------------------------
CForeProc::~CForeProc()
{
	SAFE_DELETE(m_pForegrd);
}

//-----------------------------------------------------------------------------
// �O�i�v���V�[�W���̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CForeProc::Update()
{
	switch (m_dwStatusPhase) {
	case FORE_GAMEMAIN:
		// �Q�[�����C�����
		GameUI();
		break;

	case FORE_GAMECLEAR:
		// �N���A���
		if (ClearUI()) {
			m_dwStatusPhase = FORE_CLICK_BUTTON;
		}
		break;

	case FORE_GAMEOVER:
		// �Q�[���I�[�o�[���
		if (OverUI()) {
			m_dwStatusPhase = FORE_CLICK_BUTTON;
		}
		break;

	case FORE_CLICK_BUTTON:
		// �Q�[���I�[�o�[�A�Q�[���N���A��ʂŉ����ꂽ�{�^�����Ƃ̏���
		switch (m_dwPushButton) {
		case 1:
			// �X�e�[�W�Z���N�g��ʂւ̑J��
			m_pForegrd->m_bFade = true;
			m_dwStatusPhase = FORE_BLACKOUT;
			break;

		case 2:
			// �Q�[���I��
			m_pGMain->m_dwGameStatus = GAMEEND;
			m_pGMain->m_pEnmProc->SetNonActive();	// �G��S�ď����B�G�̔����t���O�����Z�b�g����
			m_pGMain->m_pEffectProc->SetNonActive();	// �A�C�e����S�ď����B�A�C�e���̔����t���O�����Z�b�g����
			break;

		default:
			break;
		}
		break;

	case FORE_BLACKOUT:
		// �t�F�[�h�A�E�g�I������܂ŃV�[���J�ڂ�ҋ@�����鏈��
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
			m_pGMain->m_pEnmProc->SetNonActive();	// �G��S�ď����B�G�̔����t���O�����Z�b�g����
			m_pGMain->m_pEffectProc->SetNonActive();	// �A�C�e����S�ď����B�A�C�e���̔����t���O�����Z�b�g����
		}
		break;
	}
}

//-----------------------------------------------------------------------------
// �Q�[�����C����ʂ�UI
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void CForeProc::GameUI()
{
	CSpriteImage* pImageFore = m_pGMain->m_pImageSprite; // ���łɓǂݍ���ł���X�v���C�g�C���[�W���g�p����
	float h = 0, m = 0;
	int   DestX, DestY;

	if (m_pGMain->m_pPcProc->GetPcObjPtr()->m_bMovieFlag) {
		// ���[�r�[�������͏㉺�ɍ����o�[���d�˂�
		m_pForegrd->Draw(pImageFore, 0, 0, 0, 576, WINDOW_WIDTH, 100);
		m_pForegrd->Draw(pImageFore, 0, WINDOW_HEIGHT - 100, 0, 576, WINDOW_WIDTH, 100);
	}
	else {
		// �X�e�[�^�X�o�[�̕\��
		h = (float)m_pGMain->m_pPcProc->GetPcObjPtr()->GetHp() / m_pGMain->m_pPcProc->GetPcObjPtr()->GetMaxHp();
		if (h < 0) h = 0;
		m = (float)m_pGMain->m_pPcProc->GetPcObjPtr()->GetMaterial() / m_pGMain->m_pPcProc->GetPcObjPtr()->GetMaxMaterial();
		if (m < 0) m = 0;

		// �g�o�Ƃo�b�c���̕\��
		DestX = 10;
		DestY = 10;
		// �o�[�̍�
		m_pForegrd->Draw(pImageFore, DestX, DestY, 0, 96, 48, 48);

		// �o�[�{�̂̔w�i
		DestX += 48;
		m_pForegrd->Draw(pImageFore, DestX, DestY, 48, 96, (DWORD)(624 * h), 48);

		// hp
		m_pForegrd->Draw(pImageFore, DestX, DestY + 6, 0, 0, (DWORD)(624 * h), 12);
		// mp
		m_pForegrd->Draw(pImageFore, DestX, DestY + 30, 0, 48, (int)(624 * m), 12);

		// �o�[�̉E
		m_pForegrd->Draw(pImageFore, DestX + (int)(DWORD)(624 * h), DestY, 672, 96, 48, 48);
	}
}

//-----------------------------------------------------------------------------
// �Q�[���N���A��ʂ�UI
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
BOOL CForeProc::ClearUI()
{
	bool bRet = FALSE;
	CSpriteImage* m_pSprite = m_pGMain->m_pImageUI; // ���łɓǂݍ���ł���X�v���C�g�C���[�W���g�p����
	const float fScale = 1.1f;
	const int nStartX = 433, nStartY = 384;
	const int nWidth = 500, nHeight = 150;

	const int nWidthScale = nWidth * fScale;
	const int nHeightScale = nHeight * fScale;

	// �w�i�̕\��
	m_pForegrd->Draw(m_pSprite, 158, 96, 0, 420, 1049, 160);

	// �Q�[�����[�h�Z���N�g�\��
	for (int i = 0; i < 2; i++)
	{
		if (m_dwPushButton == i + 1)
		{
			// �I�𒆂̃��[�h
			m_pForegrd->Draw(m_pSprite, nStartX - (nWidthScale - nWidth) / 2, nStartY + (nHeight + 42) * i - (nHeightScale - nHeight) / 2,
				0, 0 + nHeight * i, nWidth, nHeight, nWidthScale, nHeightScale);
		}
		else {
			// �I�����Ă��Ȃ����[�h
			m_pForegrd->Draw(m_pSprite, nStartX, nStartY + (nHeight + 42) * i, 0, 0 + nHeight * i, nWidth, nHeight, 0.7f);
		}
	}

	// �}�E�X�ɂ��Q�[�����[�h�Z���N�g(1�`4)
	for (int i = 0; i < 2; i++)
	{
		if (CheckMousePos(nStartX, nStartY + (nHeight + 42) * i, nWidth, nHeight))
		{
			m_dwPushButton = i + 1;     // �}�E�X�J�[�\�����Q�[�����[�h�X�v���C�g���ɂ���
		}
	}

	if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_A) || m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))	//
	{
		bRet = TRUE;  // �I��
	}
	return bRet;
}

//-----------------------------------------------------------------------------
// �Q�[���I�[�o�[��UI
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
BOOL CForeProc::OverUI()
{
	bool bRet = FALSE;
	CSpriteImage* m_pSprite = m_pGMain->m_pImageUI; // ���łɓǂݍ���ł���X�v���C�g�C���[�W���g�p����
	const float fScale = 1.1f;
	const int nStartX = 433, nStartY = 384;
	const int nWidth = 500, nHeight = 150;

	const int nWidthScale = nWidth * fScale;
	const int nHeightScale = nHeight * fScale;

	// �w�i�̕\��
	m_pForegrd->Draw(m_pSprite, 158, 96, 0, 703, 942, 161);

	// �Q�[�����[�h�Z���N�g�\��
	for (int i = 0; i < 2; i++)
	{
		if (m_dwPushButton == i + 1)
		{
			// �I�𒆂̃��[�h
			m_pForegrd->Draw(m_pSprite, nStartX - (nWidthScale - nWidth) / 2, nStartY + (nHeight + 42) * i - (nHeightScale - nHeight) / 2,
				0, 0 + nHeight * i, nWidth, nHeight, nWidthScale, nHeightScale);
		}
		else {
			// �I�����Ă��Ȃ����[�h
			m_pForegrd->Draw(m_pSprite, nStartX, nStartY + (nHeight + 42) * i, 0, 0 + nHeight * i, nWidth, nHeight, 0.7f);
		}
	}

	// �}�E�X�ɂ��Q�[�����[�h�Z���N�g(1�`4)
	for (int i = 0; i < 2; i++)
	{
		if (CheckMousePos(nStartX, nStartY + (nHeight + 42) * i, nWidth, nHeight))
		{
			m_dwPushButton = i + 1;     // �}�E�X�J�[�\�����Q�[�����[�h�X�v���C�g���ɂ���
		}
	}

	if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_A) || m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))	//
	{
		bRet = TRUE;  // �I��
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
BOOL CForeProc::CheckMousePos(int nPosX, int nPosY, int nWidth, int nHeight)
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

//============================================================================
// �A�N�Z�X�֐�
//============================================================================
void CForeProc::SetPhase(DWORD phase)
{
	m_dwStatusPhase = phase;
}

DWORD CForeProc::GetPhase()
{
	return m_dwStatusPhase;
}
