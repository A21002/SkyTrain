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

#define  WEAPON_MISSILE_MAX  100

//======================================================================
// ミサイル　プロシージャクラス
class CWeaponMissileProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CWeaponMissileProc(CGameMain* pGMain);	// コンストラクタ
	~CWeaponMissileProc() { ; }

};