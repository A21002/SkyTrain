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

#define  ITEMRESQUE		1           // 救急箱
#define  ITEMGOAL		2
#define  ITEMFIRSTSLOPE	3
#define  ITEMPCDUMMY	4

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

//======================================================================
// 定数クラス
//======================================================================
class ItemConstruct
{
public:
	static const int IMAGE_RESQUE_WIDTH = 48;
	static const int IMAGE_RESQUE_HEIGHT = 48;
	static const int IMAGE_GOAL_WIDTH = 188;
	static const int IMAGE_GOAL_HEIGHT = 100;
};