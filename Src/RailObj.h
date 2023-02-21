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

//=========================================================================
// ���[���@�I�u�W�F�N�g�N���X
//=========================================================================
class CRailObj : public CBaseObj
{
protected:
	double m_LimitTime;
	double m_StartTime;
	BOOL   m_isMoveRotate;

public:
	VECTOR2 GetNextRailPos() override;

	BOOL Start(VECTOR2, DWORD) override;

	void Update() override;

	void SetRotate();

	CRailObj(CGameMain* pGMain);	// �R���X�g���N�^
	~CRailObj();					// �f�X�g���N�^
};

//=========================================================================
// �萔�N���X
//=========================================================================
class RailConstruct
{
public:
	static const int ANIM_NUM = 1;
	static const int LIMIT_TIME = 3;

	static const VECTOR2 SPRITE_SRC;
	static const VECTOR2 SPRITE_SIZE;
};