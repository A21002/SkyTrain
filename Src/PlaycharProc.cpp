#include "PlaycharProc.h"

//------------------------------------------------------------------------
//	�o�b�v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//------------------------------------------------------------------------
CPcProc::CPcProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	m_pObjArray.push_back(new CPcObj(m_pGMain));  // m_pObjArray�ɃI�u�W�F�N�g��o�^����

	m_nPcNum = 2;
}