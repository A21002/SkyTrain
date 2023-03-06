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

#define  ITEMRESQUE		1           // �~�}��
#define  ITEMGOAL		2
#define  ITEMFIRSTSLOPE	3
#define  ITEMPCDUMMY	4

//======================================================================
// �A�C�e���@�I�u�W�F�N�g�N���X
//======================================================================
class CItemObj : public CBaseObj
{
protected:
	;

public:
	BOOL Start(VECTOR2, DWORD) override;

	void Update() override;

	// �R���X�g���N�^
	CItemObj(CGameMain* pGMain);
	~CItemObj();
};

//======================================================================
// �萔�N���X
//======================================================================
class ItemConstruct
{
public:
	static const int IMAGE_RESQUE_WIDTH = 48;
	static const int IMAGE_RESQUE_HEIGHT = 48;
	static const int IMAGE_GOAL_WIDTH = 188;
	static const int IMAGE_GOAL_HEIGHT = 100;
};