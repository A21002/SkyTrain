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

#define  ITEM_MAX  100

//======================================================================
// �A�C�e���@�v���V�[�W���N���X
//======================================================================
class CItemProc : public CBaseProc
{
public:
	void Update() override;
	CItemProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CItemProc() { ; }	// �f�X�g���N�^

	// �S�[�����W
	VECTOR2 GetGoalPos();
};