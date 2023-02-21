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

//======================================================================
// プレイキャラクター　オブジェクトクラス
class CPcObj : public CBaseObj
{
protected:
	int  m_nOldStatusSub;
	VECTOR2 m_vOldRailPos;
	VECTOR2 m_vRailPos;
	BOOL m_isFirstClick;
	BOOL m_bFirstFlag;					// 最初の坂を登ったかの判定フラグ
	BOOL m_bCollisionGroundFirst;		// 地面に触れた最初にのみ、実行するためのフラグ

public:
	void Update() override;
	BOOL Start(VECTOR2 vPos) override;
	void NormalUpdate();
	void MovieCamera();
	void AddMaterial(int material);

	BOOL m_bMovieFlag;
	BOOL m_bLavaStartFlag;
	BOOL m_bOnce;

	// アクセス関数
	BOOL GetClick() { return m_isFirstClick; }

	// コンストラクタ（オブジェクトの初期化）
	CPcObj(CGameMain* pGMain);
	~CPcObj();
};