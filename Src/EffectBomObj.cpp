#include "EffectBomObj.h"

//============================================================================
// �萔��`
//============================================================================
const VECTOR2 EffectBomConstruct::SPRITE_SRC = VECTOR2(144, 480);
const VECTOR2 EffectBomConstruct::SPRITE_SIZE = VECTOR2(64, 64);

//------------------------------------------------------------------------
//	�f�����ʁE�����I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//------------------------------------------------------------------------
CEffectBomObj::CEffectBomObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite, EffectBomConstruct::SPRITE_SRC.x, EffectBomConstruct::SPRITE_SRC.y,
		EffectBomConstruct::SPRITE_SIZE.x, EffectBomConstruct::SPRITE_SIZE.y);
	m_nAnimNum = EffectBomConstruct::ANIM_NUM;
}

// ---------------------------------------------------------------------------
// �f�����ʁE�����I�u�W�F�N�g�̃f�X�g���N�^
// ---------------------------------------------------------------------------
CEffectBomObj::~CEffectBomObj()
{
	SAFE_DELETE(m_pSprite);
}

//-----------------------------------------------------------------------------
// �f�����ʁE�����I�u�W�F�N�g�̊J�n
//
//   VECTOR2 vPos    �����ʒu
//
//   �߂�l�@�@TRUE
//-----------------------------------------------------------------------------
BOOL	CEffectBomObj::Start(VECTOR2 vPos)
{
	m_bActive = TRUE;
	m_dwStatus = NORMAL;
	m_dwStatusSub = STOP;
	m_dwStatusPhase = 0;
	m_vPos = vPos;	// �����ʒu
	m_nAnimIdx = 0;

	return TRUE;
}

//-----------------------------------------------------------------------------
// �f�����ʁE�����I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CEffectBomObj::Update()
{
	if (m_bActive)
	{
		if (AnimCountup() == 1)
		{
			// �A�j���[�V�����I��
			m_bActive = FALSE;
		}
		Draw();
	}
}