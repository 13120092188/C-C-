
// MFCFileCompress.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFCFileCompressApp: 
// �йش����ʵ�֣������ MFCFileCompress.cpp
//

class CMFCFileCompressApp : public CWinApp
{
public:
	CMFCFileCompressApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFCFileCompressApp theApp;