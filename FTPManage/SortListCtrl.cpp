#include "stdafx.h"
#include "SortListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


LPCTSTR g_pszSection = _T("ListCtrls");


class CItemData
{
public:
	CItemData()
	{
		m_ColumnTexts = NULL;
		m_dwData = 0;
	}
	LPTSTR* m_ColumnTexts;	//记录当前行所有列文本
	DWORD	m_dwData;		//视图项数据

private:
	//禁止复制
	CItemData( const CItemData& );
	CItemData& operator=( const CItemData& );
};


CSortListCtrl::CSortListCtrl()
{
	m_BaseDir = m_CurDir = "";
	m_nListType = 0;
	m_nNumColumns = 0;
	m_nSortColumn = -1;
	m_bAscend = FALSE;

}


CSortListCtrl::~CSortListCtrl()
{
}


BEGIN_MESSAGE_MAP(CSortListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CSortListCtrl)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnClick)
	ON_WM_DESTROY()
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_NOTIFY_REFLECT(LVN_KEYDOWN, OnKeydown)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSortListCtrl message handlers

void CSortListCtrl::PreSubclassWindow()
{
	// the list control must have the report style.
	ASSERT( GetStyle() & LVS_REPORT );

	CListCtrl::PreSubclassWindow();
	VERIFY( m_ctlHeader.SubclassWindow( GetHeaderCtrl()->GetSafeHwnd() ) );
}


BOOL CSortListCtrl::SetColumns( UINT uiStringID )
{
	CString strHeadings;
	VERIFY( strHeadings.LoadString( uiStringID ) );
	return SetColumns( strHeadings );
}

//设置列，格式为文本,宽度; 文本,宽度; ......
BOOL CSortListCtrl::SetColumns( const CString& strHeadings )
{
	int nStart = 0;
	for( ;; )
	{
		int nComma = strHeadings.Find( _T(','), nStart );	
		if( nComma == -1 )
			break;
		//获取文本
		CString strHeading = strHeadings.Mid( nStart, nComma - nStart );

		nStart = nComma + 1;	//掠过“,”

		int nSemiColon = strHeadings.Find( _T(';'), nStart );

		if( nSemiColon == -1 )
			nSemiColon = strHeadings.GetLength();

		int nWidth = atoi( strHeadings.Mid( nStart, nSemiColon - nStart ) );	//获取宽度
		
		nStart = nSemiColon + 1;			//指向下一列信息
		
		if( InsertColumn( m_nNumColumns++, strHeading, LVCFMT_LEFT, nWidth ) == -1 )
			return FALSE;					//插入列
	}

	return TRUE;
}


int CSortListCtrl::AddItem( LPCTSTR pszText, ... )
{
	//添加行，返回行索引
	int nIndex = InsertItem( GetItemCount(), pszText );
	//记录各列文本
	LPTSTR* pszColumnTexts = new LPTSTR[ m_nNumColumns ];
	pszColumnTexts[ 0 ] = new TCHAR[ lstrlen( pszText ) + 1 ];
	lstrcpy( pszColumnTexts[ 0 ], pszText );
 	va_list list;
	va_start( list, pszText );
	//设置列文本
	for( int nColumn = 1; nColumn < m_nNumColumns; nColumn++ )
	{
		pszText = va_arg( list, LPCTSTR );
		CListCtrl::SetItem( nIndex, nColumn, LVIF_TEXT, pszText, 0, 0, 0, 0 );

		pszColumnTexts[ nColumn ] = new TCHAR[ lstrlen( pszText ) + 1 ];
		lstrcpy( pszColumnTexts[ nColumn ], pszText );
	}
	va_end( list );
	SetItemDataList( nIndex, pszColumnTexts );
	return nIndex;
}


void CSortListCtrl::FreeData( const int nItem )
{
	CItemData* pItemData = ( CItemData* )CListCtrl::GetItemData( nItem  );
	LPTSTR* pcsTexts = pItemData->m_ColumnTexts;

	for( int i = 0; i < m_nNumColumns; i++ )
		delete[] pcsTexts[ i ];

	delete[] pcsTexts;
	delete pItemData;

	VERIFY( CListCtrl::SetItemData( nItem , NULL ) );
}


