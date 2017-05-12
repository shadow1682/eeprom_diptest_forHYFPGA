
// EE_testtool_hidusbDlg.h : 头文件
//

#pragma once

#include "Hidusb.h"
#include "DataProcess.h"
#include "VersionDlg.h"
#include "afxwin.h"
#include "afxcmn.h"

// CEE_testtool_hidusbDlg 对话框
class CEE_testtool_hidusbDlg : public CDialogEx
{
// 构造
public:
	CEE_testtool_hidusbDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EE_TESTTOOL_HIDUSB_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

public:
	CHidusb m_hidusb;
	CStatusBar m_StatusBar;
	CDataProcess m_DataPrecess;
	bool bStateRun;

	HANDLE hThread;										//线程1线程句柄

// 实现
protected:
	HICON m_hIcon;

	POINT old;
	int width;
	CRect m_rect;
	CString strScriptText;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

protected:

	afx_msg LRESULT OnDevicechange(WPARAM wParam, LPARAM lParam);
public:
	CListBox m_ctrl_listbox_eecommand;
	CString m_str_listbox_eecommand;
	afx_msg void OnLbnDblclkListEecommand();
	afx_msg void OnBnClickedButtonEetestRun();
	void Func_Enable(bool bEnable);// 控制按钮使能
	void Enable_Run(bool bEnable);
	CRichEditCtrl m_ctrl_richedit_script;
	CString m_str_richedit_script;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	void Resize();
	afx_msg void OnBnClickedButtonEetestOpenFile();
	bool SetWordColor(CString sNew, int iColor);
	bool SetScriptColor(int lineStart, int lineEnd, BOOL bColor);
private:

public:
	CRichEditCtrl m_ctrl_richedit_result;
	CString m_str_richedit_result;
	afx_msg void OnBnClickedButtonEetestSaveResult();
	afx_msg void OnBnClickedButtonEetestSaveScript();
	CString m_str_editaddr;
	CString m_str_editdata;
	CString m_str_editlen;
	CString m_str_editcompare;
	afx_msg void OnEnChangeEditEepromRegdata();
	CEdit m_ctrl_editaddr;
	afx_msg void OnEnChangeEditEepromAddr();
	CString m_str_editregdata;
	CEdit m_ctrl_editregdata;
	CEdit m_ctrl_editdelay;
	CEdit m_ctrl_editrepeat;
	afx_msg void OnBnClickedButtonEetestClearscript();
	afx_msg void OnBnClickedButtonEetestClearresult();
	afx_msg void OnBnClickedButtonEetestStop();
	int m_int_editdelay;
	int m_int_editrepeat;
	afx_msg void OnBnClickedButtonEetestStep();
	CEdit m_ctrl_editregaddr;
	CString m_str_editregaddr;
	afx_msg void OnEnChangeEditEepromRegaddr();
	afx_msg void OnEnChangeEditEepromLen();
	CEdit m_ctrl_editeelen;
	afx_msg void OnBnClickedButtonEetestClearcmd();
	afx_msg void OnVersion();
	afx_msg void OnEnChangeEditEepromData();
	afx_msg void OnEnChangeEditEepromCompare();
	CString m_str_wdata;
	afx_msg void OnEnChangeEditWdata();
	CString m_str_editWt14;
	afx_msg void OnEnChangeEditWt14();
	CString m_str_editWt15;
	afx_msg void OnEnChangeEditWt15();
	CString m_str_editHK;
	afx_msg void OnEnChangeEditEehkadd();
	CString m_str_editHKdata;
	afx_msg void OnEnChangeEditEehkEdata();
	CComboBox m_ctrl_comboxEmod;
	CComboBox m_ctrl_comboxWotpsel;
	//afx_msg void OnEnSetfocusEditEehkadd();
	CEdit m_edit_editHKaddr;
};
