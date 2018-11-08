
// XiaoMiPhoneDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "XiaoMiPhone.h"
#include "XiaoMiPhoneDlg.h"
#include "afxdialogex.h"
#include "Login.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	
END_MESSAGE_MAP()


// CXiaoMiPhoneDlg �Ի���



CXiaoMiPhoneDlg::CXiaoMiPhoneDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CXiaoMiPhoneDlg::IDD, pParent)
	, m_strIMEI(_T(""))
	, m_strIMEIFilePath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hThread = NULL;
}

void CXiaoMiPhoneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_IMEI, m_strIMEI);
	DDX_Control(pDX, IDC_LIST_DATA, m_ListCtrl);
	DDX_Text(pDX, IDC_EDIT_FILEPATH, m_strIMEIFilePath);
	DDX_Control(pDX, IDC_BTN_EXEC, m_BtnExec);
}

BEGIN_MESSAGE_MAP(CXiaoMiPhoneDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()	
	ON_BN_CLICKED(IDC_BTN_LOADFILE, &CXiaoMiPhoneDlg::OnBnClickedBtnLoadfile)
	ON_BN_CLICKED(IDC_SET, &CXiaoMiPhoneDlg::OnBnClickedSet)
	ON_BN_CLICKED(IDC_BTN_EXEC, &CXiaoMiPhoneDlg::OnBnClickedBtnExec)
	ON_BN_CLICKED(ID_BTN_WRITEFILE, &CXiaoMiPhoneDlg::OnBnClickedBtnWritefile)
	ON_BN_CLICKED(IDCANCEL, &CXiaoMiPhoneDlg::OnBnClickedCancel)
	ON_WM_LBUTTONUP()
	ON_MESSAGE(WM_SHOWGETRES, ShowEMSIMsg)
END_MESSAGE_MAP()


// CXiaoMiPhoneDlg ��Ϣ�������

BOOL CXiaoMiPhoneDlg::OnInitDialog()
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	m_ListCtrl.InsertColumn(0, _T("EMSI"), LVCFMT_LEFT, 165);
    m_ListCtrl.InsertColumn(1, _T("goods_name"), LVCFMT_LEFT, 265);
	m_ListCtrl.InsertColumn(2, _T("country_text"), LVCFMT_LEFT, 100);
	m_ListCtrl.InsertColumn(3, _T("add_time"), LVCFMT_LEFT, 100);
	
	//
	write_dword();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CXiaoMiPhoneDlg::OnReadExcelData(void* ptr)
{
	CXiaoMiPhoneDlg* pThis = (CXiaoMiPhoneDlg*)ptr;
	while(true)
	{
		pThis->ReadCSVData();
		Sleep(3*1000);
	}
}
void CXiaoMiPhoneDlg::ReadCSVData()
{
	CString strPath = GetDirPathCS();
	CString strFilePath = strPath + _T("\\xiaomi_phone.ini");
	CString strStopFile = strPath + _T("\\stop.ini");
	CString strErrorMsg = GetValueString(_T("taskrtn"),_T("msg"),_T(""),1024,strFilePath);		

	CString strExcelFile = GetValueString(_T("taskrtn"),_T("filename"),_T(""),1024,strFilePath);
	strExcelFile = strPath + _T("\\") +strExcelFile;
	//string sFile = ;

	if(strExcelFile != _T(""))
	{
		m_strArray.clear();
		ifstream inFile(strExcelFile.GetBuffer(0), ios::in);
		string lineStr;
		
		while (getline(inFile, lineStr))
		{
			// ��ɶ�ά��ṹ
			stringstream ss(lineStr);
			string str;
			vector<CString> lineArray;
			// ���ն��ŷָ�
			while (getline(ss, str, ','))
			{
				CString strW = (CString)str.c_str();
				lineArray.push_back(strW);
			}
			m_strArray.push_back(lineArray);
		}
	}

	PostMessage(WM_SHOWGETRES,0,0);
	CString strStop = GetValueString(_T("task"),_T("stop"),_T("0"),1024,strStopFile);

	if(strErrorMsg.Find(_T("ֹͣ����")) != -1 || (strStop == _T("1")))
	{
		m_BtnExec.SetWindowText(_T("��ʼ����"));
		::WritePrivateProfileString(_T("task"), _T("stop"), _T("1"), strStopFile);
		::WritePrivateProfileString(_T("taskrtn"), _T("msg"), _T(""), strFilePath);
		if(m_hThread)
		{
			TerminateThread(m_hThread,0);
			m_hThread = NULL;
		}
		MessageBox(strErrorMsg);
	}
}
void CXiaoMiPhoneDlg::ReadExcelData()
{
	CString strPath = GetDirPathCS();
	CString strFilePath = strPath + _T("\\xiaomi_phone.ini");
	CString strStopFile = strPath + _T("\\stop.ini");
	CString strErrorMsg = GetValueString(_T("taskrtn"),_T("msg"),_T(""),1024,strFilePath);
	if(strErrorMsg != _T(""))
	{
		MessageBox(strErrorMsg);
		
		//m_BtnExec.SetWindowText(_T("��ʼ����"));
		::WritePrivateProfileString(_T("task"), _T("stop"), _T("1"), strStopFile);
		::WritePrivateProfileString(_T("taskrtn"), _T("msg"), _T(""), strFilePath);
		/*if(m_hThread)
		{
			TerminateThread(m_hThread,0);
			m_hThread = NULL;
		}*/
	}

	CString strExcelFile = GetValueString(_T("taskrtn"),_T("filename"),_T(""),1024,strFilePath);
	strExcelFile = strPath + _T("\\") +strExcelFile;
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CoInitialize(NULL);
	AfxEnableControlContainer();
	
	if(strExcelFile != _T(""))
	{
		CApplication app;	//Excel����
		CWorkbooks books;	//����������
		CWorkbook book;		//������
		CWorksheets sheets;	//�������� 
		CWorksheet sheet;	//������
		CRange range;		//ʹ������
 
		COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);  
		if (!app.CreateDispatch(_T("Excel.Application")))  
		{  
			MessageBox(_T("Error!Creat Excel Application Server Fail!"));  
			exit(1);  
		}  
 
		books.AttachDispatch(app.get_Workbooks(),true); 
		book.AttachDispatch(books.Add(_variant_t(strExcelFile)));//��ȡѡ���Excel�ļ�
		sheets.AttachDispatch(book.get_Worksheets(),true);//��ȡ�ļ��е�����sheet
		sheet.AttachDispatch(sheets.get_Item(_variant_t("Sheet")),true);//��ȡsheet1����	
 
		CString str;
		bool bExit = false;
		for(int irow=2;!bExit;irow++)
		{
			CString strEMSI = _T("");
			STPHONE_MSG phoneMsg;
			for(int icolumn=1;icolumn<5;icolumn++)
			{
				range.AttachDispatch(sheet.get_Cells(),true);//��ȡsheet1���еĵ�Ԫ�����õ�ǰ����ΪA1
				range.AttachDispatch(range.get_Item (COleVariant((long)irow),COleVariant((long)icolumn)).pdispVal);//��ȡ��Ԫ��
				switch(icolumn)
				{
				case 1: strEMSI = range.get_Value2(); 
						if(strEMSI.IsEmpty())
						{
							bExit = true; 
							break;
						}
						
						break;
				case 2: 
					{
						phoneMsg.strName = range.get_Value2();						
					}
						break;
				case 3: 
					{
						phoneMsg.strCounty = range.get_Value2();						
					}
						break;
				case 4: 
					{
						phoneMsg.strAddTime = range.get_Value2();						
					}
						break;
				
				default: ;
				}
				if(bExit)
				{
					break;
				}
			}

			m_mapEmsiMsg[strEMSI] = phoneMsg;
		}
 
		range.ReleaseDispatch();//�ͷŶ���
		sheet.ReleaseDispatch();
		sheets.ReleaseDispatch();
		book.ReleaseDispatch();  
		books.ReleaseDispatch();    
		app.ReleaseDispatch(); 
		app.Quit();//�˳�Excel����
	}

	PostMessage(WM_SHOWGETRES,0,0);

}
void CXiaoMiPhoneDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CXiaoMiPhoneDlg::OnPaint()
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
HCURSOR CXiaoMiPhoneDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CXiaoMiPhoneDlg::OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CXiaoMiPhoneDlg::OnBnClickedBtnLoadfile()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
 
    CFileDialog    dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Describe Files (*.csv)|*.csv|All Files (*.*)|*.*||"), NULL);
 
    if (dlgFile.DoModal())
    {
        m_strIMEIFilePath = dlgFile.GetPathName();
    }
	UpdateData(false);
    return ;
}


