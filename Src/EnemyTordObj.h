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

#include "EnemyBalloonObj.h"
//============================================================================
// ���܂̓G�@�I�u�W�F�N�g�N���X
//============================================================================
class CEnmTordObj : public CBaseObj
{
protected:
	float m_fMoveWidth;
	int m_nWaitTime;
	CEnmBalloonObj* m_pBalloonObj;

public:
	BOOL Start(VECTOR2 vPos) override;
	void Update() override;

	// �R���X�g���N�^
	CEnmTordObj(CGameMain* pGMain);
	~CEnmTordObj();
};

//============================================================================
// �萔�N���X
//============================================================================
class EnmTordConstruct
{
public:
	const static int TARGET_WIDTH = 12;
	const static int WAITTIME = 3;
};