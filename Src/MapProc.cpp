//=============================================================================
//		�}�b�v�̏���
//=============================================================================
#include "MapProc.h"
#include "PlaycharProc.h"
#include "EnemyProc.h"
#include "Effect.h"

//  CMapProc�N���X  ---------------------------------------------------------------------------------------
//  �R���X�g���N�^
CMapProc::CMapProc(CGameMain* pGMain)
{
	m_pGMain = pGMain;
	m_nMapNo = 0;
	m_bDrawMapLine = FALSE;
	for (DWORD i = 0; i < MAP_MAX; i++)
	{
		m_pMapArray[i] = NULL;
	}
	m_pBakImage2 = new CSpriteImage(m_pGMain->m_pShader, _T("Data/image/Map2_Back.png"));
	m_pBakImage = new CSpriteImage(m_pGMain->m_pShader, _T("Data/image/aozora.png"));
	m_pSpriteMap = new CSprite(m_pGMain->m_pShader); // �X�v���C�g�I�u�W�F�N�g�̐���
	m_pSpriteBak = new CSprite(m_pBakImage);
	m_pSpriteLine = new CSprite(m_pGMain->m_pShader);

	InitMapAll();
}

//  �f�X�g���N�^
CMapProc::~CMapProc()
{
	for (DWORD i = 0; i < MAP_MAX; i++)
	{
		SAFE_DELETE(m_pMapArray[i]);
	}
	SAFE_DELETE(m_pSpriteMap);
	SAFE_DELETE(m_pSpriteBak);
	SAFE_DELETE(m_pSpriteLine);
	SAFE_DELETE(m_pBakImage);
}

// ----------------------------------------------------------------------
// �e�}�b�v�X�N���v�g�t�@�C����ǂݍ���Ń}�b�v�I�u�W�F�N�g�̍쐬
// -----------------------------------------------------------------------
void CMapProc::InitMapAll()
{
	// �X�e�[�W�O�@��̃X�e�[�W
	MapRead(_T("Data/Script/Map1.txt"), m_pMapArray[0]);

	// �X�e�[�W�P�@����̃X�e�[�W
	MapRead(_T("Data/Script/Map2.txt"), m_pMapArray[1]);
}

// ----------------------------------------------------------------------
// �}�b�v�ړ��̏����@�@���ɐڐG�����Ƃ��Ă΂��
// ----------------------------------------------------------------------
void CMapProc::MoveMap(int MapNo)
{
	SetMap(MapNo);	// ���̃}�b�v�͂P
	m_pGMain->m_pEnmProc->SetNonActive();	// �G��S�ď����B�G�̔����t���O�����Z�b�g����
	m_pGMain->m_pEffectProc->SetNonActive();	// �A�C�e����S�ď����B�A�C�e���̔����t���O�����Z�b�g����
}

// ----------------------------------------------------------------------
// �J�n�}�b�v�̐ݒ�
//
// �����@�F�@int no�@�}�b�v�ԍ�
// ----------------------------------------------------------------------
void CMapProc::SetMap(int no)
{
	// �J�n�}�b�v�m�n
	m_nMapNo = no;

	// �}�b�v�p�X�v���C�g�̐ݒ�
	m_pSpriteMap->SetSrc(m_pMapArray[m_nMapNo]->m_pMapImage, 0, 0, m_pMapArray[m_nMapNo]->m_nMapchipWidth, m_pMapArray[m_nMapNo]->m_nMapchipHeight);
	// �o�b�J�n�ʒu�̐ݒ�
	VECTOR2 vPos = VECTOR2(0, 0);
	for (DWORD i = 0; i < m_pMapArray[m_nMapNo]->m_nEvtMapLength; i++)
	{
		if (m_pMapArray[m_nMapNo]->m_EvtMap[i].m_nEvtID == 1)  // �o�b�̃X�^�[�g�ʒu
		{
			vPos = m_pMapArray[m_nMapNo]->m_EvtMap[i].m_vStart;  // �o�b�̃X�^�[�g���W
			break;
		}
	}
	// Select���[�h�łȂ����
	m_bMapMovieFlag = TRUE;
	m_pGMain->m_pPcProc->GetPcObjPtr()->m_bOnce = TRUE;

	// �T�E���h�̍Đ�
	m_pGMain->m_pBgmMovie->Play(AUDIO_LOOP);

	// �o�b�J�n�ʒu��ݒ肵�A�g�o���񕜂���
	m_pGMain->m_pPcProc->GetPcObjPtr()->Start(vPos);
}

