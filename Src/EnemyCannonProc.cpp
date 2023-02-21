#include "EnemyCannonProc.h"
#include "EnemyCannonObj.h"
#include "MapProc.h"

//------------------------------------------------------------------------
//	大砲の敵プロシージャのコンストラクタ	
//
//   なお、オブジェクトのdeleteはCBaseProcのデストラクタで行うため不要
//------------------------------------------------------------------------
CEnmCannonProc::CEnmCannonProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (DWORD i = 0; i < ENM_CANNON_MAX; i++)
	{
		m_pObjArray.push_back(new CEnmCannonObj(m_pGMain));  // m_pObjArrayにオブジェクトを生成する
	}
}

// ---------------------------------------------------------------------------
// 大砲の敵プロシージャの自動発生処理
// ---------------------------------------------------------------------------
void CEnmCannonProc::Update()
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
			// イベントマップの探索　 ( EvtID:3　敵の出現位置,  EvtNo:0x08	大砲の敵  )
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 3, 0x08, vPos, nNext, dir))
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