#include "EnemyLavaObj.h"
#include "MapProc.h"
#include "PlaycharProc.h"

//------------------------------------------------------------------------
//	Big溶岩の敵オブジェクトのコンストラクタ	
//
//  引数　なし
//------------------------------------------------------------------------
CEnmLavaObj::CEnmLavaObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageLava, 0, 0, 48, 48);
	m_vPos = VECTOR2(0, 0);
}

// ---------------------------------------------------------------------------
// Big溶岩の敵オブジェクトのデストラクタ
// ---------------------------------------------------------------------------
CEnmLavaObj::~CEnmLavaObj()
{
	SAFE_DELETE(m_pSprite);
}

//-----------------------------------------------------------------------------
// Big溶岩の敵オブジェクトの開始
//
//   引数　　　なし
//-----------------------------------------------------------------------------
BOOL	CEnmLavaObj::Start(VECTOR2 vPos, DWORD dwOwner)
{
	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_nDirIdx = dwOwner;
	m_vPos = vPos;	// 発生位置
	m_vPosUp = VECTOR2(0, 0);
	m_nAnimNum = 1;
	m_nWaitTime = 120;
	SetStatus(_T("Data/Script/StatusLava.csv"));
	return TRUE;
}

//-----------------------------------------------------------------------------
// Big溶岩の敵オブジェクトの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CEnmLavaObj::Update()
{
	if (m_bActive)
	{
		switch (m_dwStatus)
		{
		case  NORMAL:
			if (!m_pGMain->m_pMapProc->m_bMapMovieFlag) {
				m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
			}
			break;

		case  DAMAGE:
			m_dwStatus = NORMAL;
			break;

		case  DEAD:
			m_dwStatus = NORMAL;
			break;
		}

		AnimCountup();
		Draw();
	}
}