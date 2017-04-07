
// EE_testtool_hidusbDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "EE_testtool_hidusb.h"
#include "EE_testtool_hidusbDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
DWORD WINAPI ThreadFun(LPVOID pthread);

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CEE_testtool_hidusbDlg 对话框

#define STR_DEV_STATE_OPEN "EETest_usb V1.0*设备状态:连接"
#define STR_DEV_STATE_CLOSE "EETest_usb V1.0*设备状态:断开"

CEE_testtool_hidusbDlg::CEE_testtool_hidusbDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_EE_TESTTOOL_HIDUSB_DIALOG, pParent)
	, m_str_listbox_eecommand(_T(""))
	, m_str_richedit_script(_T(""))
	, m_str_richedit_result(_T(""))
	, m_str_editaddr(_T(""))
	, m_str_editdata(_T(""))
	, m_str_editlen(_T(""))
	, m_str_editcompare(_T(""))
	, m_str_editregdata(_T(""))
	, m_int_editdelay(0)
	, m_int_editrepeat(0)
	, m_str_editregaddr(_T(""))
	, m_str_wdata(_T(""))
	, m_str_editWt14(_T(""))
	, m_str_editWt15(_T(""))
	, m_str_editHK(_T(""))
	, m_str_editHKdata(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEE_testtool_hidusbDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_EECOMMAND, m_ctrl_listbox_eecommand);
	DDX_LBString(pDX, IDC_LIST_EECOMMAND, m_str_listbox_eecommand);
	DDX_Control(pDX, IDC_RICHEDIT21_EESCRIPT, m_ctrl_richedit_script);
	DDX_Text(pDX, IDC_RICHEDIT21_EESCRIPT, m_str_richedit_script);
	DDX_Control(pDX, IDC_RICHEDIT21_EERESULT, m_ctrl_richedit_result);
	DDX_Text(pDX, IDC_RICHEDIT21_EERESULT, m_str_richedit_result);
	DDX_Text(pDX, IDC_EDIT_EEPROM_ADDR, m_str_editaddr);
	DDX_Text(pDX, IDC_EDIT_EEPROM_DATA, m_str_editdata);
	DDX_Text(pDX, IDC_EDIT_EEPROM_LEN, m_str_editlen);
	DDX_Text(pDX, IDC_EDIT_EEPROM_COMPARE, m_str_editcompare);
	DDX_Control(pDX, IDC_EDIT_EEPROM_ADDR, m_ctrl_editaddr);
	DDX_Text(pDX, IDC_EDIT_EEPROM_REGDATA, m_str_editregdata);
	DDX_Control(pDX, IDC_EDIT_EEPROM_REGDATA, m_ctrl_editregdata);
	DDX_Control(pDX, IDC_EDIT_EETEST_DELAY, m_ctrl_editdelay);
	DDX_Control(pDX, IDC_EDIT_EETEST_REPEAT, m_ctrl_editrepeat);
	DDX_Text(pDX, IDC_EDIT_EETEST_DELAY, m_int_editdelay);
	DDV_MinMaxInt(pDX, m_int_editdelay, 0, 1000000);
	DDX_Text(pDX, IDC_EDIT_EETEST_REPEAT, m_int_editrepeat);
	DDV_MinMaxInt(pDX, m_int_editrepeat, 1, 1000000);
	DDX_Control(pDX, IDC_EDIT_EEPROM_REGADDR, m_ctrl_editregaddr);
	DDX_Text(pDX, IDC_EDIT_EEPROM_REGADDR, m_str_editregaddr);
	DDX_Control(pDX, IDC_EDIT_EEPROM_LEN, m_ctrl_editeelen);
	DDX_Text(pDX, IDC_EDIT_WDATA, m_str_wdata);
	DDX_Text(pDX, IDC_EDIT_WT14, m_str_editWt14);
	DDX_Text(pDX, IDC_EDIT_WT15, m_str_editWt15);
	DDX_Text(pDX, IDC_EDIT_EEHKADD, m_str_editHK);
	DDX_Text(pDX, IDC_EDIT_EEHK_EDATA, m_str_editHKdata);
	DDX_Control(pDX, IDC_COMBO_WEMOD, m_ctrl_comboxEmod);
	DDX_Control(pDX, IDC_COMBO_WOTP, m_ctrl_comboxWotpsel);
	DDX_Control(pDX, IDC_EDIT_EEHKADD, m_edit_editHKaddr);
}

BEGIN_MESSAGE_MAP(CEE_testtool_hidusbDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_DEVICECHANGE, &CEE_testtool_hidusbDlg::OnDevicechange)
	ON_LBN_DBLCLK(IDC_LIST_EECOMMAND, &CEE_testtool_hidusbDlg::OnLbnDblclkListEecommand)
	ON_BN_CLICKED(IDC_BUTTON_EETEST_RUN, &CEE_testtool_hidusbDlg::OnBnClickedButtonEetestRun)
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(IDC_BUTTON_EETEST_OPEN_FILE, &CEE_testtool_hidusbDlg::OnBnClickedButtonEetestOpenFile)
	ON_BN_CLICKED(IDC_BUTTON_EETEST_SAVE_RESULT, &CEE_testtool_hidusbDlg::OnBnClickedButtonEetestSaveResult)
	ON_BN_CLICKED(IDC_BUTTON_EETEST_SAVE_SCRIPT, &CEE_testtool_hidusbDlg::OnBnClickedButtonEetestSaveScript)
	ON_EN_CHANGE(IDC_EDIT_EEPROM_REGDATA, &CEE_testtool_hidusbDlg::OnEnChangeEditEepromRegdata)
	ON_EN_CHANGE(IDC_EDIT_EEPROM_ADDR, &CEE_testtool_hidusbDlg::OnEnChangeEditEepromAddr)
	ON_BN_CLICKED(IDC_BUTTON_EETEST_CLEARSCRIPT, &CEE_testtool_hidusbDlg::OnBnClickedButtonEetestClearscript)
	ON_BN_CLICKED(IDC_BUTTON_EETEST_CLEARRESULT, &CEE_testtool_hidusbDlg::OnBnClickedButtonEetestClearresult)
	ON_BN_CLICKED(IDC_BUTTON_EETEST_STOP, &CEE_testtool_hidusbDlg::OnBnClickedButtonEetestStop)
	ON_BN_CLICKED(IDC_BUTTON_EETEST_STEP, &CEE_testtool_hidusbDlg::OnBnClickedButtonEetestStep)
	ON_EN_CHANGE(IDC_EDIT_EEPROM_REGADDR, &CEE_testtool_hidusbDlg::OnEnChangeEditEepromRegaddr)
	ON_EN_CHANGE(IDC_EDIT_EEPROM_LEN, &CEE_testtool_hidusbDlg::OnEnChangeEditEepromLen)
	ON_BN_CLICKED(IDC_BUTTON_EETEST_CLEARCMD, &CEE_testtool_hidusbDlg::OnBnClickedButtonEetestClearcmd)
	ON_COMMAND(ID_VERSION, &CEE_testtool_hidusbDlg::OnVersion)
	ON_EN_CHANGE(IDC_EDIT_EEPROM_DATA, &CEE_testtool_hidusbDlg::OnEnChangeEditEepromData)
	ON_EN_CHANGE(IDC_EDIT_EEPROM_COMPARE, &CEE_testtool_hidusbDlg::OnEnChangeEditEepromCompare)
	ON_EN_CHANGE(IDC_EDIT_WDATA, &CEE_testtool_hidusbDlg::OnEnChangeEditWdata)
	ON_EN_CHANGE(IDC_EDIT_WT14, &CEE_testtool_hidusbDlg::OnEnChangeEditWt14)
	ON_EN_CHANGE(IDC_EDIT_WT15, &CEE_testtool_hidusbDlg::OnEnChangeEditWt15)
	ON_EN_CHANGE(IDC_EDIT_EEHKADD, &CEE_testtool_hidusbDlg::OnEnChangeEditEehkadd)
	ON_EN_CHANGE(IDC_EDIT_EEHK_EDATA, &CEE_testtool_hidusbDlg::OnEnChangeEditEehkEdata)
	//ON_EN_SETFOCUS(IDC_EDIT_EEHKADD, &CEE_testtool_hidusbDlg::OnEnSetfocusEditEehkadd)
