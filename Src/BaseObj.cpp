#include "BaseObj.h"
#include "BaseProc.h"

//------------------------------------------------------------------------
//  ��{�I�u�W�F�N�g
//	�R���X�g���N�^	
//
//  �����@CGameMain* pGMain  // �Q�[�����C���N���X
//------------------------------------------------------------------------
CBaseObj::CBaseObj(CGameMain* pGMain)
{
	// �S�̂̃[���N�����[
	// ���ӓ_�F�N���X���ɂr�s�k��錾���Ă���Ƃ��͎g�p���Ă͂Ȃ�Ȃ�
	ZeroMemory(this, sizeof(CBaseObj));

	m_pGMain = pGMain;			// �Q�[�����C���N���X
	m_dwStatus = NORMAL;
	m_dwStatusSub = NONE;
	m_vCenter.x = -1;			// ��]��X���S�́A�X�v���C�g���S
	m_vCenter.y = -1;			// ��]��Y���S�́A�X�v���C�g���S
	m_fScale = 1.0f;			// �g��k��
	m_fAlpha = 1.0f;			// �����x
	m_nAnimNum = 2;				// �A�j���[�V�����v�f��(�����l�͂Q)
	m_nArrNum = -1;
	fSpeed = 0.0f;				// �ړ����x
	m_tag = NONE;				// �����蔻��Ȃǂ̔��ʗp�̃^�O
	m_isTouchRail = FALSE;
	m_isFinishedRail = FALSE;
	m_isHit = FALSE;
	m_isBoost = FALSE;
}

//------------------------------------------------------------------------
//  ��{�I�u�W�F�N�g
//	�f�X�g���N�^	
//------------------------------------------------------------------------
CBaseObj::~CBaseObj()
{
	SAFE_DELETE(m_pSprite);		// �p����̃f�X�g���N�^�Ŏ��s�����Ǝv�����A�O�̂���
}

//------------------------------------------------------------------------
//  ��{�I�u�W�F�N�g
//	�X�e�[�^�X�̃��Z�b�g����	
//
//  �����@�Ȃ�
//
//	�߂�l �Ȃ�
//------------------------------------------------------------------------
void  CBaseObj::ResetStatus()
{
	m_dwStatus = NORMAL;		// �X�e�[�^�X
	m_dwStatusPhase = 0;		// �X�e�[�^�X�t�F�[�Y
}

//------------------------------------------------------------------------
//  ��{�I�u�W�F�N�g
//	�X�e�[�^�X�̓ǂݎ��ɂ�鏉��������	
//
//  �����@TCHAR*
//			�ǂݍ��݃t�@�C����
//
//	�߂�l �Ȃ�
//------------------------------------------------------------------------
void CBaseObj::SetStatus(TCHAR* FileName)
{
	const int BUFSIZE = 512;
	TCHAR str[BUFSIZ];
	FILE* fp;

	fp = _tfopen(FileName, _T("r"));
	if (fp) {
		_fgetts(str, BUFSIZE, fp);
		_stscanf_s(str, _T("%d, %d, %d, %d, %d, %f"), &m_nHp, &m_nMaxHp, &m_nMaterial, &m_nMaxMaterial, &m_nAtc, &fSpeed);  // �^�C�g���s
	}
}

//------------------------------------------------------------------------
//  ��{�I�u�W�F�N�g
//	�A�j���[�V�����̃��Z�b�g����	
//
//  �����@�Ȃ�
//
//	�߂�l �Ȃ�
//------------------------------------------------------------------------
void  CBaseObj::ResetAnim()
{
	m_nAnimIdx = 0;		// �A�j���[�V�����C���f�b�N�X��
	m_nAnimFrm = 0;		// �A�j���[�V�����t���[���J�E���g
	m_nFlashIdx = 0;		// �t���b�V���A�j���[�V�����C���f�b�N�X��
	m_nFlashFrm = 0;		// �t���b�V���A�j���[�V�����t���[���J�E���g
}

