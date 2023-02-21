//=============================================================================
//		映像効果の処理
//=============================================================================
#include "Effect.h"
#include "EnemyProc.h"
#include "PlaycharProc.h"
#include "MapProc.h"
#include "ForeProc.h"

//------------------------------------------------------------------------
//	映像効果メインプロシージャのコンストラクタ
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//------------------------------------------------------------------------
CEffectProc::CEffectProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	m_pEffectBomProc = new CEffectBomProc(m_pGMain);	// 映像効果・爆発プロシージャ
	m_pProcArray.push_back(m_pEffectBomProc);			// プロシージャをプロシージャ配列に登録する

	m_pEffectSmokeProc = new CEffectSmokeProc(m_pGMain);//映像効果・煙プロシージャ
	m_pProcArray.push_back(m_pEffectSmokeProc);			// プロシージャをプロシージャ配列に登録する

	m_pEffectGoalArrowProc = new CEffectGoalArrowProc(m_pGMain);	// 映像効果・ゴールを示す矢印プロシージャ
	m_pProcArray.push_back(m_pEffectGoalArrowProc);					// プロシージャをプロシージャ配列に登録する

	m_pItemProc = new CItemProc(m_pGMain);				// アイテムプロシージャ
	m_pProcArray.push_back(m_pItemProc);				// プロシージャをプロシージャ配列に登録する
}

//------------------------------------------------------------------------
//   プロシージャとオブジェクトを探索し全てのオブジェクトをノンアクティブにする
//   プロシージャの開始フラグをリセットする
//------------------------------------------------------------------------
void  CEffectProc::SetNonActive()
{
	//オブジェクトポインタ配列の探索
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		m_pObjArray[i]->SetActive(FALSE);
	}

	// 下位のプロシージャポインタ配列の探索
	for (DWORD i = 0; i < m_pProcArray.size(); i++)
	{
		m_pProcArray[i]->SetStartFlag(0);				// 開始フラグのリセット
		((CEffectProc*)m_pProcArray[i])->SetNonActive();      // 下位のプロシージャの処理（再帰処理）
	}
}