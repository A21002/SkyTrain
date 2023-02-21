#include "EffectBomObj.h"

//============================================================================
// 定数定義
//============================================================================
const VECTOR2 EffectBomConstruct::SPRITE_SRC = VECTOR2(144, 480);
const VECTOR2 EffectBomConstruct::SPRITE_SIZE = VECTOR2(64, 64);

//------------------------------------------------------------------------
//	映像効果・爆発オブジェクトのコンストラクタ	
//
//  引数　なし
//------------------------------------------------------------------------
CEffectBomObj::CEffectBomObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite, EffectBomConstruct::SPRITE_SRC.x, EffectBomConstruct::SPRITE_SRC.y,
		EffectBomConstruct::SPRITE_SIZE.x, EffectBomConstruct::SPRITE_SIZE.y);
	m_nAnimNum = EffectBomConstruct::ANIM_NUM;
}

// ---------------------------------------------------------------------------
// 映像効果・爆発オブジェクトのデストラクタ
// ---------------------------------------------------------------------------
CEffectBomObj::~CEffectBomObj()
{
	SAFE_DELETE(m_pSprite);
}

//-----------------------------------------------------------------------------
// 映像効果・爆発オブジェクトの開始
//
//   VECTOR2 vPos    発生位置
//
//   戻り値　　TRUE
//-----------------------------------------------------------------------------
BOOL	CEffectBomObj::Start(VECTOR2 vPos)
{
	m_bActive = TRUE;
	m_dwStatus = NORMAL;
	m_dwStatusSub = STOP;
	m_dwStatusPhase = 0;
	m_vPos = vPos;	// 発生位置
	m_nAnimIdx = 0;

	return TRUE;
}

//-----------------------------------------------------------------------------
// 映像効果・爆発オブジェクトの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CEffectBomObj::Update()
{
	if (m_bActive)
	{
		if (AnimCountup() == 1)
		{
			// アニメーション終了
			m_bActive = FALSE;
		}
		Draw();
	}
}