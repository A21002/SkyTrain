#include "BaseObj.h"
#include "BaseProc.h"

//------------------------------------------------------------------------
//  基本オブジェクト
//	コンストラクタ	
//
//  引数　CGameMain* pGMain  // ゲームメインクラス
//------------------------------------------------------------------------
CBaseObj::CBaseObj(CGameMain* pGMain)
{
	// 全体のゼロクリヤー
	// 注意点：クラス中にＳＴＬを宣言しているときは使用してはならない
	ZeroMemory(this, sizeof(CBaseObj));

	m_pGMain = pGMain;			// ゲームメインクラス
	m_dwStatus = NORMAL;
	m_dwStatusSub = NONE;
	m_vCenter.x = -1;			// 回転のX中心は、スプライト中心
	m_vCenter.y = -1;			// 回転のY中心は、スプライト中心
	m_fScale = 1.0f;			// 拡大縮小
	m_fAlpha = 1.0f;			// 透明度
	m_nAnimNum = 2;				// アニメーション要素数(初期値は２)
	m_nArrNum = -1;
	fSpeed = 0.0f;				// 移動速度
	m_tag = NONE;				// 当たり判定などの判別用のタグ
	m_isTouchRail = FALSE;
	m_isFinishedRail = FALSE;
	m_isHit = FALSE;
	m_isBoost = FALSE;
}

//------------------------------------------------------------------------
//  基本オブジェクト
//	デストラクタ	
//------------------------------------------------------------------------
CBaseObj::~CBaseObj()
{
	SAFE_DELETE(m_pSprite);		// 継承先のデストラクタで実行されると思うが、念のため
}

//------------------------------------------------------------------------
//  基本オブジェクト
//	ステータスのリセット処理	
//
//  引数　なし
//
//	戻り値 なし
//------------------------------------------------------------------------
void  CBaseObj::ResetStatus()
{
	m_dwStatus = NORMAL;		// ステータス
	m_dwStatusPhase = 0;		// ステータスフェーズ
}

//------------------------------------------------------------------------
//  基本オブジェクト
//	ステータスの読み取りによる初期化処理	
//
//  引数　TCHAR*
//			読み込みファイル名
//
//	戻り値 なし
//------------------------------------------------------------------------
void CBaseObj::SetStatus(TCHAR* FileName)
{
	const int BUFSIZE = 512;
	TCHAR str[BUFSIZ];
	FILE* fp;

	fp = _tfopen(FileName, _T("r"));
	if (fp) {
		_fgetts(str, BUFSIZE, fp);
		_stscanf_s(str, _T("%d, %d, %d, %d, %d, %f"), &m_nHp, &m_nMaxHp, &m_nMaterial, &m_nMaxMaterial, &m_nAtc, &fSpeed);  // タイトル行
	}
}

//------------------------------------------------------------------------
//  基本オブジェクト
//	アニメーションのリセット処理	
//
//  引数　なし
//
//	戻り値 なし
//------------------------------------------------------------------------
void  CBaseObj::ResetAnim()
{
	m_nAnimIdx = 0;		// アニメーションインデックス数
	m_nAnimFrm = 0;		// アニメーションフレームカウント
	m_nFlashIdx = 0;		// フラッシュアニメーションインデックス数
	m_nFlashFrm = 0;		// フラッシュアニメーションフレームカウント
}

//------------------------------------------------------------------------
//  基本オブジェクト
//	アニメーションのカウントアップ処理	
//
//  引数　なし
//
//	戻り値 int
//         アニメーション継続中:0　　　　アニメーション終了:1
//------------------------------------------------------------------------
int  CBaseObj::AnimCountup()
{
	int ret = 0;
	int speed = 10;

	if (m_nAnimNum <= 1) return 1;

	m_nAnimFrm++;
	if (m_nAnimFrm >= speed) {
		m_nAnimFrm = 0;
		m_nAnimIdx++;
		if (m_nAnimIdx >= m_nAnimNum) {
			m_nAnimIdx = 0;
			ret = 1;
		}
	}
	return ret;
}

