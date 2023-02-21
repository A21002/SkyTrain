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

#include "MapLine.h"
#include "EvtMap.h"

class CGameMain;
//----------------------------------------------------------------------------
// マップ配列クラスの定義
//----------------------------------------------------------------------------
class  CMap
{
public:
	CGameMain* m_pGMain;
	TCHAR                    m_MapFileName[512]; // マップファイル名  
	TCHAR                    m_ImageName[512];  // マップチップイメージファイル名
	CSpriteImage* m_pMapImage;       // マップチップのスプライトイメージ
	int                      m_nMapX;           // 画面の幅　（マップチップが何個分か）
	int                      m_nMapY;           // 画面の高さ（マップチップが何個分か）
	int                      m_nMapchipWidth;   // 一つのマップチップの幅
	int                      m_nMapchipHeight;  // 一つのマップチップの高さ
	int                      m_nMapLnLength;    // マップライン配列の要素数
	int                      m_nEvtMapLength;   // イベントマップ配列の要素数
	int* m_MapBakTbl;	    // マップ配列　背景
	int* m_MapForTbl;	    // マップ配列　前景
	CMapLine* m_MapLn;		    // マップライン配列
	CEvtMap* m_EvtMap;		    // イベントマップ配列

public:
	// コンストラクタ
	CMap(CGameMain* pGMain);
	void InitMap();
	BOOL  MakeERelativeFName(TCHAR* szBaseFullPath, TCHAR* szPath, TCHAR* szERelativeFName);

	~CMap();
};