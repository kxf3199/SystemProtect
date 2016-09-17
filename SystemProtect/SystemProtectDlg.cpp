
// SystemProtectDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SystemProtect.h"
#include "SystemProtectDlg.h"
#include "afxdialogex.h"
#include "Shlobj.h"
#include <string>
#include <fstream> 

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
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSystemProtectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SRCPATH, m_srcPath);
	DDX_Control(pDX, IDC_LIST_FILEINFO, m_lstFileInfo);
}

BEGIN_MESSAGE_MAP(CSystemProtectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SELECTSRC, &CSystemProtectDlg::OnBnClickedBtnSelectsrc)
	ON_BN_CLICKED(IDC_BTN_FIND_DUPLICATE, &CSystemProtectDlg::OnBnClickedBtnFindDuplicate)
	ON_BN_CLICKED(IDC_BTN_DELETE, &CSystemProtectDlg::OnBnClickedBtnDelete)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_FILEINFO, &CSystemProtectDlg::OnNMDblclkListFileinfo)
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
	m_lstFileInfo.InsertColumn(0, "ID", LVCFMT_LEFT, 30);
	m_lstFileInfo.InsertColumn(1, "�ļ���", LVCFMT_LEFT, 80);
	m_lstFileInfo.InsertColumn(2, "�ļ�·��", LVCFMT_LEFT, 120);
	m_lstFileInfo.InsertColumn(3, "�ļ���С", LVCFMT_LEFT, 80);
	m_lstFileInfo.InsertColumn(4, "����ʱ��", LVCFMT_LEFT, 80);
	m_lstFileInfo.InsertColumn(5, "�޸�ʱ��", LVCFMT_LEFT, 80);
	m_lstFileInfo.SetExtendedStyle(m_lstFileInfo.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
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
	m_srcPath="";
	UpdateData(false);
	UpdateData(true);
	//m_srcPath = SelectFolder();
	CFileDialog fDlg(TRUE,"ini","config.ini", OFN_HIDEREADONLY | OFN_READONLY, "ini�ļ�(*.ini)|*.ini|�ı��ļ�(*.txt)|*.txt");
	if (fDlg.DoModal() == IDOK)//�������Ի���ȷ����ť
	{
		CString szGetName;
		szGetName = fDlg.GetPathName(); //�õ����ļ���·��
		std::ifstream fConf(szGetName);
		std::string fbuf;
		while (std::getline(fConf,fbuf))
			m_srcPath=m_srcPath+fbuf.c_str()+' ';
	}
	UpdateData(false);
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
	time_t t_start, t_end;
	t_start = clock();
	UpdateData(TRUE);
	if (m_srcPath.IsEmpty())
	{
		AfxMessageBox("���������ļ�Ŀ¼��");
		return;
	}
	if (m_FileNameLst.size()!=0)
	{
		m_FileNameLst.clear();
	}
	if (m_lstFileInfo.GetItemCount()!=0)
	{
		m_lstFileInfo.DeleteAllItems();
	}
	CString srcPath = m_srcPath;
	CString strTmp;
	while (!srcPath.IsEmpty())
	{
		strTmp = srcPath.Left(srcPath.Find(' '));
		srcPath = srcPath.Right(srcPath.GetLength() - srcPath.Find(' ') - 1);
		getFileInfo(m_FileNameLst, strTmp);

	}
	
	int nCount = 0;
	CString strNum;
	errno_t err;
	char timeBuf[26];
	long size = 0;
	for (map<unsigned int, vector<structFileInfo>>::iterator it = m_FileNameLst.begin(); it != m_FileNameLst.end();)
	{
		int i = 1;
		for (; i < it->second.size();i++)
		{
			nCount = m_lstFileInfo.GetItemCount();
			strNum.Format("%d", nCount);
			m_lstFileInfo.InsertItem(nCount, strNum);
			if (i==1)
			{
				m_lstFileInfo.SetItemText(nCount, 1, getFileName(it->second[0].m_strFileName));
			}			
			m_lstFileInfo.SetItemText(nCount, 2, it->second[i-1].m_strFileName);

			strNum.Format("%ld", *&it->second[i - 1].m_statFileInfo.st_size);
			m_lstFileInfo.SetItemText(nCount, 3, strNum);
			err = ctime_s(timeBuf, 26, &it->second[i-1].m_statFileInfo.st_ctime);
			if (!err)
			{
				m_lstFileInfo.SetItemText(nCount, 4, timeBuf);
			}
			err = ctime_s(timeBuf, 26, &it->second[i - 1].m_statFileInfo.st_mtime);
			if (!err)
			{
				m_lstFileInfo.SetItemText(nCount, 5, timeBuf);
			}
			m_lstFileInfo.SetItemData(nCount, it->first);
		}
		if (i==1)
		{
			m_FileNameLst.erase(it++);			
		}
		else
		{
			nCount = m_lstFileInfo.GetItemCount();
			strNum.Format("%d", nCount);
			m_lstFileInfo.InsertItem(nCount, strNum);			
			m_lstFileInfo.SetItemText(nCount, 2, it->second[i-1].m_strFileName);

			strNum.Format("%ld", *&it->second[i - 1].m_statFileInfo.st_size);
			m_lstFileInfo.SetItemText(nCount, 3, strNum);
			err = ctime_s(timeBuf, 26, &it->second[i-1].m_statFileInfo.st_ctime);
			if (!err)
			{
				m_lstFileInfo.SetItemText(nCount, 4, timeBuf);
			}
			err = ctime_s(timeBuf, 26, &it->second[i-1].m_statFileInfo.st_mtime);
			if (!err)
			{
				m_lstFileInfo.SetItemText(nCount, 5, timeBuf);
			}
			m_lstFileInfo.SetItemData(nCount, it->first);
			it++;
		}

	}
	isHadDuplicateInfo = true;
	UpdateData(FALSE);
	t_end = clock();
	CString strInfo;
	strInfo.Format("������ϣ���ʱ%.0fms��", double(t_end - t_start) * 1000 / CLOCKS_PER_SEC);
	AfxMessageBox(strInfo);
	
	
}
CString CSystemProtectDlg::getFileName(CString &filePath)
{
	CString fileName;
	fileName = filePath.Right(filePath.GetLength() - filePath.ReverseFind('\\')-1);
	return fileName;
}
CString CSystemProtectDlg::getFilePath(CString &filePathName)
{
	CString filePath;
	filePath = filePathName.Left(filePath.ReverseFind('\\'));
	return filePath;
}
void CSystemProtectDlg::getFileInfo(map<unsigned int,vector<structFileInfo>>&mapFileNameLst,CString & srcPath)
{
	CString myDataPath, fdPath,fdName;
	myDataPath = srcPath + "\\*.*";
	CString strTmp,strNum;
	CFileFind find;
	BOOL bf = find.FindFile(myDataPath);
	unsigned int fileFlag;
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
				getFileInfo(mapFileNameLst,fdPath);
			}
			else
			{
				//������ļ�,
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
						AfxMessageBox("Unexpected error in _stat.\n"+ fdPath);
						break;
					}
				}
				else
				{
					fileFlag = calculateHASH((char*)fdName.GetBuffer());
					std::map<unsigned int,vector<structFileInfo>>::iterator it = mapFileNameLst.find(fileFlag);
					if (it!=mapFileNameLst.end())
					{

						structFileInfo structF;
						structF.m_strFileName = fdPath;
						structF.m_statFileInfo = buf;
						it->second.push_back(structF);					
					}
					else
					{
						vector<structFileInfo> structFs;
						structFileInfo structF;
						structF.m_strFileName = fdPath;
						structF.m_statFileInfo = buf;
						structFs.push_back(structF);
						mapFileNameLst.insert(pair<unsigned int, vector<structFileInfo>>(fileFlag, structFs));	
					}					
		
				}


			}
		}
	}
	find.Close();

}
unsigned int CSystemProtectDlg::calculateHASH(const char * fileName)
{
	unsigned int seed=131;
	unsigned int hashV = 0;
	// BKDR Hash 

	while (*fileName)
	{
		hashV = hashV*seed + (*fileName++);
	}
	return (hashV & 0x7FFFFFFF);
// 	CString strfileName =fileName;
// 	int iproduct=0;
// 	int ilenght = strfileName.GetLength();
// 	for (size_t i = 0; i < ilenght / 2;i++)
// 	{
// 		int tmp= (short)strfileName.GetAt(i)*(short)strfileName.GetAt(ilenght - i-1);
// 		if ((short)strfileName.GetAt(i)>(short)strfileName.GetAt(ilenght - i-1))
// 		{
// 			tmp += 1;
// 		}
// 		else if((short)strfileName.GetAt(i)<(short)strfileName.GetAt(ilenght - i-1)) {
// 			tmp -= 1;
// 		}
// 		iproduct += tmp;
// 	}
// 
// 	char chrProduct[20] = { 0 };
// 	char firstChar, centerChar, lastChar;
// 	firstChar = strfileName.GetAt(0);
// 	lastChar = strfileName.GetAt(ilenght-1);
// 	centerChar = strfileName.GetAt(ilenght / 2);
// 	sprintf_s(chrProduct,20,"%d%d%d%d%d", iproduct, ilenght,(short)firstChar,(short)centerChar,(short)lastChar);
// 	fileFlag = _atoi64(chrProduct);
// 	return fileFlag;
}

