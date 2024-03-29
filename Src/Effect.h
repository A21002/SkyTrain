//=============================================================================
//		映像効果の処理
//=============================================================================
#pragma once

//警告非表示
#pragma warning(disable : 4005)
#pragma warning(disable : 4244)
#pragma warning(disable : 4018)

//ヘッダーファイルのインクルード
#include <stdio.h>
#include <windows.h>

#include "Main.h"
#include "Direct3D.h"
#include "XAudio.h"
#include "Dinput.h"
#include "Sprite.h"
#include "EffectBomProc.h"
#include "EffectSmokeProc.h"
#include "EffectGoalArrowProc.h"
#include "ItemProc.h"

// 映像効果　プロシージャクラス
class CEffectProc : public CBaseProc
{
public:
	CEffectBomProc* m_pEffectBomProc;
	CEffectSmokeProc* m_pEffectSmokeProc;
	CEffectGoalArrowProc* m_pEffectGoalArrowProc;
	CItemProc* m_pItemProc;

public:
	void  SetNonActive();

	CEffectProc(CGameMain* pGMain);	// コンストラクタ
	~CEffectProc() { ; }	// デストラクタ
};
