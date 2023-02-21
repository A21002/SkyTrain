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
// 大砲の敵　オブジェクトクラス
//============================================================================
class CEnmCannonObj : public CBaseObj
{
protected:
	int m_nWaitTime;

public:
	BOOL Start(VECTOR2 vPos, DWORD dwOwner) override;
	void Update() override;

	// コンストラクタ
	CEnmCannonObj(CGameMain* pGMain);
	~CEnmCannonObj();
};