#include "EffectBomProc.h"
#include "EffectBomObj.h"

//------------------------------------------------------------------------
//	�f�����ʁE�����v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//------------------------------------------------------------------------
CEffectBomProc::CEffectBomProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (DWORD i = 0; i < EFFECT_BOM_MAX; i++)
	{
		m_pObjArray.push_back(new CEffectBomObj(m_pGMain));	// m_pObjArray�ɉf�����ʁE�����I�u�W�F�N�g�𐶐�����
	}
}

//-----------------------------------------------------------------------------
// �f�����ʁE�����v���V�[�W���̊J�n
//
//   VECTOR2 vPos    �����ʒu
//
//   �߂�l�@�@����ɔ��� : TRUE    �������Ȃ����� : FALSE
//-----------------------------------------------------------------------------
BOOL	CEffectBomProc::Start(VECTOR2 vPos)
{
	BOOL bRet = FALSE;

	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vPos);	// �f�����ʁE�����̔���
			bRet = TRUE;
			break;
		}
	}

	return TRUE;
}