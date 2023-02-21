#pragma once

//警告非表示
#pragma warning(disable : 4005)
#pragma warning(disable : 4244)
#pragma warning(disable : 4018)

//ヘッダーファイルのインクルード
#include <stdio.h>
#include <windows.h>
#include <vector>

#include "Main.h"
#include "Direct3D.h"
#include "XAudio.h"
#include "Dinput.h"
#include "Sprite.h"

//----------------------------------------------------------------------------
// マップ線クラスの定義
// 		始点座標｛Ｘ座標、Ｙ座標｝、終点座標｛Ｘ座標、Ｙ座標｝・・・・
// 		法線座標 (開始位置から終了位置に向かって、左手方向に法線が出来る)
//----------------------------------------------------------------------------
class  CMapLine
{
public:
	VECTOR2 m_vStart;		// 始点座標
	VECTOR2 m_vEnd;			// 終点座標
	VECTOR2 m_vNormal;		// 法線座標 (開始位置から終了位置に向かって、左手方向に法線が出来る)

public:
	// コンストラクタ
	CMapLine()
	{
		m_vStart = VECTOR2(0, 0);
		m_vEnd = VECTOR2(0, 0);
		m_vNormal = VECTOR2(0, 0);
	}
};