// ----------------------------------------------------------------------
// �}�b�v�̍X�V
// ----------------------------------------------------------------------
void  CMapProc::Update()
{
	VECTOR2 vScr;

	// �o�b�̈ʒu����X�N���[�����W��ݒ肷��
	vScr.x = m_pGMain->m_pPcProc->GetPcObjPtr()->GetPos().x + m_pGMain->m_pPcProc->GetPcObjPtr()->GetOf().x + m_pGMain->m_pPcProc->GetPcObjPtr()->GetSprite()->GetSrcWidth() / 2 - WINDOW_WIDTH / 2;
	if (vScr.x > m_pMapArray[m_nMapNo]->m_nMapX * m_pMapArray[m_nMapNo]->m_nMapchipWidth - WINDOW_WIDTH)
		vScr.x = m_pMapArray[m_nMapNo]->m_nMapX * m_pMapArray[m_nMapNo]->m_nMapchipWidth - WINDOW_WIDTH;
	if (vScr.x < 0) vScr.x = 0;

	vScr.y = m_pGMain->m_pPcProc->GetPcObjPtr()->GetPos().y + m_pGMain->m_pPcProc->GetPcObjPtr()->GetOf().y + m_pGMain->m_pPcProc->GetPcObjPtr()->GetSprite()->GetSrcHeight() / 2 - WINDOW_HEIGHT / 2 - 100;
	if (vScr.y > m_pMapArray[m_nMapNo]->m_nMapY * m_pMapArray[m_nMapNo]->m_nMapchipHeight - WINDOW_HEIGHT)
		vScr.y = m_pMapArray[m_nMapNo]->m_nMapY * m_pMapArray[m_nMapNo]->m_nMapchipHeight - WINDOW_HEIGHT;
	if (vScr.y < 0) vScr.y = 0;

	m_pGMain->m_vScroll = vScr;			// �X�N���[�����W��ݒ�

	// �}�b�v���̕`������邩�ǂ���
	if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_P))
	{
		if (m_bDrawMapLine)
		{
			m_bDrawMapLine = FALSE;
		}
		else {
			m_bDrawMapLine = TRUE;
		}
	}
	DrawBack();  // �w�i�}�b�v�̕`��
}

// ----------------------------------------------------------------------
// �}�b�v�̍X�V�Q
// ----------------------------------------------------------------------
void  CMapProc::Update2()
{
	DrawFore();
	if (m_bDrawMapLine) DrawMapLine();
}

// ----------------------------------------------------------------------
// �C�x���g�}�b�v�̒T������
//
// ����
// �@�@int         nStart;		// �T���J�n�ʒu
// �@�@int         nEvtID;		// �C�x���g�h�c
// �@�@DWORD       dwEvtNo;		// �C�x���g�m��
// �@�@VECTOR2 vPos;		// ���W(OUT)
//     int         nNext;       // ���J�n�ʒu(OUT) �ŏI�ɒB������@-1 
//
// �߂�l
//�@�@TRUE:��������  FALSE:������Ȃ�
// ----------------------------------------------------------------------
BOOL  CMapProc::SearchEvt(int nStart, int nEvtID, DWORD dwEvtNo, VECTOR2& vPos, int& nNext)
{
	BOOL bRet = FALSE;

	if (nStart < 0 || nStart >= m_pMapArray[m_nMapNo]->m_nEvtMapLength)
	{
		nNext = -1;
		return bRet;
	}

	for (DWORD i = nStart; i < m_pMapArray[m_nMapNo]->m_nEvtMapLength; i++)
	{
		if (m_pMapArray[m_nMapNo]->m_EvtMap[i].m_nEvtID == nEvtID &&	    // �C�x���g�}�b�v�@ID�@�G�̏o���ʒu
			m_pMapArray[m_nMapNo]->m_EvtMap[i].m_dwEvtNo & dwEvtNo)			// �C�x���g�}�b�v�@NO
		{
			vPos = m_pMapArray[m_nMapNo]->m_EvtMap[i].m_vStart;	// �����ʒu

			nNext = i + 1;  // ���̊J�n�ʒu��ݒ�
			bRet = TRUE;
			break;
		}
	}
	if (!bRet)
	{
		nNext = -1;
	}

	return bRet;
}

