//=============================================================================
//		�f�����ʂ̏���
//=============================================================================
#include "Effect.h"
#include "EnemyProc.h"
#include "PlaycharProc.h"
#include "MapProc.h"
#include "ForeProc.h"

//------------------------------------------------------------------------
//	�f�����ʃ��C���v���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//------------------------------------------------------------------------
CEffectProc::CEffectProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	m_pEffectBomProc = new CEffectBomProc(m_pGMain);	// �f�����ʁE�����v���V�[�W��
	m_pProcArray.push_back(m_pEffectBomProc);			// �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pEffectSmokeProc = new CEffectSmokeProc(m_pGMain);//�f�����ʁE���v���V�[�W��
	m_pProcArray.push_back(m_pEffectSmokeProc);			// �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pEffectGoalArrowProc = new CEffectGoalArrowProc(m_pGMain);	// �f�����ʁE�S�[�����������v���V�[�W��
	m_pProcArray.push_back(m_pEffectGoalArrowProc);					// �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pItemProc = new CItemProc(m_pGMain);				// �A�C�e���v���V�[�W��
	m_pProcArray.push_back(m_pItemProc);				// �v���V�[�W�����v���V�[�W���z��ɓo�^����
}

//------------------------------------------------------------------------
//   �v���V�[�W���ƃI�u�W�F�N�g��T�����S�ẴI�u�W�F�N�g���m���A�N�e�B�u�ɂ���
//   �v���V�[�W���̊J�n�t���O�����Z�b�g����
//------------------------------------------------------------------------
void  CEffectProc::SetNonActive()
{
	//�I�u�W�F�N�g�|�C���^�z��̒T��
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		m_pObjArray[i]->SetActive(FALSE);
	}

	// ���ʂ̃v���V�[�W���|�C���^�z��̒T��
	for (DWORD i = 0; i < m_pProcArray.size(); i++)
	{
		m_pProcArray[i]->SetStartFlag(0);				// �J�n�t���O�̃��Z�b�g
		((CEffectProc*)m_pProcArray[i])->SetNonActive();      // ���ʂ̃v���V�[�W���̏����i�ċA�����j
	}
}