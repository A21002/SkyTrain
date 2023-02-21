//=============================================================================
//		�G�̏���
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

#include "EnemyLavaProc.h"
#include "EnemyTordProc.h"
#include "EnemyThornProc.h"
#include "EnemyCannonProc.h"
#include "EnemyBigLavaProc.h"

//======================================================================
// �G�L�����N�^�[�S�̂̃��C���v���V�[�W���N���X
//======================================================================
class CEnmProc : public CBaseProc
{
public:
	CEnmLavaProc* m_pEnmLavaProc;
	CEnmTordProc* m_pEnmTordProc;
	CEnmThornProc* m_pEnmThornProc;
	CEnmCannonProc* m_pEnmCannonProc;
	CEnmBigLavaProc* m_pEnmBigLavaProc;

public:
	void  SetNonActive();
	CEnmProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CEnmProc() { ; }
};