// ----------------------------------------------------------------------
// �C�x���g�}�b�v�̒T������
//
// ����
// �@�@int         nStart;		// �T���J�n�ʒu
// �@�@int         nEvtID;		// �C�x���g�h�c
// �@�@DWORD       dwEvtNo;		// �C�x���g�m��
// �@�@VECTOR2 vPos;		// ���W(OUT)
//     int         nNext;       // ���J�n�ʒu(OUT) �ŏI�ɒB������@-1 
//	   int		   dir			// ��]����
//
// �߂�l
//�@�@TRUE:��������  FALSE:������Ȃ�
// ----------------------------------------------------------------------
BOOL  CMapProc::SearchEvt(int nStart, int nEvtID, DWORD dwEvtNo, VECTOR2& vPos, int& nNext, int& dir)
{
	BOOL bRet = FALSE;

	if (nStart < 0 || nStart >= m_pMapArray[m_nMapNo]->m_nEvtMapLength)
	{
		nNext = -1;
		return bRet;
	}

	for (DWORD i = nStart; i < m_pMapArray[m_nMapNo]->m_nEvtMapLength; i++)
	{
		if (m_pMapArray[m_nMapNo]->m_EvtMap[i].m_nEvtID == nEvtID &&	    // �C�x���g�}�b�v�@ID�@�G�̏o���ʒu
			m_pMapArray[m_nMapNo]->m_EvtMap[i].m_dwEvtNo & dwEvtNo)			// �C�x���g�}�b�v�@NO
		{
			vPos = m_pMapArray[m_nMapNo]->m_EvtMap[i].m_vStart;	// �����ʒu
			dir = m_pMapArray[m_nMapNo]->m_EvtMap[i].m_nCnt1;
			nNext = i + 1;  // ���̊J�n�ʒu��ݒ�
			bRet = TRUE;
			break;
		}
	}
	if (!bRet)
	{
		nNext = -1;
	}

	return bRet;
}

// ----------------------------------------------------------------------
// �}�b�v�̔w�i�̕`��
// ----------------------------------------------------------------------
void  CMapProc::DrawBack()
{
	// �X�e�[�W�w�i�̕`��i�S�����X�N���[���j�@�|�|�|�|�|�|�|�|�|�|
	VECTOR2 scr;

	scr.x = WINDOW_WIDTH - ((int)(m_pGMain->m_vScroll.x / 2)) % WINDOW_WIDTH;
	scr.y = WINDOW_HEIGHT - ((int)(m_pGMain->m_vScroll.y / 2)) % WINDOW_HEIGHT;

	if (m_nMapNo == 0) {
		m_pSpriteBak->Draw(m_pBakImage, 0, 0, WINDOW_WIDTH - scr.x, WINDOW_HEIGHT - scr.y, scr.x, scr.y);
		m_pSpriteBak->Draw(m_pBakImage, scr.x, 0, 0, WINDOW_HEIGHT - scr.y, WINDOW_WIDTH - scr.x, scr.y);
		m_pSpriteBak->Draw(m_pBakImage, 0, scr.y, WINDOW_WIDTH - scr.x, 0, scr.x, WINDOW_HEIGHT - scr.y);
		m_pSpriteBak->Draw(m_pBakImage, scr.x, scr.y, 0, 0, WINDOW_WIDTH - scr.x, WINDOW_HEIGHT - scr.y);
	}
	else {
		m_pSpriteBak->Draw(m_pBakImage2, 0, 0, WINDOW_WIDTH - scr.x, WINDOW_HEIGHT - scr.y, scr.x, scr.y);
		m_pSpriteBak->Draw(m_pBakImage2, scr.x, 0, 0, WINDOW_HEIGHT - scr.y, WINDOW_WIDTH - scr.x, scr.y);
		m_pSpriteBak->Draw(m_pBakImage2, 0, scr.y, WINDOW_WIDTH - scr.x, 0, scr.x, WINDOW_HEIGHT - scr.y);
		m_pSpriteBak->Draw(m_pBakImage2, scr.x, scr.y, 0, 0, WINDOW_WIDTH - scr.x, WINDOW_HEIGHT - scr.y);
	}

	// �}�b�v�w�i�̕`��@�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|
	int x, y, no;

	for (y = 0; y < m_pMapArray[m_nMapNo]->m_nMapY; y++)
	{
		for (x = 0; x < m_pMapArray[m_nMapNo]->m_nMapX; x++)
		{
			no = m_pMapArray[m_nMapNo]->m_MapBakTbl[y * m_pMapArray[m_nMapNo]->m_nMapX + x];
			if (no == -1)
			{
				;  		// �}�b�v�̖������͕`�悵�Ȃ�
			}
			else {
				m_pSpriteMap->m_ofX = no % 1000 * m_pMapArray[m_nMapNo]->m_nMapchipWidth;
				m_pSpriteMap->m_ofY = no / 1000 * m_pMapArray[m_nMapNo]->m_nMapchipHeight;
				m_pSpriteMap->Draw(x * m_pMapArray[m_nMapNo]->m_nMapchipWidth - m_pGMain->m_vScroll.x, y * m_pMapArray[m_nMapNo]->m_nMapchipHeight - m_pGMain->m_vScroll.y);
			}
		}
	}
}

