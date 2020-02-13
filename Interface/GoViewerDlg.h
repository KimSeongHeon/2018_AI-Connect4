// GoViewerDlg.h : header file
//

#if !defined(AFX_GOVIEWERDLG_H__8674E2B9_D53E_433E_A794_3EEC4451AEB2__INCLUDED_)
#define AFX_GOVIEWERDLG_H__8674E2B9_D53E_433E_A794_3EEC4451AEB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CGoViewerDlg dialog

class CGoViewerDlg : public CDialog
{
// Construction
public:
	void LastStonePresentation();
	void Who_turn();
	void All_view_board();
	void Drawboard();
	void load();
	void save();
	int AiOldColor;
	int AiOldy;
	int AiOldx;
	int OldColor;
	int Oldy;
	int Oldx;
	int index;
	int m_board[8][8];
	BOOL m_check;
	CBitmap m_bmpBack;
	CBitmap m_bmpBlack;
	CBitmap m_bmpWhite;
	CBitmap m_bmpEndB;
	CBitmap m_bmpEndW;

	CGoViewerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGoViewerDlg)
	enum { IDD = IDD_GOVIEWER_DIALOG };
	CString	m_analy;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGoViewerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGoViewerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnAi();
	afx_msg void OnMNew();
	afx_msg void OnMLoad();
	afx_msg void OnMQuit();
	afx_msg void OnMSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnBnClickedback();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GOVIEWERDLG_H__8674E2B9_D53E_433E_A794_3EEC4451AEB2__INCLUDED_)