BOOL CSortListCtrl::DeleteItem( int iItem )
{
	FreeData( iItem );
	return CListCtrl::DeleteItem( iItem );
}


BOOL CSortListCtrl::DeleteAllItems()
{
	for( int iItem = 0; iItem < GetItemCount(); iItem ++ )
		FreeData( iItem );

	return CListCtrl::DeleteAllItems();
}

//判断文本是否为数据
bool IsNumber( LPCTSTR pszText )
{
	for( int i = 0; i < lstrlen( pszText ); i++ )
		if( !_istdigit( pszText[ i ] ) )
			return false;
	return true;
}


int CompareDataAsNumber( LPCTSTR pszParam1, LPCTSTR pszParam2 )
{
	int nNumber1 = atoi( pszParam1 );
	int nNumber2 = atoi( pszParam2 );
	return nNumber1 - nNumber2;
}

//判断是否为日期
bool IsDate( LPCTSTR pszText )
{
	//格式为0000-00-00
	if( lstrlen( pszText ) < 10 )
		return false;
	return _istdigit( pszText[ 0 ] )
		&& _istdigit( pszText[ 1 ] )
		&& _istdigit( pszText[ 2 ] )
		&& _istdigit( pszText[ 3 ] )
		&& pszText[ 4 ] == _T('-')
		&& _istdigit( pszText[ 5 ] )
		&& _istdigit( pszText[ 6 ] )
		&& pszText[ 7 ] == _T('-')
		&& _istdigit( pszText[ 8 ] )
		&& _istdigit( pszText[ 9 ] );
}

//按日期比较数据
int CompareDataAsDate( const CString& strDate1, const CString& strDate2 )
{
	//先比较年
	int nYear1 = atoi( strDate1.Mid(0, 4 ) );
	int nYear2 = atoi( strDate2.Mid(0, 4 ) );
	if (nYear1 != nYear2)
	{
		return nYear1 - nYear2;
	}
	//比较月
	int nMonth1 = atoi( strDate1.Mid( 5, 2 ) );
	int nMonth2 = atoi( strDate2.Mid( 5, 2 ) );
	if( nMonth1 != nMonth2 )
	{
		return nMonth1 = nMonth2;	
	}
	//比较日
	int nDay1 = atoi( strDate1.Mid( 8, 2 ) );
	int nDay2 = atoi( strDate2.Mid( 8, 2 ) );
	
	if( nDay1 !=  nDay2 )
	{
		return nDay1 - nDay2;
	}
	return 0;		//日期相等，返回0
}


int CALLBACK CSortListCtrl::SortFunction( LPARAM lParam1, LPARAM lParam2, LPARAM lParamData )
{
	CSortListCtrl* pListCtrl = ( CSortListCtrl* )( lParamData );

	CItemData* pParam1 = ( CItemData* )( lParam1 );
	CItemData* pParam2 = ( CItemData* )( lParam2 ); 

	//获取排序列的文本
	LPCTSTR pszText1 = pParam1->m_ColumnTexts[ pListCtrl->m_nSortColumn ];
	LPCTSTR pszText2 = pParam2->m_ColumnTexts[ pListCtrl->m_nSortColumn ];

	if( IsNumber( pszText1 ) )	//按数值比较
		return pListCtrl->m_bAscend ? CompareDataAsNumber( pszText1, pszText2 ) : CompareDataAsNumber( pszText2, pszText1 );
	else if( IsDate( pszText1 ) )	//按日期比较
		return pListCtrl->m_bAscend ? CompareDataAsDate( pszText1, pszText2 ) : CompareDataAsDate( pszText2, pszText1 );
	else						//按文本比较
		return pListCtrl->m_bAscend ? lstrcmp( pszText1, pszText2 ) : lstrcmp( pszText2, pszText1 );
}


