#include "stdafx.h"
#include "Merry Christmas.h"
#include "Merry ChristmasDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include <MMSystem.h>

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif
#define NONE -1
#define START 1
#define CONTINUE 2
#define QUIT 3
#define YES 4
#define NO 5
#define CONFIRM 6
#define CANCEL 7
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
//�ػ�ʱ��
#define TIMER_PAINT 1001  
//��ͷ����ʱ��
#define TIMER_CREATE 1002  
#define TIMER_CREATE0 1003
#define TIMER_CREATE1 1004
#define TIMER_CREATE2 1005
#define TIMER_CREATE3 1006
//��ͷ����ʱ��
#define TIMER_BIRD 1007//�嶾��
#define TIMER_LOADING 1008//��������
//���ֻ�ˢ
#define TIMER_WORD 1009

//ת��ʱ��
#define TIMER_TRANSLATION1 1012
#define TIMER_TRANSLATION2 1013
#define TIMER_TRANSLATION3 1014
#define TIMER_TRANSLATION4 1010
#define TIMER_TRANSLATION5 1011
#define TIMER_TRANSLATION6 1015


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMerryChristmasDlg �Ի���




CMerryChristmasDlg::CMerryChristmasDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMerryChristmasDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMerryChristmasDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

//***************�Զ��庯��
void TransparentPNG(CImage *png)
{
    for(int i = 0; i <png->GetWidth(); i++)
    {
        for(int j = 0; j <png->GetHeight(); j++)
        {
            unsigned char* pucColor = reinterpret_cast<unsigned char*>(png->GetPixelAddress(i , j));
            pucColor[0] = pucColor[0] *pucColor[3] / 255;
            pucColor[1] = pucColor[1] *pucColor[3] / 255;
            pucColor[2] = pucColor[2] *pucColor[3] / 255;
        }
    }
}

