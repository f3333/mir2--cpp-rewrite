/******************************************************************************************************************
                                                                                                                   
	Module Name:
																													
	Author:
	Date:
																													
	[Date][Modifier] : Modified contents
                                                                                                                   
*******************************************************************************************************************/



#include "StdAfx.h"



/******************************************************************************************************************

	CStatusWnd Class

*******************************************************************************************************************/
/******************************************************************************************************************

	Function Name : CStatusWnd::CStatusWnd()

	Author :
	Date :

	Purpose   :
	Return   :

	[Date][Modifier] : ��������

*******************************************************************************************************************/
CStatusWnd::CStatusWnd()
{
	Init();
}



/******************************************************************************************************************

	Function Name : CStatusWnd::~CStatusWnd()

	Author :
	Date :

	Purpose   :
	Return   :

	[Date][Modifier] : ��������

*******************************************************************************************************************/
CStatusWnd::~CStatusWnd()
{
	Destory();
}


VOID CStatusWnd::Init()
{
	INT nCnt;
	CGameWnd::Init();

	m_bType	= _TYPE_EQUIP;
	m_nStartLineNum = 0;
	m_pstMyMagic = NULL;
	m_bMyMagicCnt = 0;
	ZeroMemory(&m_bMagicIdxTable, _MAX_MAGIC_SKILL);
	ZeroMemory(&m_rcCell, sizeof(RECT)*_EQUIP_MAX_CELL);
	ZeroMemory(&m_rcMagicCell, sizeof(RECT)*_MAGIC_MAX_CELL);
	ZeroMemory(&m_stEquipItem, sizeof(ITEMSET)*_EQUIP_MAX_CELL);
	ZeroMemory(&m_stTakeOnItemSet, sizeof(CItem));
	ZeroMemory(&m_szEquipItemIdx, sizeof(m_szEquipItemIdx));

	for ( nCnt  = 0; nCnt < _MAX_STAUTS_BTN; nCnt ++ )
	{
		m_xStatusBtn[nCnt].Init();
	}
	for ( nCnt  = 0; nCnt < 2; nCnt ++ )
	{
		m_xMagicScrlBtn[nCnt].Init();
	}

}

VOID CStatusWnd::Destory()
{
	CGameWnd::Destroy();
	SAFE_DELETE(m_pstMyMagic);
	Init();
}


/******************************************************************************************************************

	Function Name : CStatusWnd::CreateStatusWnd()

	Author :
	Date :

	Purpose   :
	Params   : INT nID
	         CWHWilImageData* pxWndImage
	         INT nFrameImgIdx
	         INT nStartX
	         INT nStartY
	         INT nWidth
	         INT nHeight
	         BOOL bCanMove
	Return   : VOID

	[Date][Modifier] : ��������

*******************************************************************************************************************/
VOID CStatusWnd::CreateStatusWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove)
{
	CreateGameWnd(nID, pxWndImage, nFrameImgIdx, bCanMove, nStartX, nStartY, nWidth, nHeight);

	// ��ư�ʱ�ȭ.
	m_xStatusBtn[_BTN_ID_STATUSCLOSE].CreateGameBtn(pxWndImage,  214,  215, nStartX+222, nStartY+298);
	m_xStatusBtn[_BTN_ID_STATUS].CreateGameBtn(pxWndImage,  212,  213, nStartX+_BTN_ID_STATUS_X, nStartY+_BTN_ID_STATUS_Y);
	m_xStatusBtn[_BTN_ID_STATUSMAGIC].CreateGameBtn(pxWndImage,  99, 100, nStartX+_BTN_ID_STATUSMAGIC_X, nStartY+_BTN_ID_STATUSMAGIC_Y);

	// ����â �ʱ�ȭ.
	SetRect(&m_rcCell[_U_NECKLACE], 187,  70, 190+_INVENTORY_CELL_WIDTH,  70+_INVENTORY_CELL_HEIGHT);
	SetRect(&m_rcCell[_U_RIGHTHAND], 37, 264,  37+_INVENTORY_CELL_WIDTH, 264+_INVENTORY_CELL_HEIGHT);
	SetRect(&m_rcCell[_U_CHARM],	74, 264, 74+_INVENTORY_CELL_WIDTH, 264+_INVENTORY_CELL_HEIGHT);
	SetRect(&m_rcCell[_U_ARMRINGL],  37, 186,  37+_INVENTORY_CELL_WIDTH, 186+_INVENTORY_CELL_HEIGHT);
	SetRect(&m_rcCell[_U_ARMRINGR], 185, 186, 185+_INVENTORY_CELL_WIDTH, 186+_INVENTORY_CELL_HEIGHT);
	SetRect(&m_rcCell[_U_RINGL],	37, 227, 37+_INVENTORY_CELL_WIDTH, 227+_INVENTORY_CELL_HEIGHT);
	SetRect(&m_rcCell[_U_RINGR],   185, 227,185+_INVENTORY_CELL_WIDTH, 227+_INVENTORY_CELL_HEIGHT);
	SetRect(&m_rcCell[_U_HELMET],	104,  71, 143,  104);
	SetRect(&m_rcCell[_U_DRESS],	96,  114, 146,  204);
	SetRect(&m_rcCell[_U_WEAPON],	48,  70,   91,  154);

	// ������ư�ʱ�ȭ.
	m_xMagicScrlBtn[0].CreateGameBtn(pxWndImage, 74, 75, nStartX+232, nStartY+147);
	m_xMagicScrlBtn[1].CreateGameBtn(pxWndImage, 74, 75, nStartX+232, nStartY+253);

	// ����â�ʱ�ȭ.
	SetRect(&m_rcMagicCell[0], 39,  77, 74, 112);
	SetRect(&m_rcMagicCell[1], 39, 115, 74, 149);
	SetRect(&m_rcMagicCell[2], 39, 152, 74, 186);
	SetRect(&m_rcMagicCell[3], 39, 188, 74, 223);
	SetRect(&m_rcMagicCell[4], 39, 225, 74, 260);

	// ���� ���� �ʱ�ȭ.
	m_pstMyMagic  = NULL;
	m_bMyMagicCnt = 0;
}



