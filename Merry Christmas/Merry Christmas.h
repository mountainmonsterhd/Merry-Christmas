
// Merry Christmas.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMerryChristmasApp:
// �йش����ʵ�֣������ Merry Christmas.cpp
//

class CMerryChristmasApp : public CWinApp
{
public:
	CMerryChristmasApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMerryChristmasApp theApp;