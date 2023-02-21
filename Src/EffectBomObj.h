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
// 映像効果・爆発　オブジェクトクラス
//======================================================================
class CEffectBomObj : public CBaseObj
{
protected:
	;

public:
	BOOL Start(VECTOR2) override;

	void Update() override;

	// コンストラクタ
	CEffectBomObj(CGameMain* pGMain);
	~CEffectBomObj();
};

//======================================================================
// 定数クラス
//======================================================================

class EffectBomConstruct
{
public:
	static const int ANIM_NUM = 7;

	static const VECTOR2 SPRITE_SRC;
	static const VECTOR2 SPRITE_SIZE;
};