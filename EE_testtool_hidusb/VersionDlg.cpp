// VersionDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EE_testtool_hidusb.h"
#include "VersionDlg.h"
#include "afxdialogex.h"


// CVersionDlg �Ի���

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


// CVersionDlg ��Ϣ�������


BOOL CVersionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	//m_ctrl_editver.SetSel(-1);
	m_ctrl_editver.ReplaceSel(_T("2016.12.13   ghan   creat EE Test             Version 1.0 \r\n"));
	m_ctrl_editver.ReplaceSel(_T("2016.12.14    ...   add new command           ...          \r\n"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
