
// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// XiaoMiPhone.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"

CString GetDirPathCS()
{
	WCHAR szPath[1024] = { 0 };
	GetModuleFileName(NULL, szPath, 1024);
	WCHAR *p = wcsrchr(szPath, _T('\\'));
	*p = 0;
	return szPath;
}
