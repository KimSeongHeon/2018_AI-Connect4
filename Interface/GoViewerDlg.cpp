// GoViewerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GoViewer.h"
#include "GoViewerDlg.h"
#include <dos.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#define WHITE 1
#define BLACK 2
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

static struct sequence{
	int x, y, index, color;
} seq[500];

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGoViewerDlg dialog

CGoViewerDlg::CGoViewerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGoViewerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGoViewerDlg)
	m_analy = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGoViewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGoViewerDlg)
	//}}AFX_DATA_MAP

}

BEGIN_MESSAGE_MAP(CGoViewerDlg, CDialog)
	//{{AFX_MSG_MAP(CGoViewerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_AI, OnAi)
	ON_COMMAND(IDM_NEW, OnMNew)
	ON_COMMAND(IDM_LOAD, OnMLoad)
	ON_COMMAND(IDM_QUIT, OnMQuit)
	ON_COMMAND(IDM_SAVE, OnMSave)
	//}}AFX_MSG_MAP
	//ON_BN_CLICKED(IDC_back, &CGoViewerDlg::OnBnClickedback)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGoViewerDlg message handlers

BOOL CGoViewerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	index=1;
	Oldx=-1;
	Oldy=-1;
	OldColor=0;
	AiOldx=-1;
	AiOldy=-1;
	AiOldColor=0;
	m_check=FALSE;

	m_bmpBack.LoadBitmap(IDB_BOARD);
	m_bmpBlack.LoadBitmap(IDB_BLACK);
	m_bmpWhite.LoadBitmap(IDB_WHITE);
	m_bmpEndB.LoadBitmap(IDB_ENDB);
	m_bmpEndW.LoadBitmap(IDB_ENDW);

	for(int i=0; i<8; i++)		//initialize m_board[][]
		for(int j=0; j< 8; j++){
			m_board[i][j] = 0;
		}

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGoViewerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGoViewerDlg::OnPaint() 
{

	CPaintDC dc(this);

	if (IsIconic())
	{
		 // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		Drawboard();
		All_view_board();
		Who_turn();

		CDialog::OnPaint();
	}

}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGoViewerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CGoViewerDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	int x, y;
	CClientDC dc(this);
	CDC MemDCTemp;
	MemDCTemp.CreateCompatibleDC(&dc);

	x = (point.x+0)/60;
	y = (point.y+0)/60;
    if((x<0) || (x>=8) || (y<0) || (y>=8)) return;

	if(m_board[x][y] != WHITE && m_board[x][y] != BLACK)
	{
		if(m_check == FALSE) 
		{
			seq[index].color = BLACK;
			m_board[x][y] = BLACK;
		}
		else if(m_check == TRUE) 
		{
			seq[index].color = WHITE;
			m_board[x][y] = WHITE;
		}
		
		seq[index].index=index;
		seq[index].x=x;
		seq[index].y=y;
		index++;

		m_check = !m_check;	//순서 바꾸기 

		LastStonePresentation();

		if(m_board[x][y] == WHITE){
			MemDCTemp.SelectObject(&m_bmpEndW);
			dc.BitBlt(0, 0, 600, 600, &MemDCTemp, -(x*60-0), -(y*60-0), SRCCOPY);
		}

		if(m_board[x][y] == BLACK){
			MemDCTemp.SelectObject(&m_bmpEndB);
			dc.BitBlt(0, 0, 600, 600, &MemDCTemp, -(x*60-0), -(y*60-0), SRCCOPY);
		}
		
		
		if(OldColor == WHITE){
			MemDCTemp.SelectObject(&m_bmpWhite);
			dc.BitBlt(0, 0, 600, 600, &MemDCTemp, -(Oldx*60-0), -(Oldy*60-0), SRCCOPY);
		}

		if(OldColor == BLACK){
			MemDCTemp.SelectObject(&m_bmpBlack);
			dc.BitBlt(0, 0, 600, 600, &MemDCTemp, -(Oldx*60-0), -(Oldy*60-0), SRCCOPY);
		}
		Oldx=x;
		Oldy=y;
		OldColor=m_board[x][y];

		Who_turn();
	}

    
	CDialog::OnLButtonDown(nFlags, point);
}

void CGoViewerDlg::OnAi() 
{
	
	// TODO: Add your control notification handler code here
	SHELLEXECUTEINFO sei;

    ZeroMemory(&sei,sizeof(SHELLEXECUTEINFO));
    sei.cbSize = sizeof(SHELLEXECUTEINFO);
    sei.lpVerb = __TEXT("open");
    
    sei.nShow = SW_HIDE;
    sei.fMask = SEE_MASK_NOCLOSEPROCESS;
	sei.lpFile = "000000000.exe"; // 구현한 실행파일 이름으로 대체 학번.exe

	save();
	
    DWORD result = ShellExecuteEx( &sei );
    if( sei.hProcess != NULL )
        ::WaitForSingleObject( sei.hProcess, INFINITE ); 

	load();
	::CloseHandle(sei.hProcess);
	
}

