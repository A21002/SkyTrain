#include "PlaycharObj.h"
#include "MapProc.h"
#include "RailProc.h"
#include "ForeProc.h"
#include "Effect.h"

//------------------------------------------------------------------------
//	ＰＣオブジェクトのコンストラクタ	
//
//  引数　CGameMain* pGMain
//------------------------------------------------------------------------
CPcObj::CPcObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageChar, 0, 192, 93, 48);	// スプライトの位置
	m_vPos = VECTOR2(0, 0);
	ResetStatus();
	ResetAnim();
	m_bActive = TRUE;
	m_nDirIdx = RIGHT;
	m_vCenter = VECTOR2(0, 0);											// 回転の中心点
	m_nAnimNum = 1;
	m_vOldRailPos = VECTOR2(0, 0);										// 以前設置したレールの位置
	m_vRailPos = VECTOR2(0, 0);											// 設置するレールの位置
	m_vPosUp = VECTOR2(0, 0);
	m_vTarget = VECTOR2(0, 0);
	m_isFirstClick = FALSE;
	m_isTouchRail = FALSE;
	m_bFirstFlag = TRUE;
	m_bMovieFlag = TRUE;
	m_bCollisionGroundFirst = FALSE;
	m_bOnce = FALSE;
	SetStatus(_T("Data/Script/StatusPC.csv"));
}

// ---------------------------------------------------------------------------
// ＰＣオブジェクトのデストラクタ
// ---------------------------------------------------------------------------
CPcObj::~CPcObj()
{
	SAFE_DELETE(m_pSprite);
}

//-----------------------------------------------------------------------------
// ＰＣオブジェクトのスタート
//
//   引数　　　正常：TRUE　異常：FALSE
//-----------------------------------------------------------------------------
BOOL	CPcObj::Start(VECTOR2 vPos) {
	m_vPos = vPos;
	ResetStatus();
	ResetAnim();
	m_bActive = TRUE;
	m_nDirIdx = RIGHT;
	m_vCenter = VECTOR2(0, 0);											// 回転の中心点
	m_nAnimNum = 1;
	m_nCnt1 = 2 * 60;
	m_vOldRailPos = VECTOR2(0, 0);										// 以前設置したレールの位置
	m_vRailPos = VECTOR2(0, 0);											// 設置するレールの位置
	m_vPosUp = VECTOR2(0, 0);
	m_vTarget = VECTOR2(0, 0);
	m_isFirstClick = FALSE;
	m_isTouchRail = FALSE;
	m_bFirstFlag = TRUE;
	m_bMovieFlag = TRUE;
	m_bLavaStartFlag = FALSE;
	m_bCollisionGroundFirst = FALSE;
	SetStatus(_T("Data/Script/StatusPC.csv"));
	return TRUE;
}

//-----------------------------------------------------------------------------
// ＰＣオブジェクトの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CPcObj::Update()
{
	// アクティブのみUpdateを実行
	if (!m_bActive) return;

	if (m_pGMain->m_pMapProc->m_bMapMovieFlag) {
		MovieCamera();
	}
	else {
		// ステージ内
		NormalUpdate();
		AnimCountup();
		Draw();
	}
}