END_MESSAGE_MAP()


// CEE_testtool_hidusbDlg 消息处理程序

BOOL CEE_testtool_hidusbDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	/*
	初始化设备连接
	*/
	if (m_hidusb.OpenDev(this->GetSafeHwnd()))
	{
		this->Func_Enable(TRUE);
		this->SetWindowText(STR_DEV_STATE_OPEN);
	}
	else
	{
		this->Func_Enable(FALSE);
		this->SetWindowText(STR_DEV_STATE_CLOSE);
	}

	/*
	初始化命令列表
	*/
	m_ctrl_listbox_eecommand.AddString("Write_EE");
	m_ctrl_listbox_eecommand.AddString("Read_EE");
	m_ctrl_listbox_eecommand.AddString("Write_Reg");
	m_ctrl_listbox_eecommand.AddString("Read_Reg");
	m_ctrl_listbox_eecommand.AddString("Compare");
	m_ctrl_listbox_eecommand.AddString("Write_EE_CK");
	m_ctrl_listbox_eecommand.AddString("Write_All");
	m_ctrl_listbox_eecommand.AddString("EE_HardCheck");
	m_ctrl_listbox_eecommand.AddString("Beep");

	/*
	窗口默认大小设定
	*/
	GetClientRect(&m_rect);
	old.x = m_rect.right - m_rect.left;
	old.y = m_rect.bottom- m_rect.top;
	/*
	创建状态栏
	*/
	m_StatusBar.Create(this);
	UINT Statusarray[4];
	for (int i = 0; i < 4; i++)
	{
		Statusarray[i] = 50 + i;
	}
	m_StatusBar.SetIndicators(Statusarray, 4);

	width = m_rect.Width() - 200;
	m_StatusBar.SetPaneInfo(0,500,SBPS_NORMAL , 70);// loop
	m_StatusBar.SetPaneInfo(1, 501, SBPS_NORMAL, 30);//progress
	m_StatusBar.SetPaneInfo(2, 502, SBPS_NORMAL,width );//file
	m_StatusBar.SetPaneInfo(3, 503, SBPS_NORMAL, 70);//error

	m_StatusBar.SetPaneText(0, "Loop:");
	m_StatusBar.SetPaneText(2, "Command Status");
	m_StatusBar.SetPaneText(3, "Error:");

	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

	/*
	初始化RICHEDIT字体
	*/
	CHARFORMAT2 cf;
	memset(&cf, 0, sizeof(cf));
	cf.cbSize = sizeof(cf);
	cf.dwMask |= CFM_FACE;
	strcpy_s(cf.szFaceName, _T("宋体")); //设置字体
	m_ctrl_richedit_script.SetDefaultCharFormat(cf);

	m_ctrl_richedit_script.SetTargetDevice(NULL, 0);//设置Richedit切换换行
	m_ctrl_richedit_result.SetTargetDevice(NULL, 0);


	m_ctrl_editdelay.SetWindowText("0");
	m_ctrl_editrepeat.SetWindowText("1");
	((CButton*)GetDlgItem(IDC_CHECK_EETEST_REPEAT))->SetCheck(TRUE);

	SetDlgItemText(IDC_COMBO_WEMOD, "emod");
	SetDlgItemText(IDC_COMBO_WOTP, "otp sel");
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CEE_testtool_hidusbDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CEE_testtool_hidusbDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CEE_testtool_hidusbDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CEE_testtool_hidusbDlg::OnLbnDblclkListEecommand()
{
	UpdateData(true);
	CString sCmdTxt,sEmod = _T(""),sOtpSel = _T("");

	int nCmdListbox = m_ctrl_listbox_eecommand.GetCurSel();

	switch (nCmdListbox)
	{
	case 0: {sCmdTxt = "Write_EE,"+ m_str_editlen+" "+ m_str_editaddr +" "+ m_str_editdata; break; }
	case 1: {sCmdTxt = "Read_EE,00," + m_str_editaddr + " "+ m_str_editlen; break; }
	case 2: 
	{
		sCmdTxt = "Write_Reg,01," + m_str_editregaddr + m_str_editregdata; break;
	}
	case 3: {sCmdTxt = "Read_Reg,00," + m_str_editregaddr; break; }
	case 4:
	{
		sCmdTxt = "Compare," + m_str_editcompare;break;
	}
	case 5: {sCmdTxt = "Write_EE_CK," + m_str_editlen + " " + m_str_editaddr + " " + m_str_editdata; break; }
	case 6: 
	{
		if (m_ctrl_comboxEmod.GetCurSel() == 0)sEmod = "01";
		else if (m_ctrl_comboxEmod.GetCurSel() == 1)sEmod = "02";
		else if (m_ctrl_comboxEmod.GetCurSel() == 2)sEmod = "03";
		if (m_ctrl_comboxWotpsel.GetCurSel() == 0)sOtpSel = "00";
		else if (m_ctrl_comboxWotpsel.GetCurSel() == 1)sOtpSel = "01";
		sCmdTxt = "Write_All,05,00 00," + sEmod + " " + sOtpSel + " " + m_str_editWt14 + " " + m_str_editWt15 + " " + m_str_wdata; break;
	}
	case 7: 
	{
		sCmdTxt = "EE_HardCheck,0A," + m_str_editHK + " " + m_str_editHKdata; break;
	}
	default:
	{
		sCmdTxt = "Beep" ;
		break;
	}
	}

	sCmdTxt += "\r\n";
	m_ctrl_richedit_script.SetSel(-1, -1);
	m_ctrl_richedit_script.ReplaceSel(sCmdTxt);

}

