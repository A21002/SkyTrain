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

#define ENM_CANNON_MAX 10

//============================================================================
// 大砲の敵　プロシージャクラス
//============================================================================
class CEnmCannonProc : public CBaseProc
{
protected:
	;

public:
	void   Update() override;

	// コンストラクタ
	CEnmCannonProc(CGameMain* pGMain);
	~CEnmCannonProc() { ; }
};