//------------------------------------------------------------------------
//  基本オブジェクト
//	フラッシュアニメーションのカウントアップ処理	
//
//  引数　なし
//
//	戻り値 int
//         アニメーション継続中:0　　　　アニメーション終了:1
//------------------------------------------------------------------------
int  CBaseObj::FlashCountup()
{
	int ret = 0;
	int speed = 2;
	int num = 2;

	m_nFlashFrm++;
	if (m_nFlashFrm >= speed) {
		m_nFlashFrm = 0;
		m_nFlashIdx++;
		if (m_nFlashIdx >= num) {
			m_nFlashIdx = 0;
			ret = 1;
		}
	}
	return ret;
}

//------------------------------------------------------------------------
//  基本オブジェクト
//	描画メソッド	
// （ スケールと回転を考慮して描画　）
// （ スクロールを考慮して描画　）
//
//  引数　なし
//
//	戻り値 なし
//------------------------------------------------------------------------
void  CBaseObj::Draw()
{
	VECTOR2 vScr = m_pGMain->m_vScroll;  // ---------スクロール
	int cx, cy;
	if (m_bActive) {
		// 透明度
		if (m_nFlashIdx == 0)
		{
			if (m_pSprite->m_bFade) {
				m_pSprite->m_vDiffuse.w = m_pSprite->m_fFadeDiffuse;
			}
			else {
				m_pSprite->m_vDiffuse.w = m_fAlpha;
			}
		}
		else {
			m_pSprite->m_vDiffuse.w = m_fAlpha * 0.2f; // 透明に近くする
		}

		// アニメーション
		m_pSprite->m_ofX = m_pSprite->GetDestWidth() * m_nAnimIdx;
		m_pSprite->m_ofY = m_pSprite->GetDestHeight() * m_nDirIdx;

		if (m_fRotate == 0) {	// 回転しないとき

			MATRIX4X4 mWorld, mScale;
			mWorld = XMMatrixTranslation((m_vPos.x + m_vOf.x - vScr.x), (m_vPos.y + m_vOf.y - vScr.y), 0);
			mScale = XMMatrixScaling(m_fScale, m_fScale, 1.0f);
			mWorld = mScale * mWorld;

			// 画面外は描画しない
			if (mWorld._41 + m_pSprite->GetDestWidth() * m_fScale  < 0 || mWorld._41 > WINDOW_WIDTH ||
				mWorld._42 + m_pSprite->GetDestHeight() * m_fScale < 0 || mWorld._42 > WINDOW_HEIGHT)
			{
				;
			}
			else {
				m_pSprite->Draw(mWorld);
			}
		}
		else {			// 回転するとき
			if (m_vCenter.x == -1) {// 回転中心Ｘ座標の設定（-1のときはキャラクタ中心）
				cx = m_pSprite->GetDestWidth() / 2;
			}
			else {
				cx = (int)m_vCenter.x;
			}
			if (m_vCenter.y == -1) {// 回転中心Ｙ座標の設定（-1のときはキャラクタ中心）
				cy = m_pSprite->GetDestHeight() / 2;
			}
			else {
				cy = (int)m_vCenter.y;
			}
			// 回転マトリックスの作成
			MATRIX4X4 mWorld, mCenter, mRot, mScale;
			mWorld = XMMatrixTranslation((m_vPos.x + m_vOf.x - vScr.x), (m_vPos.y + m_vOf.y - vScr.y), 0);
			mScale = XMMatrixScaling(m_fScale, m_fScale, 1.0f);
			mCenter = XMMatrixTranslation(cx, cy, 0);
			mRot = XMMatrixRotationZ(XMConvertToRadians(m_fRotate));
			mWorld = mRot * mCenter * mScale * mWorld;
			mCenter = XMMatrixTranslation(-cx, -cy, 0);
			mWorld = mCenter * mWorld;

			// 画面外は描画しない
			if (mWorld._41 + m_pSprite->GetDestWidth() * m_fScale  < 0 || mWorld._41 > WINDOW_WIDTH ||
				mWorld._42 + m_pSprite->GetDestHeight() * m_fScale < 0 || mWorld._42 > WINDOW_HEIGHT)
			{
				;
			}
			else {
				m_pSprite->Draw(mWorld);
			}
		}
	}
}

