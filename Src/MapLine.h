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
// �}�b�v���N���X�̒�`
// 		�n�_���W�o�w���W�A�x���W�p�A�I�_���W�o�w���W�A�x���W�p�E�E�E�E
// 		�@�����W (�J�n�ʒu����I���ʒu�Ɍ������āA��������ɖ@�����o����)
//----------------------------------------------------------------------------
class  CMapLine
{
public:
	VECTOR2 m_vStart;		// �n�_���W
	VECTOR2 m_vEnd;			// �I�_���W
	VECTOR2 m_vNormal;		// �@�����W (�J�n�ʒu����I���ʒu�Ɍ������āA��������ɖ@�����o����)

public:
	// �R���X�g���N�^
	CMapLine()
	{
		m_vStart = VECTOR2(0, 0);
		m_vEnd = VECTOR2(0, 0);
		m_vNormal = VECTOR2(0, 0);
	}
};