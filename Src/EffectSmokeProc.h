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

#define  EFFECT_SMOKE_MAX  1
//======================================================================
// �f�����ʁE���v���V�[�W��
//======================================================================
class CEffectSmokeProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2);

	CEffectSmokeProc(CGameMain* pGMain);
	~CEffectSmokeProc() { ; }
};