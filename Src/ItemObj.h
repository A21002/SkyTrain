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

#define  ITEMRESQUE   1           // 救急箱
#define  ITEMDOOR1    2           // ドア
#define  ITEMDOOR2	  3
#define  ITEMDOOR3	  4
#define  ITEMGOAL	  5
#define  ITEMFIRSTSLOPE 6
#define  ITEMPCDUMMY	7

//======================================================================
// アイテム　オブジェクトクラス
//======================================================================
class CItemObj : public CBaseObj
{
protected:
	;

public:
	BOOL Start(VECTOR2, DWORD) override;

	void Update() override;

	// コンストラクタ
	CItemObj(CGameMain* pGMain);
	~CItemObj();
};