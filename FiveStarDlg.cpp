
// FiveStarDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FiveStar.h"
#include "FiveStarDlg.h"
#include "afxdialogex.h"
#include<windows.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

int flag = 2;	//flag=1为玩家1下，flag=2为玩家2下
int a[16][16] = { 0 };	//定义一个二维数组存放棋子该地方是否有棋子
bool Isfirst = TRUE;
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFiveStarDlg 对话框



CFiveStarDlg::CFiveStarDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FIVESTAR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFiveStarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}

BEGIN_MESSAGE_MAP(CFiveStarDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BT_EXIT, &CFiveStarDlg::OnBnClickedBtExit)
	ON_WM_LBUTTONDOWN()
//	ON_WM_LBUTTONUP()
	//ON_WM_RBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON1, &CFiveStarDlg::OnBnClickedButton1)
//	ON_WM_SETCURSOR()
END_MESSAGE_MAP()


// CFiveStarDlg 消息处理程序
/*DWORD WINAPI thread(LPVOID lpa)
{
	CFiveStarDlg *p = (CFiveStarDlg *)lpa;
	while (1)
	{
		if (flag == 2)
		{
			p->ComputerPlay();
		}
	}
	return 0;
}*/

BOOL CFiveStarDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	

	// TODO: 在此添加额外的初始化代码
	//CreateThread(NULL, 0, thread, this, 0, 0);
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 16; j++)
			a[i][j] = 0;
	a[6][6] = 7;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFiveStarDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFiveStarDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//--------------------------------背景----------------------------------------

		CPaintDC dc(this);
		CRect   myrect;
		GetClientRect(&myrect);
		CDC   dcMem;
		dcMem.CreateCompatibleDC(&dc);
		CBitmap   bmpBackground;
		bmpBackground.LoadBitmap(IDB_BITMAP1);   //IDB_BITMAP_TOOL是你自己的图对应的ID 
		BITMAP   bitmap;
		bmpBackground.GetBitmap(&bitmap);
		CBitmap   *pbmpOld = dcMem.SelectObject(&bmpBackground);
		dc.SetStretchBltMode(COLORONCOLOR);	//防止位图失真
		dc.StretchBlt(0, 0, myrect.Width(), myrect.Height(), &dcMem, 0, 0,
			bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
		//SetWindowPos(NULL, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SWP_NOMOVE);
		//------------------------------------------------------------------------------------------------------
		CDC *pDC = GetDC();
		CPen pen;
		pen.CreatePen(PS_SOLID,1,RGB(10,100,10));
		CPen * pOldPen = pDC->SelectObject(&pen);
		
		CRect rec;
		GetClientRect(&rec);
		//int x = rec.Width();
		//int y = rec.Height();
		int x = 30;
		int y = 30;
		for (int i = 0; i < 15; i++)
		{
			pDC->MoveTo(x + i *30,y);
			pDC->LineTo(x + i * 30,450);

		}
		for (int j = 0; j< 15; j++)
		{
			pDC->MoveTo(x ,y+j*30);
			pDC->LineTo(450,y+j*30);

		}
		pDC->SelectObject(pOldPen);
		pen.DeleteObject();

		m_font.CreatePointFont(200, _T("华文行楷")); //12号微软雅黑
		//CClientDC dc(this);
		
		CFont* def_font = dc.SelectObject(&m_font);
	
		dc.SetBkMode(TRANSPARENT);
		dc.TextOut(530, 60, _T("玩 家："));
		dc.SetBkMode(TRANSPARENT);
		dc.TextOut(530,110, _T("电 脑："));
		
		
		m_font.DeleteObject();
		m_font.CreatePointFont(1000, _T("楷体")); //12号微软雅黑
		 dc.SelectObject(&m_font);
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(RGB(155, 150,105));
		dc.TextOut(30, 30, _T("五"));
		dc.TextOut(180,180, _T("子"));
		dc.TextOut(330, 330, _T("棋"));

		dc.SelectObject(def_font);
		if (Isfirst)
		{
			a[6][6] = 7;
			draw(6, 6);
		}
		
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CFiveStarDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CFiveStarDlg::ComFirst()
{
	
}

void CFiveStarDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int x = point.x;
	int y = point.y;
	int temp1;
	int temp2;
	int m, n;
	
	
//	brush.CreateSolidBrush(RGB(255, 0, 0)); // 填充椭圆的颜色
	//CBrush *pOldBrush = pDC->SelectObject(&brush);
	
	//CRgn rgn;
//	CBrush brush;
	if (x > 450 || x < 30 || y>450 || y < 30)
		return;
	if (Isfirst)
	{
		flag = 1;
		Isfirst = FALSE;
	}
	if(x%30<=15&&y%30<=15)
	{
		temp1 = (x / 30);
		temp2 = (y / 30) ;
	}
	if (x % 30> 15 && y % 30 > 15)
	{
		temp1 = ((x / 30)+1);
		temp2 = ((y / 30)+1) ;
	}
	if (x % 30 <= 15 && y % 30 > 15)
	{
		temp1 = (x / 30) ;
		temp2 = ((y / 30) + 1) ;
	}
	if (x % 30> 15 && y % 30 <= 15)
	{
		temp1 = ((x / 30)+1) ;
		temp2 = (y / 30);
	}
	if (a[temp1][temp2 ] == 0)
	{
		if (flag == 1)
		{
			draw(temp1, temp2);
			PlaySound(_T("1.wav"),0,SND_ASYNC);
			a[temp1 ][temp2 ] = 3;
			flag = 2;
			prex = temp1;
			prey = temp2;
		}
	}
	else
		return;
	for (m = 1; m < 16; m++)
		for (n = 1; n < 16; n++)
		{
			if (a[m][n] == 3)				//判断黑棋是否赢了
			{
				if ((a[m + 1][n] == 3&& a[m + 2][n] == 3 && a[m + 3][n] == 3 && a[m + 4][n] == 3) || a[m - 1][n + 1] ==3 && a[m - 2][n + 2] == 3 && a[m - 3][n + 3] ==3 && a[m - 4][n + 4] == 3 || (a[m][n + 1] == 3 && a[m][n + 2] ==3 && a[m][n+ 3] == 3 && a[m][n + 4] == 3) || (a[m + 1][n + 1] ==3 && a[m + 2][n + 2] == 3 && a[m + 3][n + 3] == 3 && a[m + 4][n+ 4] == 3))
				{
					AfxMessageBox(_T("666~你赢啦!！"));
					return;
					/*int res = AfxMessageBox(_T("是否重来？"), MB_YESNO);
					if (res == IDYES)
					{
						CClientDC dc(this);
						int oldRop = dc.SetROP2(R2_NOT);
						dc.Ellipse(prex - 13, prey - 13, prex + 13, prey + 13);
						dc.SetROP2(oldRop);
						Invalidate(FALSE);
						for (int I = 1; I < 16; I++)
							for (int J = 1; J < 16; J++)
								a[I][J] = 0;
						flag = 1;
					}
					else
						AfxGetMainWnd()->DestroyWindow();*/
				}
				
			}

			
		}
	Sleep(200);
	ComputerPlay();
	
	CDialogEx::OnLButtonDown(nFlags, point);
}
void CFiveStarDlg::draw(int i, int j)
{
	CDC *pDC = GetDC();
	CClientDC dc(this);
	CBrush brush;
	if(flag==1)
		brush.CreateSolidBrush(RGB(255, 255, 255));
	else
		brush.CreateSolidBrush(RGB(0,0,0));
	pDC->SelectObject(&brush);
	pDC->Ellipse((i)*30-13, (j ) * 30 - 13, (i) * 30 + 13, (j) * 30 + 13);
	if(flag==1)
		pDC->Ellipse(610, 60, 636, 86);
	else
		pDC->Ellipse(610, 110, 636, 136);
	brush.DeleteObject();
	pDC->DeleteDC();
}
void CFiveStarDlg::usual()
{
	
	//srand((unsigned int )time(NULL));
	int i;
	int j ;
	for (i=1; i < 16; i++)
		for (j=1; j < 16; j++)
		{
			if (a[i][j] == 7&&a[i+1][j]==0 )
			{
				//AfxMessageBox(_T("2"));
				a[i + 1][j] = 7;
				draw(i + 1, j);
				return;
			}
			else if ((a[i][j] == 7 || a[i][j] == 3) && a[i][j + 1] == 0)
			{
				//AfxMessageBox(_T("3"));
				a[i][j + 1] = 7;
				draw(i, j + 1);
			
				return;
			}
			/*else if (a[6][6] == 0)
			{
				//AfxMessageBox(_T("usual3"));
				a[6][6] = 7;
				draw(6, 6);
				return;
			}
			else
			{
				int t1=0; int t2=0;  
				while (t1 == 0 || t2 == 0 || a[t1][t2] != 0)
				{
					t1 = rand() % 16;
					t2 = rand() % 16;
				}
				draw(t1, t2);
				a[t1][t2] = 7;
				return;
			}*/
		
		}
			/*else if(a[i][j] == 7 && a[i][j+1] == 0)
			{
				a[i][j+1] = 7;
				draw(i, j+1);
				return;
			}
			else
			{
				int t1=4, t2=4;
				while (a[t1][t2]==0)
				{
					t1 = rand() % 15;
					t2 = rand() % 15;
					if (t1 == 0 || t2 == 0)
						continue;
				}
				a[t1][t2] = 7;
				draw(t1, t2);
				return;
			}*/
				
}
//此函数的主要用途是判断三个连在一起的，且周围没有阻拦的 可以构成威胁的，如果是三个连在一起时，后一个已阻拦过了，则此函数不执行
bool CFiveStarDlg::ThreeOnLine()
{	//用户是3，电脑是7
	//注：由于为了方便观察，数组的a[3][4]不是常规意义上的第三行第四列，而是第四行第三列！！！方便切换到坐标轴
	int i, j,m,n;
	for ( i= 1; i < 16; i++)//横向三个连在一起
		for (j = 1; j < 16; j++)
		{
			if (a[i][j] + a[i + 1][j] + a[i + 2][j] + a[i + 3][j] == 9)//当有连续的4个里有三个一样
			{
				if ((i > 1 && a[i - 1][j] != 7)&&(i<12&&a[i+4][j]!=7))//如果连续的几个里面旁边的都没有拦，则需要阻拦
				{
					for (m = i; m < i + 4; m++)
						if (a[m][j] == 0)
						{
							a[m][j] = 7; draw(m, j); return true;
						}
				}
			}
		}
	for (i = 1; i < 16; i++)//纵向判断
		for (j = 1; j < 16; j++)
		{
			if (a[i][j] + a[i ][j+1] + a[i][j + 2] + a[i ][j + 3] == 9)
			{
				if ((i > 1 && a[i ][j - 1] != 7) && (j<12 && a[i ][j + 4] != 7))//如果连续的几个里面
				{
					for (m = j; m < j + 4; m++)
						if (a[i][m] == 0)
						{
							a[i][m] = 7; draw(i, m); return true;
						}
				}
			}
		}
	for (i = 1; i < 16; i++)//左下判断
		for (j = 1; j < 16; j++)
		{
			if (a[i][j] + a[i-1][j+1] + a[i-2][j + 2] + a[i-3][j +3] == 9)
			{
				if ((i > 4 &&j<12&& a[i-4][j +4] != 7) && (j>1 &&i<15&& a[i+1][j-1] != 7))//如果连续的几个里面
				{
					for (m = i,n=j; m > i - 4; m--,n++)
						if (a[m][n] == 0)
						{
							a[m][n] = 7; draw(m, n); return true;
						}
						
				}
			}
		}
	for (i = 1; i < 16; i++)//右下判断
		for (j = 1; j < 16; j++)
		{
			if (a[i][j] + a[i + 1][j + 1] + a[i + 2][j + 2] + a[i +3][j + 3] == 9)
			{
				if ((i > 1 && j>1 && a[i - 1][j - 1] != 7) && (j<12 && i<12 && a[i + 4][j +4] != 7))//如果连续的几个里面
				{
					for (m = i, n = j; m<i+4; m++, n++)
						if (a[m][n] == 0)
						{
							a[m][n] = 7; draw(m, n); return true;
						}

				}
			}
		}


	return false;
}
bool CFiveStarDlg::FourOnLine()
{
	//用户3，电脑7,所以四个连线的情况是连续5个加起来等于4*3+0 代表四个一样的
	int i, j,m,n;
	//竖向判断
	for (i =1; i < 16; i++)
		for (j = 1; j < 16;j++)
			if (a[i][j] + a[i][j + 1] + a[i][j + 2] + a[i][j + 3] + a[i][j + 4] == 12)// 如果连续的五个加起来等于12，说明已经有四个相同的了，
			{
				for (m = j; m < j + 5;m++)
					if (a[i][m] == 0)
					{
						a[i][m] = 7; draw(i, m); return true;
					}
				if (j > 1 && a[i][j - 1] == 0)//如果相连的
				{
					a[i][j-1] = 7; draw(i, j-1); return true;
				}
				if (j < 15 && a[i][j + 1] == 0)
				{
					a[i][j + 1] = 7; draw(i, j + 1); return true;
				}
			}
	//横向判断
	for (i = 1; i < 16; i++)
		for (j = 1; j < 16; j++)
			if (a[i][j] + a[i+1][j] + a[i+2][j] + a[i+3][j] + a[i+4][j] == 12)// 如果连续的五个加起来等于12，说明已经有四个相同的了，
			{
				for (m = i; m < i + 5; m++)
					if (a[m][j] == 0)
					{
						a[m][j] = 7; draw(m,j); return true;
					}
				if (i > 1 && a[i-1][j] == 0)
				{
					a[i-1][j] = 7; draw(i-1, j); return true;
				}
				if (i<15 && a[i+1][j] == 0)
				{
					a[i+1][j] = 7; draw(i+1, j); return true;
				}
			}
	//左下判断
	for (i = 1; i < 16; i++)
		for (j =1; j < 16; j++)
			if (a[i][j] + a[i- 1][j+1] + a[i - 2][j+2] + a[i - 3][j+3] + a[i - 4][j+4] == 12)// 如果连续的五个加起来等于12，说明已经有四个相同的了，
			{
				for (m = i,n=j; m > i - 5; m--,n++)
					if (a[m][n] == 0)
					{
						a[m][n] = 7; draw(m, n); return true;
					}
				if (i > 5&&j<11 && a[i - 5][j+5] == 0)
				{
					a[i - 5][j+5] = 7; draw(i - 5, j+5); return true;
				}
				if (i<15&&j>1 && a[i + 1][j-1] == 0)
				{
					a[i + 1][j-1] = 7; draw(i + 1, j-1); return true;
				}
			}
	//右下判断
	for (i = 1; i < 16; i++)
		for (j = 1; j < 16; j++)
			if (a[i][j] + a[i + 1][j + 1] + a[i +2][j + 2] + a[i + 3][j + 3] + a[i + 4][j + 4] == 12)// 如果连续的五个加起来等于12，说明已经有四个相同的了，
			{
				for (m = i, n = j; m < i + 5; m++, n++)
					if (a[m][n] == 0)
					{
						a[m][n] = 7; draw(m, n); return true;
					}
				if (i < 11 && j<11 && a[i + 5][j + 5] == 0)
				{
					a[i + 5][j + 5] = 7; draw(i + 5, j + 5); return true;
				}
				if (i>1 && j>1 && a[i - 1][j - 1] == 0)
				{
					a[i - 1][j - 1] = 7; draw(i- 1, j - 1); return true;
				}
			}


	return false;

}
bool CFiveStarDlg::ComTwoToThree()
{
	int i, j, m, n;
	for (i = 1; i < 16; i++)//纵向判断
		for (j = 1; j < 16; j++)
		{
			if (a[i][j] + a[i][j + 1] + a[i][j + 2] + a[i][j + 3] == 14)
			{
				if ((j > 1 && a[i][j - 1] == 0)&& (j < 12 && a[i][j + 4] == 0))
				{
					for (m = j; m < j + 4; m++)
						if (a[i][m] == 0&&a[i][m+1]!=0)
						{
							a[i][m] = 7; draw(i,m); return true;
						}
				}
			}
		}

	for (i = 1; i < 16; i++)//横向判断
		for (j =1; j < 16; j++)
		{
			if (a[i][j] + a[i+1][j] + a[i + 2][j] + a[i + 3][j] == 14)
			{
				if ((i > 1 && a[i-1][j] == 0) && (i< 12 && a[i+4][j] == 0))
				{
					for (m = i; m < i + 4; m++)
						if (a[m][j] == 0&&a[m+1][j]!=0)
						{
							a[m][j] = 7; draw(m, j); return true;
						}
				}
			}
		}
	for (i = 1; i < 16; i++)//左下判断
		for (j = 1; j < 16; j++)
		{
			if (a[i][j] + a[i - 1][j+1] + a[i- 2][j+2] + a[i - 3][j+3] == 14)
			{
				if ((i > 4 &&j<12&& a[i - 4][j+4] == 0) && (i< 15&&j>1 && a[i + 1][j-1] == 0))
				{
					for (m = i,n=j; m >i -4; m--,n++)
						if (a[m][n] == 0&&a[m-1][n+1]!=0)
						{
							a[m][n] = 7; draw(m, n); return true;
						}
				}
			}
		}
	for (i = 1; i < 16; i++)//右下判断
		for (j = 1; j < 16; j++)
		{
			if (a[i][j] + a[i + 1][j + 1] + a[i+ 2][j + 2] + a[i + 3][j + 3] == 14)
			{
				if ((i > 1 && j>1 && a[i-1][j -1] == 0) && (i< 12 && j<12 && a[i +4][j +4] == 0))
				{
					for (m = i, n = j; m <i + 4; m++, n++)
						if (a[m][n] == 0 && a[m + 1][n + 1] != 0)
						{
							a[m][n] = 7; draw(m, n); return true;
						}
				}
			}
		}
	return false;
}
bool CFiveStarDlg::ComThreeToFour()
{
	int i, j, m, n;
	for (i = 1; i < 16; i++)//横向三个连在一起
		for (j = 1; j < 16; j++)
		{
			if (a[i][j] + a[i + 1][j] + a[i + 2][j] + a[i + 3][j] == 21)//当有连续的4个里有三个一样
			{
				if((i>1&&a[i-1][j]==0)||(i<12&&a[i+4][j]==0))
					for (m = i+3; m > i -1; m--)
						if (a[m][j] == 0)
						{
							a[m][j] = 7; draw(m, j); return true;
						}
			}
		}
	for (i = 1; i < 16; i++)//纵向判断
		for (j = 1; j < 16; j++)
		{
			if (a[i][j] + a[i][j + 1] + a[i][j + 2] + a[i][j + 3] == 21)
			{
				if((j>1&&a[i][j-1]==0)||(j<12&&a[i][j+4]==0))
					for (m = j+3; m >j-1; m--)
						if (a[i][m] == 0)
						{
							a[i][m] = 7; draw(i, m); return true;
						}
			}
		}
	for (i = 1; i < 16; i++)//左下判断
		for (j = 1; j < 16; j++)
		{
			if (a[i][j] + a[i - 1][j + 1] + a[i - 2][j + 2] + a[i - 3][j + 3] == 21)
			{
				if(((i<15&&j>1)&&a[i+1][j-1]==0)||(i>4&&j<12)&&a[i-4][j+4]==0)
					for (m = i-3, n = j+3; m <i-1; m++, n--)
						if (a[m][n] == 0)
						{
							a[m][n] = 7; draw(m, n); return true;
						}
			}
		}
	for (i = 1; i < 16; i++)//右下判断
		for (j =1; j < 16; j++)
		{
			if (a[i][j] + a[i + 1][j + 1] + a[i + 2][j + 2] + a[i + 3][j + 3] == 21)
			{
				if (((i>1 && j>1) && a[i - 1][j - 1] == 0) || (i<12 && j<12) && a[i + 4][j + 4] == 0)
					for (m = i+4, n = j+4; m>i-1; m--, n--)
						if (a[m][n] == 0)
						{
							a[m][n] = 7; draw(m, n); return true;
						}
			
			}
		}


	return false;
}
bool CFiveStarDlg::ComFourToFive()
{
	int i, j, m, n;
	//竖向判断
	for (i = 1; i < 16; i++)
		for (j =1; j < 16; j++)
			if (a[i][j] + a[i][j + 1] + a[i][j + 2] + a[i][j + 3] + a[i][j + 4] == 28)// 如果连续的五个加起来等于28，说明已经有四个相同的了，
			{
				for (m = j; m < j + 5; m++)
					if (a[i][m] == 0)
					{
						a[i][m] = 7; draw(i, m); return true;
					}
			}
	//横向判断
	for (i = 1; i < 16; i++)
		for (j = 1; j < 16; j++)
			if (a[i][j] + a[i + 1][j] + a[i + 2][j] + a[i + 3][j] + a[i + 4][j] == 28)// 如果连续的五个加起来等于12，说明已经有四个相同的了，
			{
				for (m = i; m < i + 5; m++)
					if (a[m][j] == 0)
					{
						a[m][j] = 7; draw(m, j); return true;
					}
			}
	//左下判断
	for (i = 1; i < 16; i++)
		for (j = 1; j < 16; j++)
			if (a[i][j] + a[i - 1][j + 1] + a[i - 2][j + 2] + a[i - 3][j + 3] + a[i - 4][j + 4] == 28)// 如果连续的五个加起来等于12，说明已经有四个相同的了，
			{
				for (m = i, n = j; m > i - 5; m--, n++)
					if (a[m][n] == 0)
					{
						a[m][n] = 7; draw(m, n); return true;
					}
				 
			}
	//右下判断
	for (i = 1; i < 16; i++)
		for (j = 1; j < 16; j++)
			if (a[i][j] + a[i + 1][j + 1] + a[i + 2][j + 2] + a[i + 3][j + 3] + a[i + 4][j + 4] == 28)// 如果连续的五个加起来等于12，说明已经有四个相同的了，
			{
				for (m = i, n = j; m < i + 5; m++, n++)
					if (a[m][n] == 0)
					{
						a[m][n] = 7; draw(m, n); return true;
					}
			}
	return false;
}
void CFiveStarDlg::ComputerPlay()
{
	Sleep(200);
	//此处按照危急情况进行判断下最优棋
	if (flag == 2)
	{
		if (ComFourToFive())//如果电脑已经有四个一起的了，那补上第五子直接结束了
		{
			IsComputerWin();
			flag = 1;
			return;
		}
		if (FourOnLine())//电脑没有四个一起的，那最先要判断的是玩家是否有四个连线的
		{
			IsComputerWin();
			flag = 1;
			return;
		}
		if (ComThreeToFour())//如果没有致命威胁，那就看电脑可以不可以一击毙命变成四个连线的
		{
			IsComputerWin();
			flag = 1;
			return;
		}
		if (ThreeOnLine())//如果没有，就要先判断对面有没有三个一起的
		{
			IsComputerWin();
			flag = 1;
			return;
		}
		if (ComTwoToThree())//度过对面没有三个一起的，那电脑就凑三个一起的
		{
			IsComputerWin();
			flag = 1;
			return;
		}
		else 
		{
			usual();
			IsComputerWin();
			flag = 1;
		}
	
	}
}

