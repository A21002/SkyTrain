#include "ItemProc.h"
#include "ItemObj.h"
#include "MapProc.h"

//------------------------------------------------------------------------
//	アイテムプロシージャのコンストラクタ	
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//------------------------------------------------------------------------
CItemProc::CItemProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (DWORD i = 0; i < ITEM_MAX; i++)
	{
		m_pObjArray.push_back(new CItemObj(m_pGMain));	// m_pObjArrayにアイテムを生成する
	}
	m_nStartFlag = 0;
}

//------------------------------------------------------------------------
//	ゴール地点の座標を返す
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
// アイテムプロシージャの開始
//
//   戻り値　　なし
//-----------------------------------------------------------------------------
void	CItemProc::Update()
{
	VECTOR2 vPos;
	int  nNext;

	if (m_nStartFlag == 0 && m_pGMain->m_dwGameStatus == GAMEMAIN)
	{
		// イベントマップを探索し、救急箱を設定する
		nNext = 0;
		while (nNext != -1)
		{
			// イベントマップの探索　 ( EvtID:2　アイテムの出現位置,  EvtNo:0x10 救急箱	)
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

		// イベントマップを探索し、ドア（出口）を設定する
		nNext = 0;
		while (nNext != -1)
		{
			// イベントマップの探索　 ( EvtID:2　アイテムの出現位置,  EvtNo:0x20 ムービー中のダミーオブジェクト	)
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
			// イベントマップの探索　 ( EvtID:2　アイテムの出現位置,  EvtNo:0x40 ゴール判定	)
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
			// イベントマップの探索　 ( EvtID:2　アイテムの出現位置,  EvtNo:0x200 最初の坂の開始地点	)
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

		m_nStartFlag = 1;  // 一回発させたら、もう発生しない
	}
}