// ----------------------------------------------------------------------
// �}�b�v�̑O�i�̕`��
// ----------------------------------------------------------------------
void  CMapProc::DrawFore()
{
	int x, y, no;
	for (y = 0; y < m_pMapArray[m_nMapNo]->m_nMapY; y++)
	{
		for (x = 0; x < m_pMapArray[m_nMapNo]->m_nMapX; x++)
		{
			no = m_pMapArray[m_nMapNo]->m_MapForTbl[y * m_pMapArray[m_nMapNo]->m_nMapX + x];
			if (no == -1)
			{
				;		// �}�b�v�̖������͕`�悵�Ȃ�
			}
			else {
				m_pSpriteMap->m_ofX = no % 1000 * m_pMapArray[m_nMapNo]->m_nMapchipWidth;
				m_pSpriteMap->m_ofY = no / 1000 * m_pMapArray[m_nMapNo]->m_nMapchipHeight;
				m_pSpriteMap->Draw(x * m_pMapArray[m_nMapNo]->m_nMapchipWidth - m_pGMain->m_vScroll.x, y * m_pMapArray[m_nMapNo]->m_nMapchipHeight - m_pGMain->m_vScroll.y);
			}
		}
	}
}

// ----------------------------------------------------------------------
// �}�b�v���̕`��
// ----------------------------------------------------------------------
void  CMapProc::DrawMapLine()
{
	int i;

	for (i = 0; i < m_pMapArray[m_nMapNo]->m_nMapLnLength; i++)
	{
		m_pSpriteLine->DrawLine(m_pMapArray[m_nMapNo]->m_MapLn[i].m_vStart.x - m_pGMain->m_vScroll.x, m_pMapArray[m_nMapNo]->m_MapLn[i].m_vStart.y - m_pGMain->m_vScroll.y,
			m_pMapArray[m_nMapNo]->m_MapLn[i].m_vEnd.x - m_pGMain->m_vScroll.x, m_pMapArray[m_nMapNo]->m_MapLn[i].m_vEnd.y - m_pGMain->m_vScroll.y, 3, RGB(255, 0, 0));
		float cx = (m_pMapArray[m_nMapNo]->m_MapLn[i].m_vStart.x + m_pMapArray[m_nMapNo]->m_MapLn[i].m_vEnd.x) / 2;
		float cy = (m_pMapArray[m_nMapNo]->m_MapLn[i].m_vStart.y + m_pMapArray[m_nMapNo]->m_MapLn[i].m_vEnd.y) / 2;
		float nx = cx + m_pMapArray[m_nMapNo]->m_MapLn[i].m_vNormal.x * 10.0f;
		float ny = cy + m_pMapArray[m_nMapNo]->m_MapLn[i].m_vNormal.y * 10.0f;
		m_pSpriteLine->DrawLine(cx - m_pGMain->m_vScroll.x, cy - m_pGMain->m_vScroll.y, nx - m_pGMain->m_vScroll.x, ny - m_pGMain->m_vScroll.y, 3, RGB(255, 0, 0));
	}
}

