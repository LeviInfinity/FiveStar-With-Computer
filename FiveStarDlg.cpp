
// FiveStarDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

int flag = 2;	//flag=1Ϊ���1�£�flag=2Ϊ���2��
int a[16][16] = { 0 };	//����һ����ά���������Ӹõط��Ƿ�������
bool Isfirst = TRUE;
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CFiveStarDlg �Ի���



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


// CFiveStarDlg ��Ϣ�������
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

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//CreateThread(NULL, 0, thread, this, 0, 0);
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 16; j++)
			a[i][j] = 0;
	a[6][6] = 7;
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CFiveStarDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//--------------------------------����----------------------------------------

		CPaintDC dc(this);
		CRect   myrect;
		GetClientRect(&myrect);
		CDC   dcMem;
		dcMem.CreateCompatibleDC(&dc);
		CBitmap   bmpBackground;
		bmpBackground.LoadBitmap(IDB_BITMAP1);   //IDB_BITMAP_TOOL�����Լ���ͼ��Ӧ��ID 
		BITMAP   bitmap;
		bmpBackground.GetBitmap(&bitmap);
		CBitmap   *pbmpOld = dcMem.SelectObject(&bmpBackground);
		dc.SetStretchBltMode(COLORONCOLOR);	//��ֹλͼʧ��
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

		m_font.CreatePointFont(200, _T("�����п�")); //12��΢���ź�
		//CClientDC dc(this);
		
		CFont* def_font = dc.SelectObject(&m_font);
	
		dc.SetBkMode(TRANSPARENT);
		dc.TextOut(530, 60, _T("�� �ң�"));
		dc.SetBkMode(TRANSPARENT);
		dc.TextOut(530,110, _T("�� �ԣ�"));
		
		
		m_font.DeleteObject();
		m_font.CreatePointFont(1000, _T("����")); //12��΢���ź�
		 dc.SelectObject(&m_font);
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(RGB(155, 150,105));
		dc.TextOut(30, 30, _T("��"));
		dc.TextOut(180,180, _T("��"));
		dc.TextOut(330, 330, _T("��"));

		dc.SelectObject(def_font);
		if (Isfirst)
		{
			a[6][6] = 7;
			draw(6, 6);
		}
		
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CFiveStarDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CFiveStarDlg::ComFirst()
{
	
}

void CFiveStarDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int x = point.x;
	int y = point.y;
	int temp1;
	int temp2;
	int m, n;
	
	
