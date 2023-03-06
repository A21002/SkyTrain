#include "EffectSmokeObj.h"
#include "PlaycharProc.h"

//======================================================================
// 定数クラス
//======================================================================
const VECTOR2 EffectSmokeConstruct::SPRITE_SRC_RIGHT = VECTOR2(0, 799);
const VECTOR2 EffectSmokeConstruct::SPRITE_SRC_LEFT = VECTOR2(0, 1081);
const VECTOR2 EffectSmokeConstruct::SPRITE_SIZE = VECTOR2(248, 94);

//------------------------------------------------------------------------
//	映像効果・煙オブジェクトのコンストラクタ	
//
//  引数　なし
//------------------------------------------------------------------------
CEffectSmokeObj::CEffectSmokeObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite, EffectSmokeConstruct::SPRITE_SRC_RIGHT.x, EffectSmokeConstruct::SPRITE_SRC_RIGHT.y,
		EffectSmokeConstruct::SPRITE_SIZE.x, EffectSmokeConstruct::SPRITE_SIZE.y);
	m_nAnimNum = EffectSmokeConstruct::ANIM_NUM;
}

// ---------------------------------------------------------------------------
// 映像効果・煙オブジェクトのデストラクタ
// ---------------------------------------------------------------------------
CEffectSmokeObj::~CEffectSmokeObj()
{
	SAFE_DELETE(m_pSprite);
}

//-----------------------------------------------------------------------------
// 映像効果・煙オブジェクトの開始
//
//   VECTOR2 vPos    発生位置
//
//   戻り値　　TRUE
//-----------------------------------------------------------------------------
BOOL	CEffectSmokeObj::Start(VECTOR2 vPos)
{
	m_bActive = TRUE;
	m_dwStatus = NORMAL;
	m_dwStatusSub = STOP;
	m_dwStatusPhase = PHASE_SMOKE_START;
	m_vPos = vPos;	// 発生位置
	m_nAnimIdx = 1;
	m_nCnt1 = LEFT;

	// 汽笛音を鳴らす
	m_pGMain->m_pSeDash->Play();
	return TRUE;
}

//-----------------------------------------------------------------------------
// 映像効果・煙オブジェクトの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CEffectSmokeObj::Update()
{
	if (m_bActive)
	{
		switch (m_dwStatusPhase) {
		case PHASE_SMOKE_START:		// 煙出現アニメーション
			if (AnimCountup() == 1)
			{
				// 終了後、ループ状態へ遷移
				m_dwStatusPhase = PHASE_SMOKE_LOOP;
				m_nDirIdx = 1;
			}
			break;

		case PHASE_SMOKE_LOOP:		// 煙ループアニメーション
			if (AnimCountup() == 1)
			{
				// 一巡後、プレイヤーの速度を参照して、終了するか決める
				if (m_pGMain->m_pPcProc->GetPcObjPtr()->GetSpeed() < 10.0f) {
					m_dwStatusPhase = PHASE_SMOKE_FINISH;
					m_nDirIdx = 2;
				}
			}
			break;

		case PHASE_SMOKE_FINISH:	// 煙終了アニメーション
			if (AnimCountup() == 1) {
				m_bActive = false;
			}
			break;
		}

		// プレイヤーの左右反転に合わせて煙を反転させる
		if (m_pGMain->m_pPcProc->GetPcObjPtr()->GetDirIdx() == RIGHT) {
			m_pSprite->SetSrc(EffectSmokeConstruct::SPRITE_SRC_RIGHT.x, EffectSmokeConstruct::SPRITE_SRC_RIGHT.y,
				EffectSmokeConstruct::SPRITE_SIZE.x, EffectSmokeConstruct::SPRITE_SIZE.y);
			if (m_nCnt1 == RIGHT) {
				m_vPos.x -= EffectSmokeConstruct::DIFF;
				m_nCnt1 = LEFT;
			}
		}
		else if (m_pGMain->m_pPcProc->GetPcObjPtr()->GetDirIdx() == LEFT) {
			m_pSprite->SetSrc(EffectSmokeConstruct::SPRITE_SRC_LEFT.x, EffectSmokeConstruct::SPRITE_SRC_LEFT.y,
				EffectSmokeConstruct::SPRITE_SIZE.x, EffectSmokeConstruct::SPRITE_SIZE.y);
			if (m_nCnt1 == LEFT) {
				m_vPos.x += EffectSmokeConstruct::DIFF;
				m_nCnt1 = RIGHT;
			}
		}

		// プレイヤーと回転数と増分数を同期
		m_fRotate = m_pGMain->m_pPcProc->GetPcObjPtr()->GetRotate();
		m_vPosUp = m_pGMain->m_pPcProc->GetPcObjPtr()->GetPosUp();

		m_vPos += m_vPosUp;
		Draw();
	}
}