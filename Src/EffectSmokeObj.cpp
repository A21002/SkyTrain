#include "EffectSmokeObj.h"
#include "PlaycharProc.h"

//======================================================================
// �萔�N���X
//======================================================================
const VECTOR2 EffectSmokeConstruct::SPRITE_SRC_RIGHT = VECTOR2(0, 799);
const VECTOR2 EffectSmokeConstruct::SPRITE_SRC_LEFT = VECTOR2(0, 1081);
const VECTOR2 EffectSmokeConstruct::SPRITE_SIZE = VECTOR2(248, 94);

//------------------------------------------------------------------------
//	�f�����ʁE���I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//------------------------------------------------------------------------
CEffectSmokeObj::CEffectSmokeObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite, EffectSmokeConstruct::SPRITE_SRC_RIGHT.x, EffectSmokeConstruct::SPRITE_SRC_RIGHT.y,
		EffectSmokeConstruct::SPRITE_SIZE.x, EffectSmokeConstruct::SPRITE_SIZE.y);
	m_nAnimNum = EffectSmokeConstruct::ANIM_NUM;
}

// ---------------------------------------------------------------------------
// �f�����ʁE���I�u�W�F�N�g�̃f�X�g���N�^
// ---------------------------------------------------------------------------
CEffectSmokeObj::~CEffectSmokeObj()
{
	SAFE_DELETE(m_pSprite);
}

//-----------------------------------------------------------------------------
// �f�����ʁE���I�u�W�F�N�g�̊J�n
//
//   VECTOR2 vPos    �����ʒu
//
//   �߂�l�@�@TRUE
//-----------------------------------------------------------------------------
BOOL	CEffectSmokeObj::Start(VECTOR2 vPos)
{
	m_bActive = TRUE;
	m_dwStatus = NORMAL;
	m_dwStatusSub = STOP;
	m_dwStatusPhase = PHASE_SMOKE_START;
	m_vPos = vPos;	// �����ʒu
	m_nAnimIdx = 1;
	m_nCnt1 = LEFT;

	// �D�J����炷
	m_pGMain->m_pSeDash->Play();
	return TRUE;
}

//-----------------------------------------------------------------------------
// �f�����ʁE���I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CEffectSmokeObj::Update()
{
	if (m_bActive)
	{
		switch (m_dwStatusPhase) {
		case PHASE_SMOKE_START:		// ���o���A�j���[�V����
			if (AnimCountup() == 1)
			{
				// �I����A���[�v��Ԃ֑J��
				m_dwStatusPhase = PHASE_SMOKE_LOOP;
				m_nDirIdx = 1;
			}
			break;

		case PHASE_SMOKE_LOOP:		// �����[�v�A�j���[�V����
			if (AnimCountup() == 1)
			{
				// �ꏄ��A�v���C���[�̑��x���Q�Ƃ��āA�I�����邩���߂�
				if (m_pGMain->m_pPcProc->GetPcObjPtr()->GetSpeed() < 10.0f) {
					m_dwStatusPhase = PHASE_SMOKE_FINISH;
					m_nDirIdx = 2;
				}
			}
			break;

		case PHASE_SMOKE_FINISH:	// ���I���A�j���[�V����
			if (AnimCountup() == 1) {
				m_bActive = false;
			}
			break;
		}

		// �v���C���[�̍��E���]�ɍ��킹�ĉ��𔽓]������
		if (m_pGMain->m_pPcProc->GetPcObjPtr()->GetDirIdx() == RIGHT) {
			m_pSprite->SetSrc(EffectSmokeConstruct::SPRITE_SRC_RIGHT.x, EffectSmokeConstruct::SPRITE_SRC_RIGHT.y,
				EffectSmokeConstruct::SPRITE_SIZE.x, EffectSmokeConstruct::SPRITE_SIZE.y);
			if (m_nCnt1 == RIGHT) {
				m_vPos.x -= EffectSmokeConstruct::DIFF;
				m_nCnt1 = LEFT;
			}
		}
		else if (m_pGMain->m_pPcProc->GetPcObjPtr()->GetDirIdx() == LEFT) {
			m_pSprite->SetSrc(EffectSmokeConstruct::SPRITE_SRC_LEFT.x, EffectSmokeConstruct::SPRITE_SRC_LEFT.y,
				EffectSmokeConstruct::SPRITE_SIZE.x, EffectSmokeConstruct::SPRITE_SIZE.y);
			if (m_nCnt1 == LEFT) {
				m_vPos.x += EffectSmokeConstruct::DIFF;
				m_nCnt1 = RIGHT;
			}
		}

		// �v���C���[�Ɖ�]���Ƒ������𓯊�
		m_fRotate = m_pGMain->m_pPcProc->GetPcObjPtr()->GetRotate();
		m_vPosUp = m_pGMain->m_pPcProc->GetPcObjPtr()->GetPosUp();

		m_vPos += m_vPosUp;
		Draw();
	}
}