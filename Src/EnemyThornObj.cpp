#include "EnemyThornObj.h"
#include "MapProc.h"
#include "PlaycharProc.h"

//------------------------------------------------------------------------
//	ハリセンボンの敵オブジェクトのコンストラクタ	
//
//  引数　なし
//------------------------------------------------------------------------
CEnmThornObj::CEnmThornObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageChar, 144, 192, 48, 48);
	m_vPos = VECTOR2(0, 0);
}

// ---------------------------------------------------------------------------
// ハリセンボンの敵オブジェクトのデストラクタ
// ---------------------------------------------------------------------------
CEnmThornObj::~CEnmThornObj()
{
	SAFE_DELETE(m_pSprite);
}

//-----------------------------------------------------------------------------
// ハリセンボンの敵オブジェクトの開始
//
//   引数　　　なし
//-----------------------------------------------------------------------------
BOOL	CEnmThornObj::Start(VECTOR2 vPos)
{
	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwStatusSub = WALK;
	m_nDirIdx = RIGHT;
	m_vPos = vPos;	// 発生位置
	m_vPosUp = VECTOR2(0, 0);
	m_nAnimNum = 1;
	m_nWaitTime = 120;
	m_nCnt2 = 90;
	SetStatus(_T("Data/Script/StatusThorn.csv"));
	return TRUE;
}

//-----------------------------------------------------------------------------
// ハリセンボンの敵オブジェクトの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CEnmThornObj::Update()
{
	CMapLine* pHitmapline = NULL;
	BOOL bRet;
	if (m_bActive)
	{
		m_vPosUp = VECTOR2(0, fSpeed);
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
			switch (m_dwStatusSub)
			{
			case  WALK:
				m_nCnt2--;
				if (m_nCnt2 <= 0) {
					fSpeed *= -1;
					m_nCnt2 = 90;
				}

				// マップ線との接触判定と適切な位置への移動
				bRet = m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline);
				if (bRet)
				{
					// マップ線の端に来たので上下反転
					fSpeed *= -1;
					m_nCnt2 = 90;
				}
				break;
			}
			// 増分
			m_vPos += m_vPosUp;
			// ＰＣとのあたり判定
			if (!m_pGMain->m_pMapProc->m_bMapMovieFlag) {
				m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
			}

			// 膨らむ処理
			if (m_nWaitTime <= 0) {
				if (m_nDirIdx == RIGHT) {
					m_nDirIdx = LEFT;
				}
				else {
					m_nDirIdx = RIGHT;
				}
				m_nWaitTime = 120;
			}
			m_nWaitTime--;
			if (m_nWaitTime < 0) {
				m_nWaitTime = 0;
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