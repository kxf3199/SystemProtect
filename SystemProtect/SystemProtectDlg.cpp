
// SystemProtectDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SystemProtect.h"
#include "SystemProtectDlg.h"
#include "afxdialogex.h"
#include "Shlobj.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CSystemProtectDlg �Ի���



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


// CSystemProtectDlg ��Ϣ�������

BOOL CSystemProtectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSystemProtectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSystemProtectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSystemProtectDlg::OnBnClickedBtnSelectsrc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);	
	m_srcPath = SelectFolder();
	UpdateData(false);
}


void CSystemProtectDlg::OnBnClickedBtnSelectdst()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	bi.lpszTitle = _T("������ѡ�ļ���Ŀ¼:");
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
				//������ļ��У��ݹ飬��������
				getFileInfo(FileInfoLst,fdPath);
			}
			else
			{
				//������ļ�,
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