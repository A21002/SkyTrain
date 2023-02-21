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

#include "EnemyBalloonObj.h"
//============================================================================
// がまの敵　オブジェクトクラス
//============================================================================
class CEnmTordObj : public CBaseObj
{
protected:
	float m_fMoveWidth;
	int m_nWaitTime;
	CEnmBalloonObj* m_pBalloonObj;

public:
	BOOL Start(VECTOR2 vPos) override;
	void Update() override;

	// コンストラクタ
	CEnmTordObj(CGameMain* pGMain);
	~CEnmTordObj();
};

//============================================================================
// 定数クラス
//============================================================================
class EnmTordConstruct
{
public:
	const static int TARGET_WIDTH = 12;
	const static int WAITTIME = 3;
};