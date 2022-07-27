
// Merry ChristmasDlg.h : 头文件
//

#pragma once


// CMerryChristmasDlg 对话框
class CMerryChristmasDlg : public CDialogEx
{
// 构造
public:
	CMerryChristmasDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MERRYCHRISTMAS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
//	afx_msg void OnClose();


	//************************************DC初始化***************
	CRect m_client;    //保存客户区大小

	CDC m_cacheDC;   //缓冲DC
	CBitmap m_cacheCBitmap;//缓冲位图
	//*************************开始界面************
	struct begin
	{
	//单张图片

		CImage background;//第二界面
		CImage translation;//转场（白色）
		CImage beginpic;//第一界面
		CImage mainpic;//主界面菜单
		CImage dialog;//提示框
		CImage warning1;//离开游戏提示
		CImage warning2;//未通关继续游戏提示
		CImage warning3;//进入游戏提示
		CImage text;//加载界面文字

		//动态物件
		struct items
		{
			int frame;
			CImage pic;
			int y;
		}start;
		items continues;//继续
		items quit;//离开
		items bird;//五毒兽
		items loading;//加载文字
		items yes;//是的
		items no;//不要
		items cancel;//取消
		items confirm;//确定
		
		Gdiplus::Brush *m_pBrush;//转场画刷
		Gdiplus::Brush *textBrush;//文字画刷
		Gdiplus::Color A;

		int tmd;//窗口透明度
		int tmd2;//画刷透明度
		int texttmd[100];//文字画刷透明度
		int textnum;
		int pointer;//目标指针
		int mousepoint;//鼠标指针
	}beg;
	//*******************bool变量
	struct mybools
	{
		bool beginloading;//是否在开始准备阶段
		bool second;//判断在第二界面
		bool main;//主界面
		bool translation;//判断是否转场
		bool loading;//判断是否加载
		bool quitdialog;//判断离开对话框是否打开
		bool click;//判断鼠标左键是否点下
		bool Misioncompleted;///判断是否通关
		bool dialogopen;//判断对话框是否打开
		bool continuedialog;//判断继续对话框是否打开
		bool startdialog;//判断进入游戏对话框是否打开
		bool startgame;//判断是否进入游戏
		bool plot0[50];
		bool plot1[50];
	}bools;
	//***********线程定义
	struct mythreads
	{
		CWinThread* LOADING;//加载线路
		CWinThread* BGM;//背景音乐线路
	}threads;
	int plotnum;
	//***************场景结构体
	struct places
	{
		CImage dia;
		CImage p1;
		CImage p2;
		CImage p3;
		CImage p4;
	}place;
	//*********************人物结构体
	struct characters
	{
		CImage hei1;
		CImage hei2;
	}character;

	int bgmflags;

	HCURSOR hCursor;//自定义鼠标

	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
};
//全局变量定义（因为使用多线程加载，没办法了。。。）

	
	