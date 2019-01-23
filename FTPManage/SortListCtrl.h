#ifndef SORTLISTCTRL_H
#define SORTLISTCTRL_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef SORTHEADERCTRL_H
	#include "SortHeaderCtrl.h"
#endif	// SORTHEADERCTRL_H

#ifdef _DEBUG
	#define ASSERT_VALID_STRING( str ) ASSERT( !IsBadStringPtr( str, 0xfffff ) )
#else	//	_DEBUG
	#define ASSERT_VALID_STRING( str ) ( (void)0 )
#endif	//	_DEBUG

#include <afxinet.h>

class CSortListCtrl : public CListCtrl
{
// Construction
public:
	CSortListCtrl();
	CString m_BaseDir;					//基目录
	CString m_CurDir;					//记录当前列表中文件的目录
	int     m_nListType;				//列表类型,0表示显示本地信息，1，表示显示FTP服务器信息,默认为0
	CInternetSession m_Session;			//Internet会话
	CString m_FtpServer,m_Port,m_User,m_Password;	//FTP服务器，端口号，用户名和密码
	CSortHeaderCtrl m_ctlHeader;		//列头
	int m_nNumColumns;					//列数
	int m_nSortColumn;					//排序列
	BOOL m_bAscend;						//是否升序排列
//	CImageList m_Images;
// Attributes
public:

// Operations
public:
	BOOL SetColumns( UINT uiStringID );
	BOOL SetColumns( const CString& strHeadings );

	int AddItem( LPCTSTR pszText, ... );
	BOOL DeleteItem( int iItem );
	BOOL DeleteAllItems();
	BOOL SetItemText( int nItem, int nSubItem, LPCTSTR lpszText );
	void Sort( int iColumn, BOOL bAscending );
	BOOL SetItemData(int nItem, DWORD dwData);
	DWORD GetItemData(int nItem) const;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSortListCtrl)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	HICON GetIconFromExtendedName(LPCTSTR lpName);
	void DisplayPath(LPCTSTR lpPath,CFtpConnection* pTemp = NULL);
	virtual ~CSortListCtrl();

	// Generated message map functions
protected:
	void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	void OnKeydown(NMHDR* pNMHDR, LRESULT* pResult);

	static int CALLBACK SortFunction( LPARAM lParam1, LPARAM lParam2, LPARAM lParamData );

	void FreeData( const int nItem );
	//设置项目数据列表
	BOOL CSortListCtrl::SetItemDataList( int iItem, LPTSTR* pchTexts );
	LPTSTR* CSortListCtrl::GetItemDataList( int iItem ) const;


	//{{AFX_MSG(CSortListCtrl)
	afx_msg void OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // SORTLISTCTRL_H