/******************************************************************************************************************

	Function Name : CStatusWnd::ShowStatusWnd()

	Author :
	Date :

	Purpose   :
	Return   : VOID

	[Date][Modifier] : ��������

*******************************************************************************************************************/
VOID CStatusWnd::ShowStatusWnd()
{
	RECT rcID;
	switch ( m_bType )
	{
	case _TYPE_EQUIP:
		ShowCharEquipWnd();
		SetRect(&rcID, m_rcWnd.left+81, m_rcWnd.top+38, m_rcWnd.left+173, m_rcWnd.top+50);
		g_xMainWnd.PutsHan(NULL, rcID, RGB(255, 250, 180), RGB(0, 0, 0), g_xGameProc.m_xMyHero.m_szName, NULL);
		
		rcID.top		+= 15;
		rcID.bottom		+= 15;

		g_xMainWnd.PutsHan(NULL, rcID, RGB(255, 250, 180), RGB(0, 0, 0), g_xGameProc.m_xMyHero.m_szGuildName, NULL);

		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(204) )
		{
			g_xMainWnd.DrawWithImageForComp(
											m_rcWnd.left+187, 
											m_rcWnd.top+266, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
											(WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage));
		}


//		g_xMainWnd.DrawWithGDI(m_rcWnd, NULL, RGB(255, 250, 180), 1);

		break;
	case _TYPE_STATUS:

		ShowCharEquipWnd();
		SetRect(&rcID, m_rcWnd.left+81, m_rcWnd.top+38, m_rcWnd.left+173, m_rcWnd.top+50);
		g_xMainWnd.PutsHan(NULL, rcID, RGB(255, 250, 180), RGB(0, 0, 0), g_xGameProc.m_xMyHero.m_szName, g_xMainWnd.CreateGameFont("�ü�ü", 10, 0, FW_BOLD));

		ShowCharStatus();

		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(203) )
		{
			g_xMainWnd.DrawWithImageForComp(
											m_rcWnd.left+187, 
											m_rcWnd.top+266, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
											(WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage));
		}

//		g_xMainWnd.DrawWithGDI(m_rcWnd, NULL, RGB(255, 250, 180), 1);

		break;
	case _TYPE_SETMAGIC:
		ShowCharSetMagicWnd();
		SetRect(&rcID, m_rcWnd.left+81, m_rcWnd.top+38, m_rcWnd.left+173, m_rcWnd.top+50);
		g_xMainWnd.PutsHan(NULL, rcID, RGB(255, 250, 180), RGB(0, 0, 0), g_xGameProc.m_xMyHero.m_szName, g_xMainWnd.CreateGameFont("�ü�ü", 10, 0, FW_BOLD));
		break;
	}

	m_xStatusBtn[_BTN_ID_STATUSCLOSE].ShowGameBtn();
	m_xStatusBtn[_BTN_ID_STATUS].ShowGameBtn();
	m_xStatusBtn[_BTN_ID_STATUSMAGIC].ShowGameBtn();
}



/******************************************************************************************************************

	Function Name : CStatusWnd::SetStatusBtnInit()

	Author :
	Date :

	Purpose   :
	Return   : VOID

	[Date][Modifier] : ��������

*******************************************************************************************************************/
VOID CStatusWnd::SetStatusBtnInit()
{
	m_xStatusBtn[_BTN_ID_STATUSCLOSE].SetBtnState(_BTN_STATE_NORMAL);
	m_xStatusBtn[_BTN_ID_STATUS].SetBtnState(_BTN_STATE_NORMAL);
	m_xStatusBtn[_BTN_ID_STATUSMAGIC].SetBtnState(_BTN_STATE_NORMAL);
}











/******************************************************************************************************************

	ĳ���� ����â����.

*******************************************************************************************************************/
/******************************************************************************************************************

	Function Name : CStatusWnd::ShowCharEquipWnd()

	Author :
	Date :

	Purpose   :
	Return   : VOID

	[Date][Modifier] : ��������

*******************************************************************************************************************/
VOID CStatusWnd::ShowCharEquipWnd()
{
	INT nStartX, nStartY;

	ShowGameWnd();

	// ��������, ������������.
	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].NewSetIndex(g_xGameProc.m_xMyHero.m_stFeature.bGender) )
	{
		g_xMainWnd.DrawWithImageForComp(
						m_rcWnd.left+_EQUIP_CHAR_X+g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shPX, 
						m_rcWnd.top+_EQUIP_CHAR_Y+g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shPY, 
						g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shWidth, 
						g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shHeight,
						(WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_pbCurrImage));
	}

	// ������ �׸���.
	for ( INT nCnt = 0; nCnt < _EQUIP_MAX_CELL; nCnt++ )
	{
		if ( m_stEquipItem[nCnt].bSetted )
		{
//			m_stEquipItem[nCnt].xItem.m_stItemInfo.stStdItem.wLooks = 1;
			if ( nCnt!=_U_HELMET && nCnt!=_U_WEAPON && nCnt!=_U_DRESS )
			{
				nStartX = m_rcWnd.left+m_rcCell[nCnt].left;
				nStartY = m_rcWnd.top+m_rcCell[nCnt].top;

				m_stEquipItem[nCnt].xItem.DrawItem(nStartX, nStartY);
			}
			else
			{
				nStartX = m_rcWnd.left+_EQUIP_CHAR_X;
				nStartY = m_rcWnd.top+_EQUIP_CHAR_Y;

				m_stEquipItem[nCnt].xItem.DrawItem(nStartX, nStartY, _ITEM_TYPE_EQUIP);
			}

		}
	}

	ShowEquipItemState();
}



/******************************************************************************************************************

	Function Name : CStatusWnd::ShowEquipItemState()

	Author :
	Date :

	Purpose   :
	Return   : VOID

	[Date][Modifier] : ��������

*******************************************************************************************************************/
VOID CStatusWnd::ShowEquipItemState()
{
	INT nEquipNum = GetEquipNum(g_xGameProc.m_ptMousePos);

	if ( nEquipNum != -1 )
	{
		if ( m_stEquipItem[nEquipNum].bSetted )
		{
			m_stEquipItem[nEquipNum].xItem.ShowItemStatus(m_rcWnd.left+37, m_rcWnd.top+288);
		}		
	}
}



