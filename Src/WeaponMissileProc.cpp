#include "WeaponMissileProc.h"
#include "WeaponMissileObj.h"

//------------------------------------------------------------------------
//	�~�T�C���v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//------------------------------------------------------------------------
CWeaponMissileProc::CWeaponMissileProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// �~�T�C��
	for (DWORD i = 0; i < WEAPON_MISSILE_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponMissileObj(m_pGMain));	// m_pObjArray�ɕ���E�V���b�g�I�u�W�F�N�g�𐶐�����
	}
}

//-----------------------------------------------------------------------------
// �~�T�C���v���V�[�W���̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@����ɔ��� : TRUE    �������Ȃ����� : FALSE
//-----------------------------------------------------------------------------
BOOL	CWeaponMissileProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	BOOL bRet = FALSE;

	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vPos, pObj, dwOwner);	// ����̔���
			m_pGMain->m_pSeHit->Play();
			bRet = TRUE;
			break;
		}
	}
	if (bRet) m_pGMain->m_pSeShot->Play();
	return bRet;
}