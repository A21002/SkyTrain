//=============================================================================
//		�Q�[�����C������
//=============================================================================

#pragma once

//�x����\��
#pragma warning(disable : 4005)
#pragma warning(disable : 4244)
#pragma warning(disable : 4018)

//�w�b�_�[�t�@�C���̃C���N���[�h
#include <stdio.h>
#include <windows.h>
#include <vector>
#include <time.h>
#include <cmath>

#include "Main.h"
#include "Direct3D.h"
#include "XAudio.h"
#include "Shader.h"
#include "Dinput.h"
#include "Sprite.h"
#include "BaseProc.h"
#include "BaseObj.h"

// �X�e�[�^�X�^�C�v
#define  NONE				0x00000000
#define  TITLE				0x00000001
#define  STAGESELECT  		0x00000002
#define  GAMEMAIN			0x00000004
#define  GAMEOVER			0x00000008
#define  GAMECLEAR			0x00000010
#define  GAMEEND			0x00000020

#define  NORMAL				0x00000001
#define  STANBY				0x00000002
#define  CATCH				0x00000004
#define  ATTACK				0x00000008
#define  DAMAGE				0x00000010
#define  DEAD				0x00000020
#define  FLASH				0x00000040
#define  WALK				0x00000080
#define  JUMP				0x00000100
#define  RAND				0x00000200
#define  STOP				0x00000400
#define  BALLOON			0x00000800

// �X�e�[�^�X�T�u
#define  ATTACKNONE			0x00000001
#define  ATTACKMOVE			0x00000002
#define  ATTACKLASER		0x00000004
#define  ATTACKCANNON		0x00000008
#define  ATTACKBOM			0x00000010
#define  ATTACKEARTH		0x00000020

// �I�u�W�F�N�g�敪
#define  PC					0x00000001
#define  NPC				0x00000002
#define  ENM				0x00000004
#define  ITEM				0x00000008
#define  RAIL				0x00000010
#define  FALL               0x00000020
#define  BIGLAVA			0x00000040

// �����iDirIdx�j
#define  RIGHT				0
#define  LEFT				1

#define  GRAVITY  9.8

class CMain;
class CShader;
class CSpriteImage;
class CSprite;
class CFontTexture;
class CBaseObj;
class CBaseProc;
class CPcProc;
class CEnmProc;
class CWeaponProc;
class CEffectProc;
class CRailProc;
class CForeProc;
class CMapProc;
class CTitleProc;
class CBaseProc;

// --------------------------------------------------------------------------------------------------
//  �Q�[�����C���N���X
// --------------------------------------------------------------------------------------------------
class CGameMain
{
public:
	// �����o�ϐ�
	CMain* m_pMain;		// ���C���N���X
	CDirect3D* m_pD3D;			//	Direct3D�I�u�W�F�N�g
	CXAudio* m_pXAudio;		//	XAudio�I�u�W�F�N�g
	CDirectInput* m_pDI;			//	DirectInputD�I�u�W�F�N�g
	CShader* m_pShader;		//	�V�F�[�_�[
	CFontTexture* m_pFont;		//	�t�H���g�e�N�X�`���[

	DWORD			m_dwGameStatus;
	DWORD           m_dwGameMode;
	VECTOR2			m_vScroll;
	BOOL			m_bIsFadeOut;

	// �v���V�[�W��
	CPcProc* m_pPcProc;
	CEnmProc* m_pEnmProc;
	CWeaponProc* m_pWeaponProc;
	CEffectProc* m_pEffectProc;
	CRailProc* m_pRailProc;
	CForeProc* m_pForeProc;
	CMapProc* m_pMapProc;
	CTitleProc* m_pTitleProc;


	// �T�E���h
	CXAudioSource* m_pSeStart;
	CXAudioSource* m_pSeHit;
	CXAudioSource* m_pSePower;
	CXAudioSource* m_pSeShot;
	CXAudioSource* m_pSeDash;
	CXAudioSource* m_pBgmTitleSelect;
	CXAudioSource* m_pBgmMap1;
	CXAudioSource* m_pBgmMap2;
	CXAudioSource* m_pSeClear;
	CXAudioSource* m_pSeGameOver;

	// �X�v���C�g
	CSpriteImage* m_pImageChar;
	CSpriteImage* m_pImageSprite;
	CSpriteImage* m_pImageRail;
	CSpriteImage* m_pImageSky;
	CSpriteImage* m_pImageCave;
	CSpriteImage* m_pImageLava;
	CSpriteImage* m_pImageUI;


public:
	// ���\�b�h
	CGameMain(CMain* pMain);
	~CGameMain();

	HRESULT Init();
	void    Loop();
	void    GameMain();
	void    Quit();
	void    Fade();

	HRESULT ChangeScreenMode(int nMode = -1);    // -- 2020.1.15
};