void CXiaoMiPhoneDlg::OnBnClickedSet()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CLogin login;
	login.DoModal();
}


void CXiaoMiPhoneDlg::OnBnClickedBtnExec()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString strPath = GetDirPathCS();
	CString strFilePath = strPath + _T("\\xiaomi_phone.ini");
	CString strStopFile = strPath + _T("\\stop.ini");

	UpdateData(true);	

	CString strType = _T("");
	if(m_strIMEI != _T(""))
	{
		strType = _T("1");
		::WritePrivateProfileString(_T("task"), _T("emsi"), m_strIMEI, strFilePath);
	}
	else if(m_strIMEIFilePath != _T(""))
	{
		strType = _T("0");
		::WritePrivateProfileString(_T("task"), _T("filename"), m_strIMEIFilePath, strFilePath);
	}
	else
	{
		MessageBox(_T("����дIMEI��S/N�����ѡ�������ļ���"),_T("����"));
		return;
	}
	::WritePrivateProfileString(_T("task"), _T("tasktype"), strType, strFilePath);

	CString strText = _T("");
	m_BtnExec.GetWindowText(strText);
	if(strText == _T("��ʼ����"))
	{
		m_BtnExec.SetWindowText(_T("ֹͣ����"));
		::WritePrivateProfileString(_T("task"), _T("stop"), _T("0"), strStopFile);
		if(m_hThread == NULL)
			m_hThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)OnReadExcelData, this, 0, 0);
	}
	else
	{
		if(m_hThread)
		{
			TerminateThread(m_hThread,0);
			m_hThread = NULL;
		}
		m_BtnExec.SetWindowText(_T("��ʼ����"));
		::WritePrivateProfileString(_T("task"), _T("stop"), _T("1"), strStopFile);
		return ;
	}
	/*TCHAR ssss[1024];
	int nSize = ::GetPrivateProfileSection(_T("yundama"), ssss, 65535,strFilePath);
	nSize = ::GetPrivateProfileSection(_T("yundama"), ssss, 65535,strFilePath);
	nSize = ::GetPrivateProfileSection(_T("yundama"), ssss, 65535,strFilePath);*/

	

	CString strCmdline = _T("");
    strCmdline.Format(_T("%s\\%s"), strPath, _T("\\xiaomi_phone.exe"));

	STARTUPINFO si = { sizeof(si) };
    si.wShowWindow = SW_SHOW;
    si.dwFlags = STARTF_USESHOWWINDOW;
    PROCESS_INFORMATION pi;    

   BOOL bCreateProcess = ::CreateProcess(NULL, strCmdline.GetBuffer(0), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
}