//USB插拔监控
afx_msg LRESULT CEE_testtool_hidusbDlg::OnDevicechange(WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case DBT_DEVICEARRIVAL:
	{
		if (m_hidusb.OpenDev(this->GetSafeHwnd()))
		{
			this->SetWindowText(STR_DEV_STATE_OPEN);
			this->Func_Enable(TRUE);
		}
		else
		{
			this->SetWindowText(STR_DEV_STATE_CLOSE);
			this->Func_Enable(FALSE);
		}
		break;
	}
	case DBT_DEVICEREMOVECOMPLETE:
	{
		m_hidusb.CloseDev();
		this->SetWindowText(STR_DEV_STATE_CLOSE);
		this->Func_Enable(FALSE);
		break;
	}
	}
	return 0;
}

// 控制按钮使能
void CEE_testtool_hidusbDlg::Func_Enable(bool bEnable)
{
	::EnableWindow(::GetDlgItem(this->GetSafeHwnd(), IDC_BUTTON_EETEST_RUN),bEnable);
	::EnableWindow(::GetDlgItem(this->GetSafeHwnd(), IDC_BUTTON_EETEST_STEP), bEnable);
	::EnableWindow(::GetDlgItem(this->GetSafeHwnd(), IDC_BUTTON_EETEST_PAUSE), bEnable);
	::EnableWindow(::GetDlgItem(this->GetSafeHwnd(), IDC_BUTTON_EETEST_SAVE_SCRIPT), bEnable);
	::EnableWindow(::GetDlgItem(this->GetSafeHwnd(), IDC_BUTTON_EETEST_SAVE_RESULT), bEnable);
	::EnableWindow(::GetDlgItem(this->GetSafeHwnd(), IDC_EDIT_EETEST_DELAY), bEnable);
	::EnableWindow(::GetDlgItem(this->GetSafeHwnd(), IDC_EDIT_EETEST_REPEAT), bEnable);
}

void CEE_testtool_hidusbDlg::Enable_Run(bool bEnable)
{
	::EnableWindow(::GetDlgItem(this->GetSafeHwnd(), IDC_BUTTON_EETEST_RUN), bEnable);
	::EnableWindow(::GetDlgItem(this->GetSafeHwnd(), IDC_BUTTON_EETEST_STEP), bEnable);
	::EnableWindow(::GetDlgItem(this->GetSafeHwnd(), IDC_BUTTON_EETEST_SAVE_SCRIPT), bEnable);
	::EnableWindow(::GetDlgItem(this->GetSafeHwnd(), IDC_BUTTON_EETEST_SAVE_RESULT), bEnable);
	::EnableWindow(::GetDlgItem(this->GetSafeHwnd(), IDC_EDIT_EETEST_DELAY), bEnable);
	::EnableWindow(::GetDlgItem(this->GetSafeHwnd(), IDC_EDIT_EETEST_REPEAT), bEnable);
	::EnableWindow(::GetDlgItem(this->GetSafeHwnd(), IDC_BUTTON_EETEST_OPEN_FILE), bEnable);
	::EnableWindow(::GetDlgItem(this->GetSafeHwnd(), IDC_BUTTON_EETEST_CLEARSCRIPT), bEnable);
}

/*窗体大小改变时控件设置函数*/
void CEE_testtool_hidusbDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	GetClientRect(&m_rect);

	/*状态栏的改变*/
	if (IsWindow(m_StatusBar.m_hWnd))
	{
		if (nType != SIZE_MINIMIZED)//窗体最小化时，width变为0
		{
			Resize();

			width = m_rect.Width() - 200;
		}
		m_StatusBar.SetPaneInfo(0, 500, SBPS_NORMAL, 70);// loop
		m_StatusBar.SetPaneInfo(1, 501, SBPS_NORMAL, 30);//progress
		m_StatusBar.SetPaneInfo(2, 502, SBPS_NORMAL, width);//file
		m_StatusBar.SetPaneInfo(3, 503, SBPS_NORMAL, 70);//error
		RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
	}

}
/*限制窗体最小化*/
void CEE_testtool_hidusbDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (lpMMI->ptMinTrackSize.x < 705)
	{
		lpMMI->ptMinTrackSize.x = 705;
	}
	if (lpMMI->ptMinTrackSize.y < 600)
	{
		lpMMI->ptMinTrackSize.y = 600;
	}
	CDialogEx::OnGetMinMaxInfo(lpMMI);
}


void CEE_testtool_hidusbDlg::Resize()
{
	float fsp[2];
	POINT Newp; //获取现在对话框的大小  
	CRect recta;
	GetClientRect(&recta);     //取客户区大小    
	Newp.x = recta.right- recta.left;
	Newp.y = recta.bottom- recta.top;
	fsp[0] = (float)Newp.x / old.x;
	fsp[1] = (float)Newp.y / old.y;
	CRect Rect;
	int woc;
	CPoint OldTLPoint, TLPoint; //左上角  
	CPoint OldBRPoint, BRPoint; //右下角  
	HWND  hwndChild = ::GetWindow(m_hWnd, GW_CHILD);  //列出所有控件    
	while (hwndChild) {
		woc = ::GetDlgCtrlID(hwndChild);//取得ID  
		GetDlgItem(woc)->GetWindowRect(Rect);
		ScreenToClient(Rect);
		OldTLPoint = Rect.TopLeft();
		TLPoint.x = long(OldTLPoint.x*fsp[0]);
		TLPoint.y = long(OldTLPoint.y*fsp[1]);
		OldBRPoint = Rect.BottomRight();
		BRPoint.x = long(OldBRPoint.x *fsp[0]);
		BRPoint.y = long(OldBRPoint.y *fsp[1]);
		Rect.SetRect(TLPoint, BRPoint);
		GetDlgItem(woc)->MoveWindow(Rect, TRUE);
		hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
	}
	old = Newp;
}

void CEE_testtool_hidusbDlg::OnBnClickedButtonEetestOpenFile()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);

	CFileDialog dlg(TRUE, _T(".txt"), NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, _T("Text Files(*.txt)|*.txt|All Files (*.*)|*.*||"),this);

	if (dlg.DoModal() != IDOK)
	{	
		return ;
	}

	//获得文件路径
	CString strPathName = dlg.GetPathName();
	SetDlgItemText(IDC_STATIC_FILEPATH, "File:" + strPathName);
	//m_StatusBar.SetPaneText(2, "File:"+ strPathName);
	CFile file;

	//打开文件

	m_ctrl_richedit_script.SetWindowText(_T(""));

	if (!file.Open(strPathName, CFile::modeRead))
	{
		MessageBox("文档打开失败!", "Error", MB_ICONEXCLAMATION);
		return ;
	}

	ULONGLONG len = file.GetLength();

	strScriptText = _T("");

	file.Read(strScriptText.GetBufferSetLength((int)len), (int)len);

	strScriptText.ReleaseBuffer();

	m_ctrl_richedit_script.SetWindowText(strScriptText);

	m_ctrl_richedit_script.SetSel(0, 0);

	file.Close();//关闭文件

}

