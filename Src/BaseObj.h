#pragma once
#include "GameMain.h"

class CSprite;
class CGameMain;

// --------------------------------------------------------------------------------------------------
// ��{�I�u�W�F�N�g�N���X
// 
// ���@�I�u�W�F�N�g�Ƃ́A�Q�[�����ɓo�ꂷ����̕��́A�Ⴆ�΂o�b��A����̂P�Ȃǂ��w���B
// �@�@�Ȃ��A�I�u�W�F�N�g�́A�e�v���V�[�W���̃����o�[�z��Ƃ��Đ錾����
// --------------------------------------------------------------------------------------------------
class CBaseObj
{
protected:
	CGameMain* m_pGMain;			// �Q�[�����C���N���X�@�@
	DWORD			m_dwStatus;			// �X�e�[�^�X
	DWORD			m_dwStatusSub;		// �X�e�[�^�X�T�u
	DWORD			m_dwStatusPhase;	// �X�e�[�^�X�t�F�[�Y
	BOOL			m_bActive;			// TRUE:�\��  FALSE:��\��
	CSprite* m_pSprite;			// �X�v���C�g�I�u�W�F�N�g
	VECTOR2			m_vPos;				// �\���ʒu
	VECTOR2			m_vPosUp;			// �\���ʒu�@�ړ�����
	VECTOR2			m_vOf;				// �\���ʒu�@�ړ��ψ�
	float			m_fRotate;			// ��]�p�x
	VECTOR2			m_vCenter;			// ��]���S
	VECTOR2			m_vTarget;			// �ړ��ړI�n
	float			m_fJumpTime;		// �W�����v����
	VECTOR2			m_vJumpSpeed;		// �W�����v�X�s�[�h
	float			m_fScale;			// �g��k��
	float			m_fAlpha;			// �����x
	int				m_nAnimNum;			// �A�j���[�V�����v�f��(�����l�͂Q)
	int				m_nAnimIdx;			// �A�j���[�V�����C���f�b�N�X��(�C���f�b�N�X�ʒu�͂w����)
	int				m_nAnimFrm;			// �A�j���[�V�����t���[���J�E���g
	int				m_nDirIdx;			// �����A�j���[�V�����C���f�b�N�X��(�C���f�b�N�X�ʒu�͂x����)
	int				m_nFlashIdx;		// �t���b�V���A�j���[�V�����C���f�b�N�X��
	int				m_nFlashFrm;		// �t���b�V���A�j���[�V�����t���[���J�E���g
	CBaseObj* m_pOtherObj;		// �Ԃ���������̃I�u�W�F�N�g
	int				m_nCnt1;			// �ėp�J�E���^
	int				m_nCnt2;			// �ėp�J�E���^2
	int				m_nMaxHp;			// �ő�̗�
	int				m_nHp;				// �̗�
	int				m_nMaxMaterial;		// �ő喂��
	int				m_nMaterial;		// ����
	int				m_nAtc;				// �U����
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

	// �ǉ�
	virtual			VECTOR2 GetNextRailPos() { return VECTOR2(0, 0); }


	// �ړI�n�֌������֐�
	virtual			BOOL TargetMove(float speed);

	// �A�N�Z�X�֐�
	BOOL	GetActive() { return m_bActive; }
	void	SetActive(BOOL bActive) { m_bActive = bActive; }
	DWORD	GetStatus() { return m_dwStatus; }
	CSprite* GetSprite() { return m_pSprite; }
	VECTOR2	GetPos() { return m_vPos; }				// �\���ʒu
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

	// �R���X�g���N�^�i���ʃI�u�W�F�N�g�̏������j
	CBaseObj(CGameMain* pGMain);
	virtual ~CBaseObj();
};