// ----------------------------------------------------------------------------------------
// �}�b�v�̐ڐG����ƓK�؂Ȉʒu�ւ̈ړ�
//
//   �@�@�}�b�v����˂������Ă��邩�`�F�b�N����
//   �A�@�}�b�v���ɋߐڂ��Ă��邩�i�L�������H������ł��邩�j�`�F�b�N����
//
//   �˂������Ă��邩�ߐڂ��Ă���Ƃ��A�����lm_vPosUp��@�������ɐH�����ݕ������A�߂��Ă��
//
//   �@�@�߂�l�F�˂������Ă��邩�ߐڂ��Ă���Ƃ��^�BpHitmapline:�ڐG�����}�b�v���̃A�h���X���Ԃ�
// ----------------------------------------------------------------------------------------
BOOL CMapProc::isCollisionMoveMap(CBaseObj* obj, CMapLine*& pHitmapline1)
{
	int i, n, rw;
	BOOL bRet = FALSE;
	VECTOR2 vHitpos = VECTOR2(0, 0);
	VECTOR2 vHpw = VECTOR2(0, 0);
	float dist, dw;
	pHitmapline1 = NULL;

	dist = 999999;
	for (n = 0, i = 0; i < m_pMapArray[m_nMapNo]->m_nMapLnLength; i++) {
		rw = CheckMapcross(m_pMapArray[m_nMapNo]->m_MapLn[i], obj, vHpw);		// �@�@�}�b�v���Ƃ̓˂���������
		if (rw) {	// �˂������Ă���Ƃ�
			bRet = rw;
			dist = GetDistance(m_pMapArray[m_nMapNo]->m_MapLn[i], obj);
			n = i;
			vHitpos = vHpw;
			//break;
		}
		else {
			rw = CheckMapnear(m_pMapArray[m_nMapNo]->m_MapLn[i], obj, vHpw);	// �A�@�}�b�v���Ƃ̋ߐڔ���i�L�������}�b�v���ɐH������ł��邩�j
			if (rw) {
				bRet = rw;
				dw = GetDistance(m_pMapArray[m_nMapNo]->m_MapLn[i], obj);
				if (dist > dw) {						// ��ԋ߂��}�b�v����T��
					n = i;
					dist = dw;
					vHitpos = vHpw;
				}
			}
		}
	}

	i = n;
	if (bRet) {	// �˂������Ă��邩�ߐڂ��Ă���Ƃ��A�@�������ɐH�����ݕ������A�߂��Ă��

		pHitmapline1 = &(m_pMapArray[m_nMapNo]->m_MapLn[i]);  // �ڐG�����}�b�v���̃A�h���X

		obj->SetPosUp(obj->GetPosUp() + VECTOR2(
			round(-(dist - obj->GetSprite()->GetSrcWidth() / 2) * m_pMapArray[m_nMapNo]->m_MapLn[i].m_vNormal.x),
			round(-(dist - obj->GetSprite()->GetSrcHeight() / 2) * m_pMapArray[m_nMapNo]->m_MapLn[i].m_vNormal.y)));
	}

	// �ڐG���Ă���Ƃ��݂̂Q��ڂ̃`�F�b�N���s��
	if (bRet) {
		bRet = FALSE;	// ��U�N�����[����
		dist = 999999;
		for (n = 0, i = 0; i < m_pMapArray[m_nMapNo]->m_nMapLnLength; i++) {
			rw = CheckMapcross(m_pMapArray[m_nMapNo]->m_MapLn[i], obj, vHpw);		// �}�b�v���Ƃ̓˂���������
			if (rw) {	// �˂������Ă���Ƃ�
				bRet = rw;
				dist = GetDistance(m_pMapArray[m_nMapNo]->m_MapLn[i], obj);
				n = i;
				vHitpos = vHpw;
				break;
			}
			else {
				rw = CheckMapnear(m_pMapArray[m_nMapNo]->m_MapLn[i], obj, vHpw);	// �}�b�v���Ƃ̋ߐڔ���i�L�������}�b�v���ɐH������ł��邩�j
				if (rw) {
					bRet = rw;
					dw = GetDistance(m_pMapArray[m_nMapNo]->m_MapLn[i], obj);
					if (dist > dw) {						// ��ԋ߂��}�b�v����T��
						n = i;
						dist = dw;
						vHitpos = vHpw;
					}
				}
			}
		}

		i = n;
		if (bRet) {	// �˂������Ă��邩�ߐڂ��Ă���Ƃ��Am_vPosUp��@�������ɐH�����ݕ������A�߂��Ă��
			obj->SetPosUp(obj->GetPosUp() + VECTOR2(
				round(-(dist - obj->GetSprite()->GetSrcWidth() / 2) * m_pMapArray[m_nMapNo]->m_MapLn[i].m_vNormal.x),
				round(-(dist - obj->GetSprite()->GetSrcHeight() / 2) * m_pMapArray[m_nMapNo]->m_MapLn[i].m_vNormal.y)));
		}
		bRet = TRUE;	// �ēx�Z�b�g����
	}

	return bRet;
}