void CEE_testtool_hidusbDlg::OnBnClickedButtonEetestSaveResult()
{
	UpdateData(TRUE);   //用于获得文本框中的内容;

	CString strFilter, fileName, strText;
	strFilter = "Text Files(*.txt)|*.txt||";
	CFileDialog dlg(FALSE, "txt", NULL, OFN_EXPLORER | OFN_HIDEREADONLY |
		OFN_ENABLESIZING | OFN_FILEMUSTEXIST, strFilter);
	if (dlg.DoModal() == IDOK)								//显示保存文件对话框
	{
		fileName += dlg.GetPathName();
		SetDlgItemText(IDC_STATIC_FILEPATH, "File:" + fileName);
		CFile savefile(fileName, CFile::modeCreate | CFile::modeWrite);		//构造CFile对象
		savefile.Write(m_str_richedit_result, m_str_richedit_result.GetLength());							//写文件数据|
		savefile.Close();										//关闭文件
	}
}

void CEE_testtool_hidusbDlg::OnBnClickedButtonEetestSaveScript()
{
	UpdateData(TRUE);   //用于获得文本框中的内容;

	CString strFilter, fileName, strText;
	strFilter = "Text Files(*.txt)|*.txt||";
	CFileDialog dlg(FALSE, "txt", NULL, OFN_EXPLORER | OFN_HIDEREADONLY |
		OFN_ENABLESIZING | OFN_FILEMUSTEXIST, strFilter);
	if (dlg.DoModal() == IDOK)								//显示保存文件对话框
	{
		fileName += dlg.GetPathName();
		SetDlgItemText(IDC_STATIC_FILEPATH, "File:" + fileName);
		CFile savefile(fileName, CFile::modeCreate | CFile::modeWrite);		//构造CFile对象
		savefile.Write(m_str_richedit_script, m_str_richedit_script.GetLength());							//写文件数据|
		savefile.Close();										//关闭文件
	}
}

CString  sCirNum = _T(""), sErrorNum = _T(""),sPersent = _T("");
int iCirNum = 1,iErrorNum = 0;
CString sResult, ResultRead, ResultERROR;
unsigned char Compare_buffer[1024] = { 0 };
int m_Num = 0,iDelay = 0;  //循环次数记录
unsigned int Step_Index = 0;//连续单步记录
void CEE_testtool_hidusbDlg::OnBnClickedButtonEetestRun()
{
	// TODO: 在此添加控件通知处理程序代码

	DWORD ThreadID;
	DWORD code;

	UpdateData(TRUE);

	if (m_str_richedit_script == _T("")) //如果指令操作中无数据，线程不开启
	{
		return;
	}

	//生成线程参数
	if (!GetExitCodeThread(hThread, &code) || (code != STILL_ACTIVE))
	{
		iDelay = m_int_editdelay;

		if (((CButton*)GetDlgItem(IDC_CHECK_EETEST_REPEAT))->GetCheck())
		{
			iCirNum = m_int_editrepeat;
		}
		else
		{
			iCirNum = 1;
		}

		hThread = CreateThread(NULL, 0, ThreadFun, this, 0, &ThreadID);//创建并开始线程
	}
	else
	{
		::ResumeThread(hThread);//释放线程
	}
	//m_ctrl_richedit_result.SetWindowText(_T(""));
	this->SetWindowText("Run-EETest");
	bStateRun = TRUE;
	Enable_Run(FALSE);
	SetDlgItemText(IDC_BUTTON_EETEST_STOP, _T("Pause"));
}

