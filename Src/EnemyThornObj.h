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

//============================================================================
// ハリセンボンの敵　オブジェクトクラス
//============================================================================
class CEnmThornObj : public CBaseObj
{
protected:
	int m_nWaitTime;
public:
	BOOL Start(VECTOR2 vPos) override;
	void Update() override;

	// コンストラクタ
	CEnmThornObj(CGameMain* pGMain);
	~CEnmThornObj();
};