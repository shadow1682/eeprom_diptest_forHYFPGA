
// EE_testtool_hidusb.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CEE_testtool_hidusbApp: 
// �йش����ʵ�֣������ EE_testtool_hidusb.cpp
//

class CEE_testtool_hidusbApp : public CWinApp
{
public:
	CEE_testtool_hidusbApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CEE_testtool_hidusbApp theApp;