DWORD WINAPI ThreadFun(LPVOID pArg)						//线程入口函数
{
	// TODO: Add your control notification handler code here 

	CEE_testtool_hidusbDlg* cMyDlg = (CEE_testtool_hidusbDlg*)pArg;
	CEdit* pEdit = (CEdit*)pArg;

	int iDataLen = 0, iStrCirNum = 0;
	size_t m = 0;
	char Result_buffer[1024] = { 0 };
	char listbox_buffer[1024] = { 0 };
	unsigned char Command_buffer[1024] = { 0 }, Response_buffer[1024] = { 0 };
	unsigned char dat1 = 0, dat2 = 0, dat11 = 0, dat22 = 0;

	CString sCommand = _T(""),sCmdS = _T(""),sScriptTxt = _T(""),sCmdResult = _T("");

	cMyDlg->m_ctrl_richedit_script.GetWindowText(sScriptTxt);//获取编辑框文本
	size_t iScriptLen = strlen(sScriptTxt);//文本总长度
	if (sScriptTxt.IsEmpty())return 0;//空文本跳出

	for (int p = m_Num; p < iCirNum; p++)//循环次数
	{
		m_Num = p;//保存当前循环次数---暂停后继续进程

		/*循环次数记录*/
		iStrCirNum = p + 1;
		sCirNum.Format("%d", iStrCirNum);
		::SendMessage(cMyDlg->m_StatusBar.m_hWnd, SB_SETTEXT, 0, (LPARAM)(LPCTSTR)("Loop:" + sCirNum));

		do
		{
			int iCmdlen = sScriptTxt.Find(_T("\r\n"),m);//寻找指令

			iCmdlen -= m;

			if(iCmdlen < 0 )//指令内无空格，则获取内容
			{
				iCmdlen = strlen(sScriptTxt) - m;
			}
			sCommand = sScriptTxt.Mid(m,iCmdlen);//m:寻找起始位置，iCmdlen:寻找长度
			sCmdResult = sCommand;
			m = m+iCmdlen+2;

			if (sCommand[0] != ';')
			{
				sCommand.Remove(' ');
				sCommand.Remove(',');
			}

			strcpy_s((char*)listbox_buffer, 1024, sCommand);//判定每一行指令

			if (listbox_buffer[0] != ';')
			{
				if (strstr((char*)listbox_buffer, "Write_EE") != NULL)//Write_EE
				{
					sCmdS = "Write_EE";
					iDataLen = strlen(sCommand) - strlen(sCmdS);
					Command_buffer[0] = 0x9B;
				}
				else if (strstr((char*)listbox_buffer, "Write_EE_CK") != NULL)//Write_EE_CK
				{
					sCmdS = "Write_EE_CK";
					iDataLen = strlen(sCommand) - strlen(sCmdS);
					Command_buffer[0] = 0x8B;
				}
				else if (strstr((char*)listbox_buffer, "Read_EE") != NULL)//Read_EE
				{
					sCmdS = "Read_EE";
					iDataLen = strlen(sCommand) - strlen(sCmdS);
					Command_buffer[0] = 0x1B;
				}
				else if (strstr((char*)listbox_buffer, "Write_Reg") != NULL)//Write_Reg
				{
					sCmdS = "Write_Reg";
					iDataLen = strlen(sCommand) - strlen(sCmdS);
					Command_buffer[0] = 0x9A;
				}
				else if (strstr((char*)listbox_buffer, "Read_Reg") != NULL)//Read_Reg
				{
					sCmdS = "Read_Reg";
					iDataLen = strlen(sCommand) - strlen(sCmdS);
					Command_buffer[0] = 0x1A;
				}
				else if (strstr((char*)listbox_buffer, "Write_All") != NULL)//Write_All
				{
					sCmdS = "Write_All";
					iDataLen = strlen(sCommand) - strlen(sCmdS);
					Command_buffer[0] = 0x9C;
				}
				else if (strstr((char*)listbox_buffer, "EE_HardCheck") != NULL)//EE_HardCheck
				{
					sCmdS = "EE_HardCheck";
					iDataLen = strlen(sCommand) - strlen(sCmdS);
					Command_buffer[0] = 0x1C;
				}
				else if (strstr((char*)listbox_buffer, "Beep") != NULL)//Beep
				{
					BYTE send_buf[1024] = { 0x16,0x01,0x00 };
					cMyDlg->m_hidusb.Send(send_buf, 3);
					if (m >= iScriptLen)break;
					continue;
				}
				else if (strstr((char*)listbox_buffer, "Compare") != NULL)//Compare
				{
					int i = 0, k = 0;
					iDataLen = strlen(sCommand) - 7;
					while (i < iDataLen)
					{
						dat1 = (listbox_buffer[i + 7] <= '9') ? listbox_buffer[i + 7] - '0' : (listbox_buffer[i + 7] + 10) - 'A';
						if (dat1 > 0x20)dat1 -= 0x20;
						dat2 = (listbox_buffer[i + 8] <= '9') ? listbox_buffer[i + 8] - '0' : (listbox_buffer[i + 8] + 10) - 'A';
						if (dat2 > 0x20)dat2 -= 0x20;
						Command_buffer[k++] = dat1 * 16 + dat2;
						i = i + 2;
					}

					int jRecv = 0;
					for (int i = 0; i < k; i++)
					{
						dat1 = (Command_buffer[i] & 0xF0) >> 4;
						Result_buffer[jRecv++] = (dat1 <= 9) ? dat1 + '0' : (dat1 - 10) + 'a';
						dat1 = (Command_buffer[i] & 0x0F);
						Result_buffer[jRecv++] = (dat1 <= 9) ? dat1 + '0' : (dat1 - 10) + 'a';
						Result_buffer[jRecv++] = ' ';
					}

					sResult = Result_buffer;
					for (i = 0; i < k; i++)
					{
						if (Command_buffer[i] != Compare_buffer[i])break;
					}
					if (i >= k)
					{
						cMyDlg->SetWordColor("/***************Compare***************/", 1);
						cMyDlg->SetWordColor("/*OK:" + sResult, 1);
						cMyDlg->SetWordColor("/*************************************/", 1);
					}
					else
					{
						iErrorNum++;
						cMyDlg->SetWordColor("/***************Compare***************/", 2);
						cMyDlg->SetWordColor("/*ERROR:" + sResult, 2);
						cMyDlg->SetWordColor("/*************************************/", 2);
					}
					memset(Command_buffer, 0, k);

					/*显示进度比*/
					sPersent.Format("%.0f%%", 100.0*(float)(m) / (float)(iScriptLen));
					::SendMessage(cMyDlg->m_StatusBar.m_hWnd, SB_SETTEXT, 1, (LPARAM)(LPCTSTR)(sPersent));

					/*显示错误次数*/
					sErrorNum.Format("%d", iErrorNum);
					::SendMessage(cMyDlg->m_StatusBar.m_hWnd, SB_SETTEXT, 3, (LPARAM)(LPCTSTR)("Error:" + sErrorNum));

					if (m >= iScriptLen)break;
					continue;
				}
				else //非本软件支持的指令
				{
					/*显示进度比*/
					sPersent.Format("%.0f%%", 100.0*(float)(m) / (float)(iScriptLen));
					::SendMessage(cMyDlg->m_StatusBar.m_hWnd, SB_SETTEXT, 1, (LPARAM)(LPCTSTR)(sPersent));
					if (m >= iScriptLen)break;
					continue;
				}
			}
			else //注释行
			{
				cMyDlg->SetWordColor(sCommand, 4);

				sPersent.Format("%.0f%%", 100.0*(float)(m) / (float)(iScriptLen));
				::SendMessage(cMyDlg->m_StatusBar.m_hWnd, SB_SETTEXT, 1, (LPARAM)(LPCTSTR)(sPersent));
				if (m >= iScriptLen)break;
				continue;
			}

			/*发送指令数据*/
			int  i_k = 1, i_i = 0;
			int i_Cmd = strlen(sCommand) - iDataLen;
			while (i_i < iDataLen)
			{
				dat1 = (listbox_buffer[i_i + i_Cmd] <= '9') ? listbox_buffer[i_i + i_Cmd] - '0' : (listbox_buffer[i_i + i_Cmd] + 10) - 'A';
				if (dat1 > 0x20)dat1 -= 0x20;
				dat2 = (listbox_buffer[i_i + i_Cmd + 1] <= '9') ? listbox_buffer[i_i + i_Cmd + 1] - '0' : (listbox_buffer[i_i + i_Cmd + 1] + 10) - 'A';
				if (dat2 > 0x20)dat2 -= 0x20;
				Command_buffer[i_k++] = dat1 * 16 + dat2;
				i_i = i_i + 2;
			}
			/*将Data长度与地址等长度合并为总长度*/
			if (Command_buffer[0] == 0x9B)Command_buffer[1] += 0x02;//Write_EE
			else if (Command_buffer[0] == 0x8B)Command_buffer[1] += 0x02;//Write_EE_CK
			else if (Command_buffer[0] == 0x1B)Command_buffer[1] += 0x03;//Read_EE
			else if (Command_buffer[0] == 0x9A)Command_buffer[1] += 0x01;//Write_Reg
			else if(Command_buffer[0] == 0x1A)Command_buffer[1] += 0x01;//Read_Reg
			else if(Command_buffer[0] == 0x9C)Command_buffer[1] += 0x0A;//Write_All
			else if (Command_buffer[0] == 0x1C)Command_buffer[1] += 0x02;//EE_HardCheck
			cMyDlg->m_hidusb.Send(Command_buffer, i_k);

			int iRecv = cMyDlg->m_hidusb.Recv(Response_buffer, iDelay);

			int jRecv = 0;
			for (int i = 0; i < iRecv; i++)
			{
				Compare_buffer[i] = Response_buffer[i + 2];

				dat1 = (Response_buffer[i + 2] & 0xF0) >> 4;
				Result_buffer[jRecv++] = (dat1 <= 9) ? dat1 + '0' : (dat1 - 10) + 'a';
				dat1 = (Response_buffer[i + 2] & 0x0F);
				Result_buffer[jRecv++] = (dat1 <= 9) ? dat1 + '0' : (dat1 - 10) + 'a';
				Result_buffer[jRecv++] = ' ';
			}

			/*处理返回的结果*/
			if (iRecv == 2 && ((Response_buffer[2] == 0xFF && Response_buffer[3] == 0xFF) || (Response_buffer[2] == 0x65 && Response_buffer[3] == 0x81)))//错误
			{
				sResult = Result_buffer;
				cMyDlg->SetWordColor("/*" + sCmdResult + "*/", 2);
				cMyDlg->SetWordColor("/*Error:" + sResult, 2);

				iErrorNum++;
			}
			else if((Response_buffer[iRecv] == 0x90) && (Response_buffer[iRecv+1] == 0x00))//正确
			{
				sResult = Result_buffer;
				cMyDlg->SetWordColor("/*" + sCmdResult + "*/", 3);
				cMyDlg->SetWordColor("/*OK:" + sResult, 3);
			}
			else
			{
				sResult = Result_buffer;
				cMyDlg->SetWordColor("/*" + sCmdResult + "*/", 2);
				cMyDlg->SetWordColor("/*Unknow Error:" + sResult, 2);
			}
			memset(Result_buffer, 0, 1024);
			memset(Response_buffer, 0, 1024);
			memset(listbox_buffer, 0, 1024);

			/*显示进度比*/
			sPersent.Format("%.0f%%", 100.0*(float)(m) / (float)(iScriptLen));
			::SendMessage(cMyDlg->m_StatusBar.m_hWnd, SB_SETTEXT, 1, (LPARAM)(LPCTSTR)(sPersent));

			/*显示错误次数*/
			sErrorNum.Format("%d", iErrorNum);
			::SendMessage(cMyDlg->m_StatusBar.m_hWnd, SB_SETTEXT, 3, (LPARAM)(LPCTSTR)("Error:" + sErrorNum));

			sCommand = _T("");

		} while (m < iScriptLen);	

		m = 0;
	}
	m_Num = 0;
	cMyDlg->bStateRun = FALSE;
	cMyDlg->Enable_Run(TRUE);
	cMyDlg->SetDlgItemText(IDC_BUTTON_EETEST_STOP, _T("Stop"));
	cMyDlg->SetWindowText("Run Over-EETest");

	CloseHandle(cMyDlg->hThread);
	return true;
}

