#include "EnemyTordProc.h"
#include "EnemyTordObj.h"
#include "MapProc.h"

//------------------------------------------------------------------------
//	がまの敵プロシージャのコンストラクタ	
//
//   なお、オブジェクトのdeleteはCBaseProcのデストラクタで行うため不要
//------------------------------------------------------------------------
CEnmTordProc::CEnmTordProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (DWORD i = 0; i < ENM_TORD_MAX; i++)
	{
		m_pObjArray.push_back(new CEnmTordObj(m_pGMain));  // m_pObjArrayにオブジェクトを生成する
	}
}

// ---------------------------------------------------------------------------
// がまの敵プロシージャの自動発生処理
// ---------------------------------------------------------------------------
void CEnmTordProc::Update()
{
	VECTOR2 vPos;
	int nNext;

	// まだ発生できる場合のみ発生させる
	if (m_nStartFlag == 0 && m_pGMain->m_dwGameStatus == GAMEMAIN)
	{
		// イベントマップを探索し、敵の出現位置を設定する
		nNext = 0;
		while (nNext != -1)
		{
			// イベントマップ　 ( EvtID:3　敵の出現位置,     　EvtNo:0x02　がまの敵  )
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 3, 0x02, vPos, nNext))
			{
				for (DWORD j = 0; j < m_pObjArray.size(); j++)
				{
					if (!m_pObjArray[j]->GetActive())
					{
						m_pObjArray[j]->Start(vPos);
						break;
					}
				}
			}
		}

		m_nStartFlag = 1;  // 一回発させたら、もう発生しない
	}
}