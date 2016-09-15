
// SystemProtectDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "time.h"
#include <sys/types.h>
#include <sys/stat.h>
#include "map"
#include "vector"
using namespace std;


// CSystemProtectDlg 对话框
class CSystemProtectDlg : public CDialogEx
{
// 构造
public:
	CSystemProtectDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SYSTEMPROTECT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持



// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
