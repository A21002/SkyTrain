#include "EffectGoalArrowProc.h"
#include "EffectGoalArrowObj.h"

//============================================================================
// ゴール矢印プロシージャ
//============================================================================
// --------------------------------------------------------------------
// コンストラクタ
// --------------------------------------------------------------------
CEffectGoalArrowProc::CEffectGoalArrowProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (DWORD i = 0; i < EFFECT_GOAL_ARROW_MAX; i++) {
		m_pObjArray.push_back(new CEffectGoalArrowObj(m_pGMain));
	}
}

// --------------------------------------------------------------------
// 発生処理の関数
// --------------------------------------------------------------------
BOOL	CEffectGoalArrowProc::Start(VECTOR2 vPos)
{
	BOOL bRet = FALSE;

	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vPos);	// 映像効果・ゴール矢印の発生
			bRet = TRUE;
			break;
		}
	}

	return TRUE;
}