//	brush.CreateSolidBrush(RGB(255, 0, 0)); // �����Բ����ɫ
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
			if (a[m][n] == 3)				//�жϺ����Ƿ�Ӯ��
			{
				if ((a[m + 1][n] == 3&& a[m + 2][n] == 3 && a[m + 3][n] == 3 && a[m + 4][n] == 3) || a[m - 1][n + 1] ==3 && a[m - 2][n + 2] == 3 && a[m - 3][n + 3] ==3 && a[m - 4][n + 4] == 3 || (a[m][n + 1] == 3 && a[m][n + 2] ==3 && a[m][n+ 3] == 3 && a[m][n + 4] == 3) || (a[m + 1][n + 1] ==3 && a[m + 2][n + 2] == 3 && a[m + 3][n + 3] == 3 && a[m + 4][n+ 4] == 3))
				{
					AfxMessageBox(_T("666~��Ӯ��!��"));
					return;
					/*int res = AfxMessageBox(_T("�Ƿ�������"), MB_YESNO);
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
//�˺�������Ҫ��;���ж���������һ��ģ�����Χû�������� ���Թ�����в�ģ��������������һ��ʱ����һ�����������ˣ���˺�����ִ��
bool CFiveStarDlg::ThreeOnLine()
{	//�û���3��������7
	//ע������Ϊ�˷���۲죬�����a[3][4]���ǳ��������ϵĵ����е����У����ǵ����е����У����������л���������
	int i, j,m,n;
	for ( i= 1; i < 16; i++)//������������һ��
		for (j = 1; j < 16; j++)
		{
			if (a[i][j] + a[i + 1][j] + a[i + 2][j] + a[i + 3][j] == 9)//����������4����������һ��
			{
				if ((i > 1 && a[i - 1][j] != 7)&&(i<12&&a[i+4][j]!=7))//��������ļ��������ԱߵĶ�û����������Ҫ����
				{
					for (m = i; m < i + 4; m++)
						if (a[m][j] == 0)
						{
							a[m][j] = 7; draw(m, j); return true;
						}
				}
			}
		}
	for (i = 1; i < 16; i++)//�����ж�
		for (j = 1; j < 16; j++)
		{
			if (a[i][j] + a[i ][j+1] + a[i][j + 2] + a[i ][j + 3] == 9)
			{
				if ((i > 1 && a[i ][j - 1] != 7) && (j<12 && a[i ][j + 4] != 7))//��������ļ�������
				{
					for (m = j; m < j + 4; m++)
						if (a[i][m] == 0)
						{
							a[i][m] = 7; draw(i, m); return true;
						}
				}
			}
		}
	for (i = 1; i < 16; i++)//�����ж�
		for (j = 1; j < 16; j++)
		{
			if (a[i][j] + a[i-1][j+1] + a[i-2][j + 2] + a[i-3][j +3] == 9)
			{
				if ((i > 4 &&j<12&& a[i-4][j +4] != 7) && (j>1 &&i<15&& a[i+1][j-1] != 7))//��������ļ�������
				{
					for (m = i,n=j; m > i - 4; m--,n++)
						if (a[m][n] == 0)
						{
							a[m][n] = 7; draw(m, n); return true;
						}
						
				}
			}
		}
	for (i = 1; i < 16; i++)//�����ж�
		for (j = 1; j < 16; j++)
		{
			if (a[i][j] + a[i + 1][j + 1] + a[i + 2][j + 2] + a[i +3][j + 3] == 9)
			{
				if ((i > 1 && j>1 && a[i - 1][j - 1] != 7) && (j<12 && i<12 && a[i + 4][j +4] != 7))//��������ļ�������
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
	//�û�3������7,�����ĸ����ߵ����������5������������4*3+0 �����ĸ�һ����
	int i, j,m,n;
	//�����ж�
	for (i =1; i < 16; i++)
		for (j = 1; j < 16;j++)
			if (a[i][j] + a[i][j + 1] + a[i][j + 2] + a[i][j + 3] + a[i][j + 4] == 12)// ����������������������12��˵���Ѿ����ĸ���ͬ���ˣ�
			{
				for (m = j; m < j + 5;m++)
					if (a[i][m] == 0)
					{
						a[i][m] = 7; draw(i, m); return true;
					}
				if (j > 1 && a[i][j - 1] == 0)//���������
				{
					a[i][j-1] = 7; draw(i, j-1); return true;
				}
				if (j < 15 && a[i][j + 1] == 0)
				{
					a[i][j + 1] = 7; draw(i, j + 1); return true;
				}
			}
	//�����ж�
	for (i = 1; i < 16; i++)
		for (j = 1; j < 16; j++)
			if (a[i][j] + a[i+1][j] + a[i+2][j] + a[i+3][j] + a[i+4][j] == 12)// ����������������������12��˵���Ѿ����ĸ���ͬ���ˣ�
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
	//�����ж�
	for (i = 1; i < 16; i++)
		for (j =1; j < 16; j++)
			if (a[i][j] + a[i- 1][j+1] + a[i - 2][j+2] + a[i - 3][j+3] + a[i - 4][j+4] == 12)// ����������������������12��˵���Ѿ����ĸ���ͬ���ˣ�
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
	//�����ж�
	for (i = 1; i < 16; i++)
		for (j = 1; j < 16; j++)
			if (a[i][j] + a[i + 1][j + 1] + a[i +2][j + 2] + a[i + 3][j + 3] + a[i + 4][j + 4] == 12)// ����������������������12��˵���Ѿ����ĸ���ͬ���ˣ�
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
	for (i = 1; i < 16; i++)//�����ж�
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

	for (i = 1; i < 16; i++)//�����ж�
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
	for (i = 1; i < 16; i++)//�����ж�
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
	for (i = 1; i < 16; i++)//�����ж�
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
	for (i = 1; i < 16; i++)//������������һ��
		for (j = 1; j < 16; j++)
		{
			if (a[i][j] + a[i + 1][j] + a[i + 2][j] + a[i + 3][j] == 21)//����������4����������һ��
			{
				if((i>1&&a[i-1][j]==0)||(i<12&&a[i+4][j]==0))
					for (m = i+3; m > i -1; m--)
						if (a[m][j] == 0)
						{
							a[m][j] = 7; draw(m, j); return true;
						}
			}
		}
	for (i = 1; i < 16; i++)//�����ж�
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
	for (i = 1; i < 16; i++)//�����ж�
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
	for (i = 1; i < 16; i++)//�����ж�
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
	//�����ж�
	for (i = 1; i < 16; i++)
		for (j =1; j < 16; j++)
			if (a[i][j] + a[i][j + 1] + a[i][j + 2] + a[i][j + 3] + a[i][j + 4] == 28)// ����������������������28��˵���Ѿ����ĸ���ͬ���ˣ�
			{
				for (m = j; m < j + 5; m++)
					if (a[i][m] == 0)
					{
						a[i][m] = 7; draw(i, m); return true;
					}
			}
	//�����ж�
	for (i = 1; i < 16; i++)
		for (j = 1; j < 16; j++)
			if (a[i][j] + a[i + 1][j] + a[i + 2][j] + a[i + 3][j] + a[i + 4][j] == 28)// ����������������������12��˵���Ѿ����ĸ���ͬ���ˣ�
			{
				for (m = i; m < i + 5; m++)
					if (a[m][j] == 0)
					{
						a[m][j] = 7; draw(m, j); return true;
					}
			}
	//�����ж�
	for (i = 1; i < 16; i++)
		for (j = 1; j < 16; j++)
			if (a[i][j] + a[i - 1][j + 1] + a[i - 2][j + 2] + a[i - 3][j + 3] + a[i - 4][j + 4] == 28)// ����������������������12��˵���Ѿ����ĸ���ͬ���ˣ�
			{
				for (m = i, n = j; m > i - 5; m--, n++)
					if (a[m][n] == 0)
					{
						a[m][n] = 7; draw(m, n); return true;
					}
				 
			}
	//�����ж�
	for (i = 1; i < 16; i++)
		for (j = 1; j < 16; j++)
			if (a[i][j] + a[i + 1][j + 1] + a[i + 2][j + 2] + a[i + 3][j + 3] + a[i + 4][j + 4] == 28)// ����������������������12��˵���Ѿ����ĸ���ͬ���ˣ�
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
	//�˴�����Σ����������ж���������
	if (flag == 2)
	{
		if (ComFourToFive())//��������Ѿ����ĸ�һ����ˣ��ǲ��ϵ�����ֱ�ӽ�����
		{
			IsComputerWin();
			flag = 1;
			return;
		}
		if (FourOnLine())//����û���ĸ�һ��ģ�������Ҫ�жϵ�������Ƿ����ĸ����ߵ�
		{
			IsComputerWin();
			flag = 1;
			return;
		}
		if (ComThreeToFour())//���û��������в���ǾͿ����Կ��Բ�����һ����������ĸ����ߵ�
		{
			IsComputerWin();
			flag = 1;
			return;
		}
		if (ThreeOnLine())//���û�У���Ҫ���ж϶�����û������һ���
		{
			IsComputerWin();
			flag = 1;
			return;
		}
		if (ComTwoToThree())//�ȹ�����û������һ��ģ��ǵ��Ծʹ�����һ���
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

void CFiveStarDlg::IsComputerWin()//�жϵ�����Ӯ
{
	int m, n;
	for (m = 1; m < 16; m++)
		for (n = 1; n < 16; n++)
		{
			if (a[m][n] == 7)				//�жϺ����Ƿ�Ӯ��
			{
				if ((a[m + 1][n] == 7 && a[m + 2][n] == 7 && a[m + 3][n] == 7 && a[m + 4][n] == 7) || a[m - 1][n + 1] == 7 && a[m - 2][n + 2] == 7 && a[m - 3][n + 3] ==7 && a[m - 4][n + 4] ==7 || (a[m][n + 1] == 7 && a[m][n + 2] ==7 && a[m][n + 3] == 7&& a[m][n + 4] == 7) || (a[m + 1][n + 1] == 7 && a[m + 2][n + 2] == 7 && a[m + 3][n + 3] == 7 && a[m + 4][n + 4] == 7))
				{
					AfxMessageBox(_T("������˼Ŷ������ʤ������"));
				/*	int res = AfxMessageBox(_T("�Ƿ�������"), MB_YESNO);
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
void CFiveStarDlg::OnBnClickedButton1()//����
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int r = AfxMessageBox(_T("�Ƿ�ȷ���˳�"), MB_YESNO);
	if (r == IDYES)
		AfxGetMainWnd()->DestroyWindow();
	else
		return;
}