/******************************************************************************************************************

	Function Name : CStatusWnd::GetEquipNum()

	Author :
	Date :

	Purpose   :
	Params   : POINT ptMouse
	Return   : INT

	[Date][Modifier] : ��������

*******************************************************************************************************************/
INT CStatusWnd::GetEquipNum(POINT ptMouse)
{
	RECT rc;
	for ( INT nCnt = 0; nCnt < _EQUIP_MAX_CELL; nCnt++ )
	{
		SetRect(&rc, m_rcWnd.left+m_rcCell[nCnt].left, m_rcWnd.top+m_rcCell[nCnt].top, 
			    m_rcWnd.left+m_rcCell[nCnt].left+(m_rcCell[nCnt].right-m_rcCell[nCnt].left), m_rcWnd.top+m_rcCell[nCnt].top+(m_rcCell[nCnt].bottom-m_rcCell[nCnt].top));
		if ( PtInRect(&rc, ptMouse) )
		{
			return nCnt;
		}
	}

	return -1;
}



/******************************************************************************************************************

	Function Name : CStatusWnd::CheckEquipItem()

	Author :
	Date :

	Purpose   :
	Params   : CItem* pxItem
	         BYTE bEquipCell
	         POINT ptMouse
	Return   : BOOL

	[Date][Modifier] : ��������

*******************************************************************************************************************/
BOOL CStatusWnd::CheckEquipItem(CItem* pxItem, BYTE bEquipCell, POINT ptMouse)
{
	RECT rc;

	for ( INT nCnt = 0; nCnt < _EQUIP_MAX_CELL; nCnt++ )
	{
		SetRect(&rc, m_rcWnd.left+m_rcCell[nCnt].left, m_rcWnd.top+m_rcCell[nCnt].top, 
			    m_rcWnd.left+m_rcCell[nCnt].left+(m_rcCell[nCnt].right-m_rcCell[nCnt].left), m_rcWnd.top+m_rcCell[nCnt].top+(m_rcCell[nCnt].bottom-m_rcCell[nCnt].top));
		if ( PtInRect(&rc, ptMouse) )
		{
			if ( pxItem->m_bAttr == _U_ARMRINGL || pxItem->m_bAttr == _U_ARMRINGR )
			{
				if ( pxItem->m_stItemInfo.stStdItem.bStdMode == 25 )
				{
					if ( _U_ARMRINGL == bEquipCell )
						return TRUE;
				}
				else
				{
					if ( _U_ARMRINGL == bEquipCell || _U_ARMRINGR == bEquipCell )			return TRUE;
				}
			}
			else if ( pxItem->m_bAttr == _U_RINGL || pxItem->m_bAttr ==  _U_RINGR )
			{
				if ( _U_RINGL == bEquipCell || _U_RINGR == bEquipCell )					return TRUE;
			}
			else if ( pxItem->m_bAttr == bEquipCell )
			{
				return TRUE;
			}			
		}
	}

	return FALSE;
}



/******************************************************************************************************************

	Function Name : CStatusWnd::DeleteEquipItem()

	Author :
	Date :

	Purpose   :
	Params   : INT nEquipNum
	Return   : VOID

	[Date][Modifier] : ��������

*******************************************************************************************************************/
VOID CStatusWnd::DeleteEquipItem(INT nEquipNum)
{
	ZeroMemory(&m_stEquipItem[nEquipNum], sizeof(ITEMSET));
}



VOID CStatusWnd::DeleteEquipItem(INT nMakeIndex, CHAR* szName)
{
	for ( INT nCnt = 0; nCnt < _EQUIP_MAX_CELL; nCnt++ )
	{
		if ( m_stEquipItem[nCnt].bSetted )
		{
			if ( m_stEquipItem[nCnt].xItem.m_stItemInfo.nMakeIndex == nMakeIndex )
			{
				if ( !strcmp(m_stEquipItem[nCnt].xItem.m_stItemInfo.stStdItem.szName, szName) )
				{
					DeleteEquipItem(nCnt);
					break;
				}
			}
		}		
	}
}



/******************************************************************************************************************

	Function Name : CStatusWnd::DeleteAllEquipItem()

	Author :
	Date :

	Purpose   :
	Return   : VOID

	[Date][Modifier] : ��������

*******************************************************************************************************************/
VOID CStatusWnd::DeleteAllEquipItem()
{
	for ( INT nCnt = 0; nCnt < _EQUIP_MAX_CELL; nCnt++ )
	{
		ZeroMemory(&m_stEquipItem[nCnt], sizeof(ITEMSET));
	}
}



/******************************************************************************************************************

	Function Name : CStatusWnd::AddEquipItem()

	Author :
	Date :

	Purpose   :
	Params   : CItem xItem
	         INT nEquipNum
	         BOOL bUseEquipNum
	Return   : BOOL

	[Date][Modifier] : ��������

*******************************************************************************************************************/
BOOL CStatusWnd::AddEquipItem(CItem xItem, INT nEquipNum, BOOL bUseEquipNum)
{
	if ( bUseEquipNum )
	{
		if ( !m_stEquipItem[nEquipNum].bSetted )
		{
			m_stEquipItem[nEquipNum].bSetted = TRUE;
			m_stEquipItem[nEquipNum].xItem = xItem;
			m_stEquipItem[nEquipNum].xItem.m_shCellNum = nEquipNum;

			return TRUE;
		}
	}

	for ( INT nCnt = 0; nCnt < _EQUIP_MAX_CELL; nCnt++ )
	{
		if ( !m_stEquipItem[nCnt].bSetted )
		{
			m_stEquipItem[nCnt].bSetted = TRUE;
			m_stEquipItem[nCnt].xItem = xItem;
			m_stEquipItem[nCnt].xItem.m_shCellNum = nCnt;

			return TRUE;
		}
	}
	return FALSE;
}



/******************************************************************************************************************

	Function Name : CStatusWnd::ExtractEquipItem()

	Author :
	Date :

	Purpose   :
	Params   : CItem* pxItem
	         INT nEquipNum
	Return   : BOOL

	[Date][Modifier] : ��������

*******************************************************************************************************************/
BOOL CStatusWnd::ExtractEquipItem(CItem* pxItem, INT nEquipNum)
{
	if ( m_stEquipItem[nEquipNum].bSetted )
	{
		memcpy(pxItem, &m_stEquipItem[nEquipNum].xItem, sizeof(CItem));
		DeleteEquipItem(nEquipNum);
				
		return TRUE;
	}
	return FALSE;
}





