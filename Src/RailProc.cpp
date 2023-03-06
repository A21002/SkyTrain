#include "RailProc.h"
#include "RailObj.h"
#include "MapProc.h"
#include "PlaycharProc.h"

// --------------------------------------------------------------------
// ���[���v���V�[�W���̃R���X�g���N�^
// --------------------------------------------------------------------
CRailProc::CRailProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (DWORD i = 0; i < RAIL_MAX; i++) {
		// m_pObjArray�Ƀ��[���I�u�W�F�N�g�𐶐�����
		m_pObjArray.push_back(new CRailObj(m_pGMain));
	}
	for (DWORD i = 0; i < RAIL_MAX; i++) {
		// ���[���̏I�[�z���������
		m_vLastRightPos[i] = VECTOR2(-1, -1);
		m_vLastLeftPos[i] = VECTOR2(-1, -1);
	}
	m_nGenerationId = 0;
}

// --------------------------------------------------------------------
// ���[���v���V�[�W���̊J�n
//
// VECTOR2 vPos		�����ʒu
//
// �߂�l	���� : TRUE		�������Ȃ����� : FALSE
// --------------------------------------------------------------------
BOOL CRailProc::Start(VECTOR2 vPos)
{
	m_pObjArray[m_nGenerationId]->Start(vPos, m_nGenerationId);
	m_nGenerationId++;
	if (m_nGenerationId == RAIL_MAX) {
		m_nGenerationId = 0;
	}
	return TRUE;
}

// --------------------------------------------------------------------
// �I�u�W�F�N�g�z��̎w�肳�ꂽ�A�h���X�̃I�u�W�F�N�g��m_Active�̏�Ԃ�Ԃ�
//
// DWORD i		�A�h���X
//
// �߂�l	m_Active�̏��
// --------------------------------------------------------------------
BOOL CRailProc::CheckNextObjActive(DWORD i)
{
	if (i >= RAIL_MAX) {
		return m_pObjArray[0]->GetActive();
	}
	return m_pObjArray[i]->GetActive();
}

// --------------------------------------------------------------------
// ���g�̌��̃��[�����Q�Ƃ��APos��Ԃ�
//
// DWORD i		�A�h���X
// VECTOR2 pos	�������ꂽ�Ƃ��̃}�E�X�J�[�\���̈ʒu
//
// �߂�l	m_Pos�̒l
// --------------------------------------------------------------------
VECTOR2 CRailProc::GetLinkPos(DWORD i, VECTOR2 pos)
{
	// �ŏ��̃��[���ɌĂ΂ꂽ�Ƃ�
	int id = i - 1;
	if (id < 0) {
		id = RAIL_MAX - 1;
	}
	if (!m_pObjArray[id]->GetActive()) {
		return pos;
	}

	return m_pObjArray[id]->GetNextRailPos();
}

// --------------------------------------------------------------------
// ���g�̌��̃��[�����Q�Ƃ��Am_fRotate�̒l��Ԃ�
//
// DWORD i		�A�h���X
//
// �߂�l	��]�p�x
// --------------------------------------------------------------------
FLOAT CRailProc::GetObjRotate(DWORD i, CBaseObj* pObj)
{
	if (pObj->GetDirIdx() == RIGHT) {
		return m_pObjArray[i]->GetRotate();
	}
	else {
		return 180 + m_pObjArray[i]->GetRotate();
	}
}

// --------------------------------------------------------------------
// �P�ԍŋߐ����������[���̈ʒu��Ԃ�
// --------------------------------------------------------------------
VECTOR2 CRailProc::GetNewRailPos()
{
	int id = m_nGenerationId - 1;
	if (id < 0) {
		id = RAIL_MAX - 1;
	}
	return m_pObjArray[id]->GetPos();
}

//============================================================================
// �A�N�Z�X�֐�
//============================================================================
void CRailProc::SetLastRightPos(VECTOR2 pos, DWORD i)
{
	m_vLastRightPos[i] = pos;
}

void CRailProc::SetLastLeftPos(VECTOR2 pos, DWORD i)
{
	m_vLastLeftPos[i] = pos;
}

VECTOR2 CRailProc::GetLastPos(DWORD i, CBaseObj* pObj) {
	VECTOR2 ret;
	if (i != 0) {
		if (m_pGMain->m_pRailProc->m_pObjArray[i - 1]->GetFinishedRail()) {
			ret = VECTOR2(-1, -1);
			return ret;
		}
	}
	if (pObj->GetDirIdx() == RIGHT) {
		ret = m_vLastRightPos[i];
	}
	else {
		ret = m_vLastLeftPos[i];
	}

	return ret;
}