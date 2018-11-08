
// stdafx.cpp : 只包括标准包含文件的源文件
// XiaoMiPhone.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

CString GetDirPathCS()
{
	WCHAR szPath[1024] = { 0 };
	GetModuleFileName(NULL, szPath, 1024);
	WCHAR *p = wcsrchr(szPath, _T('\\'));
	*p = 0;
	return szPath;
}