/******************************************************************************************************************

	Function Name : CStatusWnd::ChangeEquipWithCommon()

	Author :
	Date :

	Purpose   :
	Params   : INT nEquipNum
	         LPCOMMONITEMSET pstCommonItemSet
	Return   : VOID

	[Date][Modifier] : ��������

*******************************************************************************************************************/
VOID CStatusWnd::ChangeEquipWithCommon(INT nEquipNum, LPCOMMONITEMSET pstCommonItemSet)
{
	if ( pstCommonItemSet->bSetted )
	{
		CItem xEquipItem;
		if ( ExtractEquipItem(&xEquipItem, nEquipNum) )
		{
			AddEquipItem(pstCommonItemSet->xItem, nEquipNum, TRUE);

			pstCommonItemSet->bSetted			= TRUE;
			pstCommonItemSet->xItem				= xEquipItem;
			pstCommonItemSet->bWaitResponse		= FALSE;
			pstCommonItemSet->bIsEquipItem		= TRUE;
			pstCommonItemSet->bIsHideItem		= FALSE;
			pstCommonItemSet->bIsBeltItem		= FALSE;
			pstCommonItemSet->xItem.m_shCellNum = nEquipNum; 
		}
	}
}




/******************************************************************************************************************

	Function Name : CStatusWnd::SetCommonFromEquip()

	Author :
	Date :

	Purpose   :
	Params   : INT nEquipNum
	         LPCOMMONITEMSET pstCommonItemSet
	Return   : VOID

	[Date][Modifier] : ��������

*******************************************************************************************************************/
VOID CStatusWnd::SetCommonFromEquip(INT nEquipNum, LPCOMMONITEMSET pstCommonItemSet)
{
	CItem xEquipItem;
	if ( ExtractEquipItem(&xEquipItem, nEquipNum) )
	{
		pstCommonItemSet->bSetted			= TRUE;
		pstCommonItemSet->xItem				= xEquipItem;
		pstCommonItemSet->bWaitResponse		= FALSE;
		pstCommonItemSet->bIsEquipItem		= TRUE;
		pstCommonItemSet->bIsHideItem		= FALSE;
		pstCommonItemSet->bIsBeltItem		= FALSE;
		pstCommonItemSet->xItem.m_shCellNum = nEquipNum; 
	}	
}



/******************************************************************************************************************

	Function Name : CStatusWnd::SetEquipFromCommon()

	Author :
	Date :

	Purpose   :
	Params   : INT nEquipNum
	         LPCOMMONITEMSET pstCommonItemSet
	Return   : VOID

	[Date][Modifier] : ��������

*******************************************************************************************************************/
VOID CStatusWnd::SetEquipFromCommon(INT nEquipNum, LPCOMMONITEMSET pstCommonItemSet)
{
	if ( pstCommonItemSet->bSetted )
	{
		pstCommonItemSet->xItem.m_shCellNum = nEquipNum;
		AddEquipItem(pstCommonItemSet->xItem, nEquipNum);
		ZeroMemory(pstCommonItemSet, sizeof(COMMONITEMSET));
	}
}



/******************************************************************************************************************

	Function Name : CStatusWnd::SetTakeOnFromEquip()

	Author :
	Date :

	Purpose   :
	Params   : INT nEquipNum
	Return   : VOID

	[Date][Modifier] : ��������

*******************************************************************************************************************/
VOID CStatusWnd::SetTakeOnFromEquip(INT nEquipNum)
{
	if ( m_stEquipItem[nEquipNum].bSetted )
	{
		m_stTakeOnItemSet.xItem	  = m_stEquipItem[nEquipNum].xItem;
		m_stTakeOnItemSet.bSetted = TRUE;
		m_stTakeOnItemSet.xItem.m_shCellNum = nEquipNum;
		ZeroMemory(&m_stEquipItem[nEquipNum], sizeof(ITEMSET));	
	}
}



/******************************************************************************************************************

	Function Name : CStatusWnd::SetTakeOnFromCommon()

	Author :
	Date :

	Purpose   :
	Params   : LPCOMMONITEMSET pstCommonItemSet
	Return   : VOID

	[Date][Modifier] : ��������

*******************************************************************************************************************/
VOID CStatusWnd::SetTakeOnFromCommon(INT nEquipNum, LPCOMMONITEMSET pstCommonItemSet)
{
	if ( pstCommonItemSet->bSetted )
	{
		m_stTakeOnItemSet.xItem   = pstCommonItemSet->xItem;
		m_stTakeOnItemSet.bSetted = TRUE;
		m_stTakeOnItemSet.xItem.m_shCellNum = nEquipNum;
		ZeroMemory(pstCommonItemSet, sizeof(COMMONITEMSET));	
	}
}



/******************************************************************************************************************

	Function Name : CStatusWnd::SetEquipFromTakeOn()

	Author :
	Date :

	Purpose   :
	Return   : VOID

	[Date][Modifier] : ��������

*******************************************************************************************************************/
VOID CStatusWnd::SetEquipFromTakeOn()
{
	if ( m_stTakeOnItemSet.bSetted )
	{
		AddEquipItem(m_stTakeOnItemSet.xItem, m_stTakeOnItemSet.xItem.m_shCellNum, TRUE);
		ZeroMemory(&m_stTakeOnItemSet, sizeof(ITEMSET));
	}
}





















