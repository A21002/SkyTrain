#pragma once
//=============================================================================
//		�v���C�L�����N�^�[�̏���
//=============================================================================

#pragma once

//�x����\��
#pragma warning(disable : 4005)
#pragma warning(disable : 4244)
#pragma warning(disable : 4018)

//�w�b�_�[�t�@�C���̃C���N���[�h
#include <stdio.h>
#include <windows.h>

#include "Main.h"
#include "Direct3D.h"
#include "Sprite.h"
#include "PlaycharObj.h"

//======================================================================
// �v���C�L�����N�^�[�@�v���V�[�W���N���X
class CPcProc : public CBaseProc
{
protected:
	int             m_nPcNum;

public:
	// �A�N�Z�X�֐�
	CPcObj* GetPcObjPtr() { return (CPcObj*)GetObjArrayPtr()[0]; }
	int				    GetPcNum() { return m_nPcNum; }
	void				AddPcNum(int Num) { m_nPcNum += Num; }

	CPcProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CPcProc() { ; }
};