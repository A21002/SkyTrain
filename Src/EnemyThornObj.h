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
// �n���Z���{���̓G�@�I�u�W�F�N�g�N���X
//============================================================================
class CEnmThornObj : public CBaseObj
{
protected:
	int m_nWaitTime;
public:
	BOOL Start(VECTOR2 vPos) override;
	void Update() override;

	// �R���X�g���N�^
	CEnmThornObj(CGameMain* pGMain);
	~CEnmThornObj();
};