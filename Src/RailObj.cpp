#include "RailObj.h"
#include "RailProc.h"
#include "PlaycharProc.h"

//=========================================================================
// 定数クラス
//=========================================================================
const VECTOR2 RailConstruct::SPRITE_SRC = VECTOR2(0, 0);
const VECTOR2 RailConstruct::SPRITE_SIZE = VECTOR2(24, 11);

// --------------------------------------------------------------------
// レールオブジェクトのコンストラクタ
// --------------------------------------------------------------------
CRailObj::CRailObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageRail, RailConstruct::SPRITE_SRC.x, RailConstruct::SPRITE_SRC.y,
		RailConstruct::SPRITE_SIZE.x, RailConstruct::SPRITE_SIZE.y);
	m_nAnimNum = RailConstruct::ANIM_NUM;
	m_tag = RAIL;
}

// --------------------------------------------------------------------
// レールオブジェクトのデストラクタ
// --------------------------------------------------------------------
CRailObj::~CRailObj()
{
	SAFE_DELETE(m_pSprite);
}

// --------------------------------------------------------------------
// レールオブジェクトの開始
// 
// VECTOR2 vPos		発生位置
// 
// 戻り値	正常 : TRUE
// --------------------------------------------------------------------
BOOL CRailObj::Start(VECTOR2 vPos, DWORD dwOwner)
{
	m_bActive = TRUE;
	// 発生位置
	m_vPos = vPos;

	// プロシージャのオブジェクト配列内で自身が何番目か
	m_nArrNum = dwOwner;

	// 自身の後ろに既にレールが生成されているか
	if (m_pGMain->m_pPcProc->GetPcObjPtr()->GetClick()) {
		// 後ろのオブジェクトの終端に位置を合わせて、レールがつながっているようにする
		m_vPos = m_pGMain->m_pRailProc->GetLinkPos(m_nArrNum, m_vPos);
	}

	// 回転軸を左上にする
	m_vCenter = VECTOR2(0, 0);

	// 終端位置の登録
	m_pGMain->m_pRailProc->SetLastRightPos(VECTOR2(m_vPos.x + m_pSprite->GetDestWidth(), m_vPos.y), m_nArrNum);
	m_pGMain->m_pRailProc->SetLastLeftPos(VECTOR2(m_vPos.x + m_pSprite->GetDestWidth(), m_vPos.y), m_nArrNum);
	// レールの残留時間
	m_LimitTime = RailConstruct::LIMIT_TIME;
	// 開始時間
	m_StartTime = clock();

	// マウスの位置に合わせて回転する処理のフラグ
	m_isMoveRotate = TRUE;
	// 自身がつながっているレールの終端か
	m_isFinishedRail = FALSE;
	// １度PCと接触したら以降、接触判定を行わない
	m_isHit = FALSE;
	return TRUE;
}

// --------------------------------------------------------------------
// レールオブジェクトの更新
// --------------------------------------------------------------------
void CRailObj::Update()
{
	if (m_bActive)
	{
		// 経過時間を取得
		double deltaTime = clock() - m_StartTime;

		// 経過時間が残留時間を越えているか
		if (m_LimitTime <= deltaTime / CLOCKS_PER_SEC) {
			// レールの削除
			// ゲージを回復
			m_pGMain->m_pPcProc->GetPcObjPtr()->AddMaterial(10);
			// 移動する際の目標地点をリセット
			m_pGMain->m_pRailProc->SetLastRightPos(VECTOR2(-1, -1), m_nArrNum);
			m_pGMain->m_pRailProc->SetLastLeftPos(VECTOR2(-1, -1), m_nArrNum);
			m_bActive = FALSE;
		}

		// PCとの接触判定
		if (!m_isHit) {
			m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
		}

		// 次のレールが生成されたら回転処理を行わない
		if (m_pGMain->m_pRailProc->CheckNextObjActive(m_nArrNum + 1)) {
			m_isMoveRotate = FALSE;
		}
		// クリックが離されたら、回転処理を行わず、自身をつながったレールの終端という印をつける
		if (!m_pGMain->m_pPcProc->GetPcObjPtr()->GetClick() && m_isMoveRotate) {
			m_isMoveRotate = FALSE;
			m_isFinishedRail = TRUE;
		}

		if (m_isMoveRotate) {
			SetRotate();
		}

		Draw();
	}
}

void CRailObj::SetRotate()
{
	// レールの回転処理
	CDirectInput* pDI = m_pGMain->m_pDI;	// 入力情報を取得

	// マウスポインタの位置を取得
	VECTOR2 mousePos = VECTOR2(pDI->GetMousePos().x, pDI->GetMousePos().y);
	mousePos += m_pGMain->m_vScroll;

	//arctanでラジアン角度を計算
	m_fRotate = -std::atan2(m_vPos.y - mousePos.y, mousePos.x - m_vPos.x);
	// ラジアン角度を度数に変換
	m_fRotate = XMConvertToDegrees(m_fRotate);
	double root = std::sqrt(m_pSprite->GetDestWidth() * m_pSprite->GetDestWidth() + m_pSprite->GetDestHeight() * m_pSprite->GetDestHeight());
	// 回転に合わせて、移動の際の目標地点を再設定
	m_pGMain->m_pRailProc->SetLastRightPos(VECTOR2(std::cos(XMConvertToRadians(m_fRotate)) * root + m_vPos.x,
		m_vPos.y + std::sin(XMConvertToRadians(m_fRotate)) * root), m_nArrNum);
	m_pGMain->m_pRailProc->SetLastLeftPos(VECTOR2(std::cos(XMConvertToRadians(m_fRotate)) * root + m_vPos.x,
		m_vPos.y + std::sin(XMConvertToRadians(m_fRotate)) * root), m_nArrNum);
}

VECTOR2 CRailObj::GetNextRailPos() {
	VECTOR2 ret = m_vPos;
	DWORD hypo = sqrt(m_pSprite->GetSrcWidth() * m_pSprite->GetSrcWidth() + m_pSprite->GetSrcWidth() * m_pSprite->GetSrcWidth());

	ret.x += std::cos(XMConvertToRadians(m_fRotate)) * m_pSprite->GetSrcWidth();
	ret.y += std::sin(XMConvertToRadians(m_fRotate)) * m_pSprite->GetSrcWidth();

	return ret;
}