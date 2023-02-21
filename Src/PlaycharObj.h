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
// �v���C�L�����N�^�[�@�I�u�W�F�N�g�N���X
class CPcObj : public CBaseObj
{
protected:
	int  m_nOldStatusSub;
	VECTOR2 m_vOldRailPos;
	VECTOR2 m_vRailPos;
	BOOL m_isFirstClick;
	BOOL m_bFirstFlag;					// �ŏ��̍��o�������̔���t���O
	BOOL m_bCollisionGroundFirst;		// �n�ʂɐG�ꂽ�ŏ��ɂ̂݁A���s���邽�߂̃t���O

public:
	void Update() override;
	BOOL Start(VECTOR2 vPos) override;
	void NormalUpdate();
	void MovieCamera();
	void AddMaterial(int material);

	BOOL m_bMovieFlag;
	BOOL m_bLavaStartFlag;
	BOOL m_bOnce;

	// �A�N�Z�X�֐�
	BOOL GetClick() { return m_isFirstClick; }

	// �R���X�g���N�^�i�I�u�W�F�N�g�̏������j
	CPcObj(CGameMain* pGMain);
	~CPcObj();
};