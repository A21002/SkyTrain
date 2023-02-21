#pragma once
#include "GameMain.h"

class CSprite;
class CGameMain;

// --------------------------------------------------------------------------------------------------
// 基本オブジェクトクラス
// 
// ＊　オブジェクトとは、ゲーム中に登場する一つ一つの物体、例えばＰＣや、武器の１つなどを指す。
// 　　なお、オブジェクトは、各プロシージャのメンバー配列として宣言する
// --------------------------------------------------------------------------------------------------
class CBaseObj
{
protected:
	CGameMain* m_pGMain;			// ゲームメインクラス　　
	DWORD			m_dwStatus;			// ステータス
	DWORD			m_dwStatusSub;		// ステータスサブ
	DWORD			m_dwStatusPhase;	// ステータスフェーズ
	BOOL			m_bActive;			// TRUE:表示  FALSE:非表示
	CSprite* m_pSprite;			// スプライトオブジェクト
	VECTOR2			m_vPos;				// 表示位置
	VECTOR2			m_vPosUp;			// 表示位置　移動増分
	VECTOR2			m_vOf;				// 表示位置　移動変位
	float			m_fRotate;			// 回転角度
	VECTOR2			m_vCenter;			// 回転中心
	VECTOR2			m_vTarget;			// 移動目的地
	float			m_fJumpTime;		// ジャンプ時間
	VECTOR2			m_vJumpSpeed;		// ジャンプスピード
	float			m_fScale;			// 拡大縮小
	float			m_fAlpha;			// 透明度
	int				m_nAnimNum;			// アニメーション要素数(初期値は２)
	int				m_nAnimIdx;			// アニメーションインデックス数(インデックス位置はＸ方向)
	int				m_nAnimFrm;			// アニメーションフレームカウント
	int				m_nDirIdx;			// 方向アニメーションインデックス数(インデックス位置はＹ方向)
	int				m_nFlashIdx;		// フラッシュアニメーションインデックス数
	int				m_nFlashFrm;		// フラッシュアニメーションフレームカウント
	CBaseObj* m_pOtherObj;		// ぶつかった相手のオブジェクト
	int				m_nCnt1;			// 汎用カウンタ
	int				m_nCnt2;			// 汎用カウンタ2
	int				m_nMaxHp;			// 最大体力
	int				m_nHp;				// 体力
	int				m_nMaxMaterial;		// 最大魔力
	int				m_nMaterial;		// 魔力
	int				m_nAtc;				// 攻撃力
	float			fSpeed;
	int             m_tag;
	int             m_nArrNum;
	BOOL            m_isTouchRail;
	BOOL            m_isFinishedRail;
	BOOL            m_isHit;
	BOOL			m_isBoost;

public:
	virtual			void Update() { ; }
	virtual			void Draw();

	virtual			BOOL Start() { return TRUE; }
	virtual			BOOL Start(VECTOR2 vPos) { return TRUE; }
	virtual			BOOL Start(VECTOR2 vPos, DWORD dwOwner) { return TRUE; }
	virtual			BOOL Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner) { return TRUE; }
	virtual			BOOL Start(VECTOR2 vPos, DWORD dwOwner, VECTOR2* oldPos) { return TRUE; }

	virtual			void  ResetStatus() final;
	virtual			void  SetStatus(TCHAR* FileName) final;
	virtual			void  ResetAnim() final;
	virtual			int  AnimCountup() final;
	virtual			int  FlashCountup() final;
	virtual			BOOL isCollision(CBaseObj*) final;
	virtual         BOOL isLineCross(VECTOR2 a1, VECTOR2 a2, VECTOR2 b1, VECTOR2 b2) final;
	virtual         BOOL CheckRange(float l, float r, float pt) final;
	virtual			BOOL isCollisionClick(int nMx, int nMy) final;
	virtual			BOOL Hitcheck(CBaseObj*);

	virtual			VECTOR2 GetCenterPos();

	// 追加
	virtual			VECTOR2 GetNextRailPos() { return VECTOR2(0, 0); }


	// 目的地へ向かう関数
	virtual			BOOL TargetMove(float speed);

	// アクセス関数
	BOOL	GetActive() { return m_bActive; }
	void	SetActive(BOOL bActive) { m_bActive = bActive; }
	DWORD	GetStatus() { return m_dwStatus; }
	CSprite* GetSprite() { return m_pSprite; }
	VECTOR2	GetPos() { return m_vPos; }				// 表示位置
	void    SetPos(VECTOR2 vPos) { m_vPos = vPos; }
	VECTOR2 GetPosUp() { return m_vPosUp; }
	void    SetPosUp(VECTOR2 vPosUp) { m_vPosUp = vPosUp; }
	void    AddPosUp(VECTOR2 vPosUp) { m_vPosUp += vPosUp; }
	void    SetTarget(VECTOR2 vTarget) { m_vTarget = vTarget; }
	VECTOR2 GetOf() { return m_vOf; }
	int		GetDirIdx() { return m_nDirIdx; }
	void    SetDirIdx(int dir) { m_nDirIdx = dir; }
	int		GetMaxHp() { return m_nMaxHp; }
	int		GetHp() { return m_nHp; }
	void	SetHp(int nHp) { m_nHp = nHp; }
	int		GetMaxMaterial() { return m_nMaxMaterial; }
	int		GetMaterial() { return m_nMaterial; }
	void	SetMaterial(int nMaterial) { m_nMaterial = nMaterial; }
	int		GetAtc() { return m_nAtc; }
	float   GetRotate() { return m_fRotate; }
	void    SetRotate(float rotate) { m_fRotate = rotate; }
	BOOL    GetTouchRail() { return m_isTouchRail; }
	void    SetTouchRail(BOOL touchRail) { m_isTouchRail = touchRail; }
	BOOL	GetFinishedRail() { return m_isFinishedRail; }
	int		GetStatusSub() { return m_dwStatusSub; }
	void    SetStatusSub(DWORD dwStatusSub) { m_dwStatusSub = dwStatusSub; }
	float   GetSpeed() { return fSpeed; }
	void	SetSpeed(float speed) { fSpeed = speed; }

	// コンストラクタ（共通オブジェクトの初期化）
	CBaseObj(CGameMain* pGMain);
	virtual ~CBaseObj();
};