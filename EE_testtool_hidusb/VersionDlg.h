#pragma once
#include "afxwin.h"


// CVersionDlg 对话框

class CVersionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVersionDlg)

public:
	CVersionDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CVersionDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_VERSION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	CEdit m_ctrl_editver;
	virtual BOOL OnInitDialog();
	CString m_str_editver;
};
