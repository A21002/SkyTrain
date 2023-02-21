#include "PlaycharObj.h"
#include "MapProc.h"
#include "RailProc.h"
#include "ForeProc.h"
#include "Effect.h"

//------------------------------------------------------------------------
//	�o�b�I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@CGameMain* pGMain
//------------------------------------------------------------------------
CPcObj::CPcObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageChar, 0, 192, 93, 48);	// �X�v���C�g�̈ʒu
	m_vPos = VECTOR2(0, 0);
	ResetStatus();
	ResetAnim();
	m_bActive = TRUE;
	m_nDirIdx = RIGHT;
	m_vCenter = VECTOR2(0, 0);											// ��]�̒��S�_
	m_nAnimNum = 1;
	m_vOldRailPos = VECTOR2(0, 0);										// �ȑO�ݒu�������[���̈ʒu
	m_vRailPos = VECTOR2(0, 0);											// �ݒu���郌�[���̈ʒu
	m_vPosUp = VECTOR2(0, 0);
	m_vTarget = VECTOR2(0, 0);
	m_isFirstClick = FALSE;
	m_isTouchRail = FALSE;
	m_bFirstFlag = TRUE;
	m_bMovieFlag = TRUE;
	m_bCollisionGroundFirst = FALSE;
	m_bOnce = FALSE;
	SetStatus(_T("Data/Script/StatusPC.csv"));
}

// ---------------------------------------------------------------------------
// �o�b�I�u�W�F�N�g�̃f�X�g���N�^
// ---------------------------------------------------------------------------
CPcObj::~CPcObj()
{
	SAFE_DELETE(m_pSprite);
}

//-----------------------------------------------------------------------------
// �o�b�I�u�W�F�N�g�̃X�^�[�g
//
//   �����@�@�@����FTRUE�@�ُ�FFALSE
//-----------------------------------------------------------------------------
BOOL	CPcObj::Start(VECTOR2 vPos) {
	m_vPos = vPos;
	ResetStatus();
	ResetAnim();
	m_bActive = TRUE;
	m_nDirIdx = RIGHT;
	m_vCenter = VECTOR2(0, 0);											// ��]�̒��S�_
	m_nAnimNum = 1;
	m_nCnt1 = 2 * 60;
	m_vOldRailPos = VECTOR2(0, 0);										// �ȑO�ݒu�������[���̈ʒu
	m_vRailPos = VECTOR2(0, 0);											// �ݒu���郌�[���̈ʒu
	m_vPosUp = VECTOR2(0, 0);
	m_vTarget = VECTOR2(0, 0);
	m_isFirstClick = FALSE;
	m_isTouchRail = FALSE;
	m_bFirstFlag = TRUE;
	m_bMovieFlag = TRUE;
	m_bLavaStartFlag = FALSE;
	m_bCollisionGroundFirst = FALSE;
	SetStatus(_T("Data/Script/StatusPC.csv"));
	return TRUE;
}

//-----------------------------------------------------------------------------
// �o�b�I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CPcObj::Update()
{
	// �A�N�e�B�u�̂�Update�����s
	if (!m_bActive) return;

	if (m_pGMain->m_pMapProc->m_bMapMovieFlag) {
		MovieCamera();
	}
	else {
		// �X�e�[�W��
		NormalUpdate();
		AnimCountup();
		Draw();
	}
}

