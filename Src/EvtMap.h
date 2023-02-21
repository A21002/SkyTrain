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
// イベントマップクラスの定義
// 		座標｛Ｘ座標、Ｙ座標｝、イベントＩＤ、イベントＮｏ(種類を論理和で)、汎用カウンタ
//		イベントＩＤ　1:ＰＣのスタート位置　2:アイテム　3:敵
//		イベントＮｏ　0x01 泉の水    0x02 がまの敵    0x04 オオカミの敵
//					　0x10 救急箱    0x20 扉
//----------------------------------------------------------------------------
class  CEvtMap
{
public:
	VECTOR2     m_vStart;		// 座標
	int         m_nEvtID;		// イベントＩＤ
	DWORD       m_dwEvtNo;		// イベントＮｏ
	int         m_nCnt1;		// 汎用カウンタ
public:
	// コンストラクタ
	CEvtMap()
	{
		m_vStart = VECTOR2(0, 0);
		m_nEvtID = 0;
		m_dwEvtNo = 0;
		m_nCnt1 = 0;
	}
	CEvtMap(VECTOR2 vStart, int nEvtID, DWORD dwEvtNo, int nCnt1)
	{
		m_vStart = vStart;
		m_nEvtID = nEvtID;
		m_dwEvtNo = dwEvtNo;
		m_nCnt1 = nCnt1;
	}
};