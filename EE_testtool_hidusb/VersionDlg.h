#pragma once
#include "afxwin.h"


// CVersionDlg �Ի���

class CVersionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVersionDlg)

public:
	CVersionDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CVersionDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_VERSION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	CEdit m_ctrl_editver;
	virtual BOOL OnInitDialog();
	CString m_str_editver;
};
