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

#define ENM_LAVA_MAX 50

//============================================================================
// Big�n��̓G�@�v���V�[�W���N���X
//============================================================================
class CEnmLavaProc : public CBaseProc
{
protected:
	;

public:
	void   Update() override;

	// �R���X�g���N�^
	CEnmLavaProc(CGameMain* pGMain);
	~CEnmLavaProc() { ; }
};