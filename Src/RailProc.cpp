#include "RailProc.h"
#include "RailObj.h"
#include "MapProc.h"
#include "PlaycharProc.h"

// --------------------------------------------------------------------
// レールプロシージャのコンストラクタ
// --------------------------------------------------------------------
CRailProc::CRailProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (DWORD i = 0; i < RAIL_MAX; i++) {
		// m_pObjArrayにレールオブジェクトを生成する
		m_pObjArray.push_back(new CRailObj(m_pGMain));
	}
	for (DWORD i = 0; i < RAIL_MAX; i++) {
		// レールの終端配列を初期化
		m_vLastRightPos[i] = VECTOR2(-1, -1);
		m_vLastLeftPos[i] = VECTOR2(-1, -1);
	}
	m_nGenerationId = 0;
}

// --------------------------------------------------------------------
// レールプロシージャの開始
//
// VECTOR2 vPos		発生位置
//
// 戻り値	正常 : TRUE		発生しなかった : FALSE
// --------------------------------------------------------------------
BOOL CRailProc::Start(VECTOR2 vPos)
{
	m_pObjArray[m_nGenerationId]->Start(vPos, m_nGenerationId);
	m_nGenerationId++;
	if (m_nGenerationId == RAIL_MAX) {
		m_nGenerationId = 0;
	}
	return TRUE;
}

// --------------------------------------------------------------------
// オブジェクト配列の指定されたアドレスのオブジェクトのm_Activeの状態を返す
//
// DWORD i		アドレス
//
// 戻り値	m_Activeの状態
// --------------------------------------------------------------------
BOOL CRailProc::CheckNextObjActive(DWORD i)
{
	if (i >= RAIL_MAX) {
		return m_pObjArray[0]->GetActive();
	}
	return m_pObjArray[i]->GetActive();
}

// --------------------------------------------------------------------
// 自身の後ろのレールを参照し、Posを返す
//
// DWORD i		アドレス
// VECTOR2 pos	生成されたときのマウスカーソルの位置
//
// 戻り値	m_Posの値
// --------------------------------------------------------------------
VECTOR2 CRailProc::GetLinkPos(DWORD i, VECTOR2 pos)
{
	// 最初のレールに呼ばれたとき
	int id = i - 1;
	if (id < 0) {
		id = RAIL_MAX - 1;
	}
	if (!m_pObjArray[id]->GetActive()) {
		return pos;
	}

	return m_pObjArray[id]->GetNextRailPos();
}

// --------------------------------------------------------------------
// 自身の後ろのレールを参照し、m_fRotateの値を返す
//
// DWORD i		アドレス
//
// 戻り値	回転角度
// --------------------------------------------------------------------
FLOAT CRailProc::GetObjRotate(DWORD i, CBaseObj* pObj)
{
	if (pObj->GetDirIdx() == RIGHT) {
		return m_pObjArray[i]->GetRotate();
	}
	else {
		return 180 + m_pObjArray[i]->GetRotate();
	}
}

// --------------------------------------------------------------------
// １番最近生成したレールの位置を返す
// --------------------------------------------------------------------
VECTOR2 CRailProc::GetNewRailPos()
{
	int id = m_nGenerationId - 1;
	if (id < 0) {
		id = RAIL_MAX - 1;
	}
	return m_pObjArray[id]->GetPos();
}

//============================================================================
// アクセス関数
//============================================================================
void CRailProc::SetLastRightPos(VECTOR2 pos, DWORD i)
{
	m_vLastRightPos[i] = pos;
}

void CRailProc::SetLastLeftPos(VECTOR2 pos, DWORD i)
{
	m_vLastLeftPos[i] = pos;
}

VECTOR2 CRailProc::GetLastPos(DWORD i, CBaseObj* pObj) {
	VECTOR2 ret;
	if (i != 0) {
		if (m_pGMain->m_pRailProc->m_pObjArray[i - 1]->GetFinishedRail()) {
			ret = VECTOR2(-1, -1);
			return ret;
		}
	}
	if (pObj->GetDirIdx() == RIGHT) {
		ret = m_vLastRightPos[i];
	}
	else {
		ret = m_vLastLeftPos[i];
	}

	return ret;
}