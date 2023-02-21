//=============================================================================
//		基本プロシージャ・基本オブジェクトクラス処理
//=============================================================================
#pragma once
#include "GameMain.h"
#include "BaseObj.h"

class CSprite;
class CGameMain;
class CBaseObj;

// --------------------------------------------------------------------------------------------------
// 基本プロシージャクラス
//
//   ＊　プロシージャとは、「複数の処理を一つにまとめたもの」という意味
//       複数のオブジェクトや下位プロシージャをコントロールするクラスのこと
// --------------------------------------------------------------------------------------------------
class  CBaseProc
{
protected:
	CGameMain* m_pGMain;				// ゲームメインクラス

	// 下位のプロシージャポインタ配列は、プロシージャを階層構造にして管理するときに使用する
	// オブジェクトポインタ配列は、プロシージャの中にオブジェクトを配置して管理するときに使用する
	// 一般的には、どちらか片方のみを使用すること
	std::vector<CBaseProc*>  m_pProcArray;  // 下位のプロシージャポインタ配列
	std::vector<CBaseObj*>   m_pObjArray;	// オブジェクトポインタ配列

	int				m_nMaxwaitTime;		// 最大待ち時間
	int				m_nWaitTime;		// 現在の待ち時間
	int				m_nStartFlag;		// 開始フラグ

public:
	// 全体更新処理（全てのプロシージャやオブジェクトを読み下して更新処理をする）
	virtual void	UpdateAll() final;

	// 更新処理（UpdateAll()の中で起動。プロシージャの更新処理）
	virtual void    Update() { ; }

	// あたり判定（全てのプロシージャやオブジェクトを読み下して処理をする）
	virtual BOOL	Hitcheck(CBaseObj*) final;

	// アクセス関数
	std::vector<CBaseProc*> GetProcArrayPtr() { return m_pProcArray; } // 下位のプロシージャポインタ配列のアドレスを返す
	std::vector<CBaseObj*>  GetObjArrayPtr() { return m_pObjArray; }  // オブジェクトポインタ配列のアドレスを返す

	int GetStartFlag() { return m_nStartFlag; }
	void SetStartFlag(int nFlg) { m_nStartFlag = nFlg; }

	// コンストラクタ（基本プロシージャの初期化）
	CBaseProc(CGameMain* pGMain) {
		m_pGMain = pGMain;		// ゲームメインクラス
		m_nMaxwaitTime = 0;		// 最大待ち時間
		m_nWaitTime = 0;		// 現在の待ち時間
		m_nStartFlag = 0;		// 開始フラグ
	}
	// デストラクタ（プロシージャとオブジェクトの解放）
	virtual         ~CBaseProc();

};