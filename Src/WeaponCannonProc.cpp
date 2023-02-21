#include "WeaponCannonProc.h"
#include "WeaponCannonObj.h"

//------------------------------------------------------------------------
//	大砲プロシージャのコンストラクタ	
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//------------------------------------------------------------------------
CWeaponCannonProc::CWeaponCannonProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// ミサイル
	for (DWORD i = 0; i < WEAPON_CANNON_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponCannonObj(m_pGMain));	// m_pObjArrayに武器・ショットオブジェクトを生成する
	}
	m_nWaitTime = m_nMaxwaitTime = 8;
}

//-----------------------------------------------------------------------------
// 大砲プロシージャの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　正常に発生 : TRUE    発生しなかった : FALSE
//-----------------------------------------------------------------------------
BOOL	CWeaponCannonProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	BOOL bRet = FALSE;

	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vPos, pObj, dwOwner);	// 武器の発生
			m_pGMain->m_pSeHit->Play();
			bRet = TRUE;
			break;
		}
	}
	if (bRet) m_pGMain->m_pSeShot->Play();
	return bRet;
}