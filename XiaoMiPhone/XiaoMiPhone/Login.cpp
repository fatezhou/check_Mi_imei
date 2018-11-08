// Login.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "XiaoMiPhone.h"
#include "Login.h"
#include "afxdialogex.h"


// CLogin �Ի���

IMPLEMENT_DYNAMIC(CLogin, CDialogEx)

CLogin::CLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLogin::IDD, pParent)
	, m_strUser(_T(""))
	, m_strPwd(_T(""))
{

}

CLogin::~CLogin()
{
}

void CLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_USER, m_strUser);
	DDX_Text(pDX, IDC_EDIT_PWD, m_strPwd);
}


BEGIN_MESSAGE_MAP(CLogin, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLogin::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CLogin::OnBnClickedCancel)
END_MESSAGE_MAP()


// CLogin ��Ϣ�������


void CLogin::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	CString strPath = GetDirPathCS();
	CString strFilePath = strPath + _T("\\xiaomi_phone.ini");
	::WritePrivateProfileString(_T("yundama"), _T("user"), m_strUser, strFilePath);
	::WritePrivateProfileString(_T("yundama"), _T("pwd"), m_strPwd, strFilePath);
	CDialogEx::OnOK();
}


void CLogin::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
