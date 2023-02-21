#include "WeaponMissileObj.h"
#include "MapProc.h"
#include "RailProc.h"
#include "PlaycharProc.h"
#include "Effect.h"

//============================================================================
// 定数クラス
//============================================================================
const VECTOR2 WeaponMissileConstruct::SPRITE_SRC = VECTOR2(0, 432);
const VECTOR2 WeaponMissileConstruct::SPRITE_SIZE = VECTOR2(24, 48);

//------------------------------------------------------------------------
//	ミサイルオブジェクトのコンストラクタ	
//
//  引数　なし
//------------------------------------------------------------------------
CWeaponMissileObj::CWeaponMissileObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite, WeaponMissileConstruct::SPRITE_SRC.x, WeaponMissileConstruct::SPRITE_SRC.y,
		WeaponMissileConstruct::SPRITE_SIZE.x, WeaponMissileConstruct::SPRITE_SIZE.y);
	m_nAnimNum = WeaponMissileConstruct::ANIM_NUM;
	m_nAtc = WeaponMissileConstruct::DAMAGE_NUM;
	m_dwOwner = ENM;
	m_bOnce = TRUE;
}

// ---------------------------------------------------------------------------
// ミサイルオブジェクトのデストラクタ
// ---------------------------------------------------------------------------
CWeaponMissileObj::~CWeaponMissileObj()
{
	SAFE_DELETE(m_pSprite);
}

//-----------------------------------------------------------------------------
// ミサイルオブジェクトの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　TRUE
//-----------------------------------------------------------------------------
BOOL	CWeaponMissileObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;

	m_vPos = vPos;	// 発生位置
	m_vPosUp = VECTOR2(0, 0);
	m_vCenter = VECTOR2(0, 0);

	m_bOnce = TRUE;

	return TRUE;
}

//-----------------------------------------------------------------------------
// ミサイルオブジェクトの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CWeaponMissileObj::Update()
{
	if (m_bActive)
	{
		CMapLine* pHitmapline1;
		switch (m_dwStatus)
		{
		case  NORMAL:
			m_pGMain->m_pPcProc->GetPcObjPtr()->Hitcheck(this);
			m_pGMain->m_pRailProc->Hitcheck(this);

			if (Root(m_pGMain->m_pPcProc->GetPcObjPtr()->GetPos(), m_vPos) > WeaponMissileConstruct::HOMING_AREA && m_bOnce) {
				m_vTarget = m_pGMain->m_pPcProc->GetPcObjPtr()->GetPos();
				TargetMove(WeaponMissileConstruct::SPEED);
			}
			else {
				m_bOnce = FALSE;
			}

			if (m_vPos.x - m_pGMain->m_vScroll.x < 0 || m_vPos.x - m_pGMain->m_vScroll.x > WINDOW_WIDTH ||
				m_vPos.y - m_pGMain->m_vScroll.y < 0 || m_vPos.y - m_pGMain->m_vScroll.y > WINDOW_HEIGHT) {	// 画面外へ出たので消去
				m_bActive = FALSE;
			}
			break;

		case  DAMAGE:
			m_pGMain->m_pEffectProc->m_pEffectBomProc->Start(m_vPos);
			m_bActive = FALSE;
			break;
		}

		float rad = std::atan2(m_vPosUp.x, m_vPosUp.y);
		m_fRotate = XMConvertToDegrees(-rad);

		if (m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline1)) {
			m_dwStatus = DAMAGE;
		}

		m_vPos += m_vPosUp;
		AnimCountup();
		Draw();
	}
}