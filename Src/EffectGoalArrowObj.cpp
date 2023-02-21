#include "EffectGoalArrowObj.h"

//======================================================================
// 定数クラス
//======================================================================
const VECTOR2 EffectGoalArrowConstruct::SPRITE_SRC = VECTOR2(200, 400);
const VECTOR2 EffectGoalArrowConstruct::SPRITE_SIZE = VECTOR2(95, 88);
const float EffectGoalArrowConstruct::FLASH_SECOND = 0.5f;

//------------------------------------------------------------------------
//	映像効果・ゴール矢印オブジェクトのコンストラクタ	
//
//  引数　なし
//------------------------------------------------------------------------
CEffectGoalArrowObj::CEffectGoalArrowObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageChar, EffectGoalArrowConstruct::SPRITE_SRC.x, EffectGoalArrowConstruct::SPRITE_SRC.y,
		EffectGoalArrowConstruct::SPRITE_SIZE.x, EffectGoalArrowConstruct::SPRITE_SIZE.y);
	m_nAnimNum = EffectGoalArrowConstruct::ANIM_NUM;
}

// ---------------------------------------------------------------------------
// 映像効果・ゴール矢印オブジェクトのデストラクタ
// ---------------------------------------------------------------------------
CEffectGoalArrowObj::~CEffectGoalArrowObj()
{
	SAFE_DELETE(m_pSprite);
}

//-----------------------------------------------------------------------------
// 映像効果・ゴール矢印オブジェクトの開始
//
//   VECTOR2 vPos    発生位置
//
//   戻り値　　TRUE
//-----------------------------------------------------------------------------
BOOL	CEffectGoalArrowObj::Start(VECTOR2 vPos)
{
	m_bActive = TRUE;
	m_vPos = vPos;	// 発生位置
	m_nCnt1 = 60 * EffectGoalArrowConstruct::FLASH_SECOND;
	return TRUE;
}

//-----------------------------------------------------------------------------
// 映像効果・ゴール矢印オブジェクトの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CEffectGoalArrowObj::Update()
{
	if (m_bActive)
	{
		if (m_nCnt1 >= 0) {
			Draw();
		}
		else if (m_nCnt1 <= -1 * 60 * EffectGoalArrowConstruct::FLASH_SECOND) {
			m_nCnt1 = 60 * EffectGoalArrowConstruct::FLASH_SECOND;
		}
		m_nCnt1--;
	}
}