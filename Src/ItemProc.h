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

#define  ITEM_MAX  100

//======================================================================
// アイテム　プロシージャクラス
//======================================================================
class CItemProc : public CBaseProc
{
public:
	void Update() override;
	CItemProc(CGameMain* pGMain);	// コンストラクタ
	~CItemProc() { ; }	// デストラクタ

	// ゴール座標
	VECTOR2 GetGoalPos();
};