void CEE_testtool_hidusbDlg::OnBnClickedButtonEetestStep()
{
	// TODO: 在此添加控件通知处理程序代码

	int iDataLen = 0;
	char Result_buffer[1024] = { 0 };
	char listbox_buffer[1024] = { 0 };
	unsigned char Command_buffer[1024] = { 0 }, Response_buffer[1024] = { 0 };
	unsigned char dat1 = 0, dat2 = 0, dat11 = 0, dat22 = 0;

	CString sCommand = _T(""), sCmdS = _T(""), sScriptTxt = _T(""), sCmdResult = _T("");

	m_ctrl_richedit_script.GetWindowText(sScriptTxt);//获取编辑框文本
	size_t iScriptLen = strlen(sScriptTxt);//文本总长度
	if (sScriptTxt.IsEmpty())return;//空文本跳出
	if(Step_Index < iScriptLen)
	{
		int iCmdlen = sScriptTxt.Find(_T("\r\n"), Step_Index);//寻找指令

		//SetScriptColor(Step_Index, iCmdlen+2, true);

		iCmdlen -= Step_Index;

		if (iCmdlen < 0)//指令内无空格，则获取内容
		{
			iCmdlen = strlen(sScriptTxt) - Step_Index;
		}
		sCommand = sScriptTxt.Mid(Step_Index, iCmdlen);//m:寻找起始位置，iCmdlen:寻找长度
		sCmdResult = sCommand;
		Step_Index = Step_Index + iCmdlen + 2;

		if (sCommand[0] != ';')
		{
			sCommand.Remove(' ');
			sCommand.Remove(',');
		}

		strcpy_s((char*)listbox_buffer, 1024, sCommand);//判定每一行指令

		if (listbox_buffer[0] != ';')
		{
			if (strstr((char*)listbox_buffer, "Write_EE") != NULL)//Write_EE
			{
				sCmdS = "Write_EE";
				iDataLen = strlen(sCommand) - strlen(sCmdS);
				Command_buffer[0] = 0x9B;
			}
			else if (strstr((char*)listbox_buffer, "Write_EE_CK") != NULL)//Write_EE_CK
			{
				sCmdS = "Write_EE_CK";
				iDataLen = strlen(sCommand) - strlen(sCmdS);
				Command_buffer[0] = 0x8B;
			}
			else if (strstr((char*)listbox_buffer, "Read_EE") != NULL)//Read_EE
			{
				sCmdS = "Read_EE";
				iDataLen = strlen(sCommand) - strlen(sCmdS);
				Command_buffer[0] = 0x1B;
			}
			else if (strstr((char*)listbox_buffer, "Write_Reg") != NULL)//Write_Reg
			{
				sCmdS = "Write_Reg";
				iDataLen = strlen(sCommand) - strlen(sCmdS);
				Command_buffer[0] = 0x9A;
			}
			else if (strstr((char*)listbox_buffer, "Read_Reg") != NULL)//Read_Reg
			{
				sCmdS = "Read_Reg";
				iDataLen = strlen(sCommand) - strlen(sCmdS);
				Command_buffer[0] = 0x1A;
			}
			else if (strstr((char*)listbox_buffer, "Write_All") != NULL)//Write_All
			{
				sCmdS = "Write_All";
				iDataLen = strlen(sCommand) - strlen(sCmdS);
				Command_buffer[0] = 0x9C;
			}
			else if (strstr((char*)listbox_buffer, "EE_HardCheck") != NULL)//EE_HardCheck
			{
				sCmdS = "EE_HardCheck";
				iDataLen = strlen(sCommand) - strlen(sCmdS);
				Command_buffer[0] = 0x1C;
			}
			else if (strstr((char*)listbox_buffer, "Beep") != NULL)//Beep
			{
				BYTE send_buf[1024] = { 0x16,0x01,0x00 };
				m_hidusb.Send(send_buf, 3);
				if (Step_Index >= iScriptLen)Step_Index = 0;
				return;
			}
			else if (strstr((char*)listbox_buffer, "Compare") != NULL)//Compare
			{
				int i = 0, k = 0;
				iDataLen = strlen(sCommand) - 7;
				while (i < iDataLen)
				{
					dat1 = (listbox_buffer[i + 7] <= '9') ? listbox_buffer[i + 7] - '0' : (listbox_buffer[i + 7] + 10) - 'A';
					if (dat1 > 0x20)dat1 -= 0x20;
					dat2 = (listbox_buffer[i + 8] <= '9') ? listbox_buffer[i + 8] - '0' : (listbox_buffer[i + 8] + 10) - 'A';
					if (dat2 > 0x20)dat2 -= 0x20;
					Command_buffer[k++] = dat1 * 16 + dat2;
					i = i + 2;
				}

				int jRecv = 0;
				for (int i = 0; i < k; i++)
				{
					dat1 = (Command_buffer[i] & 0xF0) >> 4;
					Result_buffer[jRecv++] = (dat1 <= 9) ? dat1 + '0' : (dat1 - 10) + 'a';
					dat1 = (Command_buffer[i] & 0x0F);
					Result_buffer[jRecv++] = (dat1 <= 9) ? dat1 + '0' : (dat1 - 10) + 'a';
					Result_buffer[jRecv++] = ' ';
				}

				sResult = Result_buffer;
				for (i = 0; i < k; i++)
				{
					if (Command_buffer[i] != Compare_buffer[i])break;
				}
				if (i >= k)
				{
					SetWordColor("/***************Compare***************/", 1);
					SetWordColor("/*OK:" + sResult, 1);
					SetWordColor("/*************************************/", 1);
				}
				else
				{
					SetWordColor("/***************Compare***************/", 2);
					SetWordColor("/*ERROR:" + sResult, 2);
					SetWordColor("/*************************************/", 2);
				}
				memset(Command_buffer, 0, k);

				if (Step_Index >= iScriptLen)Step_Index = 0;
				return;
			}
			else //非本软件支持的指令
			{
				if (Step_Index >= iScriptLen)Step_Index = 0;
				return;
			}
		}
		else //注释行
		{
			SetWordColor(sCommand, 4);
			if (Step_Index >= iScriptLen)Step_Index = 0;
			return;
		}

		/*发送指令数据*/
		int  i_k = 1, i_i = 0;
		int i_Cmd = strlen(sCommand) - iDataLen;
		while (i_i < iDataLen)
		{
			dat1 = (listbox_buffer[i_i + i_Cmd] <= '9') ? listbox_buffer[i_i + i_Cmd] - '0' : (listbox_buffer[i_i + i_Cmd] + 10) - 'A';
			if (dat1 > 0x20)dat1 -= 0x20;
			dat2 = (listbox_buffer[i_i + i_Cmd + 1] <= '9') ? listbox_buffer[i_i + i_Cmd + 1] - '0' : (listbox_buffer[i_i + i_Cmd + 1] + 10) - 'A';
			if (dat2 > 0x20)dat2 -= 0x20;
			Command_buffer[i_k++] = dat1 * 16 + dat2;
			i_i = i_i + 2;
		}
		/*将Data长度与地址等长度合并为总长度*/
		if (Command_buffer[0] == 0x9B)Command_buffer[1] += 0x02;//Write_EE
		else if (Command_buffer[0] == 0x8B)Command_buffer[1] += 0x02;//Write_EE_CK
		else if (Command_buffer[0] == 0x1B)Command_buffer[1] += 0x03;//Read_EE
		else if (Command_buffer[0] == 0x9A)Command_buffer[1] += 0x01;//Write_Reg
		else if (Command_buffer[0] == 0x1A)Command_buffer[1] += 0x01;//Read_Reg
		else if (Command_buffer[0] == 0x9C)Command_buffer[1] += 0x0A;//Write_All
		else if (Command_buffer[0] == 0x1C)Command_buffer[1] += 0x02;//EE_HardCheck
		m_hidusb.Send(Command_buffer, i_k);

		int iRecv = m_hidusb.Recv(Response_buffer, iDelay);

		int jRecv = 0;
		for (int i = 0; i < iRecv; i++)
		{
			Compare_buffer[i] = Response_buffer[i + 2];

			dat1 = (Response_buffer[i + 2] & 0xF0) >> 4;
			Result_buffer[jRecv++] = (dat1 <= 9) ? dat1 + '0' : (dat1 - 10) + 'a';
			dat1 = (Response_buffer[i + 2] & 0x0F);
			Result_buffer[jRecv++] = (dat1 <= 9) ? dat1 + '0' : (dat1 - 10) + 'a';
			Result_buffer[jRecv++] = ' ';
		}

		/*处理返回的结果*/
		sResult = sCommand;
		if (iRecv == 2 && ((Response_buffer[2] == 0xFF && Response_buffer[3] == 0xFF) || (Response_buffer[2] == 0x65 && Response_buffer[3] == 0x81)))//错误
		{
			sResult = Result_buffer;
			SetWordColor("/*" + sCmdResult + "*/", 2);
			SetWordColor("/*Error:" + sResult, 2);

		}
		else if ((Response_buffer[iRecv] == 0x90) && (Response_buffer[iRecv + 1] == 0x00))//正确
		{
			sResult = Result_buffer;
			SetWordColor("/*" + sCmdResult + "*/", 3);
			SetWordColor("/*OK:" + sResult, 3);
		}
		else
		{
			sResult = Result_buffer;
			SetWordColor("/*" + sCmdResult + "*/", 2);
			SetWordColor("/*Unknow Error:" + sResult, 2);
		}
		memset(Result_buffer, 0, 1024);
		memset(Response_buffer, 0, 1024);
		memset(listbox_buffer, 0, 1024);

		sCommand = _T("");
	}
	else
	{
		Step_Index = 0;
	}
}

