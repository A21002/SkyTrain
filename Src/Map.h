#pragma once

//�x����\��
#pragma warning(disable : 4005)
#pragma warning(disable : 4244)
#pragma warning(disable : 4018)

//�w�b�_�[�t�@�C���̃C���N���[�h
#include <stdio.h>
#include <windows.h>
#include <vector>

#include "Main.h"
#include "Direct3D.h"
#include "XAudio.h"
#include "Dinput.h"
#include "Sprite.h"

#include "MapLine.h"
#include "EvtMap.h"

class CGameMain;
//----------------------------------------------------------------------------
// �}�b�v�z��N���X�̒�`
//----------------------------------------------------------------------------
class  CMap
{
public:
	CGameMain* m_pGMain;
	TCHAR                    m_MapFileName[512]; // �}�b�v�t�@�C����  
	TCHAR                    m_ImageName[512];  // �}�b�v�`�b�v�C���[�W�t�@�C����
	CSpriteImage* m_pMapImage;       // �}�b�v�`�b�v�̃X�v���C�g�C���[�W
	int                      m_nMapX;           // ��ʂ̕��@�i�}�b�v�`�b�v���������j
	int                      m_nMapY;           // ��ʂ̍����i�}�b�v�`�b�v���������j
	int                      m_nMapchipWidth;   // ��̃}�b�v�`�b�v�̕�
	int                      m_nMapchipHeight;  // ��̃}�b�v�`�b�v�̍���
	int                      m_nMapLnLength;    // �}�b�v���C���z��̗v�f��
	int                      m_nEvtMapLength;   // �C�x���g�}�b�v�z��̗v�f��
	int* m_MapBakTbl;	    // �}�b�v�z��@�w�i
	int* m_MapForTbl;	    // �}�b�v�z��@�O�i
	CMapLine* m_MapLn;		    // �}�b�v���C���z��
	CEvtMap* m_EvtMap;		    // �C�x���g�}�b�v�z��

public:
	// �R���X�g���N�^
	CMap(CGameMain* pGMain);
	void InitMap();
	BOOL  MakeERelativeFName(TCHAR* szBaseFullPath, TCHAR* szPath, TCHAR* szERelativeFName);

	~CMap();
};