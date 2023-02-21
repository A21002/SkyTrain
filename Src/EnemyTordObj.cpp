#include "EnemyTordObj.h"
#include "MapProc.h"
#include "PlaycharProc.h"
#include "WeaponProc.h"

//------------------------------------------------------------------------
//	がまの敵オブジェクトのコンストラクタ	
//
//  引数　なし
//------------------------------------------------------------------------
CEnmTordObj::CEnmTordObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageChar, 0, 0, 58, 48);
	m_pBalloonObj = new CEnmBalloonObj(m_pGMain);
	m_vPos = VECTOR2(0, 0);
}

// ---------------------------------------------------------------------------
// がまの敵オブジェクトのデストラクタ
// ---------------------------------------------------------------------------
CEnmTordObj::~CEnmTordObj()
{
	SAFE_DELETE(m_pBalloonObj);
	SAFE_DELETE(m_pSprite);
}

//-----------------------------------------------------------------------------
// がまの敵オブジェクトの開始
//
//   引数　　　なし
//-----------------------------------------------------------------------------
BOOL	CEnmTordObj::Start(VECTOR2 vPos)
{

	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_nDirIdx = LEFT;
	m_vPos = vPos;	// 発生位置
	m_dwStatusSub = JUMP;
	m_vPosUp = VECTOR2(0, 0);
	m_nWaitTime = 0;
	m_fMoveWidth = 0;
	m_pBalloonObj->Start(m_vPos + VECTOR2(22, -48));
	SetStatus(_T("Data/Script/StatusTord.csv"));
	return TRUE;
}

//-----------------------------------------------------------------------------
// がまの敵オブジェクトの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CEnmTordObj::Update()
{
	CMapLine* pHitmapline = NULL;
	if (m_bActive)
	{
		m_vPosUp = VECTOR2(0, 0);
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
				m_fJumpTime += 0.03f;
				m_vPosUp.y = round(m_vJumpSpeed.y + GRAVITY * m_fJumpTime);
				break;

			case JUMP:
				if (m_fMoveWidth >= EnmTordConstruct::TARGET_WIDTH ||
					m_fMoveWidth < 0) {
					fSpeed *= -1;
				}
				m_fMoveWidth += fSpeed;
				m_vPosUp.y = fSpeed;

				// PCの位置に合わせて反転処理
				if (m_pGMain->m_pPcProc->GetPcObjPtr()->GetPos().x <= m_vPos.x) {
					// 自身の左にPCがいるとき
					if (m_nDirIdx != LEFT)
					{
						m_nDirIdx = LEFT;
						m_pBalloonObj->SetPos(m_vPos + VECTOR2(10, -48));
					}
				}
				else {
					if (m_nDirIdx != RIGHT)
					{
						m_nDirIdx = RIGHT;
						m_pBalloonObj->SetPos(m_vPos + VECTOR2(10, -48));
					}
				}
				break;
			}

			// 地面との接触判定
			if (!m_pBalloonObj->GetActive())
			{
				if (m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline))
				{
					m_dwStatusSub = STOP;
				}
			}

			// 増分
			m_vPos += m_vPosUp;
			// ＰＣとのあたり判定
			if (!m_pGMain->m_pMapProc->m_bMapMovieFlag) {
				if (m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this)) {
				}
			}

			// ミサイルの発射処理
			if (m_pGMain->m_vScroll.x <= m_vPos.x && m_vPos.x < m_pGMain->m_vScroll.x + WINDOW_WIDTH &&
				m_pGMain->m_vScroll.y <= m_vPos.y && m_vPos.y < m_pGMain->m_vScroll.y + WINDOW_HEIGHT &&
				!m_pGMain->m_pMapProc->m_bMapMovieFlag) {
				// 画面内にいる場合
				if (m_nWaitTime <= 0) {
					if (m_nDirIdx == LEFT) {
						m_pGMain->m_pWeaponProc->m_pWeaponMissileProc->Start(m_vPos + VECTOR2(-35, 36), this, ENM);
					}
					else {
						m_pGMain->m_pWeaponProc->m_pWeaponMissileProc->Start(m_vPos + VECTOR2(55, 36), this, ENM);
					}

					m_nWaitTime = EnmTordConstruct::WAITTIME * 60;
				}
			}
			if (m_nWaitTime > 0) {
				m_nWaitTime--;
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
				if (m_pBalloonObj->GetActive()) {
					m_pBalloonObj->SetActive(FALSE);
				}
			}
			else {
				FlashCountup();
			}
			break;
		}

		// 風船の処理
		if (m_pBalloonObj->GetActive()) {
			switch (m_pBalloonObj->GetStatus()) {
			case WALK:
				break;

			case DEAD:
				m_pBalloonObj->SetActive(FALSE);
				break;

			default:
				break;
			}
			m_pBalloonObj->SetPos(m_pBalloonObj->GetPos() + m_vPosUp);
			if (!m_pGMain->m_pMapProc->m_bMapMovieFlag) {
				m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)m_pBalloonObj);
			}

			m_pBalloonObj->Draw();
		}
		else {
			m_dwStatusSub = WALK;
		}

		AnimCountup();
		Draw();
	}
}