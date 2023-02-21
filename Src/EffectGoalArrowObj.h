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

//======================================================================
// 映像効果・ゴール矢印　オブジェクトクラス
//======================================================================
class CEffectGoalArrowObj : public CBaseObj
{
protected:
	;

public:
	BOOL Start(VECTOR2) override;

	void Update() override;

	// コンストラクタ
	CEffectGoalArrowObj(CGameMain* pGMain);
	~CEffectGoalArrowObj();
};

//======================================================================
// 定数クラス
//======================================================================
class EffectGoalArrowConstruct
{
public:
	static const int ANIM_NUM = 1;

	static const float FLASH_SECOND;

	static const VECTOR2 SPRITE_SRC;
	static const VECTOR2 SPRITE_SIZE;
};