
// FiveStarDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CFiveStarDlg 对话框
class CFiveStarDlg : public CDialogEx
{
// 构造
public:
	CFiveStarDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FIVESTAR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CFont m_font;
	int prex, prey;//prex2, prey2;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtExit();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButton1();
	afx_msg void ComputerPlay();
	afx_msg bool ThreeOnLine();
	afx_msg bool FourOnLine();
	afx_msg bool ComTwoToThree();
	afx_msg bool ComThreeToFour();
	afx_msg bool ComFourToFive();
	afx_msg void ComFirst();
	afx_msg void usual();
	afx_msg void draw(int, int);
	afx_msg void IsComputerWin();
	
	//DWORD WINAPI CFiveStarDlg::thread(LPVOID lpa);
//	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};