/******************************************************************************************************************

	ĳ���� ��������â����.

*******************************************************************************************************************/
/******************************************************************************************************************

	Function Name : CStatusWnd::ShowCharStatus()

	Author :
	Date :

	Purpose   :
	Return   : VOID

	[Date][Modifier] : ��������

*******************************************************************************************************************/
VOID CStatusWnd::ShowCharStatus()
{
	CHAR	szBuff[MAX_PATH];

	POINT	ptStart = {m_rcWnd.left+255+15, m_rcWnd.top+67};

	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), "LEVEL", g_xMainWnd.CreateGameFont("����ü", 9, 0, FW_BOLD));
	sprintf(szBuff, "%d", g_xGameProc.m_xMyHero.m_stAbility.bLevel);
	g_xMainWnd.PutsHan(NULL, ptStart.x+53, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 20;

	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), "HP", g_xMainWnd.CreateGameFont("����ü", 9, 0, FW_BOLD));
	sprintf(szBuff, "%d / %d", g_xGameProc.m_xMyHero.m_stAbility.wHP, g_xGameProc.m_xMyHero.m_stAbility.wMaxHP);
	g_xMainWnd.PutsHan(NULL, ptStart.x+53, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 20;

	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), "MP", g_xMainWnd.CreateGameFont("����ü", 9, 0, FW_BOLD));
	sprintf(szBuff, "%d / %d", g_xGameProc.m_xMyHero.m_stAbility.wMP, g_xGameProc.m_xMyHero.m_stAbility.wMaxMP);
	g_xMainWnd.PutsHan(NULL, ptStart.x+53, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);
	
	ptStart.y += 20;

	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), "AC", g_xMainWnd.CreateGameFont("����ü", 9, 0, FW_BOLD));
	sprintf(szBuff, "%d-%d", LOBYTE(g_xGameProc.m_xMyHero.m_stAbility.wAC), HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.wAC));
	g_xMainWnd.PutsHan(NULL, ptStart.x+53, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 20;

	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), "MAC", g_xMainWnd.CreateGameFont("����ü", 9, 0, FW_BOLD));
	sprintf(szBuff, "%d-%d", LOBYTE(g_xGameProc.m_xMyHero.m_stAbility.wMAC), HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.wMAC));
	g_xMainWnd.PutsHan(NULL, ptStart.x+53, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 20;

	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), "DC", g_xMainWnd.CreateGameFont("����ü", 9, 0, FW_BOLD));
	sprintf(szBuff, "%d-%d", LOBYTE(g_xGameProc.m_xMyHero.m_stAbility.wDC), HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.wDC));
	g_xMainWnd.PutsHan(NULL, ptStart.x+53, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 20;

	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), "MC", g_xMainWnd.CreateGameFont("����ü", 9, 0, FW_BOLD));
	sprintf(szBuff, "%d-%d", LOBYTE(g_xGameProc.m_xMyHero.m_stAbility.wMC), HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.wMC));
	g_xMainWnd.PutsHan(NULL, ptStart.x+53, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 20;

	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), "SC", g_xMainWnd.CreateGameFont("����ü", 9, 0, FW_BOLD));
	sprintf(szBuff, "%d-%d", LOBYTE(g_xGameProc.m_xMyHero.m_stAbility.wSC), HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.wSC));
	g_xMainWnd.PutsHan(NULL, ptStart.x+53, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.x = m_rcWnd.left+255+145;
	ptStart.y = m_rcWnd.top+67;

	FLOAT fExpRate = (FLOAT)((FLOAT)g_xGameProc.m_xMyHero.m_stAbility.dwExp/(FLOAT)g_xGameProc.m_xMyHero.m_stAbility.dwMaxExp);
	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), "����", g_xMainWnd.CreateGameFont("����ü", 9, 0, FW_BOLD));
	sprintf(szBuff, "%.2f%s", fExpRate*100, "%%");
	g_xMainWnd.PutsHan(NULL, ptStart.x+55, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 20;

	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), "���湫��", g_xMainWnd.CreateGameFont("����ü", 9, 0, FW_BOLD));
	sprintf(szBuff, "%d / %d", g_xGameProc.m_xMyHero.m_stAbility.wWeight, g_xGameProc.m_xMyHero.m_stAbility.wMaxWeight);
	g_xMainWnd.PutsHan(NULL, ptStart.x+55, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 20;

	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), "���빫��", g_xMainWnd.CreateGameFont("����ü", 9, 0, FW_BOLD));
	sprintf(szBuff, "%d / %d", g_xGameProc.m_xMyHero.m_stAbility.bWearWeight, g_xGameProc.m_xMyHero.m_stAbility.bMaxWearWeight);
	g_xMainWnd.PutsHan(NULL, ptStart.x+55, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 20;

	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), "��չ���", g_xMainWnd.CreateGameFont("����ü", 9, 0, FW_BOLD));
	sprintf(szBuff, "%d / %d", g_xGameProc.m_xMyHero.m_stAbility.bHandWeight, g_xGameProc.m_xMyHero.m_stAbility.bMaxHandWeight);
	g_xMainWnd.PutsHan(NULL, ptStart.x+55, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 20;

	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), "��Ȯ", g_xMainWnd.CreateGameFont("����ü", 9, 0, FW_BOLD));
	sprintf(szBuff, "+%d%", g_xGameProc.m_xMyHero.m_stSubAbility.bHitPoint);
	g_xMainWnd.PutsHan(NULL, ptStart.x+55, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 20;

	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), "��ø", g_xMainWnd.CreateGameFont("����ü", 9, 0, FW_BOLD));
	sprintf(szBuff, "+%d%", g_xGameProc.m_xMyHero.m_stSubAbility.bSpeedPoint);
	g_xMainWnd.PutsHan(NULL, ptStart.x+55, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 20;
	
	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), "����ȸ��", g_xMainWnd.CreateGameFont("����ü", 9, 0, FW_BOLD));
	sprintf(szBuff, "+%d%", g_xGameProc.m_xMyHero.m_stSubAbility.wAntiMagic*10);
	g_xMainWnd.PutsHan(NULL, ptStart.x+55, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 20;
	
	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), "�ߵ�ȸ��", g_xMainWnd.CreateGameFont("����ü", 9, 0, FW_BOLD));
	sprintf(szBuff, "+%d%", g_xGameProc.m_xMyHero.m_stSubAbility.bAntiPoison*10);
	g_xMainWnd.PutsHan(NULL, ptStart.x+55, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 20;
	
	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), "�ߵ�ȸ��", g_xMainWnd.CreateGameFont("����ü", 9, 0, FW_BOLD));
	sprintf(szBuff, "+%d%", g_xGameProc.m_xMyHero.m_stSubAbility.bPoisonRecover*10);
	g_xMainWnd.PutsHan(NULL, ptStart.x+55, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 20;
	
	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), "ü��ȸ��", g_xMainWnd.CreateGameFont("����ü", 9, 0, FW_BOLD));
	sprintf(szBuff, "+%d%", g_xGameProc.m_xMyHero.m_stSubAbility.bHealthRecover*10);
	g_xMainWnd.PutsHan(NULL, ptStart.x+55, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 20;
	
	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), "����ȸ��", g_xMainWnd.CreateGameFont("����ü", 9, 0, FW_BOLD));
	sprintf(szBuff, "+%d%", g_xGameProc.m_xMyHero.m_stSubAbility.bSpellRecover*10);
	g_xMainWnd.PutsHan(NULL, ptStart.x+55, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);
}