void CPcObj::NormalUpdate() {
	CDirectInput* pDI = m_pGMain->m_pDI;
	CMapLine* pHitmapline1 = NULL;
	CMapLine* pHitmapline2 = NULL;
	m_isTouchRail = FALSE;
	m_vPosUp = VECTOR2(0, 0);

	switch (m_dwStatus)
	{
	case  FLASH:
		m_nCnt1--;
		if (m_nCnt1 <= 0) {
			ResetStatus();
			ResetAnim();
		}
		else {
			FlashCountup();
		}		// break;����ꂸ���̂܂܁@NORMAL�@�̏������s��
	case  NORMAL:

		break;

	case DAMAGE:
		if (m_pOtherObj->GetAtc() > 0)
		{
			m_nHp -= m_pOtherObj->GetAtc();	// �U�����󂯂��_���[�W
			m_nMaterial -= m_pOtherObj->GetAtc();
			if (m_nHp <= 0)
			{
				m_nHp = 0;
				m_dwStatus = DEAD;		// HP���O�Ȃ̂Ŏ��S��
				m_nCnt1 = 180;			// ���S�t���b�V�����̎��Ԑݒ�
			}
			else {
				m_dwStatus = FLASH;
				m_nCnt1 = 60;
			}
			if (m_nMaterial < 0) {
				m_nMaterial = 0;
			}
		}
		else {
			m_dwStatus = NORMAL;  // �U���͂Ȃ��̂Ƃ��͂�����NORMAL�ɖ߂�
		}
		break;

	case DEAD:
		m_nCnt1--;
		if (m_nCnt1 <= 0)
		{
			m_pGMain->m_pForeProc->SetPhase(3);
			m_pGMain->m_pSeGameOver->Play();
			m_bActive = FALSE;
		}
		else {
			FlashCountup();
		}
		break;
	}

	switch (m_dwStatusSub)
	{
	case  WALK:		// �n�ʈړ����̏���
		// �n�ʂɐG��Ă���Ԃ͌���
		fSpeed -= 0.3f;
		if (fSpeed < 2.0f) {
			fSpeed = 2.0f;			// ���x�͍Œ�2.0
		}

		// �����Ă�������ɍ��킹�Ĉړ�������ݒ�
		if (m_nDirIdx == LEFT) {
			// ��
			m_vPosUp.x = -fSpeed;
		}
		else {
			// �E
			m_vPosUp.x = fSpeed;
		}

		// ���R����
		m_vJumpSpeed.x = m_vPosUp.x;
		m_vJumpSpeed.y = fSpeed / 2;
		m_fJumpTime = 0;
		m_vPosUp.y = m_vJumpSpeed.y;

		// �n�ʂɐڂ����狭���I�ɉ�]�p��0�ɂ���
		m_fRotate = 0;
		break;

	case  JUMP:		// �������̏���
		m_fJumpTime += 0.03f;

		if (m_nDirIdx != LEFT) {
			// �E
			m_vPosUp.x = m_vJumpSpeed.x;
		}
		else {
			// ��
			m_vPosUp.x = -m_vJumpSpeed.x;
		}
		m_vPosUp.y = round(m_vJumpSpeed.y + GRAVITY * m_fJumpTime);
		break;

	case RAIL:		// ���[���ɏ���Ă���Ԃ̏���
		// �n�ʂɐڂ����Ƃ���1�x�������s���鏈���̃t���O
		m_bCollisionGroundFirst = TRUE;
		m_fJumpTime = 0;
		m_pGMain->m_pSeDash->Play();

		if (!m_bFirstFlag) {	// �ŏ��̍�̂ݏ������s��Ȃ�
			// ���ݏ���Ă��郌�[���̉�]�p���擾���A���g�̉�]�p�Ƃ���
			float railRot = m_pGMain->m_pRailProc->GetObjRotate(m_nArrNum, this);
			if (railRot < 0.0f) {
				railRot = 360 + railRot;
			}
			float log = railRot - m_fRotate;

			if (railRot - m_fRotate >= 90.0f && railRot - m_fRotate <= 270.0f) {
				// �i�s�����ɒ��p�ȏ�ł���΃X�g�b�v����
				fSpeed = 0.0f;
			}
			else {
				// �p�x����
				m_fRotate = railRot;

				// ��������
				fSpeed += 0.05f;
				if (fSpeed > 12) {
					// �������x�͍ő�12.0f
					fSpeed = 12.0f;
				}
				if (fSpeed >= 10.0f) {
					m_pGMain->m_pEffectProc->m_pEffectSmokeProc->Start(m_vPos - VECTOR2(155, 46));
					m_isBoost = TRUE;
				}
				else {
					m_isBoost = FALSE;
				}
			}
			// ���ݏ���Ă��郌�[���̏I�[�ʒu���擾
			m_vTarget = m_pGMain->m_pRailProc->GetLastPos(m_nArrNum, this);
		}
		else {
			// ��������
			fSpeed += 0.05f;
			if (fSpeed > 12) {
				// �������x�͍ő�12.0f
				fSpeed = 12.0f;
			}
		}

		if (m_vTarget == VECTOR2(-1, -1)) {
			m_dwStatusSub = JUMP;
			break;
		}

		if (!m_bFirstFlag) {	// �ŏ��̍�̂ݏ������s��Ȃ�
			// ���[������ړ�����悤�Ƀ^�[�Q�b�g�ʒu�𒲐�
			m_vTarget.x += std::cos(XMConvertToRadians(-1 * (180 - (90 - -m_fRotate)))) * 48;
			m_vTarget.y += std::sin(XMConvertToRadians(-1 * (180 - (90 - -m_fRotate)))) * 48;
		}

		// �ړ�
		if (TargetMove(fSpeed)) {
			// �ړI�n�ɓ��B���Ă���ꍇ
			if (m_pGMain->m_pRailProc->GetLastPos(m_nArrNum + 1, this) == VECTOR2(-1, -1)) {
				// ���[���̏I�[�ɓ��B
				// �I�[�ɓ��B�����(-1, -1)��Ԃ�
				if (m_bFirstFlag) {
					m_bFirstFlag = FALSE;
					m_pGMain->m_pBgmMovie->Stop();
					if (m_pGMain->m_pMapProc->GetMapNo() == 0) {
						m_pGMain->m_pBgmMap1->Play(AUDIO_LOOP);
					}
					else {
						m_pGMain->m_pBgmMap2->Play(AUDIO_LOOP);
					}
				}
				m_dwStatusSub = WALK;
				m_bMovieFlag = FALSE;
			}
			else {
				// ���̃��[���̈ʒu��o�^
				m_nArrNum++;
				if (m_nArrNum == RAIL_MAX) {
					m_nArrNum = 0;
				}
			}
		}
		break;

	case BALLOON:	// ��������̕��A���̏���
		if (TargetMove(3)) {
			fSpeed = 2.0f;
			m_dwStatusSub = JUMP;
		}
		break;
	}

	// ��]�l�̏C��
	if (m_fRotate < 0.0f) {
		m_fRotate = 360.0 + m_fRotate;
	}

	VECTOR2 oldPosUp = m_vPosUp;
	// �}�b�v���Ƃ̐ڐG����ƓK�؂Ȉʒu�ւ̈ړ�
	if (m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline1, pHitmapline2))
	{
		if (pHitmapline1 && pHitmapline1->m_vNormal.y <= 0)	// �}�b�v���������܂ł͂n�j
		{
			// �ǂɐG�ꂽ�甽�]����
			if ((pHitmapline1->m_vNormal.x <= -0.2 || pHitmapline2->m_vNormal.x <= -0.2) && m_nDirIdx == RIGHT) {
				m_nDirIdx = LEFT;
				m_fRotate *= -1;
			}
			else if ((pHitmapline1->m_vNormal.x >= 0.2 || pHitmapline2->m_vNormal.x >= 0.2) && m_nDirIdx == LEFT) {
				m_nDirIdx = RIGHT;
				m_fRotate *= -1;
			}
			else {
				// �����łȂ����ɐG�ꂽ�Ƃ�
				m_dwStatusSub = WALK;	// �}�b�v���ɐڐG���Ă���Ƃ��́A�W�����v����s�ɖ߂�

				// �ڒn�����u�ԂP��̂ݎ��s
				if (m_bCollisionGroundFirst) {
					m_bCollisionGroundFirst = FALSE;
					if (m_nDirIdx == RIGHT && oldPosUp.x < 0) {
						// �E�����ŃW�����v���x��x���W���}�C�i�X�̎�
						m_nDirIdx = LEFT;
					}
					else
						if (m_nDirIdx == LEFT && oldPosUp.x > 0) {
							// �������ŃW�����v���x��x���W���v���X�̎�
							m_nDirIdx = RIGHT;
						}
				}
				m_fJumpTime = 0;
				m_vJumpSpeed.x = m_vJumpSpeed.y = 0;
			}
		}
	}
	else {
		// �󒆂ɂ���Ƃ��̏���
		if (m_dwStatusSub == RAIL || m_dwStatusSub == BALLOON) {
			// ���[���ɏ���Ă���ԁA���A��
			m_fJumpTime = 0;
		}
		else if (m_dwStatusSub != JUMP) {
			m_dwStatusSub = JUMP;
			if (m_nDirIdx == RIGHT) {
				m_vJumpSpeed.x = std::cos(XMConvertToRadians(m_fRotate)) * fSpeed;
				m_vJumpSpeed.y = std::sin(XMConvertToRadians(m_fRotate)) * fSpeed;
			}
			else {
				m_vJumpSpeed.x = std::cos(XMConvertToRadians(m_fRotate)) * fSpeed;
				m_vJumpSpeed.y = -std::sin(XMConvertToRadians(m_fRotate)) * fSpeed;
			}
		}
	}

	// �����v�Z
	m_vPos += m_vPosUp;

	if (!m_bFirstFlag) {
		if (pDI->CheckMouse(KD_DAT, DIM_RBUTTON)) {
			// �N���b�N���W���}�b�v���W�ɕϊ�
			VECTOR2 clickPos = VECTOR2(pDI->GetMousePos().x, pDI->GetMousePos().y);
			clickPos += m_pGMain->m_vScroll;
			if (!m_isFirstClick) {
				// ���N���b�N��
				// ���[���ݒu
				if (m_nMaterial >= 10) {
					m_pGMain->m_pRailProc->Start(clickPos);
					m_vOldRailPos = clickPos;
					m_nMaterial -= 10;
					m_isFirstClick = TRUE;
				}
			}
			else {
				double distance = Root(clickPos, m_vOldRailPos);
				if (distance >= 24.0) {
					// ���[���ݒu
					if (m_nMaterial >= 10) {
						m_pGMain->m_pRailProc->Start(clickPos);
						m_vOldRailPos = clickPos;
						m_nMaterial -= 10;
					}
					else {
						m_isFirstClick = FALSE;
					}
				}
			}
		}
		else {
			m_isFirstClick = FALSE;
		}
	}
}

