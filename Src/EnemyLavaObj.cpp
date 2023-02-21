#include "EnemyLavaObj.h"
#include "MapProc.h"
#include "PlaycharProc.h"

//------------------------------------------------------------------------
//	Big�n��̓G�I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//------------------------------------------------------------------------
CEnmLavaObj::CEnmLavaObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageLava, 0, 0, 48, 48);
	m_vPos = VECTOR2(0, 0);
}

// ---------------------------------------------------------------------------
// Big�n��̓G�I�u�W�F�N�g�̃f�X�g���N�^
// ---------------------------------------------------------------------------
CEnmLavaObj::~CEnmLavaObj()
{
	SAFE_DELETE(m_pSprite);
}

//-----------------------------------------------------------------------------
// Big�n��̓G�I�u�W�F�N�g�̊J�n
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
BOOL	CEnmLavaObj::Start(VECTOR2 vPos, DWORD dwOwner)
{
	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_nDirIdx = dwOwner;
	m_vPos = vPos;	// �����ʒu
	m_vPosUp = VECTOR2(0, 0);
	m_nAnimNum = 1;
	m_nWaitTime = 120;
	SetStatus(_T("Data/Script/StatusLava.csv"));
	return TRUE;
}

//-----------------------------------------------------------------------------
// Big�n��̓G�I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CEnmLavaObj::Update()
{
	if (m_bActive)
	{
		switch (m_dwStatus)
		{
		case  NORMAL:
			if (!m_pGMain->m_pMapProc->m_bMapMovieFlag) {
				m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
			}
			break;

		case  DAMAGE:
			m_dwStatus = NORMAL;
			break;

		case  DEAD:
			m_dwStatus = NORMAL;
			break;
		}

		AnimCountup();
		Draw();
	}
}