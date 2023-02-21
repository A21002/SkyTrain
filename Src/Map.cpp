#include "Map.h"
// CMap�N���X   --------------------------------------------------------------------------------------------
// �R���X�g���N�^
CMap::CMap(CGameMain* pGMain)
{
	m_pGMain = pGMain;
	m_MapFileName[0] = _T('\0');
	m_ImageName[0] = _T('\0');
	m_pMapImage = NULL;
	m_nMapX = 0;
	m_nMapY = 0;
	m_nMapchipWidth = 0;
	m_nMapchipHeight = 0;
	m_nMapLnLength = 0;
	m_nEvtMapLength = 0;
	m_MapBakTbl = NULL;
	m_MapForTbl = NULL;
	m_MapLn = NULL;
	m_EvtMap = NULL;
}

//  �f�X�g���N�^
CMap::~CMap()
{
	SAFE_DELETE(m_pMapImage);
	SAFE_DELETE_ARRAY(m_MapBakTbl);
	SAFE_DELETE_ARRAY(m_MapForTbl);
	SAFE_DELETE_ARRAY(m_MapLn);
	SAFE_DELETE_ARRAY(m_EvtMap);
}

//------------------------------------------------------------------------
// CMap�N���X�̃}�b�v�̏�����
//------------------------------------------------------------------------
void CMap::InitMap()
{
	int i;

	TCHAR szName[512];

	MakeERelativeFName(m_MapFileName, m_ImageName, szName);  // �}�b�v�t�@�C��������}�b�v�C���[�W�̃p�X�𓾂�

	m_pMapImage = new CSpriteImage(m_pGMain->m_pShader, szName);
	m_MapBakTbl = new int[m_nMapX * m_nMapY];	// �v�f�����̔z����m��
	for (i = 0; i < m_nMapX * m_nMapY; i++)
	{
		m_MapBakTbl[i] = -1;	// -1�ŏ�����
	}
	m_MapForTbl = new int[m_nMapX * m_nMapY];	// �v�f�����̔z����m��
	for (i = 0; i < m_nMapX * m_nMapY; i++)
	{
		m_MapForTbl[i] = -1;	// -1�ŏ�����
	}
}

//-----------------------------------------------------------------------------
// ����(relative)�p�X�����t�H���_����̑���(ERelative)�p�X���쐬����
//
//   ����      TCHAR*  szBaseFullPath
//             TCHAR*  szPath
//             TCHAR*  szERelativeFName(Out)
//-----------------------------------------------------------------------------
BOOL    CMap::MakeERelativeFName(TCHAR* szBaseFullPath, TCHAR* szPath, TCHAR* szERelativeFName)
{
	const DWORD NUM = 20;

	TCHAR BaseDrive[256], BasePath[512], BaseFName[512], BaseExt[256];
	TCHAR Drive[256], Path[512], FName[512], Ext[256];

	TCHAR* p;
	TCHAR BasePathArray[NUM][256] = { 0 };
	TCHAR PathArray[NUM][256] = { 0 };

	int i, j, n, m, d;

	// �h���C�u�ԍ��A�p�X���A�t�@�C�����A�g���q�ɕ���
	_tsplitpath_s(szBaseFullPath, BaseDrive, sizeof(BaseDrive) / sizeof(TCHAR), BasePath, sizeof(BasePath) / sizeof(TCHAR),
		BaseFName, sizeof(BaseFName) / sizeof(TCHAR), BaseExt, sizeof(BaseExt) / sizeof(TCHAR));
	_tsplitpath_s(szPath, Drive, sizeof(Drive) / sizeof(TCHAR), Path, sizeof(Path) / sizeof(TCHAR),
		FName, sizeof(FName) / sizeof(TCHAR), Ext, sizeof(Ext) / sizeof(TCHAR));

	// �h���C�u�ԍ�������Ƃ��͊��ɐ�΃p�X�ɂȂ��Ă���
	if (Drive[0] != _T('\0'))
	{
		_tcscpy(szERelativeFName, szPath);
		return TRUE;
	}

	// �p�X�����e�t�H���_�K�w�ɕ���
	i = 0;
	p = _tcstok(BasePath, _T("/\\"));
	while (p)
	{
		_tcscpy(BasePathArray[i], p);
		i++;
		p = _tcstok(NULL, _T("/\\"));
	}
	n = i;  // �x�[�X�̊K�w��

	i = 0;
	p = _tcstok(Path, _T("/\\"));
	while (p)
	{
		_tcscpy(PathArray[i], p);
		i++;
		p = _tcstok(NULL, _T("/\\"));
	}

	//	���΃p�X��'�D'�̐�
	i = 0;
	d = 1;
	if (PathArray[i][0] == _T('.'))
	{
		for (j = 1; PathArray[i][j] != _T('\0'); j++) d++;
		i++;
	}
	else if (PathArray[i][0] == _T('\0'))
	{
		i++;
	}
	else {
		;
	}
	m = i;

	// ��t�H���_����̑��΃p�X�̍쐬
	_tcscpy(szERelativeFName, BaseDrive);
	if (BaseDrive[0] != _T('\0')) _tcscat(szERelativeFName, _T("/"));
	for (i = 0; i < n - d + 1; i++)
	{
		_tcscat(szERelativeFName, BasePathArray[i]);
		_tcscat(szERelativeFName, _T("/"));
	}
	for (; PathArray[m][0] != _T('\0'); m++)
	{
		_tcscat(szERelativeFName, PathArray[m]);
		_tcscat(szERelativeFName, _T("/"));
	}
	_tcscat(szERelativeFName, FName);
	_tcscat(szERelativeFName, Ext);

	return TRUE;
}