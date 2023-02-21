//=============================================================================
//      武器の処理
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
#include "XAudio.h"
#include "Dinput.h"
#include "Sprite.h"

#include "WeaponMissileProc.h"
#include "WeaponCannonProc.h"

//======================================================================
// 武器全体のメインプロシージャクラス
//======================================================================
class CWeaponProc : public CBaseProc
{
public:
	CWeaponMissileProc* m_pWeaponMissileProc;
	CWeaponCannonProc* m_pWeaponCannonProc;

public:

	CWeaponProc(CGameMain* pGMain);	// コンストラクタ
	~CWeaponProc() { ; }
};