void CSortListCtrl::OnColumnClick( NMHDR* pNMHDR, LRESULT* pResult )
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nColumn = pNMListView->iSubItem;
	Sort( nColumn, nColumn == m_nSortColumn ? !m_bAscend : TRUE );
	*pResult = 0;
}


void CSortListCtrl::Sort( int iColumn, BOOL bAscending )
{
	m_nSortColumn = iColumn;
	m_bAscend = bAscending;

	m_ctlHeader.SetSortColomn( m_nSortColumn, m_bAscend );
	SortItems( SortFunction, (DWORD)this );
}

void CSortListCtrl::OnDestroy() 
{
	for( int iItem = 0; iItem < GetItemCount(); iItem ++ )
		FreeData( iItem );
	CListCtrl::OnDestroy();
}


BOOL CSortListCtrl::SetItemText( int nItem, int nSubItem, LPCTSTR lpszText )
{
	if( !CListCtrl::SetItemText( nItem, nSubItem, lpszText ) )
		return FALSE;

	//获取行各列文本
	LPTSTR* pszTexts = GetItemDataList( nItem );
	LPTSTR pszText = pszTexts[ nSubItem ];
	delete[] pszText;
	pszText = new TCHAR[ lstrlen( lpszText ) + 1 ];
	lstrcpy( pszText, lpszText );
	pszTexts[ nSubItem ] = pszText;
	return TRUE;
}



BOOL CSortListCtrl::SetItemData( int nItem, DWORD dwData )
{
	if( nItem >= GetItemCount() )
		return FALSE;
	CItemData* pItem= (CItemData*)CListCtrl::GetItemData( nItem ) ;
	pItem->m_dwData = dwData;
	return TRUE;
}


DWORD CSortListCtrl::GetItemData( int nItem ) const
{
	ASSERT( nItem < GetItemCount() );
	CItemData* pItem = (CItemData*)( CListCtrl::GetItemData( nItem ) );
	return pItem->m_dwData;
}



BOOL CSortListCtrl::SetItemDataList( int iItem, LPTSTR* pchTexts )
{
	if (CListCtrl::GetItemData( iItem ) == NULL )
	{
		CItemData* pItemData = new CItemData();
		pItemData->m_ColumnTexts = pchTexts;
		//设置项目数据
		return CListCtrl::SetItemData( iItem,  (DWORD)pItemData);
	}
}


LPTSTR* CSortListCtrl::GetItemDataList( int iItem ) const
{
	ASSERT( iItem < GetItemCount() );

	CItemData* pItemData = ( CItemData* )CListCtrl::GetItemData( iItem ) ;
	return pItemData->m_ColumnTexts;
}


void CSortListCtrl::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int nItem = GetSelectionMark();
	if (nItem != -1)
	{
		if (m_nListType==0)	//进入本地系统子目录
		{
			//判断是否为目录
			int nFlag =GetItemData(nItem);
			if (nFlag==1)	
			{
				//获取完整的目录信息
				CString csFoder = GetItemText(nItem,0);
				csFoder += "\\";
				//获取目录
				 m_CurDir += csFoder;
				 DisplayPath(m_CurDir);
			}
		}
		else	//进入FTP服务器子目录
		{
			//判断是否为目录
			int nFlag =GetItemData(nItem);
			if (nFlag==1)	
			{
				//获取完整的目录信息
				CString csFoder = GetItemText(nItem,0);
				csFoder += "/";
				//获取目录
				m_CurDir += csFoder;
				DisplayPath(m_CurDir);
			}			
		
		}
	
	}
	*pResult = 0;
}