// ----------------------------------------------------------------------------------------
// �}�b�v�̐ڐG����ƓK�؂Ȉʒu�ւ̈ړ�
//
//   �@�@�}�b�v����˂������Ă��邩�`�F�b�N����
//   �A�@�}�b�v���ɋߐڂ��Ă��邩�i�L�������H������ł��邩�j�`�F�b�N����
//
//   �˂������Ă��邩�ߐڂ��Ă���Ƃ��A�����lm_vPosUp��@�������ɐH�����ݕ������A�߂��Ă��
//
//   �@�@�߂�l�F�˂������Ă��邩�ߐڂ��Ă���Ƃ��^�B
//			pHitmapline1:�ڐG����1�ڂ̃}�b�v���̃A�h���X���Ԃ�
//			pHitmapline2:�ڐG�����Q�ڂ̃}�b�v���̃A�h���X���Ԃ�
// ----------------------------------------------------------------------------------------
BOOL CMapProc::isCollisionMoveMap(CBaseObj* obj, CMapLine*& pHitmapline1, CMapLine*& pHitmapline2)
{
	int i, n, rw;
	BOOL bRet = FALSE;
	VECTOR2 vHitpos = VECTOR2(0, 0);
	VECTOR2 vHpw = VECTOR2(0, 0);
	float dist, dw;
	pHitmapline1 = NULL;
	pHitmapline2 = NULL;

	dist = 999999;
	for (n = 0, i = 0; i < m_pMapArray[m_nMapNo]->m_nMapLnLength; i++) {
		rw = CheckMapcross(m_pMapArray[m_nMapNo]->m_MapLn[i], obj, vHpw);		// �@�@�}�b�v���Ƃ̓˂���������
		if (rw) {	// �˂������Ă���Ƃ�
			bRet = rw;
			dist = GetDistance(m_pMapArray[m_nMapNo]->m_MapLn[i], obj);
			n = i;
			vHitpos = vHpw;
			//break;
		}
		else {
			rw = CheckMapnear(m_pMapArray[m_nMapNo]->m_MapLn[i], obj, vHpw);	// �A�@�}�b�v���Ƃ̋ߐڔ���i�L�������}�b�v���ɐH������ł��邩�j
			if (rw) {
				bRet = rw;
				dw = GetDistance(m_pMapArray[m_nMapNo]->m_MapLn[i], obj);
				if (dist > dw) {						// ��ԋ߂��}�b�v����T��
					n = i;
					dist = dw;
					vHitpos = vHpw;
				}
			}
		}
	}

	i = n;

	if (bRet) {	// �˂������Ă��邩�ߐڂ��Ă���Ƃ��A�@�������ɐH�����ݕ������A�߂��Ă��

		pHitmapline1 = &(m_pMapArray[m_nMapNo]->m_MapLn[i]);  // �ڐG�����}�b�v���̃A�h���X
		pHitmapline2 = &(m_pMapArray[m_nMapNo]->m_MapLn[i]);  // �ڐG�����}�b�v���̃A�h���X

		obj->SetPosUp(obj->GetPosUp() + VECTOR2(
			round(-(dist - obj->GetSprite()->GetSrcWidth() / 2) * m_pMapArray[m_nMapNo]->m_MapLn[i].m_vNormal.x),
			round(-(dist - obj->GetSprite()->GetSrcHeight() / 2) * m_pMapArray[m_nMapNo]->m_MapLn[i].m_vNormal.y)));
	}

	// �ڐG���Ă���Ƃ��݂̂Q��ڂ̃`�F�b�N���s��
	if (bRet) {
		bRet = FALSE;	// ��U�N�����[����
		dist = 999999;
		for (n = 0, i = 0; i < m_pMapArray[m_nMapNo]->m_nMapLnLength; i++) {
			rw = CheckMapcross(m_pMapArray[m_nMapNo]->m_MapLn[i], obj, vHpw);		// �}�b�v���Ƃ̓˂���������
			if (rw) {	// �˂������Ă���Ƃ�
				bRet = rw;
				dist = GetDistance(m_pMapArray[m_nMapNo]->m_MapLn[i], obj);
				n = i;
				vHitpos = vHpw;
				break;
			}
			else {
				rw = CheckMapnear(m_pMapArray[m_nMapNo]->m_MapLn[i], obj, vHpw);	// �}�b�v���Ƃ̋ߐڔ���i�L�������}�b�v���ɐH������ł��邩�j
				if (rw) {
					bRet = rw;
					dw = GetDistance(m_pMapArray[m_nMapNo]->m_MapLn[i], obj);
					if (dist > dw) {						// ��ԋ߂��}�b�v����T��
						n = i;
						dist = dw;
						vHitpos = vHpw;
					}
				}
			}
		}

		i = n;
		if (bRet) {	// �˂������Ă��邩�ߐڂ��Ă���Ƃ��Am_vPosUp��@�������ɐH�����ݕ������A�߂��Ă��
			pHitmapline2 = &(m_pMapArray[m_nMapNo]->m_MapLn[i]);  // �ڐG�����}�b�v���̃A�h���X

			obj->SetPosUp(obj->GetPosUp() + VECTOR2(
				round(-(dist - obj->GetSprite()->GetSrcWidth() / 2) * m_pMapArray[m_nMapNo]->m_MapLn[i].m_vNormal.x),
				round(-(dist - obj->GetSprite()->GetSrcHeight() / 2) * m_pMapArray[m_nMapNo]->m_MapLn[i].m_vNormal.y)));
		}
		bRet = TRUE;	// �ēx�Z�b�g����
	}

	return bRet;
}

