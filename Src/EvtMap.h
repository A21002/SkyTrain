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

//----------------------------------------------------------------------------
// �C�x���g�}�b�v�N���X�̒�`
// 		���W�o�w���W�A�x���W�p�A�C�x���g�h�c�A�C�x���g�m��(��ނ�_���a��)�A�ėp�J�E���^
//		�C�x���g�h�c�@1:�o�b�̃X�^�[�g�ʒu�@2:�A�C�e���@3:�G
//		�C�x���g�m���@0x01 ��̐�    0x02 ���܂̓G    0x04 �I�I�J�~�̓G
//					�@0x10 �~�}��    0x20 ��
//----------------------------------------------------------------------------
class  CEvtMap
{
public:
	VECTOR2     m_vStart;		// ���W
	int         m_nEvtID;		// �C�x���g�h�c
	DWORD       m_dwEvtNo;		// �C�x���g�m��
	int         m_nCnt1;		// �ėp�J�E���^
public:
	// �R���X�g���N�^
	CEvtMap()
	{
		m_vStart = VECTOR2(0, 0);
		m_nEvtID = 0;
		m_dwEvtNo = 0;
		m_nCnt1 = 0;
	}
	CEvtMap(VECTOR2 vStart, int nEvtID, DWORD dwEvtNo, int nCnt1)
	{
		m_vStart = vStart;
		m_nEvtID = nEvtID;
		m_dwEvtNo = dwEvtNo;
		m_nCnt1 = nCnt1;
	}
};