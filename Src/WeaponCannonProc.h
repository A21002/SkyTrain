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

#define  WEAPON_CANNON_MAX 200

//======================================================================
// ��C�@�v���V�[�W���N���X
//======================================================================
class CWeaponCannonProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CWeaponCannonProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CWeaponCannonProc() { ; }
};