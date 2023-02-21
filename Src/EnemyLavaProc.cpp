#include "EnemyLavaProc.h"
#include "EnemyLavaObj.h"
#include "MapProc.h"

//------------------------------------------------------------------------
//	Big�n��̓G�v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//------------------------------------------------------------------------
CEnmLavaProc::CEnmLavaProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (DWORD i = 0; i < ENM_LAVA_MAX; i++)
	{
		m_pObjArray.push_back(new CEnmLavaObj(m_pGMain));  // m_pObjArray�ɃI�u�W�F�N�g�𐶐�����
	}
}

// ---------------------------------------------------------------------------
// Big�n��̓G�v���V�[�W���̎�����������
// ---------------------------------------------------------------------------
void CEnmLavaProc::Update()
{
	VECTOR2 vPos;
	int  nNext;
	int dir;

	// �܂������ł���ꍇ�̂ݔ���������
	if (m_nStartFlag == 0 && m_pGMain->m_dwGameStatus == GAMEMAIN)
	{
		// �C�x���g�}�b�v��T�����A�G�̏o���ʒu��ݒ肷��
		nNext = 0;
		while (nNext != -1)
		{
			// �C�x���g�}�b�v�̒T���@ ( EvtID:3�@�G�̏o���ʒu,  EvtNo:0x10	Big�n��̓G  )
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 3, 0x10, vPos, nNext, dir))
			{
				for (DWORD j = 0; j < m_pObjArray.size(); j++)
				{
					if (!m_pObjArray[j]->GetActive())
					{
						m_pObjArray[j]->Start(vPos, dir);
						break;
					}
				}
			}
		}
		m_nStartFlag = 1;  // ��񔭂�������A�����������Ȃ�
	}
}