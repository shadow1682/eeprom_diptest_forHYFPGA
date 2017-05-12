// VersionDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "EE_testtool_hidusb.h"
#include "VersionDlg.h"
#include "afxdialogex.h"


// CVersionDlg 对话框

IMPLEMENT_DYNAMIC(CVersionDlg, CDialogEx)

CVersionDlg::CVersionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_VERSION, pParent)
	, m_str_editver(_T(""))
{

}

CVersionDlg::~CVersionDlg()
{
}

void CVersionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_VER, m_ctrl_editver);
	DDX_Text(pDX, IDC_EDIT_VER, m_str_editver);
}


BEGIN_MESSAGE_MAP(CVersionDlg, CDialogEx)
	
END_MESSAGE_MAP()


// CVersionDlg 消息处理程序


BOOL CVersionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//m_ctrl_editver.SetSel(-1);
	m_ctrl_editver.ReplaceSel(_T("2016.12.13   ghan   creat EE Test             Version 1.0 \r\n"));
	m_ctrl_editver.ReplaceSel(_T("2016.12.14    ...   add new command           ...          \r\n"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
