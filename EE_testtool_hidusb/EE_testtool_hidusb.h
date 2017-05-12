
// EE_testtool_hidusb.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CEE_testtool_hidusbApp: 
// 有关此类的实现，请参阅 EE_testtool_hidusb.cpp
//

class CEE_testtool_hidusbApp : public CWinApp
{
public:
	CEE_testtool_hidusbApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CEE_testtool_hidusbApp theApp;