void CXiaoMiPhoneDlg::OnBnClickedBtnWritefile()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString strPath = GetDirPathCS();
	CString strPath2 = strPath + _T("\\xiaomi_phone.ini");
	CString strExcelFile = GetValueString(_T("taskrtn"),_T("filename"),_T(""),1024,strPath2);
	CString strFilePath = _T("�ѵ������� ")+strPath + strExcelFile;
	MessageBox(strFilePath,_T("�����ɹ�"));
	
}


void CXiaoMiPhoneDlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}

CString CXiaoMiPhoneDlg::GetValueString(LPCTSTR lpszSectionName, LPCTSTR lpszKey, LPCTSTR lpszDefault, INT nValueSize,CString strIniFilePath)
{	
	CString strRet;
	::GetPrivateProfileString(lpszSectionName, lpszKey, lpszDefault, strRet.GetBufferSetLength(nValueSize),nValueSize, strIniFilePath);
	return strRet;
}

void CXiaoMiPhoneDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnLButtonUp(nFlags, point);
}
LRESULT CXiaoMiPhoneDlg::ShowEMSIMsg(WPARAM wParam, LPARAM lParam)
{
	m_ListCtrl.DeleteAllItems();
	auto itBegin = m_mapEmsiMsg.begin();
	auto itEnd = m_mapEmsiMsg.end();
	int i = 0;
	int nSize = m_strArray.size();
	for(int i = 0;i < nSize;i++)
	{		
		int nSizeColumn = m_strArray[i].size();
		for(int j = 0;j < nSizeColumn;j++)
		{
			if(j == 0)
			{
				m_ListCtrl.InsertItem(i,m_strArray[i][j],i);
			}
			else
			{
				m_ListCtrl.SetItemText(i,j,m_strArray[i][j]);
			}		
		}
	}
	return 0;
}

void CXiaoMiPhoneDlg::write_dword()//��\Software\\Chicony\\Lenovo1�ļ�����д��һ��test111���Ӽ�������������ΪName����ֵΪ6  
{  
	return;
    HKEY hkey;//�����йص�hkey���ڲ�ѯ����ʱҪ�ر�  
    HKEY hTempKey;  
      
    DWORD dwValue = 6;  
    DWORD dwSize = sizeof(DWORD);  
    DWORD dwType = REG_DWORD;  
  
    LPCTSTR data_set= _T("Software\\XiaoMiPhone\\Level");  
    if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_CURRENT_USER, data_set, 0, KEY_SET_VALUE, &hkey))  
    {  
        if (ERROR_SUCCESS == ::RegCreateKey(hkey, _T("stop"), &hTempKey))  
        {  
            if (ERROR_SUCCESS != ::RegSetValueEx(hTempKey, _T("Name"), 0, REG_DWORD, (CONST BYTE*)&dwValue, sizeof(DWORD)))  
            {  
                int i = 0;
				i =i + 1;
            }  
        }  
    }  
    ::RegCloseKey(hkey);  
} 