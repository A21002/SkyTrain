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

//============================================================================
// ��C�̓G�@�I�u�W�F�N�g�N���X
//============================================================================
class CEnmCannonObj : public CBaseObj
{
protected:
	int m_nWaitTime;

public:
	BOOL Start(VECTOR2 vPos, DWORD dwOwner) override;
	void Update() override;

	// �R���X�g���N�^
	CEnmCannonObj(CGameMain* pGMain);
	~CEnmCannonObj();
};