void CSystemProtectDlg::OnBnClickedBtnDelete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!isHadDuplicateInfo)
	{
		AfxMessageBox("���Ȳ���һ���ظ��ļ���Ϣ��");
		return;
	}
	if (MessageBox("ע�Ȿ��ɾ��ֻ�Ǽ���ļ�����ͬ���ļ���С��ͬ���޸�ʱ����ͬ��ͬʱ����ʱɾ��\n����һЩ������ͬ�����ļ����ڲ�ͬ��Ŀ¼�´��ڣ������ɾ����\n�Ƿ�ȷ��ɾ����"
		, "��Ҫ����", MB_ICONEXCLAMATION | MB_OKCANCEL) == IDCANCEL)
		return;
	size_t delCount[2] = {0};
	for (map<unsigned int, vector<structFileInfo>>::iterator it = m_FileNameLst.begin(); it != m_FileNameLst.end();)
	{
		int i = 1;
		for (; i < it->second.size(); i++)
		{
			for (int j = i + 1; j <= it->second.size();j++)
			{
				if(it->second[i-1].m_statFileInfo.st_size!= it->second[j-1].m_statFileInfo.st_size
					|| it->second[i - 1].m_statFileInfo.st_mtime!= it->second[j-1].m_statFileInfo.st_mtime)
					continue;
				DeleteFile(it->second[j - 1].m_strFileName);
				delFileNum++;
				it->second.erase(it->second.begin() + j - 1);
				delCount[1] =delCount[0]+ j - 1;
				m_lstFileInfo.DeleteItem(delCount[1]);
				j--;				
			}			
		}
		if (it->second.size()==1)
		{
			m_FileNameLst.erase(it++);
			m_lstFileInfo.DeleteItem(delCount[0]);

		}
		else
		{
			delCount[0] += it->second.size();
			it++;
		}		
		
	}
	UpdateData(false);
	CString strInfo;
	strInfo.Format("ɾ���ظ��ļ����,����ɾ���ļ�%d��.", delFileNum);
	AfxMessageBox(strInfo);

}


void CSystemProtectDlg::OnNMDblclkListFileinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
    //˫�������ļ�����·��
	char szParam[_MAX_PATH + 64] = { 0 };
	strcpy_s(szParam, "/e,/select, ");
	strcat_s(szParam, m_lstFileInfo.GetItemText(pNMItemActivate->iItem, 2));
	ShellExecute(NULL, "open", "explorer", szParam, NULL, SW_SHOW);
	*pResult = 0;
}