//------------------------------------------------------------------------
//  基本オブジェクト
//  オブジェクト同士の衝突判定メソッド（スケールを考慮）
//
//  引数
//    CBaseObj*  pObj :  対象のオブジェクト
//
//	戻り値 BOOL
//        接触している:TRUE　　　　接触していない:FALSE
//------------------------------------------------------------------------
BOOL  CBaseObj::isCollision(CBaseObj* pObj)
{
	// オブジェクトが表示されていること
	if (!m_bActive || !pObj->m_bActive) return FALSE;

	// 衝突判定
	BOOL bRet = FALSE;
	VECTOR2 a[4], b[4];
	DWORD  w1, w2, h1, h2;

	// PCの判定ボックス
	a[0] = m_vPos;
	w1 = m_pSprite->GetDestWidth() * m_fScale;
	a[1].x = w1 * std::cos(XMConvertToRadians(m_fRotate)) + a[0].x;
	a[1].y = a[0].y - w1 * std::sin(XMConvertToRadians(m_fRotate));
	h1 = m_pSprite->GetDestHeight() * m_fScale;
	a[2].x = h1 * std::sin(XMConvertToRadians(m_fRotate)) + a[1].x;
	a[2].y = h1 * std::cos(XMConvertToRadians(m_fRotate)) + a[1].y;
	a[3].x = a[2].x - w1 * std::cos(XMConvertToRadians(m_fRotate));
	a[3].y = w1 * std::sin(XMConvertToRadians(m_fRotate)) + a[2].y;

	// 相手の判定ボックス
	b[0] = pObj->m_vPos;
	w2 = pObj->m_pSprite->GetDestWidth() * pObj->m_fScale;
	b[1].x = w2 * std::cos(XMConvertToRadians(pObj->m_fRotate)) + b[0].x;
	b[1].y = b[0].y - w2 * std::sin(XMConvertToRadians(pObj->m_fRotate));
	h2 = pObj->m_pSprite->GetDestHeight() * pObj->m_fScale;
	b[2].x = h2 * std::sin(XMConvertToRadians(pObj->m_fRotate)) + b[1].x;
	b[2].y = h2 * std::cos(XMConvertToRadians(pObj->m_fRotate)) + b[1].y;
	b[3].x = b[2].x - w2 * std::cos(XMConvertToRadians(pObj->m_fRotate));
	b[3].y = w2 * std::sin(XMConvertToRadians(pObj->m_fRotate)) + b[2].y;

	// 各ボックスの辺が交わっているかチェック
	for (int i = 0; i < 4; i++) {
		int a1 = i, a2 = i + 1;
		if (a2 == 4) {
			a2 = 0;
		}
		for (int j = 0; j < 4; j++) {
			int b1 = j, b2 = j + 1;
			if (b2 == 4) {
				b2 = 0;
			}
			bRet = isLineCross(a[a1], a[a2], b[b1], b[b2]);

			if (bRet) {
				break;
			}
		}
		if (bRet) {
			break;
		}
	}
	return bRet;
}

// ----------------------------------------------------------------------------------------
// ２直線の交差チェック
// 　直線ａと直線ｂの交差チェック。
//
// 　戻り値：交差しているとき真。交点座標がhitposに返る
// ----------------------------------------------------------------------------------------
BOOL CBaseObj::isLineCross(VECTOR2 a1, VECTOR2 a2, VECTOR2 b1, VECTOR2 b2)
{
	BOOL bRet = FALSE;
	float d1, d2;
	// 交点　ａｐ
	VECTOR2  ap = VECTOR2(0, 0);

	// 直線の長さが０のとき
	if ((a1.x == a2.x && a1.y == a2.y) ||
		(b1.x == b2.x && b1.x == b2.y)) {
		return bRet;
	}

	// 交点があるか
	float dev = (a2.y - a1.y) * (b2.x - b1.x) - (a2.x - a1.x) * (b2.y - b1.y);
	if (dev == 0) {// 平行線のとき
		return bRet;
	}

	// 交点を求める
	d1 = (b1.y * b2.x - b1.x * b2.y);
	d2 = (a1.y * a2.x - a1.x * a2.y);

	ap.x = d1 * (a2.x - a1.x) - d2 * (b2.x - b1.x);
	ap.x /= dev;
	ap.y = d1 * (a2.y - a1.y) - d2 * (b2.y - b1.y);
	ap.y /= dev;

	// 交点が直線の範囲の中にあるか
	if ((CheckRange(a1.x, a2.x, ap.x) && CheckRange(a1.y, a2.y, ap.y)) &&
		(CheckRange(b1.x, b2.x, ap.x) && CheckRange(b1.y, b2.y, ap.y))) {
		bRet = TRUE;
	}

	return bRet;
}


