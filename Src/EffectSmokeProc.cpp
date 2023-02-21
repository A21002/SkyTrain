#include "EffectSmokeProc.h"
#include "EffectSmokeObj.h"

//======================================================================
// �f�����ʁE���v���V�[�W��
//======================================================================
// --------------------------------------------------------------------
// �R���X�g���N�^
// --------------------------------------------------------------------
CEffectSmokeProc::CEffectSmokeProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (DWORD i = 0; i < EFFECT_SMOKE_MAX; i++) {
		m_pObjArray.push_back(new CEffectSmokeObj(m_pGMain));
	}
}

// --------------------------------------------------------------------
// ���������̊֐�
// --------------------------------------------------------------------
BOOL	CEffectSmokeProc::Start(VECTOR2 vPos)
{
	BOOL bRet = FALSE;

	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vPos);	// �f�����ʁE���̔���
			bRet = TRUE;
			break;
		}
	}

	return TRUE;
}