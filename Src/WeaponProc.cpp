//=============================================================================
//      ����̏���
//=============================================================================

#include "WeaponProc.h"
#include "PlaycharProc.h"
#include "EnemyProc.h"
#include "Effect.h"
#include "MapProc.h"

//=============================================================================================================================
// ���탁�C���v���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
// ----------------------------------------------------------------------------------------------------------------------------
CWeaponProc::CWeaponProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	m_pWeaponMissileProc = new CWeaponMissileProc(m_pGMain);	// ����E�~�T�C���v���V�[�W��
	m_pProcArray.push_back(m_pWeaponMissileProc);				// �v���V�[�W�����v���V�[�W���z��ɓo�^����
	m_pWeaponCannonProc = new CWeaponCannonProc(m_pGMain);		// ����E��C�v���V�[�W��
	m_pProcArray.push_back(m_pWeaponCannonProc);				// �v���V�[�W�����v���V�[�W���z��ɓo�^����
}