//------------------------------------------------------------------------
//  ��{�I�u�W�F�N�g
//	�A�j���[�V�����̃J�E���g�A�b�v����	
//
//  �����@�Ȃ�
//
//	�߂�l int
//         �A�j���[�V�����p����:0�@�@�@�@�A�j���[�V�����I��:1
//------------------------------------------------------------------------
int  CBaseObj::AnimCountup()
{
	int ret = 0;
	int speed = 10;

	if (m_nAnimNum <= 1) return 1;

	m_nAnimFrm++;
	if (m_nAnimFrm >= speed) {
		m_nAnimFrm = 0;
		m_nAnimIdx++;
		if (m_nAnimIdx >= m_nAnimNum) {
			m_nAnimIdx = 0;
			ret = 1;
		}
	}
	return ret;
}

//------------------------------------------------------------------------
//  ��{�I�u�W�F�N�g
//	�t���b�V���A�j���[�V�����̃J�E���g�A�b�v����	
//
//  �����@�Ȃ�
//
//	�߂�l int
//         �A�j���[�V�����p����:0�@�@�@�@�A�j���[�V�����I��:1
//------------------------------------------------------------------------
int  CBaseObj::FlashCountup()
{
	int ret = 0;
	int speed = 2;
	int num = 2;

	m_nFlashFrm++;
	if (m_nFlashFrm >= speed) {
		m_nFlashFrm = 0;
		m_nFlashIdx++;
		if (m_nFlashIdx >= num) {
			m_nFlashIdx = 0;
			ret = 1;
		}
	}
	return ret;
}

//------------------------------------------------------------------------
//  ��{�I�u�W�F�N�g
//	�`�惁�\�b�h	
// �i �X�P�[���Ɖ�]���l�����ĕ`��@�j
// �i �X�N���[�����l�����ĕ`��@�j
//
//  �����@�Ȃ�
//
//	�߂�l �Ȃ�
//------------------------------------------------------------------------
void  CBaseObj::Draw()
{
	VECTOR2 vScr = m_pGMain->m_vScroll;  // ---------�X�N���[��
	int cx, cy;
	if (m_bActive) {
		// �����x
		if (m_nFlashIdx == 0)
		{
			if (m_pSprite->m_bFade) {
				m_pSprite->m_vDiffuse.w = m_pSprite->m_fFadeDiffuse;
			}
			else {
				m_pSprite->m_vDiffuse.w = m_fAlpha;
			}
		}
		else {
			m_pSprite->m_vDiffuse.w = m_fAlpha * 0.2f; // �����ɋ߂�����
		}

		// �A�j���[�V����
		m_pSprite->m_ofX = m_pSprite->GetDestWidth() * m_nAnimIdx;
		m_pSprite->m_ofY = m_pSprite->GetDestHeight() * m_nDirIdx;

		if (m_fRotate == 0) {	// ��]���Ȃ��Ƃ�

			MATRIX4X4 mWorld, mScale;
			mWorld = XMMatrixTranslation((m_vPos.x + m_vOf.x - vScr.x), (m_vPos.y + m_vOf.y - vScr.y), 0);
			mScale = XMMatrixScaling(m_fScale, m_fScale, 1.0f);
			mWorld = mScale * mWorld;

			// ��ʊO�͕`�悵�Ȃ�
			if (mWorld._41 + m_pSprite->GetDestWidth() * m_fScale  < 0 || mWorld._41 > WINDOW_WIDTH ||
				mWorld._42 + m_pSprite->GetDestHeight() * m_fScale < 0 || mWorld._42 > WINDOW_HEIGHT)
			{
				;
			}
			else {
				m_pSprite->Draw(mWorld);
			}
		}
		else {			// ��]����Ƃ�
			if (m_vCenter.x == -1) {// ��]���S�w���W�̐ݒ�i-1�̂Ƃ��̓L�����N�^���S�j
				cx = m_pSprite->GetDestWidth() / 2;
			}
			else {
				cx = (int)m_vCenter.x;
			}
			if (m_vCenter.y == -1) {// ��]���S�x���W�̐ݒ�i-1�̂Ƃ��̓L�����N�^���S�j
				cy = m_pSprite->GetDestHeight() / 2;
			}
			else {
				cy = (int)m_vCenter.y;
			}
			// ��]�}�g���b�N�X�̍쐬
			MATRIX4X4 mWorld, mCenter, mRot, mScale;
			mWorld = XMMatrixTranslation((m_vPos.x + m_vOf.x - vScr.x), (m_vPos.y + m_vOf.y - vScr.y), 0);
			mScale = XMMatrixScaling(m_fScale, m_fScale, 1.0f);
			mCenter = XMMatrixTranslation(cx, cy, 0);
			mRot = XMMatrixRotationZ(XMConvertToRadians(m_fRotate));
			mWorld = mRot * mCenter * mScale * mWorld;
			mCenter = XMMatrixTranslation(-cx, -cy, 0);
			mWorld = mCenter * mWorld;

			// ��ʊO�͕`�悵�Ȃ�
			if (mWorld._41 + m_pSprite->GetDestWidth() * m_fScale  < 0 || mWorld._41 > WINDOW_WIDTH ||
				mWorld._42 + m_pSprite->GetDestHeight() * m_fScale < 0 || mWorld._42 > WINDOW_HEIGHT)
			{
				;
			}
			else {
				m_pSprite->Draw(mWorld);
			}
		}
	}
}

