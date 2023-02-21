//=============================================================================
//      武器の処理
//=============================================================================

#include "WeaponProc.h"
#include "PlaycharProc.h"
#include "EnemyProc.h"
#include "Effect.h"
#include "MapProc.h"

//=============================================================================================================================
// 武器メインプロシージャのコンストラクタ
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
// ----------------------------------------------------------------------------------------------------------------------------
CWeaponProc::CWeaponProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	m_pWeaponMissileProc = new CWeaponMissileProc(m_pGMain);	// 武器・ミサイルプロシージャ
	m_pProcArray.push_back(m_pWeaponMissileProc);				// プロシージャをプロシージャ配列に登録する
	m_pWeaponCannonProc = new CWeaponCannonProc(m_pGMain);		// 武器・大砲プロシージャ
	m_pProcArray.push_back(m_pWeaponCannonProc);				// プロシージャをプロシージャ配列に登録する
}
