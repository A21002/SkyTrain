#include "EnemyBalloonObj.h"
// --------------------------------------------------------------------
// バルーンオブジェクトのコンストラクタ
// --------------------------------------------------------------------
CEnmBalloonObj::CEnmBalloonObj(CGameMain* pGMain) : CBaseObj(pGMain) {
	m_pSprite = new CSprite(m_pGMain->m_pImageChar, 144, 0, 48, 48);
	m_nAnimNum = 1;
	m_vPos = VECTOR2(0, 0);
	m_tag = BALLOON;
}

// --------------------------------------------------------------------
// バルーンオブジェクトのデストラクタ
// --------------------------------------------------------------------
CEnmBalloonObj::~CEnmBalloonObj() {
	SAFE_DELETE(m_pSprite);
}

// --------------------------------------------------------------------
// スタートの処理
// --------------------------------------------------------------------
BOOL CEnmBalloonObj::Start(VECTOR2 vPos) {
	m_bActive = TRUE;
	m_vPos = vPos;
	m_dwStatus = WALK;
	SetStatus(_T("Data/Script/StatusBalloon.csv"));
	return TRUE;
}