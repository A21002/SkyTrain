#include "EnemyLavaProc.h"
#include "EnemyLavaObj.h"
#include "MapProc.h"

//------------------------------------------------------------------------
//	Big溶岩の敵プロシージャのコンストラクタ	
//
//   なお、オブジェクトのdeleteはCBaseProcのデストラクタで行うため不要
//------------------------------------------------------------------------
CEnmLavaProc::CEnmLavaProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (DWORD i = 0; i < ENM_LAVA_MAX; i++)
	{
		m_pObjArray.push_back(new CEnmLavaObj(m_pGMain));  // m_pObjArrayにオブジェクトを生成する
	}
}

// ---------------------------------------------------------------------------
// Big溶岩の敵プロシージャの自動発生処理
// ---------------------------------------------------------------------------
void CEnmLavaProc::Update()
{
	VECTOR2 vPos;
	int  nNext;
	int dir;

	// まだ発生できる場合のみ発生させる
	if (m_nStartFlag == 0 && m_pGMain->m_dwGameStatus == GAMEMAIN)
	{
		// イベントマップを探索し、敵の出現位置を設定する
		nNext = 0;
		while (nNext != -1)
		{
			// イベントマップの探索　 ( EvtID:3　敵の出現位置,  EvtNo:0x10	Big溶岩の敵  )
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
		m_nStartFlag = 1;  // 一回発させたら、もう発生しない
	}
}