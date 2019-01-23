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
	CString m_BaseDir;					//��Ŀ¼
	CString m_CurDir;					//��¼��ǰ�б����ļ���Ŀ¼
	int     m_nListType;				//�б�����,0��ʾ��ʾ������Ϣ��1����ʾ��ʾFTP��������Ϣ,Ĭ��Ϊ0
	CInternetSession m_Session;			//Internet�Ự
	CString m_FtpServer,m_Port,m_User,m_Password;	//FTP���������˿ںţ��û���������
	CSortHeaderCtrl m_ctlHeader;		//��ͷ
	int m_nNumColumns;					//����
	int m_nSortColumn;					//������
	BOOL m_bAscend;						//�Ƿ���������
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
	//������Ŀ�����б�
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
