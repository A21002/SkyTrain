#include "WeaponCannonObj.h"
#include "MapProc.h"
#include "PlaycharProc.h"

//======================================================================
// �萔�N���X
//======================================================================
const VECTOR2 WeaponCannonConstruct::SPRITE_SRC = VECTOR2(48, 432);
const VECTOR2 WeaponCannonConstruct::SPRITE_SIZE = VECTOR2(36, 35);

//------------------------------------------------------------------------
//	��C�I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//------------------------------------------------------------------------
CWeaponCannonObj::CWeaponCannonObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite, WeaponCannonConstruct::SPRITE_SRC.x, WeaponCannonConstruct::SPRITE_SRC.y,
		WeaponCannonConstruct::SPRITE_SIZE.x, WeaponCannonConstruct::SPRITE_SIZE.y);
	m_nAnimNum = WeaponCannonConstruct::ANIM_NUM;
	m_nAtc = WeaponCannonConstruct::DAMAGE_NUM;
}

// ---------------------------------------------------------------------------
// ��C�I�u�W�F�N�g�̃f�X�g���N�^
// ---------------------------------------------------------------------------
CWeaponCannonObj::~CWeaponCannonObj()
{
	SAFE_DELETE(m_pSprite);
}

//-----------------------------------------------------------------------------
// ��C�I�u�W�F�N�g�̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@TRUE
//-----------------------------------------------------------------------------
BOOL	CWeaponCannonObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();

	m_vPos = vPos;	// �����ʒu
	m_vPosUp = VECTOR2(0, 0);

	m_vCenter = VECTOR2(0, 0);
	m_nAtc = 20;

	switch (pObj->GetDirIdx())
	{
	case RIGHT:
		m_vPosUp = VECTOR2(0, -WeaponCannonConstruct::SPEED);
		break;
	case LEFT:
		m_vPosUp = VECTOR2(0, WeaponCannonConstruct::SPEED);
		break;

	case 2:
		m_vPosUp = VECTOR2(WeaponCannonConstruct::SPEED, 0);
		break;

	case 3:
		m_vPosUp = VECTOR2(-WeaponCannonConstruct::SPEED, 0);
		break;
	}

	return TRUE;
}

//-----------------------------------------------------------------------------
// �~�T�C���I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CWeaponCannonObj::Update()
{
	if (m_bActive)
	{
		CMapLine* pHitmapline1;

		switch (m_dwStatus) {
		case DAMAGE:
			m_bActive = FALSE;
			break;
		}
		m_pGMain->m_pRailProc->Hitcheck(this);
		if (!m_pGMain->m_pMapProc->m_bMapMovieFlag) {
			m_pGMain->m_pPcProc->GetPcObjPtr()->Hitcheck(this);
		}

		if (m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline1)) {
			m_dwStatus = DAMAGE;
		}

		m_vPos += m_vPosUp;
		AnimCountup();
		Draw();
	}
}