//------------------------------------------------------------------------
//  ��{�I�u�W�F�N�g
//  �I�u�W�F�N�g���m�̏Փ˔��胁�\�b�h�i�X�P�[�����l���j
//
//  ����
//    CBaseObj*  pObj :  �Ώۂ̃I�u�W�F�N�g
//
//	�߂�l BOOL
//        �ڐG���Ă���:TRUE�@�@�@�@�ڐG���Ă��Ȃ�:FALSE
//------------------------------------------------------------------------
BOOL  CBaseObj::isCollision(CBaseObj* pObj)
{
	// �I�u�W�F�N�g���\������Ă��邱��
	if (!m_bActive || !pObj->m_bActive) return FALSE;

	// �Փ˔���
	BOOL bRet = FALSE;
	VECTOR2 a[4], b[4];
	DWORD  w1, w2, h1, h2;

	// PC�̔���{�b�N�X
	a[0] = m_vPos;
	w1 = m_pSprite->GetDestWidth() * m_fScale;
	a[1].x = w1 * std::cos(XMConvertToRadians(m_fRotate)) + a[0].x;
	a[1].y = a[0].y - w1 * std::sin(XMConvertToRadians(m_fRotate));
	h1 = m_pSprite->GetDestHeight() * m_fScale;
	a[2].x = h1 * std::sin(XMConvertToRadians(m_fRotate)) + a[1].x;
	a[2].y = h1 * std::cos(XMConvertToRadians(m_fRotate)) + a[1].y;
	a[3].x = a[2].x - w1 * std::cos(XMConvertToRadians(m_fRotate));
	a[3].y = w1 * std::sin(XMConvertToRadians(m_fRotate)) + a[2].y;

	// ����̔���{�b�N�X
	b[0] = pObj->m_vPos;
	w2 = pObj->m_pSprite->GetDestWidth() * pObj->m_fScale;
	b[1].x = w2 * std::cos(XMConvertToRadians(pObj->m_fRotate)) + b[0].x;
	b[1].y = b[0].y - w2 * std::sin(XMConvertToRadians(pObj->m_fRotate));
	h2 = pObj->m_pSprite->GetDestHeight() * pObj->m_fScale;
	b[2].x = h2 * std::sin(XMConvertToRadians(pObj->m_fRotate)) + b[1].x;
	b[2].y = h2 * std::cos(XMConvertToRadians(pObj->m_fRotate)) + b[1].y;
	b[3].x = b[2].x - w2 * std::cos(XMConvertToRadians(pObj->m_fRotate));
	b[3].y = w2 * std::sin(XMConvertToRadians(pObj->m_fRotate)) + b[2].y;

	// �e�{�b�N�X�̕ӂ�������Ă��邩�`�F�b�N
	for (int i = 0; i < 4; i++) {
		int a1 = i, a2 = i + 1;
		if (a2 == 4) {
			a2 = 0;
		}
		for (int j = 0; j < 4; j++) {
			int b1 = j, b2 = j + 1;
			if (b2 == 4) {
				b2 = 0;
			}
			bRet = isLineCross(a[a1], a[a2], b[b1], b[b2]);

			if (bRet) {
				break;
			}
		}
		if (bRet) {
			break;
		}
	}
	return bRet;
}

