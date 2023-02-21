//=============================================================================
//		敵の処理
//=============================================================================

#include "EnemyProc.h"
#include "WeaponProc.h"
#include "Effect.h"
#include "PlaycharProc.h"
#include "MapProc.h"

//------------------------------------------------------------------------
// 敵メインプロシージャのコンストラクタ
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//------------------------------------------------------------------------
CEnmProc::CEnmProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	m_pEnmLavaProc = new CEnmLavaProc(m_pGMain);
	m_pProcArray.push_back(m_pEnmLavaProc);   // プロシージャをプロシージャ配列に登録する

	m_pEnmTordProc = new CEnmTordProc(m_pGMain);
	m_pProcArray.push_back(m_pEnmTordProc);

	m_pEnmThornProc = new CEnmThornProc(m_pGMain);
	m_pProcArray.push_back(m_pEnmThornProc);

	m_pEnmCannonProc = new CEnmCannonProc(m_pGMain);
	m_pProcArray.push_back(m_pEnmCannonProc);

	m_pEnmBigLavaProc = new CEnmBigLavaProc(m_pGMain);
	m_pProcArray.push_back(m_pEnmBigLavaProc);
}

//============================================================================
//   敵プロシージャとオブジェクトを探索し全てのオブジェクトをノンアクティブにする
//   敵プロシージャの開始フラグをリセットする
//============================================================================
void  CEnmProc::SetNonActive()
{
	// 敵のオブジェクトポインタ配列の探索
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		m_pObjArray[i]->SetActive(FALSE);
	}

	// 下位のプロシージャポインタ配列の探索
	for (DWORD i = 0; i < m_pProcArray.size(); i++)
	{
		m_pProcArray[i]->SetStartFlag(0);				// 開始フラグのリセット
		((CEnmProc*)m_pProcArray[i])->SetNonActive();   // 下位のプロシージャの処理（再帰処理）
	}
}
