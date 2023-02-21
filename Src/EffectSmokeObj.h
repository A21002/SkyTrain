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

#define PHASE_SMOKE_START 1
#define PHASE_SMOKE_LOOP 2
#define PHASE_SMOKE_FINISH 4

//======================================================================
// �f�����ʁE���@�I�u�W�F�N�g�N���X
//======================================================================
class CEffectSmokeObj : public CBaseObj
{
protected:
	;

public:
	BOOL Start(VECTOR2) override;

	void Update() override;

	// �R���X�g���N�^
	CEffectSmokeObj(CGameMain* pGMain);
	~CEffectSmokeObj();
};

//======================================================================
// �萔�N���X
//======================================================================
class EffectSmokeConstruct
{
public:
	static const int ANIM_NUM = 5;
	static const int DIFF = 155;

	static const VECTOR2 SPRITE_SRC_RIGHT;
	static const VECTOR2 SPRITE_SRC_LEFT;
	static const VECTOR2 SPRITE_SIZE;
};