/******************************************************************************************************************

	ĳ���� ����â����.

*******************************************************************************************************************/
VOID CStatusWnd::ShowCharSetMagicWnd()
{
	INT nLine, nCnt, nStartX, nStartY;
	CHAR szKey[MAX_PATH];
	CHAR szLevel[MAX_PATH];

/*	CHAR* szSkillName[] =
	{ 
		"�ݿ��˹�",   "�Ͽ���",   "ȭ��ǳ",   "�׸�����", "������ȣ",   "������",	"���º�",     "��ȥ��",   "�ư����", "������ȸ", "ȭ����",	    "ȸ����",
		"���",	      "��ȸ��",   "�ڼ�ȭ",   "������",   "����ȯ��", "����ǳ",	"������",     "�ּ��Ǹ�", "Ž���Ŀ�", "������",   "�����",     "������",
		"�ݰ�ȭ����", "����",	  "��˼�",	  "����",	  "��ȭ��",     "����",		"�ż���ȯ",	  "�ϱ��˹�",  "�ܼ��˹�",
	};
*/
	ShowGameWnd();

	for ( nCnt = 0; nCnt < _MAGIC_MAX_CELL; nCnt++ )
	{
		nLine = nCnt + m_nStartLineNum;

		if ( nLine >= m_bMyMagicCnt )			break;

		nStartX = m_rcWnd.left+m_rcMagicCell[nCnt].left;
		nStartY = m_rcWnd.top +m_rcMagicCell[nCnt].top;

		INT nMagicImgIdx = m_pstMyMagic[nLine].stStdMagic.wMagicID * 2;
		g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].NewSetIndex(nMagicImgIdx);
		g_xMainWnd.DrawWithImageForComp(
										nStartX, 
										nStartY, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].m_pbCurrImage));

		g_xMainWnd.PutsHan(NULL, nStartX+50, nStartY+5, RGB(255, 255, 220), RGB(0, 0, 0), m_pstMyMagic[nLine].stStdMagic.szMagicName);

		if ( m_pstMyMagic[nLine].bUseKey != 0 )
		{
			nMagicImgIdx = m_pstMyMagic[nLine].stStdMagic.wMagicID * 2 + 1;
			g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].NewSetIndex(nMagicImgIdx);
			g_xMainWnd.DrawWithImageForComp(
											nStartX, 
											nStartY, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].m_lpstNewCurrWilImageInfo->shWidth, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].m_lpstNewCurrWilImageInfo->shHeight,
											(WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].m_pbCurrImage));

			sprintf(szKey, "F%c", (char)m_pstMyMagic[nLine].bUseKey);
			g_xMainWnd.PutsHan(NULL, nStartX+140, nStartY+7, RGB(255, 255, 255), RGB(125, 125, 255), szKey);
		}

	
		if ( m_pstMyMagic[nLine].bLevel < 3 )
		{
			sprintf(szLevel, "%d        %d/%d", m_pstMyMagic[nLine].bLevel, m_pstMyMagic[nLine].nCurrTrain, m_pstMyMagic[nLine].stStdMagic.nTrain[m_pstMyMagic[nLine].bLevel]);
			g_xMainWnd.PutsHan(NULL, nStartX+50, nStartY+23, RGB(255, 255, 220), RGB(0, 0, 0), szLevel);
		}
		else
		{
			sprintf(szLevel, "%d        ", m_pstMyMagic[nLine].bLevel);
			g_xMainWnd.PutsHan(NULL, nStartX+50, nStartY+23, RGB(255, 255, 220), RGB(0, 0, 0), szLevel);
		}

		m_xMagicScrlBtn[0].ShowGameBtn();
		m_xMagicScrlBtn[1].ShowGameBtn();
	}
}



/******************************************************************************************************************

	Function Name : CStatusWnd::SetMagicKey()

	Author :
	Date :

	Purpose   :
	Params   : POINT ptMouse
	         BYTE bKey
	Return   : BOOL

	[Date][Modifier] : ��������

*******************************************************************************************************************/
BOOL CStatusWnd::SetMagicKey(POINT ptMouse, BYTE bKey)
{
	RECT rc;
	INT  nCnt, nLine;
	for ( nCnt = 0; nCnt < _MAGIC_MAX_CELL; nCnt++ )
	{
		nLine = nCnt + m_nStartLineNum;

		if ( nLine >= m_bMyMagicCnt )			break;

		rc.left   = m_rcWnd.left + m_rcMagicCell[nCnt].left;
		rc.top	  = m_rcWnd.top  + m_rcMagicCell[nCnt].top;
		rc.right  = m_rcWnd.left + m_rcMagicCell[nCnt].right;
		rc.bottom = m_rcWnd.top	 + m_rcMagicCell[nCnt].bottom;

		if ( PtInRect(&rc, ptMouse) )
		{
			for ( INT nLoop = 0; nLoop < m_bMyMagicCnt; nLoop++ )
			{
				if ( m_pstMyMagic[nLoop].bUseKey == bKey )
				{
					m_pstMyMagic[nLoop].bUseKey = 0;
					g_xClientSocket.SendMagicKeyChange(m_pstMyMagic[nLoop].bUseKey, m_pstMyMagic[nLoop].stStdMagic.wMagicID);
				}
			}

			if ( m_pstMyMagic[nLine].bUseKey != bKey )
			{
				m_pstMyMagic[nLine].bUseKey = bKey;

				g_xClientSocket.SendMagicKeyChange(m_pstMyMagic[nLine].bUseKey, m_pstMyMagic[nLine].stStdMagic.wMagicID);
			}
			return TRUE;
		}
	}

	return FALSE;
}



/******************************************************************************************************************

	Function Name : CStatusWnd::GetMagicByKey()

	Author :
	Date :

	Purpose   :
	Params   : BYTE bKey
	Return   : LPCLIENTMAGICRCD

	[Date][Modifier] : ��������

*******************************************************************************************************************/
LPCLIENTMAGICRCD CStatusWnd::GetMagicByKey(BYTE bKey)
{
	LPCLIENTMAGICRCD pstMagic = NULL;

	for ( INT nCnt = 0; nCnt < m_bMyMagicCnt; nCnt++ )
	{
		pstMagic = &m_pstMyMagic[nCnt];
		if ( pstMagic->bUseKey == bKey )
		{
			break;
		}
	}
	return pstMagic;
}






















/******************************************************************************************************************

	Message Function.

*******************************************************************************************************************/

