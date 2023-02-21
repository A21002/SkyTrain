#include "EnemyBigLavaProc.h"
#include "EnemyBigLavaObj.h"
#include "MapProc.h"

//------------------------------------------------------------------------
//	溶岩の敵プロシージャのコンストラクタ	
//
//   なお、オブジェクトのdeleteはCBaseProcのデストラクタで行うため不要
//------------------------------------------------------------------------
CEnmBigLavaProc::CEnmBigLavaProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (DWORD i = 0; i < ENM_BIGLAVA_MAX; i++)
	{
		m_pObjArray.push_back(new CEnmBigLavaObj(m_pGMain));  // m_pObjArrayにオブジェクトを生成する
	}
}

// ---------------------------------------------------------------------------
// 溶岩の敵プロシージャの自動発生処理
// ---------------------------------------------------------------------------
void CEnmBigLavaProc::Update()
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
			// イベントマップ　 ( EvtID:3　敵の出現位置,     　EvtNo:0x01	泉の水の敵  )
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 3, 0x01, vPos, nNext))
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