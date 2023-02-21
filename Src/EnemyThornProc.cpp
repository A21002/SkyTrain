#include "EnemyThornProc.h"
#include "EnemyThornObj.h"
#include "MapProc.h"

//------------------------------------------------------------------------
//	ハリセンボンの敵プロシージャのコンストラクタ	
//
//   なお、オブジェクトのdeleteはCBaseProcのデストラクタで行うため不要
//------------------------------------------------------------------------
CEnmThornProc::CEnmThornProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (DWORD i = 0; i < ENM_THORN_MAX; i++)
	{
		m_pObjArray.push_back(new CEnmThornObj(m_pGMain));  // m_pObjArrayにオブジェクトを生成する
	}
}

// ---------------------------------------------------------------------------
// ハリセンボンの敵プロシージャの自動発生処理
// ---------------------------------------------------------------------------
void CEnmThornProc::Update()
{
	VECTOR2 vPos;
	int  nNext;

	// まだ発生できる場合のみ発生させる
	if (m_nStartFlag == 0 && m_pGMain->m_dwGameStatus == GAMEMAIN)
	{
		// イベントマップを探索し、敵の出現位置を設定する
		nNext = 0;
		while (nNext != -1)
		{
			// イベントマップの探索　 ( EvtID:3　敵の出現位置,  EvtNo:0x04	ハリセンボンの敵  )
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 3, 0x04, vPos, nNext))
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