void CSortListCtrl::DisplayPath(LPCTSTR lpPath,CFtpConnection* pTemp)
{
	DeleteAllItems();
	if (m_nListType==0)	//本地信息
	{
		BOOL bFind;
		CFileFind flFind;
		CString csPath = lpPath;
		m_CurDir = lpPath;
		if ( csPath.Right(1) != "\\" )
		{
			csPath += "\\";
			m_CurDir +="\\";
		}
		csPath += "*.*";

		bFind = flFind.FindFile(csPath);
		CString csText,csFileSize,csDataTime;
		//设置列表当前显示的目录
		while ( bFind )
		{
			
			bFind = flFind.FindNextFile();
			if ( !flFind.IsDots() && !flFind.IsHidden())
			{		

				__int64 lFileLen = flFind.GetLength();
				
				if (flFind.IsDirectory())
				{
					csFileSize = "文件夹";
				}
				else
				{
					double fGB = lFileLen /(double)(1024*1024*1024);
					if (fGB < 1)
					{
						double fMB = lFileLen / (double)(1024*1024);
						if (fMB < 1)
						{
							double fBK = lFileLen / (double)(1024);
							if (fBK >1)
							{
								csFileSize.Format("%2.2f KB",fBK);
							}
							else
							{
								csFileSize.Format("%i B",lFileLen);
							}
						}
						else
						{
							csFileSize.Format("%2.2f MB",fMB);
						}
					}
					else
					{
						csFileSize.Format("%2.2f GB",fGB);
					}
				}
				
				csText = flFind.GetFileName();
				CTime time;
				flFind.GetCreationTime(time);
				csDataTime = time.Format("%Y-%m-%d %H:%M");
				int nItem = AddItem(csText,csFileSize,csDataTime);

				//设置文件显示的图标
				SHFILEINFO shInfo;
				int nIcon = 0;
				
				SHGetFileInfo(flFind.GetFilePath(),0,&shInfo,sizeof(shInfo),SHGFI_ICON | SHGFI_SMALLICON );
				DestroyIcon(shInfo.hIcon);
				nIcon = shInfo.iIcon;
				SetItem(nItem,0,LVIF_IMAGE,"",nIcon,0,0,0);
				 //设置项目标记,0表示文件，1表示目录
				if (flFind.IsDirectory())
				{
					SetItemData(nItem,1);
				}
				else
				{
					SetItemData(nItem,0);
				}
				nItem++;
			}
		}
	}
	else		//显示FTP服务器信息
	{
		CFtpConnection* pFTP = NULL;

		pFTP = m_Session.GetFtpConnection(m_FtpServer,m_User,m_Password,atoi(m_Port));
		pFTP->SetCurrentDirectory("");
		CFtpFileFind Find(pFTP);
		
		BOOL bFind;

		m_CurDir =lpPath;
		if (strlen(lpPath)==0)
			bFind = Find.FindFile(NULL,INTERNET_FLAG_EXISTING_CONNECT|INTERNET_FLAG_RELOAD);
		else
			bFind = Find.FindFile(lpPath,INTERNET_FLAG_EXISTING_CONNECT|INTERNET_FLAG_RELOAD);
		
		if (bFind)
		{
			CString csFileName,csDataTime,csFileSize;
			while (bFind )
			{
				bFind = Find.FindNextFile();
				csFileName = Find.GetFileName();

				CTime fileTime;
				Find.GetLastWriteTime(fileTime);

				csDataTime = fileTime.Format("%Y-%m-%d %H:%M");
				if ( !Find.IsDots() && !Find.IsHidden())
				{		

					__int64 lFileLen = Find.GetLength();
					
					if (Find.IsDirectory())
					{
						csFileSize = "文件夹";
					}
					else
					{
						double fGB = lFileLen /(double)(1024*1024*1024);
						if (fGB < 1)
						{
							double fMB = lFileLen / (double)(1024*1024);
							if (fMB < 1)
							{
								double fBK = lFileLen / (double)(1024);
								if (fBK >1)
								{
									csFileSize.Format("%2.2f KB",fBK);
								}
								else
								{
									csFileSize.Format("%i B",lFileLen);
								}
							}
							else
							{
								csFileSize.Format("%2.2f MB",fMB);
							}
						}
						else
						{
							csFileSize.Format("%2.2f GB",fGB);
						}
					}
				}

				int nItem = AddItem(csFileName,csFileSize,csDataTime);

				//设置文件显示的图标
				SHFILEINFO shInfo;
				int nIcon = 0;
				CString csName = Find.GetFileName();
				int nPos = csName.ReverseFind('.');
				if (nPos >0)
				{
					SHGetFileInfo(csName ,FILE_ATTRIBUTE_NORMAL,&shInfo,sizeof(shInfo),SHGFI_ICON | SHGFI_SMALLICON|SHGFI_USEFILEATTRIBUTES );
				}
				else
				{
					char chPath[MAX_PATH] = {0};
					GetCurrentDirectory(MAX_PATH,chPath);
					SHGetFileInfo(chPath,FILE_ATTRIBUTE_NORMAL,&shInfo,sizeof(shInfo),SHGFI_ICON | SHGFI_SMALLICON  );		
				}
				DestroyIcon(shInfo.hIcon);
				nIcon = shInfo.iIcon;
				SetItem(nItem,0,LVIF_IMAGE,"",nIcon,0,0,0);
				 //设置项目标记,0表示文件，1表示目录
				if (Find.IsDirectory())
				{
					SetItemData(nItem,1);
				}
				else
				{
					SetItemData(nItem,0);
				}
			}
		}
		Find.Close();
		pFTP->Close();
		delete pFTP;
	}
}

