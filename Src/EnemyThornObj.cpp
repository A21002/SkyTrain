#include "EnemyThornObj.h"
#include "MapProc.h"
#include "PlaycharProc.h"

//------------------------------------------------------------------------
//	�n���Z���{���̓G�I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//------------------------------------------------------------------------
CEnmThornObj::CEnmThornObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageChar, 144, 192, 48, 48);
	m_vPos = VECTOR2(0, 0);
}

// ---------------------------------------------------------------------------
// �n���Z���{���̓G�I�u�W�F�N�g�̃f�X�g���N�^
// ---------------------------------------------------------------------------
CEnmThornObj::~CEnmThornObj()
{
	SAFE_DELETE(m_pSprite);
}

//-----------------------------------------------------------------------------
// �n���Z���{���̓G�I�u�W�F�N�g�̊J�n
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
BOOL	CEnmThornObj::Start(VECTOR2 vPos)
{
	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwStatusSub = WALK;
	m_nDirIdx = RIGHT;
	m_vPos = vPos;	// �����ʒu
	m_vPosUp = VECTOR2(0, 0);
	m_nAnimNum = 1;
	m_nWaitTime = 120;
	m_nCnt2 = 90;
	SetStatus(_T("Data/Script/StatusThorn.csv"));
	return TRUE;
}

//-----------------------------------------------------------------------------
// �n���Z���{���̓G�I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CEnmThornObj::Update()
{
	CMapLine* pHitmapline = NULL;
	BOOL bRet;
	if (m_bActive)
	{
		m_vPosUp = VECTOR2(0, fSpeed);
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
			switch (m_dwStatusSub)
			{
			case  WALK:
				m_nCnt2--;
				if (m_nCnt2 <= 0) {
					fSpeed *= -1;
					m_nCnt2 = 90;
				}

				// �}�b�v���Ƃ̐ڐG����ƓK�؂Ȉʒu�ւ̈ړ�
				bRet = m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline);
				if (bRet)
				{
					// �}�b�v���̒[�ɗ����̂ŏ㉺���]
					fSpeed *= -1;
					m_nCnt2 = 90;
				}
				break;
			}
			// ����
			m_vPos += m_vPosUp;
			// �o�b�Ƃ̂����蔻��
			if (!m_pGMain->m_pMapProc->m_bMapMovieFlag) {
				m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
			}

			// �c��ޏ���
			if (m_nWaitTime <= 0) {
				if (m_nDirIdx == RIGHT) {
					m_nDirIdx = LEFT;
				}
				else {
					m_nDirIdx = RIGHT;
				}
				m_nWaitTime = 120;
			}
			m_nWaitTime--;
			if (m_nWaitTime < 0) {
				m_nWaitTime = 0;
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