// ----------------------------------------------------------------------------------------
// �Q�����̌����`�F�b�N
// �@�������ƒ������̌����`�F�b�N�B
//
// �@�߂�l�F�������Ă���Ƃ��^�B��_���W��hitpos�ɕԂ�
// ----------------------------------------------------------------------------------------
BOOL CBaseObj::isLineCross(VECTOR2 a1, VECTOR2 a2, VECTOR2 b1, VECTOR2 b2)
{
	BOOL bRet = FALSE;
	float d1, d2;
	// ��_�@����
	VECTOR2  ap = VECTOR2(0, 0);

	// �����̒������O�̂Ƃ�
	if ((a1.x == a2.x && a1.y == a2.y) ||
		(b1.x == b2.x && b1.x == b2.y)) {
		return bRet;
	}

	// ��_�����邩
	float dev = (a2.y - a1.y) * (b2.x - b1.x) - (a2.x - a1.x) * (b2.y - b1.y);
	if (dev == 0) {// ���s���̂Ƃ�
		return bRet;
	}

	// ��_�����߂�
	d1 = (b1.y * b2.x - b1.x * b2.y);
	d2 = (a1.y * a2.x - a1.x * a2.y);

	ap.x = d1 * (a2.x - a1.x) - d2 * (b2.x - b1.x);
	ap.x /= dev;
	ap.y = d1 * (a2.y - a1.y) - d2 * (b2.y - b1.y);
	ap.y /= dev;

	// ��_�������͈̔͂̒��ɂ��邩
	if ((CheckRange(a1.x, a2.x, ap.x) && CheckRange(a1.y, a2.y, ap.y)) &&
		(CheckRange(b1.x, b2.x, ap.x) && CheckRange(b1.y, b2.y, ap.y))) {
		bRet = TRUE;
	}

	return bRet;
}


