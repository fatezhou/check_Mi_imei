
// XiaoMiPhoneDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include<map>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

struct STPHONE_MSG
{
	CString strName;
	CString strCounty;
	CString strAddTime;
	STPHONE_MSG()
	{
		strName = _T("");
		strCounty = _T("");
		strAddTime = _T("");
	}
};
#define WM_SHOWGETRES WM_USER+1
// CXiaoMiPhoneDlg �Ի���
class CXiaoMiPhoneDlg : public CDialogEx
{
// ����
public:
	CXiaoMiPhoneDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_XIAOMIPHONE_DIALOG };

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
	afx_msg LRESULT ShowEMSIMsg(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnLoadfile();
	afx_msg void OnBnClickedSet();
	afx_msg void OnBnClickedBtnExec();
	afx_msg void OnBnClickedBtnWritefile();
	afx_msg void OnBnClickedCancel();
	CString GetValueString(LPCTSTR lpszSectionName, LPCTSTR lpszKey, LPCTSTR lpszDefault, INT nValueSize,CString strIniFilePath);
	static void OnReadExcelData(void* ptr);
	void ReadExcelData();
	void ReadCSVData();
	void write_dword();
	
	CString m_strIMEI;
	CListCtrl m_ListCtrl;
	HANDLE m_hThread;
	CString m_strIMEIFilePath;	
	CButton m_BtnExec;

	map<CString ,STPHONE_MSG> m_mapEmsiMsg;
	vector<vector<CString>> m_strArray;
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