void CGoViewerDlg::save()
{
	FILE *fout;
	int k, savecnt=1, incount=0;

	fout = fopen("an.sgf", "wt");

	for(k=0; k<500; k++)
		if(seq[k].index==savecnt)
		{			
			fputc(59,fout);
			if(seq[k].color == BLACK) fputc(66,fout);
			if(seq[k].color == WHITE) fputc(87,fout);
			fputc(91,fout);
			fputc(97+seq[k].x,fout);
			fputc(97+seq[k].y,fout);
			fputc(93,fout);
			savecnt++;
		}
			
	fclose(fout);

	CClientDC dc(this);
	CDC MemDCTemp;
	MemDCTemp.CreateCompatibleDC(&dc);
	if(m_board[seq[savecnt-1].x][seq[savecnt-1].y] == WHITE){
			MemDCTemp.SelectObject(&m_bmpWhite);
			dc.BitBlt(0, 0, 480, 480, &MemDCTemp,
				-((seq[savecnt-1].x)*60-0), 
				-((seq[savecnt-1].y)*60-0), SRCCOPY);
		}

		if(m_board[seq[savecnt-1].x][seq[savecnt-1].y] == BLACK){
			MemDCTemp.SelectObject(&m_bmpBlack);
			dc.BitBlt(0, 0, 480, 480, &MemDCTemp,
				-((seq[savecnt-1].x)*60-0), 
				-((seq[savecnt-1].y)*60-0), SRCCOPY);
		}
}

void CGoViewerDlg::load()
{
	FILE *fin;
	
	char ch;		
	int count=0, headcount=0, order=0, x, y, loadcnt=1, i, j;

	fin = fopen("re.sgf", "rt");

	for(i=0; i<8; i++)		//initialize m_board[][]
		for(j=0; j<8; j++){
			m_board[i][j] = 0;
		}

	for(x=0; x<500; x++)
		seq[x].index=0;

	while(ch = fgetc(fin)){
		if(ch == EOF) break;
		count++;

		if(ch == 'B') order=BLACK;
		else if(ch == 'W') order=WHITE;

	
		if(ch == ';') continue;
		if(ch == '[') { 
			count = 0; 
			continue; 
		}
		if(count == 1) x=ch-97;
		if(count == 2) y=ch-97;
		if(ch == ']' && count == 3) { 
			m_board[x][y] = order;
			seq[loadcnt].color = order;
			seq[loadcnt].x = x;
			seq[loadcnt].y = y;
			seq[loadcnt].index = loadcnt;
			loadcnt++;
		}	
	}

	if(seq[loadcnt-1].color == WHITE) m_check = FALSE;
	if(seq[loadcnt-1].color == BLACK) m_check = TRUE;
	index = loadcnt;

	LastStonePresentation();
	

	Who_turn();
	fclose(fin);
}

void CGoViewerDlg::Drawboard()
{

	CClientDC dc(this);
	CDC MemDC;
	CBitmap *pOldBitmap;

	MemDC.CreateCompatibleDC(&dc);
	pOldBitmap = (CBitmap *)MemDC.SelectObject(&m_bmpBack);
	dc.BitBlt(0, 0, 480, 480, &MemDC, 0, 0, SRCCOPY);
	MemDC.SelectObject(pOldBitmap);
}

void CGoViewerDlg::All_view_board()
{
	Drawboard();
	CClientDC dc(this);
	CDC MemDCTemp;

	MemDCTemp.CreateCompatibleDC(&dc);


	for(int x=1; x<8; x++)
		for(int y=1; y<8;y++){
			if(m_board[x][y] == WHITE){
				MemDCTemp.SelectObject(&m_bmpWhite);
				dc.BitBlt(0, 0, 480, 480, &MemDCTemp, -(x*60-0), -(y*60-0), SRCCOPY);
			}
			if(m_board[x][y] == BLACK){
				MemDCTemp.SelectObject(&m_bmpBlack);
				dc.BitBlt(0, 0, 480, 480, &MemDCTemp, -(x*60-0), -(y*60-0), SRCCOPY);

			}
		}
	LastStonePresentation();

}

void CGoViewerDlg::Who_turn()
{
	CClientDC dc(this);
	CString TurnMessage;
	CFont FixedFont;
	FixedFont.CreateFont(12,6,0,0,0,0,0,0,1,0,0,0,0,"굴림");
	dc.SelectObject(FixedFont);
	
	if(m_check==FALSE)
	{
		TurnMessage.Format(" ▶ 흑(●)이 둘 차례 입니다.");
	}
	else
	{
		TurnMessage.Format(" ▶ 백(○)이 둘 차례 입니다.");
	}
	dc.TextOut(10,490,TurnMessage);

}