bool CEE_testtool_hidusbDlg::SetWordColor(CString sNew,int iColor)//设置Edit_Color
{
	CHARFORMAT2 cf;
	memset(&cf, 0, sizeof(cf));
	cf.dwMask |= CFM_COLOR;
	if (iColor == 1)//蓝色
	{
		cf.crTextColor = RGB(0, 0, 255);
	}
	else if (iColor == 2)//红色
	{
		cf.crTextColor = RGB(255, 0, 0);
	}
	else if (iColor == 3)//绿色
	{
		cf.crTextColor = RGB(0, 128, 0);
	}
	cf.dwMask |= CFM_FACE;
	strcpy_s(cf.szFaceName, _T("宋体")); //设置字体
	sNew += "\r\n";
	m_ctrl_richedit_result.SetSel(-1, -1); //将光标放在文本最末
	m_ctrl_richedit_result.SetWordCharFormat(cf); //为将要输入的内容设定字体等格式
	m_ctrl_richedit_result.ReplaceSel(sNew); // 把新内容添加到richedit中，将采用上句设置的格式来显示，已有内容不受影响
	return false;
}

bool CEE_testtool_hidusbDlg::SetScriptColor(int lineStart,int lineEnd,BOOL bColor)//设置Edit_Color
{
	CHARFORMAT2 cf;
	memset(&cf, 0, sizeof(cf));
	cf.dwMask |= CFM_COLOR;
	if(bColor == TRUE)cf.crTextColor = RGB(0, 128, 0);
	cf.dwMask |= CFM_FACE;
	strcpy_s(cf.szFaceName, _T("宋体")); //设置字体

	m_ctrl_richedit_script.SetFocus();
	m_ctrl_richedit_script.SetSel(lineStart, lineEnd);//选取第一行字符
	//m_ctrl_richedit_script.SetSelectionCharFormat(cf);//设置颜色

	//m_ctrl_richedit_script.SetSel(0xFFFF, 0xFFFF);

	//m_ctrl_richedit_script.HideSelection(FALSE, TRUE);

	m_ctrl_richedit_script.SetSelectionCharFormat(cf);



	//richEditCtrl->HideSelection(TRUE, TRUE);


	return false;
}

