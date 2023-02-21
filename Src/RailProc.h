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

#define RAIL_MAX 120

//=========================================================================
// レール　プロシージャクラス
//=========================================================================
class CRailProc : public CBaseProc
{
protected:
	VECTOR2 m_vLastRightPos[RAIL_MAX];
	VECTOR2 m_vLastLeftPos[RAIL_MAX];
	int     m_nGenerationId;

public:
	BOOL Start(VECTOR2 vPos);
	BOOL CheckNextObjActive(DWORD i);
	VECTOR2 GetLinkPos(DWORD i, VECTOR2 pos);
	FLOAT GetObjRotate(DWORD i, CBaseObj* pObj);
	VECTOR2 GetNewRailPos();

	CRailProc(CGameMain* pGMain);	// コンストラクタ
	~CRailProc() { ; }				// デストラクタ

	// アクセス関数
	void SetLastRightPos(VECTOR2 pos, DWORD i);
	void SetLastLeftPos(VECTOR2 pos, DWORD i);
	VECTOR2 GetLastPos(DWORD i, CBaseObj* pObj);
};