// ----------------------------------------------------------------------------------------
// �}�b�v���Ƃ̓˂���������
//
// �@�߂�l�F�������Ă���Ƃ��^�B��_���W��hitpos�ɕԂ�
// ----------------------------------------------------------------------------------------
BOOL CMapProc::CheckMapcross(CMapLine map, CBaseObj* obj, VECTOR2& hitpos)
{
	BOOL bRet = FALSE;

	// �����P�@���P�C���Q   �E�E�E�E�@�}�b�v��
	VECTOR2  m1 = map.m_vStart, m2 = map.m_vEnd;
	// �����Q�@�����P�C�����Q �E�E�E�@�I�u�W�F�N�g�ړ�
	VECTOR2  oj1 = obj->GetCenterPos();
	VECTOR2  oj2 = obj->GetCenterPos() + obj->GetPosUp();

	// �Q�����̌����`�F�b�N
	bRet = CheckLinecross(m1, m2, oj1, oj2, hitpos);

	return bRet;
}

// ----------------------------------------------------------------------------------------
// �Q�����̌����`�F�b�N
// �@�������ƒ������̌����`�F�b�N�B
//
// �@�߂�l�F�������Ă���Ƃ��^�B��_���W��hitpos�ɕԂ�
// ----------------------------------------------------------------------------------------
BOOL CMapProc::CheckLinecross(VECTOR2 a1, VECTOR2 a2, VECTOR2 b1, VECTOR2 b2, VECTOR2& hitpos)
{
	BOOL bRet = FALSE;

	// ��_�@����
	VECTOR2  ap = VECTOR2(0, 0);
	float d1, d2;

	// �����̒������O�̂Ƃ�
	if ((a1.x == a2.x && a1.y == a2.y) ||
		(b1.x == b2.x && b1.x == b2.y)) {
		return bRet;
	}

	// ��_�����邩
	float dev = (a2.y - a1.y) * (b2.x - b1.x) - (a2.x - a1.x) * (b2.y - b1.y);
	if (dev == 0) {// ���s���̂Ƃ�
		return bRet;
	}

	// ��_�����߂�
	d1 = (b1.y * b2.x - b1.x * b2.y);
	d2 = (a1.y * a2.x - a1.x * a2.y);

	ap.x = d1 * (a2.x - a1.x) - d2 * (b2.x - b1.x);
	ap.x /= dev;
	ap.y = d1 * (a2.y - a1.y) - d2 * (b2.y - b1.y);
	ap.y /= dev;

	// ��_�������͈̔͂̒��ɂ��邩
	if ((CheckRange(a1.x, a2.x, ap.x) && CheckRange(a1.y, a2.y, ap.y)) &&
		(CheckRange(b1.x, b2.x, ap.x) && CheckRange(b1.y, b2.y, ap.y))) {
		bRet = TRUE;
	}

	if (bRet) {
		hitpos = ap;
	}

	return bRet;
}