void CGoViewerDlg::OnMNew() 
{
	// TODO: Add your command handler code here
	int i, j;

	for(i=0; i<8; i++)		//initialize m_board[][]
		for(j=0; j<8; j++){
			m_board[i][j] = 0;
		}

		
	for(i=0; i<500; i++)
		seq[i].index=0;
	index=1;
	AiOldColor=0;
	OldColor=0;
	m_check=FALSE;
	Drawboard();	
	
}

void CGoViewerDlg::OnMLoad() 
{
	// TODO: Add your command handler code here
	CString filename;
	FILE *fin;
	char ch;		
	int count=0, headcount=0, order=0, x, y, loadcnt=1;
	
	CFileDialog dlg(TRUE, "*", "*.sgf");	
	
	if ( dlg.DoModal() != IDOK ) return;
	filename = dlg.GetPathName();
	fin = fopen(filename, "rt");
	
	OnMNew(); //all initialize

	//수순 읽기
	while(ch = fgetc(fin)){
		if(ch == EOF) break;
		count++;
	
		if(ch == ';') continue;
		
		if(ch == 'B') order=BLACK;
		else if(ch == 'W') order=WHITE;
		
		if(ch == '[') { 
			count = 0; 
			continue; 
		}
		if(count == 1) x=ch-97;
		if (count == 2) y = ch - 97;
		if(ch == ']' && count == 3) { 
			m_board[x][y] = order;
			seq[loadcnt].color = order;
			seq[loadcnt].x = x;
			seq[loadcnt].y = y;
			seq[loadcnt].index=loadcnt;
			loadcnt++;
		}		
	}
	if(m_board[seq[loadcnt-1].x][seq[loadcnt-1].y] == WHITE) m_check = FALSE;
	if(m_board[seq[loadcnt-1].x][seq[loadcnt-1].y] == BLACK) m_check = TRUE;

	index = loadcnt;

	fclose(fin);
	All_view_board();
	
}

void CGoViewerDlg::OnMSave() 
{
	// TODO: Add your command handler code here
	CString filename;
	FILE *fout;
	int k, savecnt=1, printcnt=0;

	CFileDialog dlg(FALSE, "sgf", "an", OFN_OVERWRITEPROMPT);	
	if ( dlg.DoModal() != IDOK ) return;
	filename = dlg.GetPathName();

	fout = fopen(filename, "wt");


	for(k=0; k<500; k++)
		if(seq[k].index==savecnt)
		{			
			fputc(59,fout);//';'
			if(seq[k].color==BLACK) fputc(66,fout);
			if(seq[k].color==WHITE) fputc(87,fout);
			fputc(91,fout);//'['
			fputc(97+seq[k].x,fout);
			fputc(97+seq[k].y,fout);
			fputc(93,fout);//']'
			savecnt++; 		
		}
			

	fclose(fout);
	
}

void CGoViewerDlg::OnMQuit() 
{
	// TODO: Add your command handler code here
	OnOK();
}

void CGoViewerDlg::LastStonePresentation()
{
	CClientDC dc(this);
	CDC MemDCTemp;
	MemDCTemp.CreateCompatibleDC(&dc);

	if(m_board[seq[index-1].x][seq[index-1].y] == WHITE){
		MemDCTemp.SelectObject(&m_bmpWhite);
		dc.BitBlt(0, 0, 480, 480, &MemDCTemp, -((seq[index-1].x)*60-0), -((seq[index-1].y)*60-0), SRCCOPY);
	}
	if(m_board[seq[index-1].x][seq[index-1].y] == BLACK){
		MemDCTemp.SelectObject(&m_bmpBlack);
		dc.BitBlt(0, 0, 480, 480, &MemDCTemp, -((seq[index-1].x)*60-0), -((seq[index-1].y)*60-0), SRCCOPY);
	}

	if(m_board[seq[index-1].x][seq[index-1].y] == WHITE){
		MemDCTemp.SelectObject(&m_bmpEndW);
		dc.BitBlt(0, 0, 480, 480, &MemDCTemp, -((seq[index-1].x)*60-0), -((seq[index-1].y)*60-0), SRCCOPY);
	}
	if(m_board[seq[index-1].x][seq[index-1].y] == BLACK){
		MemDCTemp.SelectObject(&m_bmpEndB);
		dc.BitBlt(0, 0, 480, 480, &MemDCTemp, -((seq[index-1].x)*60-0), -((seq[index-1].y)*60-0), SRCCOPY);
	}
	if(AiOldColor == WHITE){
		MemDCTemp.SelectObject(&m_bmpWhite);
		dc.BitBlt(0, 0, 480, 480, &MemDCTemp, -(AiOldx*60-0), -(AiOldy*60-0), SRCCOPY);
	}

	if(AiOldColor == BLACK){
		MemDCTemp.SelectObject(&m_bmpBlack);
		dc.BitBlt(0, 0, 600, 600, &MemDCTemp, -(AiOldx*60-0), -(AiOldy*60-0), SRCCOPY);
	}
	AiOldx=seq[index-1].x;
	AiOldy=seq[index-1].y;
	AiOldColor=m_board[seq[index-1].x][seq[index-1].y];

}