void CFiveStarDlg::IsComputerWin()//判断电脑输赢
{
	int m, n;
	for (m = 1; m < 16; m++)
		for (n = 1; n < 16; n++)
		{
			if (a[m][n] == 7)				//判断黑棋是否赢了
			{
				if ((a[m + 1][n] == 7 && a[m + 2][n] == 7 && a[m + 3][n] == 7 && a[m + 4][n] == 7) || a[m - 1][n + 1] == 7 && a[m - 2][n + 2] == 7 && a[m - 3][n + 3] ==7 && a[m - 4][n + 4] ==7 || (a[m][n + 1] == 7 && a[m][n + 2] ==7 && a[m][n + 3] == 7&& a[m][n + 4] == 7) || (a[m + 1][n + 1] == 7 && a[m + 2][n + 2] == 7 && a[m + 3][n + 3] == 7 && a[m + 4][n + 4] == 7))
				{
					AfxMessageBox(_T("不好意思哦，电脑胜利啦！"));
				/*	int res = AfxMessageBox(_T("是否重来？"), MB_YESNO);
					if (res == IDYES)
					{
						CClientDC dc(this);
						int oldRop = dc.SetROP2(R2_NOT);
						dc.Ellipse(prex - 13, prey - 13, prex + 13, prey + 13);
						dc.SetROP2(oldRop);
						Invalidate(FALSE);
						for (int I = 1; I < 16; I++)
							for (int J = 1; J< 16; J++)
								a[I][J] = 0;
						flag = 2;
						Isfirst = TRUE;
					}
					else
						AfxGetMainWnd()->DestroyWindow();*/
				}

			}
		}
}
void CFiveStarDlg::OnBnClickedButton1()//重来
{
	// TODO: 在此添加控件通知处理程序代码
	CClientDC dc(this);
	int oldRop = dc.SetROP2(R2_NOT);
	dc.Ellipse(prex - 13, prey - 13, prex + 13, prey + 13);
	dc.SetROP2(oldRop);
	Invalidate(FALSE);
	for (int I = 1; I < 16; I++)
		for (int J = 1; J< 16; J++)
			a[I][J] = 0;
	flag = 2;
	Isfirst = TRUE;
}


void CFiveStarDlg::OnBnClickedBtExit()
{
	// TODO: 在此添加控件通知处理程序代码
	int r = AfxMessageBox(_T("是否确定退出"), MB_YESNO);
	if (r == IDYES)
		AfxGetMainWnd()->DestroyWindow();
	else
		return;
}
