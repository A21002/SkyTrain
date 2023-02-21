//=============================================================================
//		�O�i�E��i����
//=============================================================================
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

#define FORE_GAMEMAIN 1
#define FORE_GAMECLEAR 2
#define FORE_GAMEOVER 3
#define FORE_CLICK_BUTTON 4
#define FORE_BLACKOUT 5

//======================================================================
// �o�b�N�N���E���h�@�v���V�[�W���N���X
//======================================================================
class CBackProc
{
protected:
	CGameMain* m_pGMain;
	CSpriteImage* m_pImageBk;
	CSprite* m_pBackgrd;
	VECTOR2			m_vScroll;
};

//======================================================================
// �t�H�A�N���E���h�@�v���V�[�W���N���X
// (����)��{�v���V�[�W���N���X�͌p�����Ă��Ȃ�
//======================================================================
class CForeProc
{
protected:
	CGameMain* m_pGMain;
	CSprite* m_pForegrd;
	DWORD			m_dwStatusPhase;
	DWORD			m_dwPushButton;

public:
	void Update();		// �X�V����

	void GameUI();		// �Q�[��UI�̕\��
	BOOL ClearUI();		// �N���A�����A�{�^���̕\��
	BOOL OverUI();		// �Q�[���I�[�o�[�����A�{�^���̕\��
	BOOL CheckMousePos(int, int, int, int);

	// �A�N�Z�X�֐�
	void SetPhase(DWORD phase);
	DWORD GetPhase();

	CForeProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CForeProc();

};
