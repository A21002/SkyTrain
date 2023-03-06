#include "EnemyCannonObj.h"
#include "MapProc.h"
#include "PlaycharProc.h"
#include "WeaponProc.h"

//------------------------------------------------------------------------
//	大砲の敵オブジェクトのコンストラクタ	
//
//  引数　なし
//------------------------------------------------------------------------
CEnmCannonObj::CEnmCannonObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageChar, 192, 192, 48, 48);
	m_vPos = VECTOR2(0, 0);
}

// ---------------------------------------------------------------------------
// 大砲の敵オブジェクトのデストラクタ
// ---------------------------------------------------------------------------
CEnmCannonObj::~CEnmCannonObj()
{
	SAFE_DELETE(m_pSprite);
}

//-----------------------------------------------------------------------------
// 大砲の敵オブジェクトの開始
//
//   引数　　　なし
//-----------------------------------------------------------------------------
BOOL	CEnmCannonObj::Start(VECTOR2 vPos, DWORD dwOwner)
{
	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_nDirIdx = dwOwner;
	m_vPos = vPos;	// 発生位置
	m_vPosUp = VECTOR2(0, 0);
	m_nAnimNum = 1;
	m_nWaitTime = 120;
	SetStatus(_T("Data/Script/StatusCannoon.csv"));
	return TRUE;
}

//-----------------------------------------------------------------------------
// 大砲の敵オブジェクトの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CEnmCannonObj::Update()
{
	float fSpeed = 1;
	if (m_bActive)
	{
		switch (m_dwStatus)
		{
		case  FLASH:
			m_nCnt1--;
			if (m_nCnt1 <= 0) {
				ResetStatus();
				ResetAnim();
			}
			else {
				FlashCountup();
			}		// break;を入れずそのまま　NORMAL　の処理を行う
		case  NORMAL:
			// 画面内にいる場合
			VECTOR2 scroll = m_pGMain->m_vScroll;
			if (scroll.x <= m_vPos.x && m_vPos.x <= scroll.x + WINDOW_WIDTH &&
				scroll.y <= m_vPos.y && m_vPos.y <= scroll.y + WINDOW_HEIGHT) {
				if (m_nWaitTime <= 0) {
					m_pGMain->m_pWeaponProc->m_pWeaponCannonProc->Start(m_vPos, this, ENM);
					m_nWaitTime = 180;
				}
			}
			if (m_nWaitTime > 0) {
				m_nWaitTime--;
			}

			// 増分
			m_vPos += m_vPosUp;
			// ＰＣとのあたり判定
			if (!m_pGMain->m_pMapProc->m_bMapMovieFlag) {
				m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
			}
			break;

		case  DAMAGE:
			m_nHp -= m_pOtherObj->GetAtc();
			if (m_nHp <= 0) {
				m_dwStatus = DEAD;
				m_nCnt1 = 180;
			}
			else {
				m_dwStatus = FLASH;
				m_nCnt1 = 60;
			}
			m_pGMain->m_pSeHit->Play();
			break;

		case  DEAD:
			m_nCnt1--;
			if (m_nCnt1 <= 0)
			{
				m_bActive = FALSE;
			}
			else {
				FlashCountup();
			}
			break;
		}

		AnimCountup();
		Draw();
	}
}