// ----------------------------------------------------------------------------------------
// 範囲チェック
//
// 　戻り値：ptがｌとｒの間に入っているとき真。
// ----------------------------------------------------------------------------------------
BOOL CBaseObj::CheckRange(float l, float r, float pt)
{
	float low, hi;
	float mgn = 0.05f;	// 誤差

	if (l <= r) {
		low = l;
		hi = r;
	}
	else {
		low = r;
		hi = l;
	}
	low -= mgn;
	hi += mgn;

	if (low <= pt && pt <= hi) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

//------------------------------------------------------------------------
//  基本オブジェクト
//  オブジェクトとクリック位置の衝突判定メソッド（スケールを考慮）
//
//  引数
//    int nMx :  マウス座標　Ｘ座標
//    int nMy :  マウス座標　Ｙ座標
//
//	戻り値 BOOL
//        ヒットしている:TRUE　　　　ヒットしていない:FALSE
//------------------------------------------------------------------------
BOOL  CBaseObj::isCollisionClick(int nMx, int nMy)
{
	BOOL bRet = FALSE;

	// 矩形の判定
	if (m_bActive && (m_vPos.x + m_vOf.x) <= nMx && (m_vPos.x + m_vOf.x) + (m_pSprite->GetDestWidth() * m_fScale) >= nMx &&
		(m_vPos.y + m_vOf.y) <= nMy && (m_vPos.y + m_vOf.y) + (m_pSprite->GetDestHeight() * m_fScale) >= nMy) bRet = TRUE;

	return bRet;

}

//-----------------------------------------------------------------------------
// 基本プロシージャクラスのあたり判定
//
// ・全ての相手プロシージャと相手オブジェクトを読み下しあたり判定を行う
//
//   CBaseObj* pOtherObj      相手のオブジェクト
//
//   戻り値　BOOL
//           TRUE:ヒットしたとき       FALSE：ヒットしていないとき
//
//   判定結果　　
//           ヒットしたときは　　　　相手と自分のオブジェクトのm_pOtherObjに値をセット
//                                   相手と自分のオブジェクトのm_dwStatusにDAMAGEを設定する
//           ヒットしていないときは　相手と自分のオブジェクトのm_pOtherObjにNULLをセット
//-----------------------------------------------------------------------------
BOOL   CBaseProc::Hitcheck(CBaseObj* pOtherObj)
{
	BOOL  bRet = FALSE;

	// 全ての相手とのあたり判定
	for (DWORD i = 0; i < m_pObjArray.size(); i++)  // 全ての相手オブジェクト
	{
		bRet = m_pObjArray[i]->Hitcheck(pOtherObj);  // 相手オブジェクトとのあたり判定
		if (bRet) return bRet;
	}

	for (DWORD i = 0; i < m_pProcArray.size(); i++)  // 下位の相手プロシージャ
	{
		bRet = m_pProcArray[i]->Hitcheck(pOtherObj);  // 相手プロシージャとのあたり判定
		if (bRet) return bRet;
	}

	return bRet;
}

//------------------------------------------------------------------------
//  基本オブジェクト
//  オブジェクト同士のあたり判定メソッド
//
//  isCollisionメソッドを使用してオブジェクト同士のあたり判定を行う
//  接触していれば、両方のオブジェクトのm_dwStatusを DAMAGE に、
//  m_pOtherObjに相手のオブジェクトを設定する。
//
//  引数
//    CBaseObj* pObj:  相手のオブジェクト
//
//	戻り値 BOOL
//        ヒットしている:TRUE　　　　ヒットしていない:FALSE
//------------------------------------------------------------------------
BOOL  CBaseObj::Hitcheck(CBaseObj* pObj)
{
	if (m_dwStatus == NORMAL && pObj->m_dwStatus == NORMAL && isCollision(pObj))
	{
		switch (pObj->m_tag) {
		case RAIL:
			// レールと当たった際の処理
			pObj->m_isHit = TRUE;
			if (m_dwStatusSub != RAIL) {
				m_dwStatusSub = RAIL;
				m_nArrNum = pObj->m_nArrNum;
			}
			break;

		case BALLOON:
			// 風船と当たった際の処理
			pObj->m_dwStatus = DEAD;
			break;

		default:
			if (!m_isBoost) {
				m_dwStatus = DAMAGE;
			}
			pObj->m_dwStatus = DAMAGE;
			break;
		}
		m_pOtherObj = pObj;
		pObj->m_pOtherObj = this;
		return TRUE;
	}
	return FALSE;
}

//------------------------------------------------------------------------
//  基本オブジェクト
//  スプライトの中心点の座標を求める
//
//  引数
//    なし
//
//	戻り値 VECTOR2
//        スプライト中心点の座標
//------------------------------------------------------------------------
VECTOR2  CBaseObj::GetCenterPos()
{
	VECTOR2 vPos = m_vPos;
	if (m_pSprite)
	{
		vPos.x += m_pSprite->GetSrcWidth() / 2;
		vPos.y += m_pSprite->GetSrcHeight() / 2;
	}
	return vPos;
}

//------------------------------------------------------------------------
// 目的地（targetX,Y）への移動処理
//   引数　　：　speed:一回の移動量
//   戻り値　：　true：目的地に達した　　false:まだ目的地に達していない
//   オブジェクトに設定する値　：　m_vPosUpに移動量を設定する
//------------------------------------------------------------------------
BOOL CBaseObj::TargetMove(float speed)
{
	float mvX, mvY, n;
	BOOL ret = FALSE;

	if (m_vPos.x == m_vTarget.x && m_vPos.y == m_vTarget.y) {  // 目的地に達したとき
		m_vPosUp.x = 0;
		m_vPosUp.y = 0;
		ret = TRUE; // 目的地に達した
	}
	else {    // 目的地への移動処理

		mvX = m_vTarget.x - m_vPos.x;   // 目的地までのＸ方向の変位
		mvY = m_vTarget.y - m_vPos.y;   // 目的地までのＹ方向の変位

		if (abs(mvX) >= abs(mvY)) {   // Ｘ方向の距離が長いとき
			if (abs(mvX) < speed) {        // １回の移動量より近接しているとき
				m_vPosUp.x = mvX;
				m_vPosUp.y = mvY;
			}
			else {
				if (mvX >= 0) {
					m_vPosUp.x = speed; // Ｘ方向の移動量をspeedにする
				}
				else {
					m_vPosUp.x = -speed; // Ｘ方向の移動量を-speedにする
				}
				n = abs(mvX / speed);
				m_vPosUp.y = floor(mvY / n); // Ｘ方向の移動量に合わせて、Ｙ方向の移動量を設定する
			}
		}
		else {                                // Ｙ方向の距離が長いとき
			if (abs(mvY) < speed) {        // １回の移動量より近接していると
				m_vPosUp.x = mvX;
				m_vPosUp.y = mvY;
			}
			else {
				if (mvY >= 0) {
					m_vPosUp.y = speed; // Ｙ方向の移動量をspeedにする
				}
				else {
					m_vPosUp.y = -speed; // Ｙ方向の移動量を-speedにする
				}
				n = abs(mvY / speed);
				m_vPosUp.x = floor(mvX / n); // Ｙ方向の移動量に合わせて、Ｘ方向の移動量を設定する
			}
		}
		ret = FALSE;    // まだ目的地に達していない
	}

	return ret;
}