void CPcObj::NormalUpdate() {
	CDirectInput* pDI = m_pGMain->m_pDI;
	CMapLine* pHitmapline1 = NULL;
	CMapLine* pHitmapline2 = NULL;
	m_isTouchRail = FALSE;
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

		break;

	case DAMAGE:
		if (m_pOtherObj->GetAtc() > 0)
		{
			m_nHp -= m_pOtherObj->GetAtc();	// 攻撃を受けたダメージ
			m_nMaterial -= m_pOtherObj->GetAtc();
			if (m_nHp <= 0)
			{
				m_nHp = 0;
				m_dwStatus = DEAD;		// HPが０なので死亡へ
				m_nCnt1 = 180;			// 死亡フラッシュ中の時間設定
			}
			else {
				m_dwStatus = FLASH;
				m_nCnt1 = 60;
			}
			if (m_nMaterial < 0) {
				m_nMaterial = 0;
			}
		}
		else {
			m_dwStatus = NORMAL;  // 攻撃力なしのときはすぐにNORMALに戻る
		}
		break;

	case DEAD:
		m_nCnt1--;
		if (m_nCnt1 <= 0)
		{
			m_pGMain->m_pForeProc->SetPhase(3);
			m_pGMain->m_pSeGameOver->Play();
			m_bActive = FALSE;
		}
		else {
			FlashCountup();
		}
		break;
	}

	switch (m_dwStatusSub)
	{
	case  WALK:		// 地面移動中の処理
		// 地面に触れている間は減速
		fSpeed -= 0.3f;
		if (fSpeed < 2.0f) {
			fSpeed = 2.0f;			// 速度は最低2.0
		}

		// 向いている方向に合わせて移動距離を設定
		if (m_nDirIdx == LEFT) {
			// 左
			m_vPosUp.x = -fSpeed;
		}
		else {
			// 右
			m_vPosUp.x = fSpeed;
		}

		// 自然落下
		m_vJumpSpeed.x = m_vPosUp.x;
		m_vJumpSpeed.y = fSpeed / 2;
		m_fJumpTime = 0;
		m_vPosUp.y = m_vJumpSpeed.y;

		// 地面に接したら強制的に回転角を0にする
		m_fRotate = 0;
		break;

	case  JUMP:		// 落下中の処理
		m_fJumpTime += 0.03f;

		if (m_nDirIdx != LEFT) {
			// 右
			m_vPosUp.x = m_vJumpSpeed.x;
		}
		else {
			// 左
			m_vPosUp.x = -m_vJumpSpeed.x;
		}
		m_vPosUp.y = round(m_vJumpSpeed.y + GRAVITY * m_fJumpTime);
		break;

	case RAIL:		// レールに乗っている間の処理
		// 地面に接したときに1度だけ実行する処理のフラグ
		m_bCollisionGroundFirst = TRUE;
		m_fJumpTime = 0;
		m_pGMain->m_pSeDash->Play();

		if (!m_bFirstFlag) {	// 最初の坂のみ処理を行わない
			// 現在乗っているレールの回転角を取得し、自身の回転角とする
			float railRot = m_pGMain->m_pRailProc->GetObjRotate(m_nArrNum, this);
			if (railRot < 0.0f) {
				railRot = 360 + railRot;
			}
			float log = railRot - m_fRotate;

			if (railRot - m_fRotate >= 90.0f && railRot - m_fRotate <= 270.0f) {
				// 進行方向に直角以上であればストップする
				fSpeed = 0.0f;
			}
			else {
				// 角度調整
				m_fRotate = railRot;

				// 加速処理
				fSpeed += 0.05f;
				if (fSpeed > 12) {
					// 加速速度は最大12.0f
					fSpeed = 12.0f;
				}
				if (fSpeed >= 10.0f) {
					m_pGMain->m_pEffectProc->m_pEffectSmokeProc->Start(m_vPos - VECTOR2(155, 46));
					m_isBoost = TRUE;
				}
				else {
					m_isBoost = FALSE;
				}
			}
			// 現在乗っているレールの終端位置を取得
			m_vTarget = m_pGMain->m_pRailProc->GetLastPos(m_nArrNum, this);
		}
		else {
			// 加速処理
			fSpeed += 0.05f;
			if (fSpeed > 12) {
				// 加速速度は最大12.0f
				fSpeed = 12.0f;
			}
		}

		if (m_vTarget == VECTOR2(-1, -1)) {
			m_dwStatusSub = JUMP;
			break;
		}

		if (!m_bFirstFlag) {	// 最初の坂のみ処理を行わない
			// レール上を移動するようにターゲット位置を調整
			m_vTarget.x += std::cos(XMConvertToRadians(-1 * (180 - (90 - -m_fRotate)))) * 48;
			m_vTarget.y += std::sin(XMConvertToRadians(-1 * (180 - (90 - -m_fRotate)))) * 48;
		}

		// 移動
		if (TargetMove(fSpeed)) {
			// 目的地に到達している場合
			if (m_pGMain->m_pRailProc->GetLastPos(m_nArrNum + 1, this) == VECTOR2(-1, -1)) {
				// レールの終端に到達
				// 終端に到達すると(-1, -1)を返す
				if (m_bFirstFlag) {
					m_bFirstFlag = FALSE;
					m_pGMain->m_pBgmMovie->Stop();
					if (m_pGMain->m_pMapProc->GetMapNo() == 0) {
						m_pGMain->m_pBgmMap1->Play(AUDIO_LOOP);
					}
					else {
						m_pGMain->m_pBgmMap2->Play(AUDIO_LOOP);
					}
				}
				m_dwStatusSub = WALK;
				m_bMovieFlag = FALSE;
			}
			else {
				// 次のレールの位置を登録
				m_nArrNum++;
				if (m_nArrNum == RAIL_MAX) {
					m_nArrNum = 0;
				}
			}
		}
		break;

	case BALLOON:	// 落下からの復帰中の処理
		if (TargetMove(3)) {
			fSpeed = 2.0f;
			m_dwStatusSub = JUMP;
		}
		break;
	}

	// 回転値の修正
	if (m_fRotate < 0.0f) {
		m_fRotate = 360.0 + m_fRotate;
	}

	VECTOR2 oldPosUp = m_vPosUp;
	// マップ線との接触判定と適切な位置への移動
	if (m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline1, pHitmapline2))
	{
		if (pHitmapline1 && pHitmapline1->m_vNormal.y <= 0)	// マップ線が垂直まではＯＫ
		{
			// 壁に触れたら反転処理
			if ((pHitmapline1->m_vNormal.x <= -0.2 || pHitmapline2->m_vNormal.x <= -0.2) && m_nDirIdx == RIGHT) {
				m_nDirIdx = LEFT;
				m_fRotate *= -1;
			}
			else if ((pHitmapline1->m_vNormal.x >= 0.2 || pHitmapline2->m_vNormal.x >= 0.2) && m_nDirIdx == LEFT) {
				m_nDirIdx = RIGHT;
				m_fRotate *= -1;
			}
			else {
				// 垂直でない線に触れたとき
				m_dwStatusSub = WALK;	// マップ線に接触しているときは、ジャンプを歩行に戻す

				// 接地した瞬間１回のみ実行
				if (m_bCollisionGroundFirst) {
					m_bCollisionGroundFirst = FALSE;
					if (m_nDirIdx == RIGHT && oldPosUp.x < 0) {
						// 右向きでジャンプ速度のx座標がマイナスの時
						m_nDirIdx = LEFT;
					}
					else
						if (m_nDirIdx == LEFT && oldPosUp.x > 0) {
							// 左向きでジャンプ速度のx座標がプラスの時
							m_nDirIdx = RIGHT;
						}
				}
				m_fJumpTime = 0;
				m_vJumpSpeed.x = m_vJumpSpeed.y = 0;
			}
		}
	}
	else {
		// 空中にいるときの処理
		if (m_dwStatusSub == RAIL || m_dwStatusSub == BALLOON) {
			// レールに乗っている間、復帰中
			m_fJumpTime = 0;
		}
		else if (m_dwStatusSub != JUMP) {
			m_dwStatusSub = JUMP;
			if (m_nDirIdx == RIGHT) {
				m_vJumpSpeed.x = std::cos(XMConvertToRadians(m_fRotate)) * fSpeed;
				m_vJumpSpeed.y = std::sin(XMConvertToRadians(m_fRotate)) * fSpeed;
			}
			else {
				m_vJumpSpeed.x = std::cos(XMConvertToRadians(m_fRotate)) * fSpeed;
				m_vJumpSpeed.y = -std::sin(XMConvertToRadians(m_fRotate)) * fSpeed;
			}
		}
	}

	// 増分計算
	m_vPos += m_vPosUp;

	if (!m_bFirstFlag) {
		if (pDI->CheckMouse(KD_DAT, DIM_RBUTTON)) {
			// クリック座標をマップ座標に変換
			VECTOR2 clickPos = VECTOR2(pDI->GetMousePos().x, pDI->GetMousePos().y);
			clickPos += m_pGMain->m_vScroll;
			if (!m_isFirstClick) {
				// 初クリック時
				// レール設置
				if (m_nMaterial >= 10) {
					m_pGMain->m_pRailProc->Start(clickPos);
					m_vOldRailPos = clickPos;
					m_nMaterial -= 10;
					m_isFirstClick = TRUE;
				}
			}
			else {
				double distance = Root(clickPos, m_vOldRailPos);
				if (distance >= 24.0) {
					// レール設置
					if (m_nMaterial >= 10) {
						m_pGMain->m_pRailProc->Start(clickPos);
						m_vOldRailPos = clickPos;
						m_nMaterial -= 10;
					}
					else {
						m_isFirstClick = FALSE;
					}
				}
			}
		}
		else {
			m_isFirstClick = FALSE;
		}
	}
}

