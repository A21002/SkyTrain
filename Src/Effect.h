//=============================================================================
//		�f�����ʂ̏���
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
#include "XAudio.h"
#include "Dinput.h"
#include "Sprite.h"
#include "EffectBomProc.h"
#include "EffectSmokeProc.h"
#include "EffectGoalArrowProc.h"
#include "ItemProc.h"

// �f�����ʁ@�v���V�[�W���N���X
class CEffectProc : public CBaseProc
{
public:
	CEffectBomProc* m_pEffectBomProc;
	CEffectSmokeProc* m_pEffectSmokeProc;
	CEffectGoalArrowProc* m_pEffectGoalArrowProc;
	CItemProc* m_pItemProc;

public:
	void  SetNonActive();

	CEffectProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CEffectProc() { ; }	// �f�X�g���N�^
};
