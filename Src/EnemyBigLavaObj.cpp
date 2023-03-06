#include "EnemyBigLavaObj.h"
#include "MapProc.h"
#include "PlaycharProc.h"

//------------------------------------------------------------------------
//	溶岩の敵オブジェクトのコンストラクタ	
//
//  引数　なし
//------------------------------------------------------------------------
CEnmBigLavaObj::CEnmBigLavaObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageLava, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	m_vPos = VECTOR2(0, 0);
}

// ---------------------------------------------------------------------------
// 溶岩の敵オブジェクトのデストラクタ
// ---------------------------------------------------------------------------
CEnmBigLavaObj::~CEnmBigLavaObj()
{
	SAFE_DELETE(m_pSprite);
}

//-----------------------------------------------------------------------------
// 溶岩の敵オブジェクトの開始
//
//   引数　　　なし
//-----------------------------------------------------------------------------
BOOL	CEnmBigLavaObj::Start(VECTOR2 vPos)
{
	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_nDirIdx = RIGHT;
	m_vPos = m_pGMain->m_vScroll;
	m_vPos.y += WINDOW_HEIGHT;
	m_vPosUp = VECTOR2(0, 0);
	m_nAnimNum = 1;
	m_tag = BIGLAVA;
	SetStatus(_T("Data/Script/StatusBigLava.csv"));
	return TRUE;
}

//-----------------------------------------------------------------------------
// 溶岩の敵オブジェクトの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CEnmBigLavaObj::Update()
{
	if (m_bActive)
	{
		if (m_pGMain->m_pMapProc->m_bMapMovieFlag) {
			m_vPos = m_pGMain->m_vScroll;
			m_vPos.y += WINDOW_HEIGHT;
		}
		else {
			m_vPos.x = m_pGMain->m_vScroll.x;
			m_vPos.y -= fSpeed;
		}
		m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
		AnimCountup();
		Draw();
	}
}