void CPcObj::MovieCamera()
{
	CDirectInput* pDI = m_pGMain->m_pDI;
	if (m_bOnce) {
		m_pGMain->m_pEffectProc->m_pItemProc->Update();
		m_vTarget = m_vPos;
		m_vPos = m_pGMain->m_pEffectProc->m_pItemProc->GetGoalPos();
		m_dwStatusPhase = 1;
		m_bOnce = FALSE;
	}
	switch (m_dwStatusPhase) {
	case 1:
		if (pDI->CheckKey(KD_DAT, DIK_F)) {
			m_vPos = m_vTarget;
		}
		if (TargetMove(10)) {
			// 到達
			m_pGMain->m_pSeStart->Play();
			m_dwStatusPhase = 2;
			m_nCnt1 = 60 * 4;
			break;
		}
		if (!m_pSprite->m_bFade) {
			if (m_nCnt1 <= 0) {
				m_vPos += m_vPosUp;
			}
			else {
				m_nCnt1--;
			}
		}
		break;

	case 2:
		m_nCnt1--;
		if (m_nCnt1 <= 0) {
			m_pGMain->m_pMapProc->m_bMapMovieFlag = FALSE;
		}
		break;
	}
}

void CPcObj::AddMaterial(int material)
{
	if (m_nHp < m_nMaterial + material) {
		m_nMaterial = m_nHp;
	}
	else {
		m_nMaterial += material;
	}
}