/******************************************************************************************************************

	Function Name : CStatusWnd::OnKeyDown()

	Author :
	Date :

	Purpose   :
	Params   : WPARAM wParam
	         LPARAM lParam
	         POINT ptMouse
	Return   : BOOL

	[Date][Modifier] : ��������

*******************************************************************************************************************/
BOOL CStatusWnd::OnKeyDown(WPARAM wParam, LPARAM lParam, POINT ptMouse)
{
	INT	 nLine, nCnt;
	BOOL bCheck;
	RECT rc;

	if ( !PtInRect(&m_rcWnd, ptMouse) )		return TRUE;

	bCheck = FALSE;

	for ( nCnt = 0; nCnt < _MAGIC_MAX_CELL; nCnt++ )
	{
		nLine = nCnt + m_nStartLineNum;

		rc.left  = m_rcWnd.left + m_rcMagicCell[nCnt].left;
		rc.top	 = m_rcWnd.top  + m_rcMagicCell[nCnt].top;
		rc.right = m_rcWnd.left + m_rcMagicCell[nCnt].right;
		rc.bottom= m_rcWnd.top	+ m_rcMagicCell[nCnt].bottom;
		if ( PtInRect(&rc, ptMouse) )
		{
			bCheck = TRUE;
			break;
		}
	}

	if ( !bCheck ) 							return TRUE;

	if ( m_bType == _TYPE_SETMAGIC )
	{
		switch ( wParam )
		{
		case VK_F1:		SetMagicKey(ptMouse, '1');		return TRUE;
		case VK_F2:		SetMagicKey(ptMouse, '2');		return TRUE;
		case VK_F3:		SetMagicKey(ptMouse, '3');		return TRUE;
		case VK_F4:		SetMagicKey(ptMouse, '4');		return TRUE;
		case VK_F5:		SetMagicKey(ptMouse, '5');		return TRUE;
		case VK_F6:		SetMagicKey(ptMouse, '6');		return TRUE;
		case VK_F7:		SetMagicKey(ptMouse, '7');		return TRUE;
		case VK_F8:		SetMagicKey(ptMouse, '8');		return TRUE;
		}
	}

	return FALSE;
}



/******************************************************************************************************************

	Function Name : CStatusWnd::OnLButtonUp()

	Author :
	Date :

	Purpose   :
	Params   : POINT ptMouse
	Return   : BOOL

	[Date][Modifier] : ��������

*******************************************************************************************************************/
BOOL CStatusWnd::OnLButtonUp(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse)
{
	INT nEquipNum;

	m_xStatusBtn[_BTN_ID_STATUSCLOSE].ChangeRect(m_rcWnd.left+222, m_rcWnd.top+298);
	m_xStatusBtn[_BTN_ID_STATUS     ].ChangeRect(m_rcWnd.left+_BTN_ID_STATUS_X, m_rcWnd.top+_BTN_ID_STATUS_Y);
	m_xStatusBtn[_BTN_ID_STATUSMAGIC].ChangeRect(m_rcWnd.left+_BTN_ID_STATUSMAGIC_X, m_rcWnd.top+_BTN_ID_STATUSMAGIC_Y);
	
	if ( m_xStatusBtn[_BTN_ID_STATUSCLOSE].OnLButtonUp(ptMouse) )		return TRUE;
	if ( m_xStatusBtn[_BTN_ID_STATUS].OnLButtonUp(ptMouse) )
	{
		if ( m_bType == _TYPE_STATUS )
		{
			ResetWndImg(_WNDIMGIDX_ITEMSET);
			m_bType = _TYPE_EQUIP;
			m_xStatusBtn[_BTN_ID_STATUS].ResetGameBtn(212, 213);
		}
		else
		{
			ResetWndImg(_WNDIMGIDX_STATUS);
			m_bType = _TYPE_STATUS; 
			m_xStatusBtn[_BTN_ID_STATUS].ResetGameBtn(210, 211);

			if ( m_rcWnd.right > 800 )
			{
				m_rcWnd.left  = 260;
				m_rcWnd.right = 800;
			}
		}
	}
	if ( m_xStatusBtn[_BTN_ID_STATUSMAGIC].OnLButtonUp(ptMouse) )
	{
		m_bType = _TYPE_SETMAGIC;
		ResetWndImg(_WNDIMGIDX_SKILLSET);
	}

	if ( m_bType == _TYPE_SETMAGIC )
	{
		m_xMagicScrlBtn[0].ChangeRect(m_rcWnd.left+232, m_rcWnd.top+147);
		m_xMagicScrlBtn[1].ChangeRect(m_rcWnd.left+232, m_rcWnd.top+253);
		if ( m_xMagicScrlBtn[0].OnLButtonUp(ptMouse) )
		{
			if ( m_nStartLineNum > 0 )									m_nStartLineNum--;
		}

		if ( m_xMagicScrlBtn[1].OnLButtonUp(ptMouse) )
		{
			if ( m_nStartLineNum < m_bMyMagicCnt-_MAGIC_MAX_CELL)		m_nStartLineNum++;
		}
	}

	// ����â Ȱ��ȭ �������.
	if ( m_bType == _TYPE_EQUIP || m_bType == _TYPE_STATUS )
	{
		nEquipNum = GetEquipNum(ptMouse);
		// ���콺�� ����â������ ������.
		if ( nEquipNum != -1)
		{
			// Ŭ��������â�� �������� �������.
			if ( m_stEquipItem[nEquipNum].bSetted )
			{
				// ����(���콺)�����ۼ��� ���������,
				if ( !pstCommonItemSet->bSetted )
				{				  
					// ���콺�� �������� �ٿ������� �κ��丮 �������� Ŭ���ϴ¼��� CM_TAKEOFFITEM�޽����� ������.
					SetCommonFromEquip(nEquipNum, pstCommonItemSet);
				}
				// ����(���콺)�����ۼ��� �ְ�, �����κ��� �����ȣ�� ��ٸ��� ���� �ƴϸ�,
				// ����������� m_stTakeOnItemSet�� �������� �����صΰ�, ���� Ŭ���� ����â �������� ������������� �����ϰ�����,
				// CM_TAKEONITEM�޽����� ������.
				else if ( pstCommonItemSet->bSetted && !pstCommonItemSet->bWaitResponse )
				{
					// �������� ������ ���� �´°�(�����ڸ��� ������ �ߵ�����)�� üũ�Ѵ�.
					if ( CheckEquipItem(&pstCommonItemSet->xItem, nEquipNum, ptMouse) )
					{
						SetTakeOnFromCommon(nEquipNum, pstCommonItemSet);
						SetCommonFromEquip(nEquipNum, pstCommonItemSet);					
						g_xClientSocket.SendTakeOnOffItem(CM_TAKEONITEM, nEquipNum, m_stTakeOnItemSet.xItem.m_stItemInfo.stStdItem.szName, m_stTakeOnItemSet.xItem.m_stItemInfo.nMakeIndex);
						pstCommonItemSet->bWaitResponse	= TRUE;
					}
				}
			}
			// Ŭ���� ����â�� �������� �������.
			else
			{
				// ����(���콺)�����ۼ��� �ְ�, �����κ��� �����ȣ�� ��ٸ��� ���� �ƴϸ�, ����������� m_stTakeOnItemSet�� �������� �����صд�.
				if ( pstCommonItemSet->bSetted && !pstCommonItemSet->bWaitResponse )
				{	
					if ( CheckEquipItem(&pstCommonItemSet->xItem, nEquipNum, ptMouse) )
					{
						// ������ �޽����� �����ʿ�� ����. �������� �����ٰ� �ٽ������Ѱ��.
						if ( pstCommonItemSet->bIsEquipItem )
						{
							SetEquipFromCommon(pstCommonItemSet->xItem.m_shCellNum, pstCommonItemSet);
							ZeroMemory(pstCommonItemSet, sizeof(COMMONITEMSET));
						}
						else
						{
							SetTakeOnFromCommon(nEquipNum, pstCommonItemSet);
							g_xClientSocket.SendTakeOnOffItem(CM_TAKEONITEM, nEquipNum, m_stTakeOnItemSet.xItem.m_stItemInfo.stStdItem.szName, m_stTakeOnItemSet.xItem.m_stItemInfo.nMakeIndex);
							pstCommonItemSet->bWaitResponse	= TRUE;
						}
					}
				}
			}
		}
	}

	return FALSE;
}