// ----------------------------------------------------------------------------------------
// �͈̓`�F�b�N
//
// �@�߂�l�Fpt�����Ƃ��̊Ԃɓ����Ă���Ƃ��^�B
// ----------------------------------------------------------------------------------------
BOOL CBaseObj::CheckRange(float l, float r, float pt)
{
	float low, hi;
	float mgn = 0.05f;	// �덷

	if (l <= r) {
		low = l;
		hi = r;
	}
	else {
		low = r;
		hi = l;
	}
	low -= mgn;
	hi += mgn;

	if (low <= pt && pt <= hi) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

//------------------------------------------------------------------------
//  ��{�I�u�W�F�N�g
//  �I�u�W�F�N�g�ƃN���b�N�ʒu�̏Փ˔��胁�\�b�h�i�X�P�[�����l���j
//
//  ����
//    int nMx :  �}�E�X���W�@�w���W
//    int nMy :  �}�E�X���W�@�x���W
//
//	�߂�l BOOL
//        �q�b�g���Ă���:TRUE�@�@�@�@�q�b�g���Ă��Ȃ�:FALSE
//------------------------------------------------------------------------
BOOL  CBaseObj::isCollisionClick(int nMx, int nMy)
{
	BOOL bRet = FALSE;

	// ��`�̔���
	if (m_bActive && (m_vPos.x + m_vOf.x) <= nMx && (m_vPos.x + m_vOf.x) + (m_pSprite->GetDestWidth() * m_fScale) >= nMx &&
		(m_vPos.y + m_vOf.y) <= nMy && (m_vPos.y + m_vOf.y) + (m_pSprite->GetDestHeight() * m_fScale) >= nMy) bRet = TRUE;

	return bRet;

}

//-----------------------------------------------------------------------------
// ��{�v���V�[�W���N���X�̂����蔻��
//
// �E�S�Ă̑���v���V�[�W���Ƒ���I�u�W�F�N�g��ǂ݉��������蔻����s��
//
//   CBaseObj* pOtherObj      ����̃I�u�W�F�N�g
//
//   �߂�l�@BOOL
//           TRUE:�q�b�g�����Ƃ�       FALSE�F�q�b�g���Ă��Ȃ��Ƃ�
//
//   ���茋�ʁ@�@
//           �q�b�g�����Ƃ��́@�@�@�@����Ǝ����̃I�u�W�F�N�g��m_pOtherObj�ɒl���Z�b�g
//                                   ����Ǝ����̃I�u�W�F�N�g��m_dwStatus��DAMAGE��ݒ肷��
//           �q�b�g���Ă��Ȃ��Ƃ��́@����Ǝ����̃I�u�W�F�N�g��m_pOtherObj��NULL���Z�b�g
//-----------------------------------------------------------------------------
BOOL   CBaseProc::Hitcheck(CBaseObj* pOtherObj)
{
	BOOL  bRet = FALSE;

	// �S�Ă̑���Ƃ̂����蔻��
	for (DWORD i = 0; i < m_pObjArray.size(); i++)  // �S�Ă̑���I�u�W�F�N�g
	{
		bRet = m_pObjArray[i]->Hitcheck(pOtherObj);  // ����I�u�W�F�N�g�Ƃ̂����蔻��
		if (bRet) return bRet;
	}

	for (DWORD i = 0; i < m_pProcArray.size(); i++)  // ���ʂ̑���v���V�[�W��
	{
		bRet = m_pProcArray[i]->Hitcheck(pOtherObj);  // ����v���V�[�W���Ƃ̂����蔻��
		if (bRet) return bRet;
	}

	return bRet;
}

//------------------------------------------------------------------------
//  ��{�I�u�W�F�N�g
//  �I�u�W�F�N�g���m�̂����蔻�胁�\�b�h
//
//  isCollision���\�b�h���g�p���ăI�u�W�F�N�g���m�̂����蔻����s��
//  �ڐG���Ă���΁A�����̃I�u�W�F�N�g��m_dwStatus�� DAMAGE �ɁA
//  m_pOtherObj�ɑ���̃I�u�W�F�N�g��ݒ肷��B
//
//  ����
//    CBaseObj* pObj:  ����̃I�u�W�F�N�g
//
//	�߂�l BOOL
//        �q�b�g���Ă���:TRUE�@�@�@�@�q�b�g���Ă��Ȃ�:FALSE
//------------------------------------------------------------------------
BOOL  CBaseObj::Hitcheck(CBaseObj* pObj)
{
	if (m_dwStatus == NORMAL && pObj->m_dwStatus == NORMAL && isCollision(pObj))
	{
		switch (pObj->m_tag) {
		case RAIL:
			// ���[���Ɠ��������ۂ̏���
			pObj->m_isHit = TRUE;
			if (m_dwStatusSub != RAIL) {
				m_dwStatusSub = RAIL;
				m_nArrNum = pObj->m_nArrNum;
			}
			break;

		case BALLOON:
			// ���D�Ɠ��������ۂ̏���
			pObj->m_dwStatus = DEAD;
			break;

		default:
			if (!m_isBoost) {
				m_dwStatus = DAMAGE;
			}
			pObj->m_dwStatus = DAMAGE;
			break;
		}
		m_pOtherObj = pObj;
		pObj->m_pOtherObj = this;
		return TRUE;
	}
	return FALSE;
}

//------------------------------------------------------------------------
//  ��{�I�u�W�F�N�g
//  �X�v���C�g�̒��S�_�̍��W�����߂�
//
//  ����
//    �Ȃ�
//
//	�߂�l VECTOR2
//        �X�v���C�g���S�_�̍��W
//------------------------------------------------------------------------
VECTOR2  CBaseObj::GetCenterPos()
{
	VECTOR2 vPos = m_vPos;
	if (m_pSprite)
	{
		vPos.x += m_pSprite->GetSrcWidth() / 2;
		vPos.y += m_pSprite->GetSrcHeight() / 2;
	}
	return vPos;
}

//------------------------------------------------------------------------
// �ړI�n�itargetX,Y�j�ւ̈ړ�����
//   �����@�@�F�@speed:���̈ړ���
//   �߂�l�@�F�@true�F�ړI�n�ɒB�����@�@false:�܂��ړI�n�ɒB���Ă��Ȃ�
//   �I�u�W�F�N�g�ɐݒ肷��l�@�F�@m_vPosUp�Ɉړ��ʂ�ݒ肷��
//------------------------------------------------------------------------
BOOL CBaseObj::TargetMove(float speed)
{
	float mvX, mvY, n;
	BOOL ret = FALSE;

	if (m_vPos.x == m_vTarget.x && m_vPos.y == m_vTarget.y) {  // �ړI�n�ɒB�����Ƃ�
		m_vPosUp.x = 0;
		m_vPosUp.y = 0;
		ret = TRUE; // �ړI�n�ɒB����
	}
	else {    // �ړI�n�ւ̈ړ�����

		mvX = m_vTarget.x - m_vPos.x;   // �ړI�n�܂ł̂w�����̕ψ�
		mvY = m_vTarget.y - m_vPos.y;   // �ړI�n�܂ł̂x�����̕ψ�

		if (abs(mvX) >= abs(mvY)) {   // �w�����̋����������Ƃ�
			if (abs(mvX) < speed) {        // �P��̈ړ��ʂ��ߐڂ��Ă���Ƃ�
				m_vPosUp.x = mvX;
				m_vPosUp.y = mvY;
			}
			else {
				if (mvX >= 0) {
					m_vPosUp.x = speed; // �w�����̈ړ��ʂ�speed�ɂ���
				}
				else {
					m_vPosUp.x = -speed; // �w�����̈ړ��ʂ�-speed�ɂ���
				}
				n = abs(mvX / speed);
				m_vPosUp.y = floor(mvY / n); // �w�����̈ړ��ʂɍ��킹�āA�x�����̈ړ��ʂ�ݒ肷��
			}
		}
		else {                                // �x�����̋����������Ƃ�
			if (abs(mvY) < speed) {        // �P��̈ړ��ʂ��ߐڂ��Ă����
				m_vPosUp.x = mvX;
				m_vPosUp.y = mvY;
			}
			else {
				if (mvY >= 0) {
					m_vPosUp.y = speed; // �x�����̈ړ��ʂ�speed�ɂ���
				}
				else {
					m_vPosUp.y = -speed; // �x�����̈ړ��ʂ�-speed�ɂ���
				}
				n = abs(mvY / speed);
				m_vPosUp.x = floor(mvX / n); // �x�����̈ړ��ʂɍ��킹�āA�w�����̈ړ��ʂ�ݒ肷��
			}
		}
		ret = FALSE;    // �܂��ړI�n�ɒB���Ă��Ȃ�
	}

	return ret;
}