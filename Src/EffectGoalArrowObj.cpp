#include "EffectGoalArrowObj.h"

//======================================================================
// �萔�N���X
//======================================================================
const VECTOR2 EffectGoalArrowConstruct::SPRITE_SRC = VECTOR2(200, 400);
const VECTOR2 EffectGoalArrowConstruct::SPRITE_SIZE = VECTOR2(95, 88);
const float EffectGoalArrowConstruct::FLASH_SECOND = 0.5f;

//------------------------------------------------------------------------
//	�f�����ʁE�S�[�����I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//------------------------------------------------------------------------
CEffectGoalArrowObj::CEffectGoalArrowObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageChar, EffectGoalArrowConstruct::SPRITE_SRC.x, EffectGoalArrowConstruct::SPRITE_SRC.y,
		EffectGoalArrowConstruct::SPRITE_SIZE.x, EffectGoalArrowConstruct::SPRITE_SIZE.y);
	m_nAnimNum = EffectGoalArrowConstruct::ANIM_NUM;
}

// ---------------------------------------------------------------------------
// �f�����ʁE�S�[�����I�u�W�F�N�g�̃f�X�g���N�^
// ---------------------------------------------------------------------------
CEffectGoalArrowObj::~CEffectGoalArrowObj()
{
	SAFE_DELETE(m_pSprite);
}

//-----------------------------------------------------------------------------
// �f�����ʁE�S�[�����I�u�W�F�N�g�̊J�n
//
//   VECTOR2 vPos    �����ʒu
//
//   �߂�l�@�@TRUE
//-----------------------------------------------------------------------------
BOOL	CEffectGoalArrowObj::Start(VECTOR2 vPos)
{
	m_bActive = TRUE;
	m_vPos = vPos;	// �����ʒu
	m_nCnt1 = 60 * EffectGoalArrowConstruct::FLASH_SECOND;
	return TRUE;
}

//-----------------------------------------------------------------------------
// �f�����ʁE�S�[�����I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CEffectGoalArrowObj::Update()
{
	if (m_bActive)
	{
		if (m_nCnt1 >= 0) {
			Draw();
		}
		else if (m_nCnt1 <= -1 * 60 * EffectGoalArrowConstruct::FLASH_SECOND) {
			m_nCnt1 = 60 * EffectGoalArrowConstruct::FLASH_SECOND;
		}
		m_nCnt1--;
	}
}