BEGIN_MESSAGE_MAP(CMerryChristmasDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
END_MESSAGE_MAP()


// CMerryChristmasDlg ��Ϣ�������

BOOL CMerryChristmasDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

UINT Loading(LPVOID pParam)
{
	CMerryChristmasDlg* merry = (CMerryChristmasDlg*)pParam;
	if(merry->bools.beginloading)
	{
		//��ʼ����ͼƬ����
		merry->beg.start.pic.Load(_T("res\\words\\start.png"));
		merry->beg.continues.pic.Load(_T("res\\words\\continue.png"));
		merry->beg.quit.pic.Load(_T("res\\words\\quit.png"));
		merry->beg.bird.pic.Load(_T("res\\birds.png"));
		merry->beg.confirm.pic.Load(_T("res\\words\\confirm.png"));
		merry->beg.cancel.pic.Load(_T("res\\words\\cancel.png"));
		merry->beg.yes.pic.Load(_T("res\\words\\yes.png"));
		merry->beg.no.pic.Load(_T("res\\words\\no.png"));
		merry->beg.dialog.Load(_T("res\\dialog.png"));
		merry->beg.mainpic.Load(_T("res\\places\\begin.png"));
		merry->beg.loading.pic.Load(_T("res\\words\\loading.png"));
		merry->beg.warning1.Load(_T("res\\words\\warning1.png"));
		merry->beg.warning2.Load(_T("res\\words\\warning2.png"));
		merry->beg.warning3.Load(_T("res\\words\\warning3.png"));
		merry->beg.text.Load(_T("res\\words\\loadingtext.png"));
		
		//ͼƬ�Ż�
		TransparentPNG(&merry->beg.warning3);
		TransparentPNG(&merry->beg.warning2);
		TransparentPNG(&merry->beg.warning1);
		TransparentPNG(&merry->beg.text);
		TransparentPNG(&merry->beg.start.pic);
		TransparentPNG(&merry->beg.continues.pic);
		TransparentPNG(&merry->beg.quit.pic);
		TransparentPNG(&merry->beg.bird.pic);
		TransparentPNG(&merry->beg.confirm.pic);
		TransparentPNG(&merry->beg.cancel.pic);
		TransparentPNG(&merry->beg.yes.pic);
		TransparentPNG(&merry->beg.no.pic);
		TransparentPNG(&merry->beg.dialog);
		TransparentPNG(&merry->beg.loading.pic);
		//��ʼ����ʼ����ֵ
		merry->beg.loading.frame = 0;
		merry->beg.bird.frame = 1;
		merry->beg.yes.frame = 0;
		merry->beg.no.frame = 0;
		merry->beg.confirm.frame = 0;
		merry->beg.cancel.frame = 0;
		merry->beg.mousepoint = NONE;

		merry->beg.bird.y = 270;
		merry->beg.start.frame = 1;
		merry->beg.continues.frame = 0;
		merry->beg.quit.frame = 0;

		//bool������ʼ��
		merry->bools.quitdialog = 0;
		merry->bools.dialogopen = 0;
		merry->bools.loading = 0;
		merry->bools.click = 0;
		merry->bools.continuedialog = 0;
		merry->bools.startdialog = 0;
		merry->bools.Misioncompleted = 0;//���ô浵����ʱ����
			//�̹߳��𣬿������Ϊ���߳���ͣ
		//	pThread->SuspendThread();
			//���¿�ʼִ�б�������߳�
		//	pThread->ResumeThread();
	}
	else if(merry->bools.loading&&!merry->bools.beginloading)
	{
		for(int i = 0;i<50;i++)
		{
			merry->bools.plot0[i]=0;
			merry->bools.plot1[i]=0;
		}
		merry->bools.plot0[0] = 1;
		for(int i = 0;i<100;i++)
		{
			merry->beg.texttmd[i] = 255;
		}
		//������Ϸ�ڲ�ͼƬ
		merry->place.p1.Load(_T("res\\places\\1.jpeg"));
		merry->place.p2.Load(_T("res\\places\\2.jpg"));
		merry->place.p3.Load(_T("res\\places\\3.png"));
		merry->place.p4.Load(_T("res\\places\\4.jpg"));
		merry->place.dia.Load(_T("res\\places\\dialog.png"));
		merry->character.hei1.Load(_T("res\\characters\\hei1.png"));
		merry->character.hei2.Load(_T("res\\characters\\hei2.png"));

		//�Ż���Ϸ�ڲ�ͼƬ
		TransparentPNG(&merry->character.hei1);
		TransparentPNG(&merry->character.hei2);
		TransparentPNG(&merry->place.dia);

		merry->plotnum = 2;
		merry->beg.tmd2 = 0;
		Gdiplus::Color B(0,0,0,0);
		merry->beg.A = B;
		Sleep(5000);
		merry->bools.translation = 1;
	}
	return 0;
}

UINT Bgmplaying(LPVOID pParam)
{
	CMerryChristmasDlg* merry = (CMerryChristmasDlg*)pParam;
	if(merry->bgmflags == 0)
		sndPlaySound(_T("res\\sounds\\memory.wav"),SND_ASYNC | SND_LOOP);
	else if(merry->bgmflags == 1)
		sndPlaySound(NULL,SND_ASYNC);
	else if(merry->bgmflags == 2)
		sndPlaySound(_T("res\\sounds\\my.wav"),SND_ASYNC | SND_LOOP);

	return 0;
}
void CMerryChristmasDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMerryChristmasDlg::OnPaint()
{
//******************����DC*****************
	
	CDC *cDC=this->GetDC();//��ȡ����DCָ��
	
	GetClientRect(&m_client);//��ȡ���ڴ�С
	
	m_cacheDC.CreateCompatibleDC(NULL);
	m_cacheCBitmap.CreateCompatibleBitmap(cDC,m_client.Width(),m_client.Height());//��������DC
	m_cacheDC.SelectObject(&m_cacheCBitmap);
	
	Gdiplus::Color c;
	Gdiplus::Graphics gp(m_cacheDC);
	
//**************************����ͼ�����*******************


	if(bools.second&&bools.beginloading&&!bools.main)//�ڶ�����
	{		
		beg.background.Draw(m_cacheDC,0,0,1280,720,0,0,1280,720);
	}
	else if(!bools.second&&bools.beginloading&&!bools.main)//��һ����
	{
		beg.translation.Draw(m_cacheDC,0,0,1280,720,0,0,1280,720);
		beg.beginpic.Draw(m_cacheDC,100,110,1100,610,0,0,1000,500);
	}
	else if(!bools.beginloading&&bools.main&&!bools.loading)//������
	{
		if(beg.pointer == START)
		{
			beg.bird.y = 270;
			beg.start.frame = 1;
			beg.continues.frame = 0;
			beg.quit.frame = 0;
		}
		else if(beg.pointer == CONTINUE)
		{
			beg.bird.y = 400;
			beg.start.frame = 0;
			beg.continues.frame = 1;
			beg.quit.frame = 0;
		}
		else if(beg.pointer == QUIT)
		{
			beg.bird.y = 534;
			beg.start.frame = 0;
			beg.continues.frame = 0;
			beg.quit.frame = 1;
		}
		beg.mainpic.Draw(m_cacheDC,0,0,1280,720,0,0,1280,720);
		beg.start.pic.Draw(m_cacheDC,300,300,364,80,0,beg.start.frame*80,364,80);
		beg.continues.pic.Draw(m_cacheDC,300,430,352,84,0,beg.continues.frame*84,352,84);
		beg.quit.pic.Draw(m_cacheDC,300,564,352,82,0,beg.quit.frame*82,352,82);
		if(!bools.dialogopen)
			beg.bird.pic.Draw(m_cacheDC,200,beg.bird.y,92,101,beg.bird.frame*92,0,92,101);

		if(bools.dialogopen)
		{
			beg.dialog.Draw(m_cacheDC,270,100,767,534,0,0,959,667);
			if(bools.quitdialog)
			{
				if(beg.pointer == YES)
				{
					beg.bird.y = 340;
					if(beg.yes.frame != 2)
					{
						beg.yes.frame = 1;
						beg.no.frame = 0;
					}
				}
				else if(beg.pointer == NO)
				{
					beg.bird.y = 450;

					if(beg.no.frame != 2)
					{
						beg.no.frame = 1;
						beg.yes.frame = 0;
					}
				}
				beg.warning1.Draw(m_cacheDC,400,225,534,91,0,0,534,91);
				beg.yes.pic.Draw(m_cacheDC,490,370,163,75,0,beg.yes.frame*75,163,75);
				beg.no.pic.Draw(m_cacheDC,490,480,182,80,0,beg.no.frame*80,182,80);
				beg.bird.pic.Draw(m_cacheDC,390,beg.bird.y,92,101,beg.bird.frame*92,0,92,101);
			}
			else if(bools.continuedialog)
			{
				if(beg.pointer == CONFIRM)
				{
					beg.bird.y = 410;
					if(beg.confirm.frame != 2)
					{
						beg.confirm.frame = 1;
					}
				}
				beg.warning2.Draw(m_cacheDC,430,200,436,162,0,0,545,202);
				beg.confirm.pic.Draw(m_cacheDC,490,440,170,85,0,beg.confirm.frame*85,170,85);
				beg.bird.pic.Draw(m_cacheDC,390,beg.bird.y,92,101,beg.bird.frame*92,0,92,101);
			}
			else if(bools.startdialog)
			{
				if(beg.pointer == CONFIRM)
				{
					beg.bird.y = 340;
					if(beg.confirm.frame != 2)
					{
						beg.confirm.frame = 1;
						beg.cancel.frame = 0;
					}
				}
				else if(beg.pointer == CANCEL)
				{
					beg.bird.y = 450;

					if(beg.cancel.frame != 2)
					{
						beg.cancel.frame = 1;
						beg.confirm.frame = 0;
					}
				}
				beg.warning3.Draw(m_cacheDC,530,150,352,194,0,0,352,194);
				beg.confirm.pic.Draw(m_cacheDC,490,370,170,85,0,beg.confirm.frame*85,170,85);
				beg.cancel.pic.Draw(m_cacheDC,490,480,168,74,0,beg.cancel.frame*74,168,74);
				beg.bird.pic.Draw(m_cacheDC,390,beg.bird.y,92,101,beg.bird.frame*92,0,92,101);
			}
		}
	}

	if(bools.startgame)
	{
		if(bools.plot0[0])
		{
			CFont font;
			font.CreateFontW(50,0,0,0,FW_BLACK,FALSE,FALSE,FALSE,GB2312_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,VARIABLE_PITCH|PROOF_QUALITY,FIXED_PITCH | FF_MODERN,_T("����"));
			m_cacheDC.SelectObject(&font);
			SetTextColor(m_cacheDC,RGB(0,0,0));
			SetBkMode(m_cacheDC,TRANSPARENT);
			beg.translation.Draw(m_cacheDC,0,0,1280,720,0,0,1280,720);
			m_cacheDC.TextOutW(200,70,_T("ʥ"));
			m_cacheDC.TextOutW(200,120,_T("��"));
			m_cacheDC.TextOutW(200,170,_T("��"));
			m_cacheDC.TextOutW(200,220,_T("ǰ"));
			m_cacheDC.TextOutW(200,270,_T("Ϧ"));
			m_cacheDC.TextOutW(200,350,_T("һ"));
			m_cacheDC.TextOutW(200,400,_T("��"));
			m_cacheDC.TextOutW(200,450,_T("��"));//////7
			m_cacheDC.TextOutW(430,70,_T("��"));//8
			m_cacheDC.TextOutW(430,120,_T("��"));
			m_cacheDC.TextOutW(430,170,_T("��"));
			m_cacheDC.TextOutW(430,220,_T("ҹ"));
			m_cacheDC.TextOutW(430,270,_T("��"));//12
			m_cacheDC.TextOutW(430,350,_T("û"));
			m_cacheDC.TextOutW(430,400,_T("��"));
			m_cacheDC.TextOutW(430,450,_T("��"));
			m_cacheDC.TextOutW(430,500,_T("��"));///////16
			m_cacheDC.TextOutW(660,70,_T("��"));
			m_cacheDC.TextOutW(660,120,_T("��"));
			m_cacheDC.TextOutW(660,200,_T("ֻ"));
			m_cacheDC.TextOutW(660,250,_T("��"));
			m_cacheDC.TextOutW(660,300,_T("��"));
			m_cacheDC.TextOutW(660,350,_T("��"));
			m_cacheDC.TextOutW(660,400,_T("��"));
			m_cacheDC.TextOutW(660,450,_T("��"));
			m_cacheDC.TextOutW(660,500,_T("ϡ"));
			m_cacheDC.TextOutW(660,550,_T("��"));
			m_cacheDC.TextOutW(660,600,_T("��"));
			m_cacheDC.TextOutW(660,650,_T("��"));//28
			m_cacheDC.TextOutW(890,70,_T("��"));
			m_cacheDC.TextOutW(890,120,_T("��"));
			m_cacheDC.TextOutW(890,200,_T("��"));
			m_cacheDC.TextOutW(890,250,_T("��"));
			m_cacheDC.TextOutW(890,300,_T("��"));
			m_cacheDC.TextOutW(890,350,_T("һ"));
			m_cacheDC.TextOutW(890,400,_T("��"));
			m_cacheDC.TextOutW(890,450,_T("��"));//36
			Gdiplus::Color B0(beg.texttmd[0],255,255,255);
			beg.textBrush = new Gdiplus::SolidBrush(B0);
			gp.FillRectangle(beg.textBrush,200,70,50,50);
			delete beg.textBrush;
			Gdiplus::Color B1(beg.texttmd[1],255,255,255);
			beg.textBrush = new Gdiplus::SolidBrush(B1);
			gp.FillRectangle(beg.textBrush,200,120,50,50);
			delete beg.textBrush;
			Gdiplus::Color B2(beg.texttmd[2],255,255,255);
			beg.textBrush = new Gdiplus::SolidBrush(B2);
			gp.FillRectangle(beg.textBrush,200,170,50,50);
			delete beg.textBrush;
			Gdiplus::Color B3(beg.texttmd[3],255,255,255);
			beg.textBrush = new Gdiplus::SolidBrush(B3);
			gp.FillRectangle(beg.textBrush,200,220,50,50);
			delete beg.textBrush;
			Gdiplus::Color B4(beg.texttmd[4],255,255,255);
			beg.textBrush = new Gdiplus::SolidBrush(B4);
			gp.FillRectangle(beg.textBrush,200,270,50,50);
			delete beg.textBrush;
			Gdiplus::Color B5(beg.texttmd[5],255,255,255);
			beg.textBrush = new Gdiplus::SolidBrush(B5);
			gp.FillRectangle(beg.textBrush,200,350,50,50);
			delete beg.textBrush;
			Gdiplus::Color B6(beg.texttmd[6],255,255,255);
			beg.textBrush = new Gdiplus::SolidBrush(B6);
			gp.FillRectangle(beg.textBrush,200,400,50,50);
			delete beg.textBrush;
			Gdiplus::Color B7(beg.texttmd[7],255,255,255);
			beg.textBrush = new Gdiplus::SolidBrush(B7);
			gp.FillRectangle(beg.textBrush,200,450,50,50);
			delete beg.textBrush;
			Gdiplus::Color B8(beg.texttmd[8],255,255,255);
			beg.textBrush = new Gdiplus::SolidBrush(B8);
			gp.FillRectangle(beg.textBrush,430,70,50,50);
			delete beg.textBrush;
			Gdiplus::Color B9(beg.texttmd[9],255,255,255);
			beg.textBrush = new Gdiplus::SolidBrush(B9);
			gp.FillRectangle(beg.textBrush,430,120,50,50);
			delete beg.textBrush;
			Gdiplus::Color B10(beg.texttmd[10],255,255,255);
			beg.textBrush = new Gdiplus::SolidBrush(B10);
			gp.FillRectangle(beg.textBrush,430,170,50,50);
			delete beg.textBrush;
			Gdiplus::Color B11(beg.texttmd[11],255,255,255);
			beg.textBrush = new Gdiplus::SolidBrush(B11);
			gp.FillRectangle(beg.textBrush,430,220,50,50);
			delete beg.textBrush;
			Gdiplus::Color B12(beg.texttmd[12],255,255,255);
			beg.textBrush = new Gdiplus::SolidBrush(B12);
			gp.FillRectangle(beg.textBrush,430,270,50,50);
			delete beg.textBrush;
			Gdiplus::Color B13(beg.texttmd[13],255,255,255);
			beg.textBrush = new Gdiplus::SolidBrush(B13);
			gp.FillRectangle(beg.textBrush,430,350,50,50);
			delete beg.textBrush;
			Gdiplus::Color B14(beg.texttmd[14],255,255,255);
			beg.textBrush = new Gdiplus::SolidBrush(B14);
			gp.FillRectangle(beg.textBrush,430,400,50,50);
			delete beg.textBrush;
			Gdiplus::Color B15(beg.texttmd[15],255,255,255);
			beg.textBrush = new Gdiplus::SolidBrush(B15);
			gp.FillRectangle(beg.textBrush,430,450,50,50);
			delete beg.textBrush;
			Gdiplus::Color B16(beg.texttmd[16],255,255,255);
			beg.textBrush = new Gdiplus::SolidBrush(B16);
			gp.FillRectangle(beg.textBrush,430,500,50,50);
			delete beg.textBrush;
			Gdiplus::Color B17(beg.texttmd[17],255,255,255);
			beg.textBrush = new Gdiplus::SolidBrush(B17);
			gp.FillRectangle(beg.textBrush,660,70,50,50);
			delete beg.textBrush;
			Gdiplus::Color B18(beg.texttmd[18],255,255,255);
			beg.textBrush = new Gdiplus::SolidBrush(B18);
			gp.FillRectangle(beg.textBrush,660,120,50,50);
			delete beg.textBrush;
			Gdiplus::Color B19(beg.texttmd[19],255,255,255);
			beg.textBrush = new Gdiplus::SolidBrush(B19);
			gp.FillRectangle(beg.textBrush,660,200,50,50);
			delete beg.textBrush;
			Gdiplus::Color B20(beg.texttmd[20],255,255,255);
			beg.textBrush = new Gdiplus::SolidBrush(B20);
			gp.FillRectangle(beg.textBrush,660,250,50,50);
			delete beg.textBrush;
			Gdiplus::Color B21(beg.texttmd[21],255,255,255);
			beg.textBrush = new Gdiplus::SolidBrush(B21);
			gp.FillRectangle(beg.textBrush,660,300,50,50);
			delete beg.textBrush;
			Gdiplus::Color B22(beg.texttmd[22],255,255,255);
			beg.textBrush = new Gdiplus::SolidBrush(B22);
			gp.FillRectangle(beg.textBrush,660,350,50,50);
			delete beg.textBrush;
			Gdiplus::Color B23(beg.texttmd[23],255,255,255);
			beg.textBrush = new Gdiplus::SolidBrush(B23);
			gp.FillRectangle(beg.textBrush,660,400,50,50);
			delete beg.textBrush;
			Gdiplus::Color B24(beg.texttmd[24],255,255,255);
			beg.textBrush = new Gdiplus::SolidBrush(B24);
			gp.FillRectangle(beg.textBrush,660,450,50,50);
			delete beg.textBrush;
			Gdiplus::Color B25(beg.texttmd[25],255,255,255);
			beg.textBrush = new Gdiplus::SolidBrush(B25);
			gp.FillRectangle(beg.textBrush,660,500,50,50);
			delete beg.textBrush;
			Gdiplus::Color B26(beg.texttmd[26],255,255,255);
			beg.textBrush = new Gdiplus::SolidBrush(B26);
			gp.FillRectangle(beg.textBrush,660,550,50,50);
			delete beg.textBrush;
			Gdiplus::Color B27(beg.texttmd[27],255,255,255);
			beg.textBrush = new Gdiplus::SolidBrush(B27);
			gp.FillRectangle(beg.textBrush,660,600,50,50);
			delete beg.textBrush;
			Gdiplus::Color B28(beg.texttmd[28],255,255,255);
			beg.textBrush = new Gdiplus::SolidBrush(B28);
			gp.FillRectangle(beg.textBrush,660,650,50,50);
			delete beg.textBrush;
			Gdiplus::Color B29(beg.texttmd[29],255,255,255);
			beg.textBrush = new Gdiplus::SolidBrush(B29);
			gp.FillRectangle(beg.textBrush,890,70,50,50);
			delete beg.textBrush;
			Gdiplus::Color B30(beg.texttmd[30],255,255,255);
			beg.textBrush = new Gdiplus::SolidBrush(B30);
			gp.FillRectangle(beg.textBrush,890,120,50,50);
			delete beg.textBrush;
			Gdiplus::Color B31(beg.texttmd[31],255,255,255);
			beg.textBrush = new Gdiplus::SolidBrush(B31);
			gp.FillRectangle(beg.textBrush,890,200,50,50);
			delete beg.textBrush;
			Gdiplus::Color B32(beg.texttmd[32],255,255,255);
			beg.textBrush = new Gdiplus::SolidBrush(B32);
			gp.FillRectangle(beg.textBrush,890,250,50,50);
			delete beg.textBrush;
			Gdiplus::Color B33(beg.texttmd[33],255,255,255);
			beg.textBrush = new Gdiplus::SolidBrush(B33);
			gp.FillRectangle(beg.textBrush,890,300,50,50);
			delete beg.textBrush;
			Gdiplus::Color B34(beg.texttmd[34],255,255,255);
			beg.textBrush = new Gdiplus::SolidBrush(B34);
			gp.FillRectangle(beg.textBrush,890,350,50,50);
			delete beg.textBrush;
			Gdiplus::Color B35(beg.texttmd[35],255,255,255);
			beg.textBrush = new Gdiplus::SolidBrush(B35);
			gp.FillRectangle(beg.textBrush,890,400,50,50);
			delete beg.textBrush;
			Gdiplus::Color B36(beg.texttmd[36],255,255,255);
			beg.textBrush = new Gdiplus::SolidBrush(B36);
			gp.FillRectangle(beg.textBrush,890,450,50,50);
			delete beg.textBrush;
			font.DeleteObject();
		}
		if(bools.plot0[1])
		{
			place.p1.Draw(m_cacheDC,0,0,1280,720,0,0,1280,720);
			CFont font;
			font.CreateFontW(30,0,0,0,FW_BLACK,FALSE,FALSE,FALSE,GB2312_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,VARIABLE_PITCH|PROOF_QUALITY,FIXED_PITCH | FF_MODERN,_T("����"));
			m_cacheDC.SelectObject(&font);
			SetTextColor(m_cacheDC,RGB(255,255,255));
			SetBkMode(m_cacheDC,TRANSPARENT);
			if(bools.plot0[2])
			{
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(30,550,_T("���壺"));
				m_cacheDC.TextOutW(90,600,_T("�������ϣ����е����أ�"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[3])
			{
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(30,550,_T("���壺"));
				m_cacheDC.TextOutW(90,600,_T("�������ʥ�����ˡ�"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[4])
			{
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(30,550,_T("���壺"));
				m_cacheDC.TextOutW(90,600,_T("��ջ�����ô�����ڵ��Ż谵�������أ�"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[5])
			{
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(30,550,_T("���壺"));
				m_cacheDC.TextOutW(90,600,_T("��һ�룬�����Ҵӳ���������ʮ�Ÿ�ʥ�����ˡ�"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[6])
			{
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(30,550,_T("���壺"));
				m_cacheDC.TextOutW(90,600,_T("���������һ���ˡ�"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[7])
			{
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(30,550,_T("���壺"));
				m_cacheDC.TextOutW(90,600,_T("��Ȼ......"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[8])
			{
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(30,550,_T("���壺"));
				m_cacheDC.TextOutW(90,600,_T("�Ҳ����������������ҡ�"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[9])
			{
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(30,550,_T("���壺"));
				m_cacheDC.TextOutW(90,600,_T("һ���ˣ�ͦ�õġ�"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[10])
			{
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(30,550,_T("���壺"));
				m_cacheDC.TextOutW(90,600,_T("����......"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[11])
			{
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(30,550,_T("���壺"));
				m_cacheDC.TextOutW(90,600,_T("Ҳ��ʱ��......"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[12])
			{
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(30,550,_T("���壺"));
				m_cacheDC.TextOutW(90,600,_T("һ���ˣ�Ҳͦ�¶��ġ�"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[13])
			{
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(90,550,_T("���Ų�����"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[32])
			{
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(90,550,_T("����Ҳ�ٴ���������ա�"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[33])
			{
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(90,550,_T("˵������Ҳ���أ�����ȴ����ª��ҹ�գ��������ǵ�����һ����"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[34])
			{
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(30,550,_T("�к���"));
				m_cacheDC.TextOutW(90,600,_T("ι��"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[35])
			{
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(90,550,_T("�����к��Ľ�����"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			font.DeleteObject();
		}
		else if(bools.plot0[14])
		{
			place.p2.Draw(m_cacheDC,0,0,1280,720,0,0,1280,720);
			CFont font;
			font.CreateFontW(30,0,0,0,FW_BLACK,FALSE,FALSE,FALSE,GB2312_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,VARIABLE_PITCH|PROOF_QUALITY,FIXED_PITCH | FF_MODERN,_T("����"));
			m_cacheDC.SelectObject(&font);
			SetTextColor(m_cacheDC,RGB(255,255,255));
			SetBkMode(m_cacheDC,TRANSPARENT);
			if(bools.plot0[15])
			{
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(30,550,_T("���壺"));
				m_cacheDC.TextOutW(90,600,_T("��ѽ����"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[16])
			{
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(90,550,_T("���屻ĳ����ײ����һƨ�������˵��ϡ�"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[17])
			{
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(30,550,_T("�к���"));
				m_cacheDC.TextOutW(90,600,_T("�Բ���Բ�����û�°ɣ�"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[18])
			{
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(90,550,_T("ֻ����һ�����������˵����"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[19])//����������
			{
				character.hei1.Draw(m_cacheDC,800,174,420,546,0,0,840,1092);
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(90,550,_T("����̧ͷһ����������һ��һ����òӢ�����ʵ��к���ͷ�������������һֻ�֣�"));
				m_cacheDC.TextOutW(30,600,_T("����������������"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[20])
			{
				character.hei1.Draw(m_cacheDC,800,174,420,546,0,0,840,1092);
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(30,550,_T("���壺"));
				m_cacheDC.TextOutW(90,600,_T("�ҡ���û�¡�"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[21])
			{
				character.hei1.Draw(m_cacheDC,800,174,420,546,0,0,840,1092);
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(90,550,_T("������Щ���͵ؿ����к����ͺ������߱��к�ץס��һ�㡣"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[22])
			{
				character.hei1.Draw(m_cacheDC,800,174,420,546,0,0,840,1092);
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(30,550,_T("�к���"));
				m_cacheDC.TextOutW(90,600,_T("���û����"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[23])
			{
				character.hei1.Draw(m_cacheDC,800,174,420,546,0,0,840,1092);
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(90,550,_T("�к����ʵ���"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[24])
			{
				character.hei1.Draw(m_cacheDC,800,174,420,546,0,0,840,1092);
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(90,550,_T("����ͻȻ�е�����һ����ȣ��۾�һ���Ӳ����ټ������к�������"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[25])
			{
				character.hei1.Draw(m_cacheDC,800,174,420,546,0,0,840,1092);
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(30,550,_T("���壺"));
				m_cacheDC.TextOutW(90,600,_T("û�²Ź��֣������ײ��ѽ����ʹ�أ�"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[26])
			{
				character.hei1.Draw(m_cacheDC,800,174,420,546,0,0,840,1092);
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(90,550,_T("����ͻȻ̬��ǿӲ������˵����"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[27])
			{
				character.hei1.Draw(m_cacheDC,800,174,420,546,0,0,840,1092);
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(30,550,_T("�к���"));
				m_cacheDC.TextOutW(90,600,_T("�Բ�����......��·��ʱ�������ϵ����ǣ�û��ע�⵽��ô���ˣ�·�ϻ����ˡ�"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[28])
			{
				character.hei1.Draw(m_cacheDC,800,174,420,546,0,0,840,1092);
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(90,550,_T("ԭ�����к�������һ���������������ⵥ����ҹ�ա�"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[29])
			{
				character.hei1.Draw(m_cacheDC,800,174,420,546,0,0,840,1092);
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(30,550,_T("���壺"));
				m_cacheDC.TextOutW(90,600,_T("������......����·�߿���İ���"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[30])
			{
				character.hei1.Draw(m_cacheDC,800,174,420,546,0,0,840,1092);
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(30,550,_T("�к���"));
				m_cacheDC.TextOutW(90,600,_T("�����ҹ�յ�������Ҳ��ʧ��������ҲӦ���ڿ��ɣ�"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[31])
			{
				character.hei2.Draw(m_cacheDC,800,174,350,548,0,0,500,783);
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(90,550,_T("�к�û��Ů���ش�̧ͷ��������ա�"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[36])
			{
				character.hei1.Draw(m_cacheDC,800,174,420,546,0,0,840,1092);
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(90,550,_T("�����ͷ�����������к��������������ɵ�����һ����ȡ�"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[37])
			{
				character.hei1.Draw(m_cacheDC,800,174,420,546,0,0,840,1092);
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(30,550,_T("���壺"));
				m_cacheDC.TextOutW(90,600,_T("���......ͻȻ���ҡ�"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[38])
			{
				character.hei1.Draw(m_cacheDC,800,174,420,546,0,0,840,1092);
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(30,550,_T("�к���"));
				m_cacheDC.TextOutW(90,600,_T("���ʲô���ְ���"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[39])
			{
				character.hei1.Draw(m_cacheDC,800,174,420,546,0,0,840,1092);
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(30,550,_T("���壺"));
				m_cacheDC.TextOutW(90,600,_T("�������ܲ���ò������ײ���ң��������Լ������֣���������Ů���ӵ������ˡ�"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[40])
			{
				character.hei1.Draw(m_cacheDC,800,174,420,546,0,0,840,1092);
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(30,550,_T("������"));
				m_cacheDC.TextOutW(90,600,_T("�ðɣ��ҽС������������أ�"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[41])
			{
				character.hei1.Draw(m_cacheDC,800,174,420,546,0,0,840,1092);
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(30,550,_T("���壺"));
				m_cacheDC.TextOutW(90,600,_T("���塣"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[42])
			{
				character.hei1.Draw(m_cacheDC,800,174,420,546,0,0,840,1092);
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(30,550,_T("������"));
				m_cacheDC.TextOutW(90,600,_T("���壬����ͦ�����ġ�"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[43])
			{
				character.hei1.Draw(m_cacheDC,800,174,420,546,0,0,840,1092);
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(30,550,_T("������"));
				m_cacheDC.TextOutW(90,600,_T("��ã����壡�ܸ�����ʶ�㣡"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[44])
			{
				character.hei1.Draw(m_cacheDC,800,174,420,546,0,0,840,1092);
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(30,550,_T("���壺"));
				m_cacheDC.TextOutW(90,600,_T("......˭......�Ÿ�����ʶ��ѽ��"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[45])
			{
				character.hei1.Draw(m_cacheDC,800,174,420,546,0,0,840,1092);
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(90,550,_T("���廹��Ϊ�ղű�ײ�����¶���Щ���������ֲ��ҹ��ڱ��ֳ���������ȴһ����ȡ�"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[46])
			{
				character.hei1.Draw(m_cacheDC,800,174,420,546,0,0,840,1092);
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(30,550,_T("������"));
				m_cacheDC.TextOutW(90,600,_T("����Ϊ�ղŵ���������"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[47])
			{
				character.hei1.Draw(m_cacheDC,800,174,420,546,0,0,840,1092);
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(30,550,_T("���壺"));
				m_cacheDC.TextOutW(90,600,_T("û�У�������ô��������ôС�����ˣ�"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[48])
			{
				character.hei1.Draw(m_cacheDC,800,174,420,546,0,0,840,1092);
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(30,550,_T("������"));
				m_cacheDC.TextOutW(90,600,_T("�Ǿͺá�"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[48])
			{
				character.hei1.Draw(m_cacheDC,800,174,420,546,0,0,840,1092);
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(90,550,_T("����΢΢һЦ����ʵ���Ҳ�������Ц���زġ�����"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			else if(bools.plot0[49])
			{
				character.hei1.Draw(m_cacheDC,800,174,420,546,0,0,840,1092);
				place.dia.Draw(m_cacheDC,0,520,1280,200,0,0,1280,200);
				m_cacheDC.TextOutW(30,550,_T("������"));
				m_cacheDC.TextOutW(90,600,_T("��˵����Ϊʲô�����￴��շ�������"));
				m_cacheDC.TextOutW(900,680,_T("(������򰴿ո������)"));
			}
			font.DeleteObject();
		}
		if(bools.plot1[0])
		{
			CFont font;
			font.CreateFontW(30,0,0,0,FW_BLACK,FALSE,FALSE,FALSE,GB2312_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,VARIABLE_PITCH|PROOF_QUALITY,FIXED_PITCH | FF_MODERN,_T("����"));
			m_cacheDC.SelectObject(&font);
			SetTextColor(m_cacheDC,RGB(255,255,255));
			SetBkMode(m_cacheDC,TRANSPARENT);
			m_cacheDC.TextOutW(30,30,_T("demo�汾��лл��������\n(����ص���ʼ����)"));
			
			font.DeleteObject();
		}
	}


	if(bools.loading)
	{
		beg.loading.pic.Draw(m_cacheDC,20,600,710,94,0,beg.loading.frame*94,710,94);
		beg.text.Draw(m_cacheDC,400,180,462,294,0,0,462,294);
	}
	
	
	///ת��͸����ˢ
	if(bools.translation)
	{
		c = beg.A;
		beg.m_pBrush = new Gdiplus::SolidBrush(c);
		gp.FillRectangle(beg.m_pBrush,0,0,1280,720);
		delete beg.m_pBrush;
	}
	
	//*********�ڴ�DC������DC****************
	//��󽫻���DC�������������DC��

	cDC->BitBlt(0,0,m_client.Width(),m_client.Height(),&m_cacheDC,0,0,SRCCOPY);
	
	

	

	//�ڻ�����ͼ��,ʹ��������Ч
	ValidateRect(&m_client);
	//�ͷŻ���DC
	m_cacheDC.DeleteDC();
	//�ͷŶ���
	m_cacheCBitmap.DeleteObject();
	//�ͷŴ���DC
	ReleaseDC(cDC);
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMerryChristmasDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMerryChristmasDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	switch(nIDEvent)
	{
	case TIMER_PAINT:
		{
			CMerryChristmasDlg::OnPaint();
		}
		break;
	case TIMER_CREATE:
		{
			SetLayeredWindowAttributes(RGB(255,255,255),beg.tmd,LWA_ALPHA|LWA_COLORKEY);
			beg.tmd+=5;
			if(beg.tmd==255)
			{			
				KillTimer(TIMER_CREATE);
				Sleep(2500);
				SetTimer(TIMER_CREATE0,10,NULL);
			}
		}
		break;
	case TIMER_CREATE0:
		{
			SetLayeredWindowAttributes(RGB(255,255,255),beg.tmd,LWA_ALPHA|LWA_COLORKEY);
			beg.tmd-=5;
			if(beg.tmd==0)
			{
				KillTimer(TIMER_CREATE0);
				bools.second = 1;
				SetTimer(TIMER_CREATE1,10,NULL);
			}
		}
		break;
	case TIMER_CREATE1:
		{
			SetLayeredWindowAttributes(RGB(0,0,0),beg.tmd,LWA_ALPHA|LWA_COLORKEY);
			if(beg.tmd<255)
				beg.tmd+=5;
			if(beg.tmd==255&&!bools.loading)
			{
					
					KillTimer(TIMER_CREATE1);
					Sleep(3000);
					bools.translation = 1;
					SetTimer(TIMER_CREATE2,10,NULL);
			}
		}
		break;
	case TIMER_CREATE2:
		{
			beg.tmd2+=5;
			Gdiplus::Color B(beg.tmd2,0,0,0);
			beg.A = B;
			if(beg.tmd2==255)
			{
				SetLayeredWindowAttributes(RGB(0,0,0),beg.tmd,LWA_ALPHA);
				KillTimer(TIMER_CREATE2);
				bools.beginloading = 0;
				bools.main = 1;
				bgmflags = 0;
				threads.BGM = AfxBeginThread(Bgmplaying,this);
				SetTimer(TIMER_CREATE3,10,NULL);
			}
		}
		break;
	case TIMER_CREATE3:
		{
			beg.tmd2-=5;
			Gdiplus::Color B(beg.tmd2,0,0,0);
			beg.A = B;
			if(beg.tmd2==0)
			{
				KillTimer(TIMER_CREATE3);
				bools.translation = 0;
				SetTimer(TIMER_BIRD,400,NULL);
			}
		}
		break;
	case TIMER_BIRD:
		{
			if(beg.bird.frame == 1)
				beg.bird.frame = 0;
			else
				beg.bird.frame = 1;
		}
		break;
	case TIMER_TRANSLATION1:
		{
			beg.tmd2+=5;
			Gdiplus::Color B(beg.tmd2,0,0,0);
			beg.A = B;
			if(beg.tmd2==255)
			{
				bools.translation=0;
				bools.loading = 1;
				bools.main = 0;
				bools.dialogopen = 0;
				bools.startdialog = 0;
				threads.LOADING = AfxBeginThread(Loading,this);
				KillTimer(TIMER_TRANSLATION1);
				SetTimer(TIMER_LOADING,400,NULL);
			}
		}
		break;
	case TIMER_TRANSLATION2:
		{
			beg.tmd2+=5;
			Gdiplus::Color B(beg.tmd2,255,255,255);
			beg.A = B;
			if(beg.tmd2==255)
			{
				KillTimer(TIMER_TRANSLATION2);
				bools.translation = 0;
				bools.loading = 0;
				bools.startgame = 1;
				beg.textnum = 0;
				SetTimer(TIMER_WORD,10,NULL);
				Sleep(2000);
			}
		}
		break;
	case TIMER_LOADING:
		{
			beg.loading.frame++;
			if(beg.loading.frame == 3)
			{
				beg.loading.frame = 0;
			}
			if(bools.translation)
			{
				KillTimer(TIMER_LOADING);
				beg.loading.frame = 0;
				bgmflags = 1;
				threads.BGM = AfxBeginThread(Bgmplaying,this);
				SetTimer(TIMER_TRANSLATION2,20,NULL);
			}
		}
		break;
	case TIMER_WORD:
		{
			if(beg.texttmd[beg.textnum]==0)
			{
				beg.textnum++;
				if(beg.textnum==8||beg.textnum==5||beg.textnum==13||beg.textnum==17||beg.textnum==19||beg.textnum==29||beg.textnum==31)
					Sleep(1500);
			}
			else beg.texttmd[beg.textnum]-=15;
			if(beg.texttmd[36]==0)
			{
				
				bools.translation = 1;
				beg.tmd2 = 0;
				Gdiplus::Color B(beg.tmd2,0,0,0);
				beg.A = B;
				Sleep(3000);
				KillTimer(TIMER_WORD);
				
				SetTimer(TIMER_TRANSLATION3,20,NULL);
			}

		}
		break;
	case TIMER_TRANSLATION3:
		{
			beg.tmd2+=5;
			Gdiplus::Color B(beg.tmd2,0,0,0);
			beg.A = B;
			if(beg.tmd2==255)
			{
					Sleep(100);
					KillTimer(TIMER_TRANSLATION3);
					SetTimer(TIMER_TRANSLATION4,20,NULL);
					bools.plot0[0] = 0;
					bools.plot0[1] = 1;
					bgmflags = 2;
					threads.BGM = AfxBeginThread(Bgmplaying,this);
			}
		}
		break;
	case TIMER_TRANSLATION4:
		{
			beg.tmd2-=5;
			Gdiplus::Color B(beg.tmd2,0,0,0);
			beg.A = B;
				if(beg.tmd2 == 0)
				{
					KillTimer(TIMER_TRANSLATION4);
					bools.translation = 0;
					bools.plot0[2] = 1;
				}
		}
		break;
	case TIMER_TRANSLATION5:
		{
			beg.tmd2+=5;
			Gdiplus::Color B(beg.tmd2,0,0,0);
			beg.A = B;
			if(beg.tmd2==255)
			{
				for(int i = 0;i<50;i++)
				{
					bools.plot0[i] = 0;
				}
				bools.plot1[0] = 1;
				KillTimer(TIMER_TRANSLATION5);
				SetTimer(TIMER_TRANSLATION6,15,NULL);
			}
		}
		break;
		case TIMER_TRANSLATION6:
		{
			beg.tmd2-=5;
			Gdiplus::Color B(beg.tmd2,0,0,0);
			beg.A = B;
			if(beg.tmd2==0)
			{
				bools.translation = 0;
				KillTimer(TIMER_TRANSLATION6);
			}
		}
		break;
	}
	//CDialogEx::OnTimer(nIDEvent);
}


int CMerryChristmasDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO:  �ڴ������ר�õĴ�������
	MoveWindow(320,180,1280,720);
	SetWindowLong(GetSafeHwnd(),GWL_EXSTYLE,GetWindowLong(GetSafeHwnd(),GWL_EXSTYLE)|0x80000);
	//AnimateWindow(1500,AW_BLEND);
	
	beg.tmd=0;
	beg.tmd2=0;
	Gdiplus::Color B(beg.tmd2,0,0,0);
	beg.A = B;
	beg.pointer = START;
	
	beg.beginpic.Load(_T("res\\places\\beginpic.png"));
	beg.background.Load(_T("res\\places\\maintitle.png"));
	beg.translation.Load(_T("res\\places\\translation.png"));

	TransparentPNG(&beg.beginpic);
	TransparentPNG(&beg.background);

	bools.startgame = 0;
	bools.beginloading = 1;
	bools.second = 0;
	bools.main = 0;
	bools.translation = 0;
	bools.loading = 0;
	SetTimer(TIMER_PAINT,10,NULL);
	SetTimer(TIMER_CREATE,10,NULL);
	threads.LOADING = AfxBeginThread(Loading,this);
	
	return 0;
}


BOOL CMerryChristmasDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	hCursor=::LoadCursorFromFileA("res\\ani03.ani");//AfxGetApp()->LoadCursor(IDC_CUR);
	::SetCursor(hCursor);
	//::ShowCursor(TRUE);
	return true;
	return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}


void CMerryChristmasDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(bools.quitdialog&&!bools.translation)
	{
		if(beg.pointer == YES&&beg.mousepoint == YES)
		{
			beg.yes.frame = 2;
		}
		else if(beg.pointer == NO&&beg.mousepoint == NO)
		{
			
			beg.no.frame = 2;
		}
	}
	else if(bools.continuedialog&&!bools.translation)
	{
		if(beg.pointer == CONFIRM&&beg.mousepoint == CONFIRM)
		{

			beg.confirm.frame = 2;
		}
	}
	else if(bools.startdialog&&!bools.translation)
	{
		if(beg.pointer == CONFIRM&&beg.mousepoint == CONFIRM)
		{
			
			beg.confirm.frame = 2;
		}
		else if(beg.pointer == CANCEL&&beg.mousepoint == CANCEL)
		{
			
			beg.cancel.frame = 2;
		}
	}
	bools.click = 1;
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMerryChristmasDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	bools.click = 0;
	bool maintemp = !bools.startdialog&&!bools.continuedialog&&!bools.beginloading&&bools.main&&!bools.loading&&!bools.translation&&!bools.quitdialog;
	if(maintemp)
	{
		if(beg.pointer == START&&beg.mousepoint == START)
		{
			bools.dialogopen = 1;
			bools.startdialog = 1;
			beg.pointer = CONFIRM;
		}
		else if(beg.pointer == CONTINUE&&beg.mousepoint == CONTINUE)
		{
			bools.continuedialog = 1;
			bools.dialogopen = 1;
			beg.pointer = CONFIRM;
		}
		else if(beg.pointer == QUIT&&beg.mousepoint == QUIT)
		{
			bools.quitdialog = 1;
			bools.dialogopen = 1;
			beg.pointer = YES;
		}
	}
	if(bools.quitdialog&&!bools.translation)
	{
		if(beg.pointer == YES&&beg.mousepoint == YES)
		{
			CDialogEx::OnCancel();
		}
		else
		{
			beg.yes.frame = 0;
		}
		if(beg.pointer == NO&&beg.mousepoint == NO)
		{
			bools.dialogopen = 0;
			bools.quitdialog = 0;
			beg.yes.frame = 1;
			beg.no.frame = 0;
			beg.mousepoint = NONE;
			beg.pointer = QUIT;
		}
		else
		{
			beg.no.frame = 0;
		}
	}
	else if(bools.continuedialog&&!bools.translation)
	{
		if(beg.pointer == CONFIRM&&beg.mousepoint == CONFIRM)
		{
			bools.dialogopen = 0;
			beg.confirm.frame = 0;
			beg.pointer = CONTINUE;
			beg.mousepoint = NONE;
			bools.continuedialog = 0;
		}
		else
		{
			beg.confirm.frame = 0;
		}
	}
	else if(bools.startdialog&&!bools.translation)
	{
		if(beg.pointer == CONFIRM&&beg.mousepoint == CONFIRM)
		{
			bools.translation = 1;
			beg.confirm.frame = 0;
			KillTimer(TIMER_BIRD);
			SetTimer(TIMER_TRANSLATION1,10,NULL);
			//�����￪ʼ�µ���Ϸ
		}
		else
		{
			beg.confirm.frame = 0;
		}
		if(beg.pointer == CANCEL&&beg.mousepoint == CANCEL)
		{
			bools.dialogopen = 0;
			bools.startdialog = 0;
			beg.confirm.frame = 1;
			beg.cancel.frame = 0;
			beg.mousepoint = NONE;
			beg.pointer = START;
		}
		else
		{
			beg.cancel.frame = 0;
		}
	}
	if(bools.startgame&&!bools.translation&&!maintemp&&!bools.startdialog&&!bools.continuedialog&&!bools.quitdialog)
	{	
		if(plotnum<14)
		{
			if(bools.plot0[13]==1)
			{
				bools.plot0[1]=0;
				bools.plot0[13]=0;
				bools.plot0[14]=1;
				bools.plot0[15]=1;
				plotnum=15;
			}
			
			for(int i = 2;i<14;i++)
			{
				if(bools.plot0[i]==1)
				{
					bools.plot0[i]=0;
					bools.plot0[i+1]=1;
					
					break;
				}
			}
		}
		else if(plotnum>14&&plotnum<32)
		{
			if(bools.plot0[31])
			{
				bools.plot0[1]=1;
				bools.plot0[31]=0;
				bools.plot0[14]=0;
				bools.plot0[32]=1;
				plotnum=33;
			}
			for(int i = 15;i<31;i++)
			{
				if(bools.plot0[i]==1)
				{
					bools.plot0[i]=0;
					bools.plot0[i+1]=1;
					break;
				}
			}
		}
		else if(plotnum>32&&plotnum<35)
		{
			if(bools.plot0[35])
			{
				bools.plot0[1]=0;
				bools.plot0[35]=0;
				bools.plot0[14]=1;
				bools.plot0[36]=1;
				plotnum=36;
			}
			for(int i = 32;i<35;i++)
			{
				if(bools.plot0[i]==1)
				{
					bools.plot0[i]=0;
					bools.plot0[i+1]=1;
					break;
				}
			}
		}
		else if(plotnum>35)
		{
			//demo�汾��ʱ����
			if(bools.plot0[49])
			{
				bools.translation = 1;
				SetTimer(TIMER_TRANSLATION5,15,NULL);
			}
			for(int i = 36;i<49;i++)
			{
				if(bools.plot0[i]==1)
				{
					bools.plot0[i]=0;
					bools.plot0[i+1]=1;
					break;
				}
			}
		}
		//���ûص���ʼ�˵�
		if(bools.plot1[0])
		{
			place.p1.Destroy();
			place.p2.Destroy();
			place.p3.Destroy();
			place.p4.Destroy();
			place.dia.Destroy();
			character.hei1.Destroy();
			character.hei2.Destroy();
			bools.main = 1;
			bools.dialogopen = 0;
			bools.startdialog = 0;
			bools.startgame = 0;
			beg.pointer = START;
			bgmflags = 0;
			threads.BGM = AfxBeginThread(Bgmplaying,this);
			SetTimer(TIMER_BIRD,400,NULL);
		}
		
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CMerryChristmasDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//***************��������Ϣ��Ӧ
	bool maintemp = !bools.startdialog&&!bools.continuedialog&&!bools.beginloading&&bools.main&&!bools.loading&&!bools.translation&&!bools.quitdialog;
	if(maintemp)
	{
		if(point.x>300&&point.x<664&&point.y>300&&point.y<380)
		{
			
			beg.pointer = START;
			beg.mousepoint = START;
		}
		else if(point.x>300&&point.x<652&&point.y>430&&point.y<514)
		{
			
			beg.pointer = CONTINUE;
			beg.mousepoint = CONTINUE;
		}
		else if(point.x>300&&point.x<652&&point.y>564&&point.y<644)
		{
			
			beg.pointer = QUIT;
			beg.mousepoint = QUIT;
		}
		else
		{
			beg.mousepoint = NONE;
		}
	}
	if(bools.quitdialog&&!bools.translation)
	{
		if(point.x>490&&point.x<653&&point.y>370&&point.y<445)
		{
			
			beg.pointer = YES;
			beg.mousepoint = YES;
		}
		else if(point.x>490&&point.x<672&&point.y>480&&point.y<560)
		{
			
			beg.pointer = NO;
			beg.mousepoint = NO;
		}
		else
		{
			beg.mousepoint = NONE;
		}
	}
	else if(bools.continuedialog&&!bools.translation)
	{
		if(point.x>490&&point.x<660&&point.y>440&&point.y<525)
		{
			
			beg.pointer = CONFIRM;
			beg.mousepoint = CONFIRM;
		}
		else
		{
			beg.mousepoint = NONE;
		}
	}
	else if(bools.startdialog&&!bools.translation)
	{
		if(point.x>490&&point.x<660&&point.y>370&&point.y<445)
		{
			
			beg.pointer = CONFIRM;
			beg.mousepoint = CONFIRM;
		}
		else if(point.x>490&&point.x<658&&point.y>480&&point.y<554)
		{
			
			beg.pointer = CANCEL;
			beg.mousepoint = CANCEL;
		}
		else
		{
			beg.mousepoint = NONE;
		}
	}
	CDialogEx::OnMouseMove(nFlags, point);
}


void CMerryChristmasDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CMerryChristmasDlg::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnKeyUp(nChar, nRepCnt, nFlags);
}


BOOL CMerryChristmasDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	//����ESC��Enter��λ�˳���Ϸ
	if(pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_RETURN:
			{
				bool maintemp = !bools.startdialog&&!bools.continuedialog&&!bools.beginloading&&bools.main&&!bools.loading&&!bools.translation&&!bools.quitdialog;
				if(maintemp)
				{
					if(beg.pointer == START)
					{
						bools.dialogopen = 1;
						bools.startdialog = 1;
						beg.pointer = CONFIRM;
						return TRUE;
					}
					else if(beg.pointer == CONTINUE)
					{
						bools.continuedialog = 1;
						bools.dialogopen = 1;
						beg.pointer = CONFIRM;
						return TRUE;
					}
					else if(beg.pointer == QUIT)
					{
						bools.quitdialog = 1;
						bools.dialogopen = 1;
						beg.pointer = YES;
						return TRUE;
					}
				}
				if(bools.quitdialog&&!bools.translation)
				{
					if(beg.pointer == YES)
					{
						CDialogEx::OnCancel();
					}
					else if(beg.pointer == NO)
					{
						bools.dialogopen = 0;
						bools.quitdialog = 0;
						beg.yes.frame = 1;
						beg.no.frame = 0;
						beg.mousepoint = NONE;
						beg.pointer = QUIT;
						return TRUE;
					}
				}
				else if(bools.continuedialog&&!bools.translation)
				{
					if(beg.pointer == CONFIRM)
					{
						bools.dialogopen = 0;
						beg.confirm.frame = 0;
						beg.pointer = CONTINUE;
						beg.mousepoint = NONE;
						bools.continuedialog = 0;
						return TRUE;
					}
				}
				else if(bools.startdialog&&!bools.translation)
				{
					if(beg.pointer == CONFIRM)
					{
						bools.translation = 1;
						beg.confirm.frame = 0;
						KillTimer(TIMER_BIRD);
						SetTimer(TIMER_TRANSLATION1,10,NULL);
						return TRUE;
						//�����￪ʼ�µ���Ϸ
					}
					if(beg.pointer == CANCEL)
					{
						bools.dialogopen = 0;
						bools.startdialog = 0;
						beg.confirm.frame = 1;
						beg.cancel.frame = 0;
						beg.mousepoint = NONE;
						beg.pointer = START;
						return TRUE;
					}
				}
			return TRUE;
			}
			break;
		case VK_ESCAPE:{return TRUE;}break;
		case VK_SPACE:
			{
				bool maintemp = !bools.startdialog&&!bools.continuedialog&&!bools.beginloading&&bools.main&&!bools.loading&&!bools.translation&&!bools.quitdialog;
				if(bools.startgame&&!bools.translation&&!maintemp&&!bools.startdialog&&!bools.continuedialog&&!bools.quitdialog)
				{	
					if(plotnum<14)
					{
						if(bools.plot0[13]==1)
						{
							bools.plot0[1]=0;
							bools.plot0[13]=0;
							bools.plot0[14]=1;
							bools.plot0[15]=1;
							plotnum=15;
						}
						for(int i = 2;i<14;i++)
						{
							if(bools.plot0[i]==1)
							{
								bools.plot0[i]=0;
								bools.plot0[i+1]=1;					
								break;
							}
						}
					}
					else if(plotnum>14&&plotnum<32)
					{
						if(bools.plot0[31])
						{
							bools.plot0[1]=1;
							bools.plot0[31]=0;
							bools.plot0[14]=0;
							bools.plot0[32]=1;
							plotnum=33;
						}
						for(int i = 15;i<31;i++)
						{
							if(bools.plot0[i]==1)
							{
								bools.plot0[i]=0;
								bools.plot0[i+1]=1;
								break;
							}
						}
					}
					else if(plotnum>32&&plotnum<35)
					{
						if(bools.plot0[35])
						{
							bools.plot0[1]=0;
							bools.plot0[35]=0;
							bools.plot0[14]=1;
							bools.plot0[36]=1;
							plotnum=36;
						}
						for(int i = 32;i<35;i++)
						{
							if(bools.plot0[i]==1)
							{
								bools.plot0[i]=0;
								bools.plot0[i+1]=1;
								break;
							}
						}
					}
					else if(plotnum>35)
					{
						//demo�汾��ʱ����
						if(bools.plot0[49])
						{
							bools.translation = 1;
							SetTimer(TIMER_TRANSLATION5,15,NULL);
						}
						for(int i = 36;i<49;i++)
						{
							if(bools.plot0[i]==1)
							{
								bools.plot0[i]=0;
								bools.plot0[i+1]=1;
								break;
							}
						}
					}
					//���ûص���ʼ�˵�
					if(bools.plot1[0])
					{
						place.p1.Destroy();
						place.p2.Destroy();
						place.p3.Destroy();
						place.p4.Destroy();
						place.dia.Destroy();
						character.hei1.Destroy();
						character.hei2.Destroy();
						bools.main = 1;
						bools.dialogopen = 0;
						bools.startdialog = 0;
						bools.startgame = 0;
						beg.pointer = START;
						bgmflags = 0;
						threads.BGM = AfxBeginThread(Bgmplaying,this);
						SetTimer(TIMER_BIRD,400,NULL);
					}
		
				}
			}
			break;
		case VK_DOWN:
			{
				if(beg.pointer == START)
					beg.pointer=CONTINUE;
				else if(beg.pointer == CONTINUE)
					beg.pointer=QUIT;
				else if(beg.pointer == QUIT)
					beg.pointer=START;
				else if(bools.startdialog&&beg.pointer == CONFIRM)
					beg.pointer=CANCEL;
				else if(bools.startdialog&&beg.pointer == CANCEL)
					beg.pointer=CONFIRM;
				else if(bools.quitdialog&&beg.pointer == YES)
					beg.pointer=NO;
				else if(bools.quitdialog&&beg.pointer == NO)
					beg.pointer = YES;
			}
			break;
		case VK_UP:
			{
				if(beg.pointer == CONTINUE)
					beg.pointer=START;
				else if(beg.pointer == START)
					beg.pointer=QUIT;
				else if(beg.pointer == QUIT)
					beg.pointer=CONTINUE;
				else if(bools.startdialog&&beg.pointer == CONFIRM)
					beg.pointer=CANCEL;
				else if(bools.startdialog&&beg.pointer == CANCEL)
					beg.pointer=CONFIRM;
				else if(bools.quitdialog&&beg.pointer == YES)
					beg.pointer=NO;
				else if(bools.quitdialog&&beg.pointer == NO)
					beg.pointer = YES;
			}
			break;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}



