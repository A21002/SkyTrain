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

//======================================================================
// �f�����ʁE�S�[�����@�I�u�W�F�N�g�N���X
//======================================================================
class CEffectGoalArrowObj : public CBaseObj
{
protected:
	;

public:
	BOOL Start(VECTOR2) override;

	void Update() override;

	// �R���X�g���N�^
	CEffectGoalArrowObj(CGameMain* pGMain);
	~CEffectGoalArrowObj();
};

//======================================================================
// �萔�N���X
//======================================================================
class EffectGoalArrowConstruct
{
public:
	static const int ANIM_NUM = 1;

	static const float FLASH_SECOND;

	static const VECTOR2 SPRITE_SRC;
	static const VECTOR2 SPRITE_SIZE;
};