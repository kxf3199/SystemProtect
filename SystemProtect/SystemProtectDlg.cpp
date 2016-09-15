
// SystemProtectDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SystemProtect.h"
#include "SystemProtectDlg.h"
#include "afxdialogex.h"
#include "Shlobj.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

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


// CSystemProtectDlg 对话框



CSystemProtectDlg::CSystemProtectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SYSTEMPROTECT_DIALOG, pParent)
	, m_srcPath(_T(""))
	, m_dstPath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSystemProtectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SRCPATH, m_srcPath);
	DDX_Text(pDX, IDC_EDIT_DSTPATH, m_dstPath);
	DDX_Control(pDX, IDC_LIST_FILEINFO, m_lstFileInfo);
}

BEGIN_MESSAGE_MAP(CSystemProtectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SELECTSRC, &CSystemProtectDlg::OnBnClickedBtnSelectsrc)
	ON_BN_CLICKED(IDC_BTN_SELECTDST, &CSystemProtectDlg::OnBnClickedBtnSelectdst)
	ON_BN_CLICKED(IDC_BTN_FIND_DUPLICATE, &CSystemProtectDlg::OnBnClickedBtnFindDuplicate)
END_MESSAGE_MAP()


// CSystemProtectDlg 消息处理程序

BOOL CSystemProtectDlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSystemProtectDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSystemProtectDlg::OnPaint()
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
HCURSOR CSystemProtectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSystemProtectDlg::OnBnClickedBtnSelectsrc()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);	
	m_srcPath = SelectFolder();
	UpdateData(false);
}


void CSystemProtectDlg::OnBnClickedBtnSelectdst()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_dstPath = SelectFolder();
	UpdateData(FALSE);
}
CString CSystemProtectDlg::SelectFolder()
{
	TCHAR szBuffer[MAX_PATH] = { 0 };
	BROWSEINFO bi;
	ZeroMemory(&bi, sizeof(BROWSEINFO));
	bi.hwndOwner = NULL;
	bi.pszDisplayName = szBuffer;
	bi.lpszTitle = _T("从下面选文件夹目录:");
	bi.ulFlags = BIF_RETURNFSANCESTORS;
	LPITEMIDLIST idl = SHBrowseForFolder(&bi);
	if (NULL == idl)
	{
		return szBuffer;
	}
	SHGetPathFromIDList(idl, szBuffer);
	return szBuffer;
}

void CSystemProtectDlg::OnBnClickedBtnFindDuplicate()
{
	// TODO: 在此添加控件通知处理程序代码
	getFileInfo(FileInfoLst, m_srcPath);

	
}
void CSystemProtectDlg::getFileInfo(map<unsigned _int64, struct _stat64>&FileInfoLst,CString & srcPath)
{
	CString myDataPath, fdPath,fdName;
	myDataPath = srcPath + "\\*.*";
	CString strTmp;
	CFileFind find;
	BOOL bf = find.FindFile(myDataPath);
	unsigned __int64 fileFlag;
	struct _stat64 buf;
	while (bf)
	{
		bf = find.FindNextFile();
		if (!find.IsDots())
		{
			fdPath = find.GetFilePath();
			fdName = find.GetFileName();
			if (find.IsDirectory())
			{
				//如果是文件夹，递归，继续往下
				getFileInfo(FileInfoLst,fdPath);
			}
			else
			{
				//如果是文件,
				//char * fileName = fdName.GetBuffer();
				int res;
				res=_stat64((char*)fdPath.GetBuffer(), &buf);
				if (res != 0)
				{
					perror("Problem getting information");
					CString tmpInfo;
					switch (errno)
					{
					case ENOENT:						
						tmpInfo.Format("File %s not found.\n", fdName);
						AfxMessageBox(tmpInfo);
						break;
					case EINVAL:
						AfxMessageBox("Invalid parameter to _stat.");
						break;
					default:
						/* Should never be reached. */
						AfxMessageBox("Unexpected error in _stat.\n");
					}
				}
				else
				{
					fileFlag = calculateFile((char*)fdName.GetBuffer(), buf);
					FileInfoLst.insert(pair<unsigned _int64, struct _stat64>(fileFlag, buf));
		
				}


			}
		}
	}
	find.Close();

}
unsigned __int64 CSystemProtectDlg::calculateFile(const char * fileName, struct _stat64 &fileInfo)
{
	unsigned __int64 fileFlag = 0;
	CString strfileName =fileName;
	int iproduct=0;
	int ilenght = strfileName.GetLength();
	for (size_t i = 0; i < ilenght / 2;i++)
	{
		int tmp= (short)strfileName.GetAt(i)*(short)strfileName.GetAt(ilenght - i-1);
		if ((short)strfileName.GetAt(i)>(short)strfileName.GetAt(ilenght - i-1))
		{
			tmp += 1;
		}
		else if((short)strfileName.GetAt(i)<(short)strfileName.GetAt(ilenght - i-1)) {
			tmp -= 1;
		}
		iproduct += tmp;
	}

	char chrProduct[20] = { 0 };
	char firstChar, centerChar, lastChar;
	firstChar = strfileName.GetAt(0);
	lastChar = strfileName.GetAt(ilenght-1);
	centerChar = strfileName.GetAt(ilenght / 2);
	sprintf_s(chrProduct,20,"%d%d%d%d%d", iproduct, ilenght,(short)firstChar,(short)centerChar,(short)lastChar);
	fileFlag = _atoi64(chrProduct);
	return fileFlag;
}