void CSortListCtrl::OnKeydown(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	if (pLVKeyDow->wVKey==VK_BACK)	//返回上一级目录
	{
		if (m_nListType == 0)
		{
			if (m_BaseDir != m_CurDir && m_BaseDir != "")
			{
				if ( m_CurDir.Right(1) == "\\" )
				{
					//去除"\\"
					m_CurDir = m_CurDir.Left(m_CurDir.GetLength()-1);
				}
				int nPos = m_CurDir.ReverseFind('\\');
				m_CurDir = m_CurDir.Left(nPos);
			}
		}
		else
		{
			CString csTmpDir = m_CurDir;
			CString csTmpBase = m_BaseDir;
			//去除字符串两端的/
			if (csTmpDir.Right(1)=="/")
				csTmpDir = csTmpDir.Left(csTmpDir.GetLength()-1);
			if(csTmpDir.Left(1)=="/")
				csTmpDir = csTmpDir.Mid(1);

			if (csTmpBase.Right(1)=="/")
				csTmpBase = csTmpBase.Left(csTmpBase.GetLength()-1);
			if(csTmpBase.Left(1)=="/")
				csTmpBase = csTmpBase.Mid(1);			

			if (csTmpBase == csTmpDir )
			{
				return;
			}

			if (m_CurDir != "")
			{
				if ( m_CurDir.Right(1) == "/" )
				{
					//去除"\\"
					m_CurDir = m_CurDir.Left(m_CurDir.GetLength()-1);
				}
				int nPos = m_CurDir.ReverseFind('/');
				if (nPos != -1)
					m_CurDir = m_CurDir.Left(nPos) + '/';
				else
					m_CurDir = "";
			}
		
		}
		DisplayPath(m_CurDir);

	}
	*pResult = 0;
}

//根据文件类型获取图标
HICON CSortListCtrl::GetIconFromExtendedName(LPCTSTR lpName)
{
	SHFILEINFO shInfo;
	int nIcon = 0;
	CString extension = lpName;
	CString csName = "text"+extension;
	int nPos = csName.ReverseFind('.');
	if (nPos >0)
	{
		SHGetFileInfo(csName ,FILE_ATTRIBUTE_NORMAL,&shInfo,sizeof(shInfo),SHGFI_ICON | 
			SHGFI_SMALLICON|SHGFI_USEFILEATTRIBUTES );
	}
	else
	{
		char chPath[MAX_PATH] = {0};
		GetCurrentDirectory(MAX_PATH,chPath);
		SHGetFileInfo(chPath,FILE_ATTRIBUTE_NORMAL,&shInfo,sizeof(shInfo),
			SHGFI_ICON | SHGFI_SMALLICON  );		
	}
	nPos = shInfo.iIcon;
	return shInfo.hIcon;
}
