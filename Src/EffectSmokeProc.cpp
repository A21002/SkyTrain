#include "EffectSmokeProc.h"
#include "EffectSmokeObj.h"

//======================================================================
// 映像効果・煙プロシージャ
//======================================================================
// --------------------------------------------------------------------
// コンストラクタ
// --------------------------------------------------------------------
CEffectSmokeProc::CEffectSmokeProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (DWORD i = 0; i < EFFECT_SMOKE_MAX; i++) {
		m_pObjArray.push_back(new CEffectSmokeObj(m_pGMain));
	}
}

// --------------------------------------------------------------------
// 発生処理の関数
// --------------------------------------------------------------------
BOOL	CEffectSmokeProc::Start(VECTOR2 vPos)
{
	BOOL bRet = FALSE;

	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vPos);	// 映像効果・煙の発生
			bRet = TRUE;
			break;
		}
	}

	return TRUE;
}