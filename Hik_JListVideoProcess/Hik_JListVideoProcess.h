
// Hik_JListVideoProcess.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CHik_JListVideoProcessApp:
// �йش����ʵ�֣������ Hik_JListVideoProcess.cpp
//

class CHik_JListVideoProcessApp : public CWinApp
{
public:
	CHik_JListVideoProcessApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CHik_JListVideoProcessApp theApp;