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

#define  ITEMRESQUE   1           // �~�}��
#define  ITEMDOOR1    2           // �h�A
#define  ITEMDOOR2	  3
#define  ITEMDOOR3	  4
#define  ITEMGOAL	  5
#define  ITEMFIRSTSLOPE 6
#define  ITEMPCDUMMY	7

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