void CPcObj::MovieCamera()
{
	CDirectInput* pDI = m_pGMain->m_pDI;
	if (m_bOnce) {
		m_pGMain->m_pEffectProc->m_pItemProc->Update();
		m_vTarget = m_vPos;
		m_vPos = m_pGMain->m_pEffectProc->m_pItemProc->GetGoalPos();
		m_dwStatusPhase = 1;
		m_bOnce = FALSE;
	}
	switch (m_dwStatusPhase) {
	case 1:
		if (pDI->CheckKey(KD_DAT, DIK_F)) {
			m_vPos = m_vTarget;
		}
		if (TargetMove(10)) {
			// ���B
			m_pGMain->m_pSeStart->Play();
			m_dwStatusPhase = 2;
			m_nCnt1 = 60 * 4;
			break;
		}
		if (!m_pSprite->m_bFade) {
			if (m_nCnt1 <= 0) {
				m_vPos += m_vPosUp;
			}
			else {
				m_nCnt1--;
			}
		}
		break;

	case 2:
		m_nCnt1--;
		if (m_nCnt1 <= 0) {
			m_pGMain->m_pMapProc->m_bMapMovieFlag = FALSE;
		}
		break;
	}
}

void CPcObj::AddMaterial(int material)
{
	if (m_nHp < m_nMaterial + material) {
		m_nMaterial = m_nHp;
	}
	else {
		m_nMaterial += material;
	}
}