
// SystemProtectDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "time.h"
#include <sys/types.h>
#include <sys/stat.h>
#include "map"
#include "vector"
using namespace std;

struct structFileInfo
{
	CString m_strFileName;
	struct _stat64 m_statFileInfo;

};
// CSystemProtectDlg �Ի���
class CSystemProtectDlg : public CDialogEx
{
// ����
public:
	CSystemProtectDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SYSTEMPROTECT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��



// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_srcPath;
	afx_msg void OnBnClickedBtnSelectsrc();
private:
	CString SelectFolder();	
	std::map<unsigned int,vector<structFileInfo>>m_FileNameLst;
	void getFileInfo(map<unsigned int, vector<structFileInfo>> &mapFileNameLst, CString & srcPath);
	unsigned int calculateHASH(const char * fileName);
	CString getFileName(CString &filePath);
	CString getFilePath(CString &filePathName);
	std::vector<CString>m_strfilePaths;
	BOOL isHadDuplicateInfo = false;
	size_t delFileNum = 0;
	CListCtrl m_lstFileInfo;
	afx_msg void OnBnClickedBtnFindDuplicate();
	afx_msg void OnBnClickedBtnDelete();
public:
	afx_msg void OnNMDblclkListFileinfo(NMHDR *pNMHDR, LRESULT *pResult);
};
