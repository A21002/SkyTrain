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

#define ENM_LAVA_MAX 50

//============================================================================
// Big溶岩の敵　プロシージャクラス
//============================================================================
class CEnmLavaProc : public CBaseProc
{
protected:
	;

public:
	void   Update() override;

	// コンストラクタ
	CEnmLavaProc(CGameMain* pGMain);
	~CEnmLavaProc() { ; }
};