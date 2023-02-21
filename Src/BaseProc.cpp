//=============================================================================
//		基本プロシージャ・基本オブジェクトクラス処理
//=============================================================================
#include  "BaseProc.h"
#include  "BaseObj.h"

//------------------------------------------------------------------------
//	基本プロシージャクラスのデストラクタ	
//  （全てのプロシージャやオブジェクトを読み下して削除する）
//
//  引数　なし
//------------------------------------------------------------------------
CBaseProc::~CBaseProc()
{
	// プロシージャポインタ配列の削除
	for (DWORD i = 0; i < m_pProcArray.size(); i++)
	{
		SAFE_DELETE(m_pProcArray[i]);
	}
	// オブジェクトポインタ配列の削除
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		SAFE_DELETE(m_pObjArray[i]);
	}
}

//------------------------------------------------------------------------
//	基本プロシージャクラスの全体更新処理	
//  （全てのプロシージャやオブジェクトを読み下して更新処理をする）
//
//  引数　なし
//------------------------------------------------------------------------
void CBaseProc::UpdateAll()
{
	Update();                              // プロシージャの更新処理
	if (m_nWaitTime > 0) m_nWaitTime--;    // ウェイトタイマーのカウントダウン

	// オブジェクトポインタ配列の更新
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		m_pObjArray[i]->Update();          // オブジェクトの更新処理
	}

	// 下位のプロシージャポインタ配列の更新
	for (DWORD i = 0; i < m_pProcArray.size(); i++)
	{
		m_pProcArray[i]->UpdateAll();      // 下位のプロシージャの全体更新処理（再帰処理）
	}
}