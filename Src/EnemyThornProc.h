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
#include "XAudio.h"
#include "Dinput.h"
#include "Sprite.h"

#define  ENM_THORN_MAX  20

//============================================================================
// �n���Z���{���̓G�@�v���V�[�W���N���X
//============================================================================
class CEnmThornProc : public CBaseProc
{
protected:
	;

public:
	void   Update() override;

	// �R���X�g���N�^
	CEnmThornProc(CGameMain* pGMain);
	~CEnmThornProc() { ; }
};