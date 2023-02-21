//=============================================================================
//		�G�̏���
//=============================================================================

#include "EnemyProc.h"
#include "WeaponProc.h"
#include "Effect.h"
#include "PlaycharProc.h"
#include "MapProc.h"

//------------------------------------------------------------------------
// �G���C���v���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//------------------------------------------------------------------------
CEnmProc::CEnmProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	m_pEnmLavaProc = new CEnmLavaProc(m_pGMain);
	m_pProcArray.push_back(m_pEnmLavaProc);   // �v���V�[�W�����v���V�[�W���z��ɓo�^����

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
//   �G�v���V�[�W���ƃI�u�W�F�N�g��T�����S�ẴI�u�W�F�N�g���m���A�N�e�B�u�ɂ���
//   �G�v���V�[�W���̊J�n�t���O�����Z�b�g����
//============================================================================
void  CEnmProc::SetNonActive()
{
	// �G�̃I�u�W�F�N�g�|�C���^�z��̒T��
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		m_pObjArray[i]->SetActive(FALSE);
	}

	// ���ʂ̃v���V�[�W���|�C���^�z��̒T��
	for (DWORD i = 0; i < m_pProcArray.size(); i++)
	{
		m_pProcArray[i]->SetStartFlag(0);				// �J�n�t���O�̃��Z�b�g
		((CEnmProc*)m_pProcArray[i])->SetNonActive();   // ���ʂ̃v���V�[�W���̏����i�ċA�����j
	}
}
