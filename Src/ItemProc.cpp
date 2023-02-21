#include "ItemProc.h"
#include "ItemObj.h"
#include "MapProc.h"

//------------------------------------------------------------------------
//	�A�C�e���v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//------------------------------------------------------------------------
CItemProc::CItemProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (DWORD i = 0; i < ITEM_MAX; i++)
	{
		m_pObjArray.push_back(new CItemObj(m_pGMain));	// m_pObjArray�ɃA�C�e���𐶐�����
	}
	m_nStartFlag = 0;
}

//------------------------------------------------------------------------
//	�S�[���n�_�̍��W��Ԃ�
//------------------------------------------------------------------------
VECTOR2 CItemProc::GetGoalPos()
{
	for (int i = 0; i < m_pObjArray.size(); i++) {
		if (m_pObjArray[i]->GetActive()) {
			if (m_pObjArray[i]->GetStatusSub() == ITEMGOAL) {
				return m_pObjArray[i]->GetPos();
			}
		}
	}
	return VECTOR2(0, 0);
}

//-----------------------------------------------------------------------------
// �A�C�e���v���V�[�W���̊J�n
//
//   �߂�l�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CItemProc::Update()
{
	VECTOR2 vPos;
	int  nNext;

	if (m_nStartFlag == 0 && m_pGMain->m_dwGameStatus == GAMEMAIN)
	{
		// �C�x���g�}�b�v��T�����A�~�}����ݒ肷��
		nNext = 0;
		while (nNext != -1)
		{
			// �C�x���g�}�b�v�̒T���@ ( EvtID:2�@�A�C�e���̏o���ʒu,  EvtNo:0x10 �~�}��	)
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 2, 0x10, vPos, nNext))
			{
				for (DWORD j = 0; j < m_pObjArray.size(); j++)
				{
					if (!m_pObjArray[j]->GetActive())
					{
						m_pObjArray[j]->Start(vPos, ITEMRESQUE);
						break;
					}
				}
			}
		}

		// �C�x���g�}�b�v��T�����A�h�A�i�o���j��ݒ肷��
		nNext = 0;
		while (nNext != -1)
		{
			// �C�x���g�}�b�v�̒T���@ ( EvtID:2�@�A�C�e���̏o���ʒu,  EvtNo:0x20 ���[�r�[���̃_�~�[�I�u�W�F�N�g	)
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 2, 0x20, vPos, nNext))
			{
				for (DWORD j = 0; j < m_pObjArray.size(); j++)
				{
					if (!m_pObjArray[j]->GetActive())
					{
						m_pObjArray[j]->Start(vPos, ITEMPCDUMMY);
						break;
					}
				}
			}
		}

		nNext = 0;
		while (nNext != -1)
		{
			// �C�x���g�}�b�v�̒T���@ ( EvtID:2�@�A�C�e���̏o���ʒu,  EvtNo:0x40 �S�[������	)
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 2, 0x40, vPos, nNext))
			{
				for (DWORD j = 0; j < m_pObjArray.size(); j++)
				{
					if (!m_pObjArray[j]->GetActive())
					{
						m_pObjArray[j]->Start(vPos, ITEMGOAL);
						break;
					}
				}
			}
		}

		nNext = 0;
		while (nNext != -1)
		{
			// �C�x���g�}�b�v�̒T���@ ( EvtID:2�@�A�C�e���̏o���ʒu,  EvtNo:0x200 �ŏ��̍�̊J�n�n�_	)
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 2, 0x200, vPos, nNext))
			{
				for (DWORD j = 0; j < m_pObjArray.size(); j++)
				{
					if (!m_pObjArray[j]->GetActive())
					{
						m_pObjArray[j]->Start(vPos, ITEMFIRSTSLOPE);
						break;
					}
				}
			}
		}

		m_nStartFlag = 1;  // ��񔭂�������A�����������Ȃ�
	}
}