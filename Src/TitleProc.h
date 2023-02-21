//=============================================================================
//      �I�[�v�j���O�^�C�g���E�Q�[���N�����[�E�Q�[���I�[�o�[�̏���
//=============================================================================
#pragma once

#include "GameMain.h"

#define TITLE_PHASE 0
#define TITLE_BLACKOUT_PHASE 1
#define STAGESELECT_PHASE 2
#define STAGESELECT_BLACKOUT_PHASE 3

// --------------------------------------------------------------------
// �^�C�g���@�v���V�[�W���N���X
// --------------------------------------------------------------------
class CTitleProc : public CBaseProc
{
protected:
	CGameMain* m_pGMain;

	CSpriteImage* m_pImageTitle;			// �^�C�g����ʂ̃C���X�g
	CSpriteImage* m_pImageSelectBack;		// �X�e�[�W�Z���N�g�̔w�i
	CSpriteImage* m_pImageSelectIcon;		// �X�e�[�W�Z���N�g���̃{�^��
	CSprite* m_pSprite;

	DWORD			m_dwStatusPhase;

public:
	void Title();
	BOOL TitleView();
	BOOL Select();

	BOOL CheckMousePos(int, int, int, int);
	CTitleProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CTitleProc();
};