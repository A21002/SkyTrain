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
// 大砲　オブジェクトクラス
//======================================================================
class CWeaponCannonObj : public CBaseObj
{
protected:

public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner) override;
	void Update() override;

	// コンストラクタ
	CWeaponCannonObj(CGameMain* pGMain);
	~CWeaponCannonObj();
};

//======================================================================
// 定数クラス
//======================================================================
class WeaponCannonConstruct
{
public:
	static const int ANIM_NUM = 1;
	static const int DAMAGE_NUM = 100;
	static const int SPEED = 5;

	static const VECTOR2 SPRITE_SRC;
	static const VECTOR2 SPRITE_SIZE;
};