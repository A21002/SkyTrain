#include "EffectBomProc.h"
#include "EffectBomObj.h"

//------------------------------------------------------------------------
//	映像効果・爆発プロシージャのコンストラクタ	
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//------------------------------------------------------------------------
CEffectBomProc::CEffectBomProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (DWORD i = 0; i < EFFECT_BOM_MAX; i++)
	{
		m_pObjArray.push_back(new CEffectBomObj(m_pGMain));	// m_pObjArrayに映像効果・爆発オブジェクトを生成する
	}
}

//-----------------------------------------------------------------------------
// 映像効果・爆発プロシージャの開始
//
//   VECTOR2 vPos    発生位置
//
//   戻り値　　正常に発生 : TRUE    発生しなかった : FALSE
//-----------------------------------------------------------------------------
BOOL	CEffectBomProc::Start(VECTOR2 vPos)
{
	BOOL bRet = FALSE;

	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vPos);	// 映像効果・爆発の発生
			bRet = TRUE;
			break;
		}
	}

	return TRUE;
}