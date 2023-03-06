#include "EnemyCannonObj.h"
#include "MapProc.h"
#include "PlaycharProc.h"
#include "WeaponProc.h"

//------------------------------------------------------------------------
//	��C�̓G�I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//------------------------------------------------------------------------
CEnmCannonObj::CEnmCannonObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageChar, 192, 192, 48, 48);
	m_vPos = VECTOR2(0, 0);
}

// ---------------------------------------------------------------------------
// ��C�̓G�I�u�W�F�N�g�̃f�X�g���N�^
// ---------------------------------------------------------------------------
CEnmCannonObj::~CEnmCannonObj()
{
	SAFE_DELETE(m_pSprite);
}

//-----------------------------------------------------------------------------
// ��C�̓G�I�u�W�F�N�g�̊J�n
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
BOOL	CEnmCannonObj::Start(VECTOR2 vPos, DWORD dwOwner)
{
	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_nDirIdx = dwOwner;
	m_vPos = vPos;	// �����ʒu
	m_vPosUp = VECTOR2(0, 0);
	m_nAnimNum = 1;
	m_nWaitTime = 120;
	SetStatus(_T("Data/Script/StatusCannoon.csv"));
	return TRUE;
}

//-----------------------------------------------------------------------------
// ��C�̓G�I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CEnmCannonObj::Update()
{
	float fSpeed = 1;
	if (m_bActive)
	{
		switch (m_dwStatus)
		{
		case  FLASH:
			m_nCnt1--;
			if (m_nCnt1 <= 0) {
				ResetStatus();
				ResetAnim();
			}
			else {
				FlashCountup();
			}		// break;����ꂸ���̂܂܁@NORMAL�@�̏������s��
		case  NORMAL:
			// ��ʓ��ɂ���ꍇ
			VECTOR2 scroll = m_pGMain->m_vScroll;
			if (scroll.x <= m_vPos.x && m_vPos.x <= scroll.x + WINDOW_WIDTH &&
				scroll.y <= m_vPos.y && m_vPos.y <= scroll.y + WINDOW_HEIGHT) {
				if (m_nWaitTime <= 0) {
					m_pGMain->m_pWeaponProc->m_pWeaponCannonProc->Start(m_vPos, this, ENM);
					m_nWaitTime = 180;
				}
			}
			if (m_nWaitTime > 0) {
				m_nWaitTime--;
			}

			// ����
			m_vPos += m_vPosUp;
			// �o�b�Ƃ̂����蔻��
			if (!m_pGMain->m_pMapProc->m_bMapMovieFlag) {
				m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
			}
			break;

		case  DAMAGE:
			m_nHp -= m_pOtherObj->GetAtc();
			if (m_nHp <= 0) {
				m_dwStatus = DEAD;
				m_nCnt1 = 180;
			}
			else {
				m_dwStatus = FLASH;
				m_nCnt1 = 60;
			}
			m_pGMain->m_pSeHit->Play();
			break;

		case  DEAD:
			m_nCnt1--;
			if (m_nCnt1 <= 0)
			{
				m_bActive = FALSE;
			}
			else {
				FlashCountup();
			}
			break;
		}

		AnimCountup();
		Draw();
	}
}