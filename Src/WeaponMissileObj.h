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
// ミサイル　オブジェクトクラス
//============================================================================
class CWeaponMissileObj : public CBaseObj
{
protected:
	DWORD  m_dwOwner;
	BOOL   m_bOnce;

public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner) override;
	void Update() override;

	// コンストラクタ
	CWeaponMissileObj(CGameMain* pGMain);
	~CWeaponMissileObj();
};

//============================================================================
// 定数クラス
//============================================================================
class WeaponMissileConstruct
{
public:
	static const int SPEED = 6;
	static const int ANIM_NUM = 1;
	static const int DAMAGE_NUM = 10;
	static const int HOMING_AREA = 100;

	static const VECTOR2 SPRITE_SRC;
	static const VECTOR2 SPRITE_SIZE;
};