#include "ItemObj.h"
#include "MapProc.h"
#include "PlaycharProc.h"
#include "Effect.h"
#include "ForeProc.h"

//------------------------------------------------------------------------
//	�A�C�e���I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//------------------------------------------------------------------------
CItemObj::CItemObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageChar);
	m_nAnimNum = 2;
}

// ---------------------------------------------------------------------------
// �A�C�e���I�u�W�F�N�g�̃f�X�g���N�^
// ---------------------------------------------------------------------------
CItemObj::~CItemObj()
{
	SAFE_DELETE(m_pSprite);
}

//-----------------------------------------------------------------------------
// �A�C�e���I�u�W�F�N�g�̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   DWORD       dwNo    �A�C�e�����
//
//   �߂�l�@�@TRUE
//-----------------------------------------------------------------------------
BOOL	CItemObj::Start(VECTOR2 vPos, DWORD dwNo)
{
	ResetStatus();
	ResetAnim();
	m_bActive = TRUE;
	m_dwStatusSub = dwNo;

	m_vPos = vPos;	// �����ʒu
	m_vPosUp = VECTOR2(0, 0);

	switch (m_dwStatusSub)
	{
	case  ITEMRESQUE:		// �~�}��
		m_pSprite->SetSrc(384, 336, 48, 48);
		break;

	case ITEMFIRSTSLOPE:	// �ŏ��̍�̊J�n�n�_
		m_pSprite->SetSrc(384, 288, 48, 48);   // �����F
		break;

	case  ITEMGOAL:			// �S�[���n�_
		m_pSprite->SetSrc(0, 384, 188, 100);
		m_nAnimNum = 1;
		m_pGMain->m_pEffectProc->m_pEffectGoalArrowProc->Start(m_vPos + VECTOR2(54, -84));
		break;

	case ITEMPCDUMMY:		// ���[�r�[���̃v���C���[�̃_�~�[�I�u�W�F�N�g
		m_pSprite->SetSrc(0, 192, 93, 48);
		m_nAnimNum = 1;
		break;
	}

	return TRUE;
}

//-----------------------------------------------------------------------------
// �A�C�e���I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CItemObj::Update()
{
	if (!m_bActive) return;
	CDirectInput* pDI = m_pGMain->m_pDI;

	if (isCollision(m_pGMain->m_pPcProc->GetPcObjPtr()) && !m_pGMain->m_pMapProc->m_bMapMovieFlag) // PC�Ƃ̐ڐG����
	{
		switch (m_dwStatusSub)
		{
		case  ITEMRESQUE:		// �~�}��
			m_pGMain->m_pPcProc->GetPcObjPtr()->SetHp(m_pGMain->m_pPcProc->GetPcObjPtr()->GetHp() + 10);
			m_pGMain->m_pPcProc->GetPcObjPtr()->SetMaterial(m_pGMain->m_pPcProc->GetPcObjPtr()->GetMaterial() + 10);
			m_pGMain->m_pSePower->Play();
			break;

		case ITEMFIRSTSLOPE:	// �ŏ��̍�̊J�n�n�_
			m_pGMain->m_pPcProc->GetPcObjPtr()->SetTarget(VECTOR2(m_pGMain->m_pPcProc->GetPcObjPtr()->GetPos().x + 384, m_pGMain->m_pPcProc->GetPcObjPtr()->GetPos().y - 384));
			m_pGMain->m_pPcProc->GetPcObjPtr()->SetRotate(-45.0f);
			m_pGMain->m_pPcProc->GetPcObjPtr()->SetStatusSub(RAIL);
			break;

		case ITEMGOAL:			// �S�[���n�_
			m_pGMain->m_pForeProc->SetPhase(FORE_GAMECLEAR);
			m_pGMain->m_pSeClear->Play();
			break;
		}
		m_bActive = FALSE;
	}

	AnimCountup();
	Draw();
}