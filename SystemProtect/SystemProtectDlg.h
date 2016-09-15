
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
	CString m_dstPath;
	afx_msg void OnBnClickedBtnSelectsrc();
	afx_msg void OnBnClickedBtnSelectdst();
private:
	CString SelectFolder();
	std::map<unsigned _int64, struct _stat64>FileInfoLst;
	void getFileInfo(map<unsigned _int64, struct _stat64> &FileInfoLst, CString & srcPath);
	unsigned __int64 calculateFile(const char * fileName, struct _stat64 &fileInfo);
public:
	CListCtrl m_lstFileInfo;
	afx_msg void OnBnClickedBtnFindDuplicate();
};