/******************************************************************************************************************

	Function Name : CStatusWnd::OnMouseMove()

	Author :
	Date :

	Purpose   :
	Params   : POINT ptMouse
	Return   : VOID

	[Date][Modifier] : ��������

*******************************************************************************************************************/
VOID CStatusWnd::OnMouseMove(POINT ptMouse)
{
	if ( m_bType == _TYPE_SETMAGIC )
	{
		m_xMagicScrlBtn[0].ChangeRect(m_rcWnd.left+232, m_rcWnd.top+147);
		m_xMagicScrlBtn[1].ChangeRect(m_rcWnd.left+232, m_rcWnd.top+253);
		m_xMagicScrlBtn[0].OnMouseMove(ptMouse);
		m_xMagicScrlBtn[1].OnMouseMove(ptMouse);
	}

	m_xStatusBtn[_BTN_ID_STATUSCLOSE   ].ChangeRect(m_rcWnd.left+222, m_rcWnd.top+298);
	m_xStatusBtn[_BTN_ID_STATUS		   ].ChangeRect(m_rcWnd.left+_BTN_ID_STATUS_X, m_rcWnd.top+_BTN_ID_STATUS_Y);
	m_xStatusBtn[_BTN_ID_STATUSMAGIC   ].ChangeRect(m_rcWnd.left+_BTN_ID_STATUSMAGIC_X, m_rcWnd.top+_BTN_ID_STATUSMAGIC_Y);
	m_xStatusBtn[_BTN_ID_STATUSCLOSE   ].OnMouseMove(ptMouse);
	m_xStatusBtn[_BTN_ID_STATUS		   ].OnMouseMove(ptMouse);
	m_xStatusBtn[_BTN_ID_STATUSMAGIC   ].OnMouseMove(ptMouse);
}



/******************************************************************************************************************

	Function Name : CStatusWnd::OnLButtonDown()

	Author :
	Date :

	Purpose   :
	Params   : LPCOMMONITEMSET pstCommonItemSet
	         POINT ptMouse
	Return   : BOOL

	[Date][Modifier] : ��������

*******************************************************************************************************************/
BOOL CStatusWnd::OnLButtonDown(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse)
{
	INT nEquipNum;

	m_xStatusBtn[_BTN_ID_STATUSCLOSE   ].ChangeRect(m_rcWnd.left+222, m_rcWnd.top+298);
	m_xStatusBtn[_BTN_ID_STATUS	       ].ChangeRect(m_rcWnd.left+_BTN_ID_STATUS_X, m_rcWnd.top+_BTN_ID_STATUS_Y);
	m_xStatusBtn[_BTN_ID_STATUSMAGIC   ].ChangeRect(m_rcWnd.left+_BTN_ID_STATUSMAGIC_X, m_rcWnd.top+_BTN_ID_STATUSMAGIC_Y);

	if ( m_xStatusBtn[_BTN_ID_STATUSCLOSE   ].OnLButtonDown(ptMouse) )		return TRUE;
	if ( m_xStatusBtn[_BTN_ID_STATUS	    ].OnLButtonDown(ptMouse) )		return TRUE;
	if ( m_xStatusBtn[_BTN_ID_STATUSMAGIC   ].OnLButtonDown(ptMouse) )		return TRUE;

	if ( m_bType == _TYPE_SETMAGIC )
	{
		m_xMagicScrlBtn[0].ChangeRect(m_rcWnd.left+232, m_rcWnd.top+147);
		m_xMagicScrlBtn[1].ChangeRect(m_rcWnd.left+232, m_rcWnd.top+253);
		if ( m_xMagicScrlBtn[0].OnLButtonDown(ptMouse) )					return TRUE;
		if ( m_xMagicScrlBtn[1].OnLButtonDown(ptMouse) )					return TRUE;
	}

	nEquipNum = GetEquipNum(ptMouse);

	if ( nEquipNum == -1 )		m_bCanMove = TRUE;
	else						
	{
		if ( m_stEquipItem[nEquipNum].bSetted )		m_bCanMove = FALSE;
		else										m_bCanMove = TRUE;				
	}

	return FALSE;
}



/******************************************************************************************************************

	Function Name : CStatusWnd::OnScrollDown()

	Author :
	Date :

	Purpose   :
	Return   : VOID

	[Date][Modifier] : ��������

*******************************************************************************************************************/
VOID CStatusWnd::OnScrollDown()
{
	if ( m_bType == _TYPE_SETMAGIC )
	{
		if ( m_nStartLineNum > 0 )										m_nStartLineNum--;
	}
}



/******************************************************************************************************************

	Function Name : CStatusWnd::OnScrollUp()

	Author :
	Date :

	Purpose   :
	Return   : VOID

	[Date][Modifier] : ��������

*******************************************************************************************************************/
VOID CStatusWnd::OnScrollUp()
{
	if ( m_bType == _TYPE_SETMAGIC )
	{
		if ( m_nStartLineNum < m_bMyMagicCnt-_MAGIC_MAX_CELL)			m_nStartLineNum++;
	}
}
