#include "PlaycharProc.h"

//------------------------------------------------------------------------
//	ＰＣプロシージャのコンストラクタ	
//
//   なお、オブジェクトのdeleteはCBaseProcのデストラクタで行うため不要
//------------------------------------------------------------------------
CPcProc::CPcProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	m_pObjArray.push_back(new CPcObj(m_pGMain));  // m_pObjArrayにオブジェクトを登録する

	m_nPcNum = 2;
}