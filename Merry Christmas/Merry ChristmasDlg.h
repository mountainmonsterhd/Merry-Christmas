
// Merry ChristmasDlg.h : ͷ�ļ�
//

#pragma once


// CMerryChristmasDlg �Ի���
class CMerryChristmasDlg : public CDialogEx
{
// ����
public:
	CMerryChristmasDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MERRYCHRISTMAS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
//	afx_msg void OnClose();


	//************************************DC��ʼ��***************
	CRect m_client;    //����ͻ�����С

	CDC m_cacheDC;   //����DC
	CBitmap m_cacheCBitmap;//����λͼ
	//*************************��ʼ����************
	struct begin
	{
	//����ͼƬ

		CImage background;//�ڶ�����
		CImage translation;//ת������ɫ��
		CImage beginpic;//��һ����
		CImage mainpic;//������˵�
		CImage dialog;//��ʾ��
		CImage warning1;//�뿪��Ϸ��ʾ
		CImage warning2;//δͨ�ؼ�����Ϸ��ʾ
		CImage warning3;//������Ϸ��ʾ
		CImage text;//���ؽ�������

		//��̬���
		struct items
		{
			int frame;
			CImage pic;
			int y;
		}start;
		items continues;//����
		items quit;//�뿪
		items bird;//�嶾��
		items loading;//��������
		items yes;//�ǵ�
		items no;//��Ҫ
		items cancel;//ȡ��
		items confirm;//ȷ��
		
		Gdiplus::Brush *m_pBrush;//ת����ˢ
		Gdiplus::Brush *textBrush;//���ֻ�ˢ
		Gdiplus::Color A;

		int tmd;//����͸����
		int tmd2;//��ˢ͸����
		int texttmd[100];//���ֻ�ˢ͸����
		int textnum;
		int pointer;//Ŀ��ָ��
		int mousepoint;//���ָ��
	}beg;
	//*******************bool����
	struct mybools
	{
		bool beginloading;//�Ƿ��ڿ�ʼ׼���׶�
		bool second;//�ж��ڵڶ�����
		bool main;//������
		bool translation;//�ж��Ƿ�ת��
		bool loading;//�ж��Ƿ����
		bool quitdialog;//�ж��뿪�Ի����Ƿ��
		bool click;//�ж��������Ƿ����
		bool Misioncompleted;///�ж��Ƿ�ͨ��
		bool dialogopen;//�ж϶Ի����Ƿ��
		bool continuedialog;//�жϼ����Ի����Ƿ��
		bool startdialog;//�жϽ�����Ϸ�Ի����Ƿ��
		bool startgame;//�ж��Ƿ������Ϸ
		bool plot0[50];
		bool plot1[50];
	}bools;
	//***********�̶߳���
	struct mythreads
	{
		CWinThread* LOADING;//������·
		CWinThread* BGM;//����������·
	}threads;
	int plotnum;
	//***************�����ṹ��
	struct places
	{
		CImage dia;
		CImage p1;
		CImage p2;
		CImage p3;
		CImage p4;
	}place;
	//*********************����ṹ��
	struct characters
	{
		CImage hei1;
		CImage hei2;
	}character;

	int bgmflags;

	HCURSOR hCursor;//�Զ������

	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
};
//ȫ�ֱ������壨��Ϊʹ�ö��̼߳��أ�û�취�ˡ�������

	
	