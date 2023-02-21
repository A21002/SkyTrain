//=============================================================================
//		��{�v���V�[�W���E��{�I�u�W�F�N�g�N���X����
//=============================================================================
#pragma once
#include "GameMain.h"
#include "BaseObj.h"

class CSprite;
class CGameMain;
class CBaseObj;

// --------------------------------------------------------------------------------------------------
// ��{�v���V�[�W���N���X
//
//   ���@�v���V�[�W���Ƃ́A�u�����̏�������ɂ܂Ƃ߂����́v�Ƃ����Ӗ�
//       �����̃I�u�W�F�N�g�≺�ʃv���V�[�W�����R���g���[������N���X�̂���
// --------------------------------------------------------------------------------------------------
class  CBaseProc
{
protected:
	CGameMain* m_pGMain;				// �Q�[�����C���N���X

	// ���ʂ̃v���V�[�W���|�C���^�z��́A�v���V�[�W�����K�w�\���ɂ��ĊǗ�����Ƃ��Ɏg�p����
	// �I�u�W�F�N�g�|�C���^�z��́A�v���V�[�W���̒��ɃI�u�W�F�N�g��z�u���ĊǗ�����Ƃ��Ɏg�p����
	// ��ʓI�ɂ́A�ǂ��炩�Е��݂̂��g�p���邱��
	std::vector<CBaseProc*>  m_pProcArray;  // ���ʂ̃v���V�[�W���|�C���^�z��
	std::vector<CBaseObj*>   m_pObjArray;	// �I�u�W�F�N�g�|�C���^�z��

	int				m_nMaxwaitTime;		// �ő�҂�����
	int				m_nWaitTime;		// ���݂̑҂�����
	int				m_nStartFlag;		// �J�n�t���O

public:
	// �S�̍X�V�����i�S�Ẵv���V�[�W����I�u�W�F�N�g��ǂ݉����čX�V����������j
	virtual void	UpdateAll() final;

	// �X�V�����iUpdateAll()�̒��ŋN���B�v���V�[�W���̍X�V�����j
	virtual void    Update() { ; }

	// �����蔻��i�S�Ẵv���V�[�W����I�u�W�F�N�g��ǂ݉����ď���������j
	virtual BOOL	Hitcheck(CBaseObj*) final;

	// �A�N�Z�X�֐�
	std::vector<CBaseProc*> GetProcArrayPtr() { return m_pProcArray; } // ���ʂ̃v���V�[�W���|�C���^�z��̃A�h���X��Ԃ�
	std::vector<CBaseObj*>  GetObjArrayPtr() { return m_pObjArray; }  // �I�u�W�F�N�g�|�C���^�z��̃A�h���X��Ԃ�

	int GetStartFlag() { return m_nStartFlag; }
	void SetStartFlag(int nFlg) { m_nStartFlag = nFlg; }

	// �R���X�g���N�^�i��{�v���V�[�W���̏������j
	CBaseProc(CGameMain* pGMain) {
		m_pGMain = pGMain;		// �Q�[�����C���N���X
		m_nMaxwaitTime = 0;		// �ő�҂�����
		m_nWaitTime = 0;		// ���݂̑҂�����
		m_nStartFlag = 0;		// �J�n�t���O
	}
	// �f�X�g���N�^�i�v���V�[�W���ƃI�u�W�F�N�g�̉���j
	virtual         ~CBaseProc();

};