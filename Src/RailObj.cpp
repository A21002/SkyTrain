#include "RailObj.h"
#include "RailProc.h"
#include "PlaycharProc.h"

//=========================================================================
// �萔�N���X
//=========================================================================
const VECTOR2 RailConstruct::SPRITE_SRC = VECTOR2(0, 0);
const VECTOR2 RailConstruct::SPRITE_SIZE = VECTOR2(24, 11);

// --------------------------------------------------------------------
// ���[���I�u�W�F�N�g�̃R���X�g���N�^
// --------------------------------------------------------------------
CRailObj::CRailObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageRail, RailConstruct::SPRITE_SRC.x, RailConstruct::SPRITE_SRC.y,
		RailConstruct::SPRITE_SIZE.x, RailConstruct::SPRITE_SIZE.y);
	m_nAnimNum = RailConstruct::ANIM_NUM;
	m_tag = RAIL;
}

// --------------------------------------------------------------------
// ���[���I�u�W�F�N�g�̃f�X�g���N�^
// --------------------------------------------------------------------
CRailObj::~CRailObj()
{
	SAFE_DELETE(m_pSprite);
}

// --------------------------------------------------------------------
// ���[���I�u�W�F�N�g�̊J�n
// 
// VECTOR2 vPos		�����ʒu
// 
// �߂�l	���� : TRUE
// --------------------------------------------------------------------
BOOL CRailObj::Start(VECTOR2 vPos, DWORD dwOwner)
{
	m_bActive = TRUE;
	// �����ʒu
	m_vPos = vPos;

	// �v���V�[�W���̃I�u�W�F�N�g�z����Ŏ��g�����Ԗڂ�
	m_nArrNum = dwOwner;

	// ���g�̌��Ɋ��Ƀ��[������������Ă��邩
	if (m_pGMain->m_pPcProc->GetPcObjPtr()->GetClick()) {
		// ���̃I�u�W�F�N�g�̏I�[�Ɉʒu�����킹�āA���[�����Ȃ����Ă���悤�ɂ���
		m_vPos = m_pGMain->m_pRailProc->GetLinkPos(m_nArrNum, m_vPos);
	}

	// ��]��������ɂ���
	m_vCenter = VECTOR2(0, 0);

	// �I�[�ʒu�̓o�^
	m_pGMain->m_pRailProc->SetLastRightPos(VECTOR2(m_vPos.x + m_pSprite->GetDestWidth(), m_vPos.y), m_nArrNum);
	m_pGMain->m_pRailProc->SetLastLeftPos(VECTOR2(m_vPos.x + m_pSprite->GetDestWidth(), m_vPos.y), m_nArrNum);
	// ���[���̎c������
	m_LimitTime = RailConstruct::LIMIT_TIME;
	// �J�n����
	m_StartTime = clock();

	// �}�E�X�̈ʒu�ɍ��킹�ĉ�]���鏈���̃t���O
	m_isMoveRotate = TRUE;
	// ���g���Ȃ����Ă��郌�[���̏I�[��
	m_isFinishedRail = FALSE;
	// �P�xPC�ƐڐG������ȍ~�A�ڐG������s��Ȃ�
	m_isHit = FALSE;
	return TRUE;
}

// --------------------------------------------------------------------
// ���[���I�u�W�F�N�g�̍X�V
// --------------------------------------------------------------------
void CRailObj::Update()
{
	if (m_bActive)
	{
		// �o�ߎ��Ԃ��擾
		double deltaTime = clock() - m_StartTime;

		// �o�ߎ��Ԃ��c�����Ԃ��z���Ă��邩
		if (m_LimitTime <= deltaTime / CLOCKS_PER_SEC) {
			// ���[���̍폜
			// �Q�[�W����
			m_pGMain->m_pPcProc->GetPcObjPtr()->AddMaterial(10);
			// �ړ�����ۂ̖ڕW�n�_�����Z�b�g
			m_pGMain->m_pRailProc->SetLastRightPos(VECTOR2(-1, -1), m_nArrNum);
			m_pGMain->m_pRailProc->SetLastLeftPos(VECTOR2(-1, -1), m_nArrNum);
			m_bActive = FALSE;
		}

		// PC�Ƃ̐ڐG����
		if (!m_isHit) {
			m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
		}

		// ���̃��[�����������ꂽ���]�������s��Ȃ�
		if (m_pGMain->m_pRailProc->CheckNextObjActive(m_nArrNum + 1)) {
			m_isMoveRotate = FALSE;
		}
		// �N���b�N�������ꂽ��A��]�������s�킸�A���g���Ȃ��������[���̏I�[�Ƃ����������
		if (!m_pGMain->m_pPcProc->GetPcObjPtr()->GetClick() && m_isMoveRotate) {
			m_isMoveRotate = FALSE;
			m_isFinishedRail = TRUE;
		}

		if (m_isMoveRotate) {
			SetRotate();
		}

		Draw();
	}
}

void CRailObj::SetRotate()
{
	// ���[���̉�]����
	CDirectInput* pDI = m_pGMain->m_pDI;	// ���͏����擾

	// �}�E�X�|�C���^�̈ʒu���擾
	VECTOR2 mousePos = VECTOR2(pDI->GetMousePos().x, pDI->GetMousePos().y);
	mousePos += m_pGMain->m_vScroll;

	//arctan�Ń��W�A���p�x���v�Z
	m_fRotate = -std::atan2(m_vPos.y - mousePos.y, mousePos.x - m_vPos.x);
	// ���W�A���p�x��x���ɕϊ�
	m_fRotate = XMConvertToDegrees(m_fRotate);
	double root = std::sqrt(m_pSprite->GetDestWidth() * m_pSprite->GetDestWidth() + m_pSprite->GetDestHeight() * m_pSprite->GetDestHeight());
	// ��]�ɍ��킹�āA�ړ��̍ۂ̖ڕW�n�_���Đݒ�
	m_pGMain->m_pRailProc->SetLastRightPos(VECTOR2(std::cos(XMConvertToRadians(m_fRotate)) * root + m_vPos.x,
		m_vPos.y + std::sin(XMConvertToRadians(m_fRotate)) * root), m_nArrNum);
	m_pGMain->m_pRailProc->SetLastLeftPos(VECTOR2(std::cos(XMConvertToRadians(m_fRotate)) * root + m_vPos.x,
		m_vPos.y + std::sin(XMConvertToRadians(m_fRotate)) * root), m_nArrNum);
}

VECTOR2 CRailObj::GetNextRailPos() {
	VECTOR2 ret = m_vPos;
	DWORD hypo = sqrt(m_pSprite->GetSrcWidth() * m_pSprite->GetSrcWidth() + m_pSprite->GetSrcWidth() * m_pSprite->GetSrcWidth());

	ret.x += std::cos(XMConvertToRadians(m_fRotate)) * m_pSprite->GetSrcWidth();
	ret.y += std::sin(XMConvertToRadians(m_fRotate)) * m_pSprite->GetSrcWidth();

	return ret;
}