void CEE_testtool_hidusbDlg::OnBnClickedButtonEetestClearscript()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ctrl_richedit_script.SetWindowText(_T(""));
}


void CEE_testtool_hidusbDlg::OnBnClickedButtonEetestClearresult()
{
	iErrorNum = 0;
	m_StatusBar.SetPaneText(3, "Error:0");
	m_ctrl_richedit_result.SetWindowText(_T(""));
}


void CEE_testtool_hidusbDlg::OnBnClickedButtonEetestStop()
{
	// TODO: 在此添加控件通知处理程序代码	

	if (bStateRun == TRUE)//pause
	{
		bStateRun = FALSE;
		GetDlgItem(IDC_BUTTON_EETEST_RUN)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_EETEST_SAVE_SCRIPT)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_EETEST_SAVE_RESULT)->EnableWindow(TRUE);
		SetDlgItemText(IDC_BUTTON_EETEST_STOP, _T("Stop"));
		this->SetWindowText("Pause-EETest");
		::SuspendThread(hThread);                          //挂起线程
	}
	else//stop
	{
		DWORD code;
		if (GetExitCodeThread(hThread, &code) || (code == STILL_ACTIVE))
		{
			TerminateThread(hThread, 0);						//终止线程
			CloseHandle(hThread);								//销毁线程句柄
		}
		this->SetWindowText("Run Over-EETest");
		Enable_Run(TRUE);
		Step_Index = 0;
		m_Num = 0;
		iErrorNum = 0;
	}
}


void CEE_testtool_hidusbDlg::OnVersion()
{
	// TODO: 在此添加命令处理程序代码
	CVersionDlg mVerDlg;
	mVerDlg.DoModal();
}

void CEE_testtool_hidusbDlg::OnBnClickedButtonEetestClearcmd()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ctrl_editregaddr.SetWindowText(_T(""));
	m_ctrl_editregdata.SetWindowText(_T(""));
	m_ctrl_editeelen.SetWindowText(_T(""));
	m_ctrl_editaddr.SetWindowText(_T(""));
	SetDlgItemText(IDC_EDIT_EEPROM_DATA, _T(""));
	SetDlgItemText(IDC_EDIT_EEPROM_COMPARE, _T(""));
	SetDlgItemText(IDC_EDIT_WDATA, _T(""));
	SetDlgItemText(IDC_EDIT_WT14, _T(""));
	SetDlgItemText(IDC_EDIT_WT15, _T(""));
	SetDlgItemText(IDC_EDIT_EEHKADD, _T(""));
	SetDlgItemText(IDC_EDIT_EEHK_EDATA, _T(""));
}

void CEE_testtool_hidusbDlg::OnEnChangeEditEepromRegdata()//reg_data Update
{
	UpdateData(TRUE);
	m_StatusBar.SetPaneText(2, "Reg data(1Bytes):" + m_str_editregdata);
	m_ctrl_editregdata.SetLimitText(2);
}

void CEE_testtool_hidusbDlg::OnEnChangeEditEepromAddr()//EE_addr Update
{
	UpdateData(TRUE);
	m_StatusBar.SetPaneText(2, "EE Addr(2Bytes):" + m_str_editaddr);
	m_ctrl_editaddr.SetLimitText(4);
}
void CEE_testtool_hidusbDlg::OnEnChangeEditEepromRegaddr()//reg_addr Update
{
	UpdateData(TRUE);
	m_StatusBar.SetPaneText(2, "Reg Addr(1Byte):" + m_str_editregaddr);
	m_ctrl_editregaddr.SetLimitText(2);
}
void CEE_testtool_hidusbDlg::OnEnChangeEditEepromLen()//EE_lenth Update
{
	UpdateData(TRUE);
	m_StatusBar.SetPaneText(2, "EE Lenth(1Byte):" + m_str_editlen);
	m_ctrl_editeelen.SetLimitText(2);
}

void CEE_testtool_hidusbDlg::OnEnChangeEditEepromData()//EE_data Update
{
	UpdateData(TRUE);
	m_StatusBar.SetPaneText(2, "EE data:" + m_str_editdata);
}


void CEE_testtool_hidusbDlg::OnEnChangeEditEepromCompare()//compare_data Update
{
	UpdateData(TRUE);
	m_StatusBar.SetPaneText(2, "Compare data:" + m_str_editcompare);
}


void CEE_testtool_hidusbDlg::OnEnChangeEditWdata()//write_all_data Update
{
	UpdateData(TRUE);
	m_StatusBar.SetPaneText(2, "Write_All data(5Bytes):" + m_str_wdata);
}


void CEE_testtool_hidusbDlg::OnEnChangeEditWt14()//t14 Update
{
	UpdateData(TRUE);
	m_StatusBar.SetPaneText(2, "t14(3Bytes):" + m_str_editWt14);
}


void CEE_testtool_hidusbDlg::OnEnChangeEditWt15()//t15 Update
{
	UpdateData(TRUE);
	m_StatusBar.SetPaneText(2, "t15(3Bytes):" + m_str_editWt15);
}


void CEE_testtool_hidusbDlg::OnEnChangeEditEehkadd()//HardCheck addr Update
{
	UpdateData(TRUE);
	m_StatusBar.SetPaneText(2, "EE HardCheck addr(2Bytes):" + m_str_editHK);
	m_edit_editHKaddr.SetLimitText(4);
}

//void CEE_testtool_hidusbDlg::OnEnSetfocusEditEehkadd()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	UpdateData(TRUE);
//	m_StatusBar.SetPaneText(2, "EE HardCheck addr(2Bytes):" + m_str_editHK);
//}

//
//


void CEE_testtool_hidusbDlg::OnEnChangeEditEehkEdata()//HardCheck data Update
{
	UpdateData(TRUE);
	m_StatusBar.SetPaneText(2, "EE HardCheck data(10Bytes):" + m_str_editHKdata);
}

