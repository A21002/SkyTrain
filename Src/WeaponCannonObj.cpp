#include "WeaponCannonObj.h"
#include "MapProc.h"
#include "PlaycharProc.h"

//======================================================================
// 定数クラス
//======================================================================
const VECTOR2 WeaponCannonConstruct::SPRITE_SRC = VECTOR2(48, 432);
const VECTOR2 WeaponCannonConstruct::SPRITE_SIZE = VECTOR2(36, 35);

//------------------------------------------------------------------------
//	大砲オブジェクトのコンストラクタ	
//
//  引数　なし
//------------------------------------------------------------------------
CWeaponCannonObj::CWeaponCannonObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite, WeaponCannonConstruct::SPRITE_SRC.x, WeaponCannonConstruct::SPRITE_SRC.y,
		WeaponCannonConstruct::SPRITE_SIZE.x, WeaponCannonConstruct::SPRITE_SIZE.y);
	m_nAnimNum = WeaponCannonConstruct::ANIM_NUM;
	m_nAtc = WeaponCannonConstruct::DAMAGE_NUM;
}

// ---------------------------------------------------------------------------
// 大砲オブジェクトのデストラクタ
// ---------------------------------------------------------------------------
CWeaponCannonObj::~CWeaponCannonObj()
{
	SAFE_DELETE(m_pSprite);
}

//-----------------------------------------------------------------------------
// 大砲オブジェクトの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　TRUE
//-----------------------------------------------------------------------------
BOOL	CWeaponCannonObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();

	m_vPos = vPos;	// 発生位置
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
// ミサイルオブジェクトの更新
//
//   引数　　　なし
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