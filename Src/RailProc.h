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

#define RAIL_MAX 120

//=========================================================================
// ���[���@�v���V�[�W���N���X
//=========================================================================
class CRailProc : public CBaseProc
{
protected:
	VECTOR2 m_vLastRightPos[RAIL_MAX];
	VECTOR2 m_vLastLeftPos[RAIL_MAX];
	int     m_nGenerationId;

public:
	BOOL Start(VECTOR2 vPos);
	BOOL CheckNextObjActive(DWORD i);
	VECTOR2 GetLinkPos(DWORD i, VECTOR2 pos);
	FLOAT GetObjRotate(DWORD i, CBaseObj* pObj);
	VECTOR2 GetNewRailPos();

	CRailProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CRailProc() { ; }				// �f�X�g���N�^

	// �A�N�Z�X�֐�
	void SetLastRightPos(VECTOR2 pos, DWORD i);
	void SetLastLeftPos(VECTOR2 pos, DWORD i);
	VECTOR2 GetLastPos(DWORD i, CBaseObj* pObj);
};