#ifndef _CTEXTBUTTON_H
#define _CTEXTBUTTON_H

class	CTextButton
{
public:
	VOID ClickFreeAllBtn(VOID);
	INT GetButtonCount(VOID);
	CMTxtBtn* GetButton(INT nIndex);
	CTextButton();												// Constructor
	virtual	~CTextButton();										// Destructor
	BOOL	AddButton(CHAR *pszTxt,RECT xRect,INT nLinePos,CHAR *pszParam,COLORREF nColor,COLORREF cColor);	// Add Button to class
	BOOL	AddButton(CHAR *pszTxt,CHAR *pszTxt2,RECT xRect,INT nLinePos,CHAR *pszParam,COLORREF nColor,COLORREF cColor);	// Add Button to class

	CMTxtBtn*	ClickCheck(POINT xWndPos,POINT	xPos,INT CurrentTopLine);	// xWndPos: ���� Text �� ������ ���� ����
	CMTxtBtn*	ButtonDownCheck(POINT xWndPos,POINT xPos,INT CurrentTopLine);
	CMTxtBtn*	ButtonUpCheck(POINT xWndPos,POINT xPos,INT CurrentTopLine);

	BOOL		IsCurrsorOnThisButton(CMTxtBtn* pBtn,POINT xWndPos,POINT xPos,INT CurrentTopLine);

	BOOL InitTxtBtn(INT nMaxLine,POINT nStartPos,INT LineGap);
//	BOOL InitTxtBtn(INT nMaxLine);	
	CPDLList<CMTxtBtn> m_pTxtBtn; 
	BOOL		ReleaseButtons(VOID);	
private:
	BOOL		m_bIsReady;
	RECT		m_rtWndRect;			// �������� Rect ��, ���ڰ� ǥ�õǴ� �κ�
	INT			m_nTxtHeight;			// Text�� Height
	INT			m_nMaxLine;				// �����쿡 ǥ�õǴ� Maximum Line ��
	INT			m_nLineGap;
	POINT		m_xStartPos;
	BOOL		m_IsUseSubTxt;
};

#endif _CTEXTBUTTON_H