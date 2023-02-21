#include "EffectGoalArrowProc.h"
#include "EffectGoalArrowObj.h"

//============================================================================
// �S�[�����v���V�[�W��
//============================================================================
// --------------------------------------------------------------------
// �R���X�g���N�^
// --------------------------------------------------------------------
CEffectGoalArrowProc::CEffectGoalArrowProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (DWORD i = 0; i < EFFECT_GOAL_ARROW_MAX; i++) {
		m_pObjArray.push_back(new CEffectGoalArrowObj(m_pGMain));
	}
}

// --------------------------------------------------------------------
// ���������̊֐�
// --------------------------------------------------------------------
BOOL	CEffectGoalArrowProc::Start(VECTOR2 vPos)
{
	BOOL bRet = FALSE;

	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vPos);	// �f�����ʁE�S�[�����̔���
			bRet = TRUE;
			break;
		}
	}

	return TRUE;
}