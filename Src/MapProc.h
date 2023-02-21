//=============================================================================
//		マップの処理
//=============================================================================
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
#include "Map.h"
#include "RailProc.h"

#define   MAP_IMAGE_PATH  _T("Data/")
#define   MAP_MAX   2

#define   STAGE1_NO 1
#define   STAGE2_NO 2

class CGameMain;
//----------------------------------------------------------------------------
// マッププロシージャクラスの定義
//----------------------------------------------------------------------------
class  CMapProc
{
protected:
	CGameMain* m_pGMain;

	// マップ名
	int   m_nMapNo;
	// マップ配列
	CMap* m_pMapArray[MAP_MAX];
	// マップ線の描画フラグ
	BOOL  m_bDrawMapLine;
	// マップイメージ
	CSpriteImage* m_pBakImage;
	CSpriteImage* m_pBakImage2;
	// マップスプライト
	CSprite* m_pSpriteMap;
	CSprite* m_pSpriteBak;
	CSprite* m_pSpriteLine;

public:
	// コンストラクタ
	CMapProc(CGameMain* pGMain);
	~CMapProc();
	void InitMapAll();
	BOOL MapRead(TCHAR* FileName, CMap*& pMap);
	void MoveMap(int MapNo);
	void SetMap(int);
	void Update();
	void Update2();
	void DrawBack();
	void DrawFore();
	void DrawMapLine();
	BOOL isCollisionMoveMap(CBaseObj* obj, CMapLine*& pHitmapline1);
	BOOL isCollisionMoveMap(CBaseObj* obj, CMapLine*& pHitmapline1, CMapLine*& pHitmapline2);
	BOOL CheckMapcross(CMapLine map, CBaseObj* obj, VECTOR2& hitpos);
	BOOL CheckLinecross(VECTOR2 a1, VECTOR2 a2, VECTOR2 b1, VECTOR2 b2, VECTOR2& hitpos);
	BOOL CheckRange(float l, float r, float pt);
	BOOL CheckMapnear(CMapLine MapLn, CBaseObj* obj, VECTOR2& vHitpos);
	float GetDistance(CMapLine MapLn, CBaseObj* obj);
	float GetLength(VECTOR2 p1, VECTOR2 p2);
	float GetCross(VECTOR2 a, VECTOR2 b);
	float GetDot(VECTOR2 a, VECTOR2 b);
	int   GetMapNo() { return m_nMapNo; }

	BOOL SearchEvt(int nStart, int nEvtID, DWORD dwEvtNo, VECTOR2& vPos, int& nNext);
	BOOL SearchEvt(int nStart, int nEvtID, DWORD dwEvtNo, VECTOR2& vPos, int& nNext, int& dir);

	// マップムービーフラグ
	BOOL  m_bMapMovieFlag;
};