// ----------------------------------------------------------------------------------------
// �͈̓`�F�b�N
//
// �@�߂�l�Fpt�����Ƃ��̊Ԃɓ����Ă���Ƃ��^�B
// ----------------------------------------------------------------------------------------
BOOL CMapProc::CheckRange(float l, float r, float pt)
{
	float low, hi;
	float mgn = 0.05f;	// �덷

	if (l <= r) {
		low = l;
		hi = r;
	}
	else {
		low = r;
		hi = l;
	}
	low -= mgn;
	hi += mgn;

	if (low <= pt && pt <= hi) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

// ----------------------------------------------------------------------------------------
// �}�b�v���Ƃ̋ߐڃ`�F�b�N
//
// �@�L�������}�b�v���ɐH������ł��邩�`�F�b�N�B
//
// �@�߂�l�F�H������ł���Ƃ��^�B�ڐG�ʒu��vHitpos�ɕԂ�
// ----------------------------------------------------------------------------------------
BOOL CMapProc::CheckMapnear(CMapLine MapLn, CBaseObj* obj, VECTOR2& vHitpos)
{
	BOOL bRet = FALSE;

	// �@�@�L�����ƃ}�b�v���̖@�������Ƃ̐H�����݃`�F�b�N���s�� --------------------------------
	// �L�����̒��S����A�}�b�v���̖@�������ɃL�����̑傫�����̒���������
	VECTOR2  p0, p1, p2;
	p0 = obj->GetCenterPos() + obj->GetPosUp();
	p1.x = p0.x - MapLn.m_vNormal.x * obj->GetSprite()->GetSrcWidth() / 2;
	p1.y = p0.y - MapLn.m_vNormal.y * obj->GetSprite()->GetSrcHeight() / 2;
	p2.x = p0.x + MapLn.m_vNormal.x * obj->GetSprite()->GetSrcWidth() / 2;
	p2.y = p0.y + MapLn.m_vNormal.y * obj->GetSprite()->GetSrcHeight() / 2;

	// �����ƃ}�b�v���Ƃ̌����`�F�b�N
	bRet = CheckLinecross(MapLn.m_vStart, MapLn.m_vEnd, p1, p2, vHitpos);

	// �A�@�������Ă��Ȃ��ꍇ�A�L�����Ɛ����������Ƃ̐H�����݃`�F�b�N���s��---------------------
	if (!bRet) {
		// �L�����̒��S����A�����������ɃL�����̑傫�����̒���������
		p0 = obj->GetCenterPos() + obj->GetPosUp();

		p1.x = p0.x - 0 * obj->GetSprite()->GetSrcWidth() / 2;
		p1.y = p0.y - 1 * obj->GetSprite()->GetSrcHeight() / 2;
		p2.x = p0.x + 0 * obj->GetSprite()->GetSrcWidth() / 2;
		p2.y = p0.y + 1 * obj->GetSprite()->GetSrcHeight() / 2;

		// �����ƃ}�b�v���Ƃ̌����`�F�b�N
		bRet = CheckLinecross(MapLn.m_vStart, MapLn.m_vEnd, p1, p2, vHitpos);
	}

	return bRet;
}

// ----------------------------------------------------------------------------------------
// �}�b�v���Ƃ̋��������߂�
//
// �@�߂�l�F �}�b�v���Ƃ̋����B�������A�@���������v���X�ƂȂ�B
// ----------------------------------------------------------------------------------------
float  CMapProc::GetDistance(CMapLine MapLn, CBaseObj* obj)
{
	VECTOR2  b = obj->GetCenterPos() + obj->GetPosUp() - MapLn.m_vStart;
	float len;

	// ���ς́A�x�N�g���̖@�������̋����ɂȂ�
	// (�@���̒������P�̂���)
	len = GetDot(MapLn.m_vNormal, b);

	return len;
}

// ----------------------------------------------------------------------------------------
// �Q�_�Ԃ̋��������߂�
// ----------------------------------------------------------------------------------------
float CMapProc::GetLength(VECTOR2 p1, VECTOR2 p2)
{
	return sqrtf((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}

// ----------------------------------------------------------------------------------------
// �x�N�g���̊O�ς����߂�
// �i�Q�����̏ꍇ�A�O�ς̓X�J���[�l�ƂȂ�j
// ----------------------------------------------------------------------------------------
float CMapProc::GetCross(VECTOR2 a, VECTOR2 b)
{
	return  a.x * b.y - a.y * b.x;
}

// ----------------------------------------------------------------------------------------
// �x�N�g���̓��ς����߂�
// ----------------------------------------------------------------------------------------
float CMapProc::GetDot(VECTOR2 a, VECTOR2 b)
{
	return  a.x * b.x + a.y * b.y;
}
