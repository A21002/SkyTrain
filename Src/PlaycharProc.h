#pragma once
//=============================================================================
//		プレイキャラクターの処理
//=============================================================================

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
#include "Sprite.h"
#include "PlaycharObj.h"

//======================================================================
// プレイキャラクター　プロシージャクラス
class CPcProc : public CBaseProc
{
protected:
	int             m_nPcNum;

public:
	// アクセス関数
	CPcObj* GetPcObjPtr() { return (CPcObj*)GetObjArrayPtr()[0]; }
	int				    GetPcNum() { return m_nPcNum; }
	void				AddPcNum(int Num) { m_nPcNum += Num; }

	CPcProc(CGameMain* pGMain);	// コンストラクタ
	~CPcProc() { ; }
};