
// FileErasingDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "FileErasing.h"
#include "FileErasingDlg.h"
#include "afxdialogex.h"
#include"CConfirmationDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CFileErasingDlg ダイアログ



CFileErasingDlg::CFileErasingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FILEERASING_DIALOG, pParent)
	, folder(_T(""))
	, extensions(_T(""))
	, strfileList(_T(""))
	, counter(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	// subfolder = _T("");
}

void CFileErasingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FOLDER_EDIT, folder);
	DDX_Text(pDX, IDC_EDIT2, extensions);
	DDX_LBString(pDX, IDC_LIST3, strfileList);
	DDX_Control(pDX, IDC_LIST3, m_FileList);
	DDX_Text(pDX, FILE_COUNT, counter);
}

BEGIN_MESSAGE_MAP(CFileErasingDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CFileErasingDlg::OnBnClickedSearchButton)
	ON_BN_CLICKED(IDC_BUTTON1, &CFileErasingDlg::OnBnClickedSelectButton)
	ON_BN_CLICKED(IDC_BUTTON4, &CFileErasingDlg::OnBnClickedErasingButton)
	ON_BN_CLICKED(IDC_BUTTON3, &CFileErasingDlg::OnBnClickedAllSelectButton)
	//ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CFileErasingDlg::OnLvnItemchangedList1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST3, &CFileErasingDlg::OnLvnItemchangedList3)
//	ON_BN_CLICKED(ERASING_BUTTON, &CFileErasingDlg::OnBnClickedButton)
END_MESSAGE_MAP()


// CFileErasingDlg メッセージ ハンドラー

BOOL CFileErasingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。
	UpdateSetting(FALSE);
	UpdateData(FALSE);
	LVCOLUMN lvCol1, lvCol2, lvCol3;
	lvCol1.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvCol1.fmt = LVCFMT_LEFT;
	lvCol1.pszText = _T("ファイル名");
	lvCol1.cx = 500;
	m_FileList.InsertColumn(0, &lvCol1);
	lvCol2.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvCol2.fmt = LVCFMT_LEFT;
	lvCol2.pszText = _T("ファイルサイズ");
	lvCol2.cx = 265;
	m_FileList.InsertColumn(1, &lvCol2);
	lvCol3.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvCol3.fmt = LVCFMT_LEFT;
	lvCol3.pszText = _T("最終更新日時");
	lvCol3.cx = 265;
	m_FileList.InsertColumn(2, &lvCol3);


	lvCol3.pszText = _T("FULL PATH");
	lvCol3.cx = 265;
	m_FileList.InsertColumn(3, &lvCol3);

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CFileErasingDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CFileErasingDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CFileErasingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFileErasingDlg::OnBnClickedSearchButton()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CWnd::UpdateData(TRUE);
	
	UpdateSetting(TRUE);
	m_FileList.DeleteAllItems();

	int i = 0;
	CStringArray arrExtension;
	// CString extension;
	// CString folderAndExtension;
	Split(&arrExtension, extensions, _T(","));
	// int iMaxCol = arrExtension.GetSize();
	//for (int iIndex = 0; iIndex < iMaxCol; iIndex++) {
		// extension = arrExtension.GetAt(iIndex); 
		//if (extension == "") { extension = '*'; }
	//	folderAndExtension = folder +"\\*."+ extension;
		FindFile(folder, arrExtension, i);
	//}
		CString number;
		number.Format(_T("%d"), m_FileList.GetItemCount());
		counter = _T("ファイル数：") + number;
		CWnd::UpdateData(FALSE);
}

void CFileErasingDlg::OnBnClickedSelectButton()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	TCHAR dir[MAX_PATH] = { '\0' };
	CString dir2 = _T("\0");
	CWnd::UpdateData(TRUE);
	BOOL bRes = SelectFolder(this->m_hWnd, folder, dir, BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE, _T("フォルダーを選択して下さい。"));
	if (bRes)
	{ folder = dir; }	//？dirの値 
	CWnd::UpdateData(FALSE);
	UpdateSetting(TRUE);
}


BOOL CFileErasingDlg::SelectFolder(HWND hWnd, LPCTSTR lpDefFolder, LPTSTR lpSelectPath, UINT nFlag, LPCTSTR lpTitle)
{		// TODO: ここに実装コードを追加します.
	LPMALLOC pMalloc;
	BOOL bRet = FALSE;
	if (SUCCEEDED(SHGetMalloc(&pMalloc))) {
		BROWSEINFO browsInfo;
		ITEMIDLIST *pIDlist;
		memset(&browsInfo, NULL, sizeof(browsInfo));
		browsInfo.hwndOwner = hWnd;
		browsInfo.pidlRoot = NULL;
		browsInfo.pszDisplayName = lpSelectPath;
		browsInfo.lpszTitle = lpTitle;
		browsInfo.ulFlags = nFlag;
		browsInfo.lpfn = (BFFCALLBACK)&BrowseCallbackProc;
		browsInfo.lParam = (LPARAM)lpDefFolder;
		browsInfo.iImage = (int)NULL;

		pIDlist = SHBrowseForFolder(&browsInfo);
		if (NULL == pIDlist) {
		//	strcpy_s((char*)lpSelectPath, MAX_PATH, lpDefFolder);
			pMalloc->Release();
		}
		else {
			SHGetPathFromIDList(pIDlist, lpSelectPath);
			folder = lpSelectPath;
			bRet = TRUE;
			pMalloc->Free(pIDlist);
			UpdateData(FALSE);
		}
	}
	return 0;
}


int CALLBACK CFileErasingDlg::BrowseCallbackProc(HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	// TODO: ここに実装コードを追加します.
	switch (uMsg) {
	case BFFM_INITIALIZED:
			::SendMessage(  hWnd, BFFM_SETSELECTION, (WPARAM)TRUE, lpData);
			break;
	case BFFM_SELCHANGED:break;
	}
	return 0;
}


void CFileErasingDlg::OnBnClickedErasingButton()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CConfirmationDlg confirmDlg;
	int ret = (int)confirmDlg.DoModal();
	if (ret==IDOK) {
		remove();
	}
}


void CFileErasingDlg::OnBnClickedAllSelectButton()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	UpdateData(TRUE);
	int cnt;
	cnt = m_FileList.GetItemCount();

	for (int i = 0; i < cnt; i++) {
		m_FileList.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
	}
	UpdateData(FALSE);
}

void CFileErasingDlg::Split(CStringArray* pstrArray, LPCTSTR szTarget, LPCTSTR szDelimiter)
{
	// TODO: ここに実装コードを追加します.
	if (!szTarget)
		return;
	if (!szDelimiter)
		return;
	if (!pstrArray)
		return;

	pstrArray->RemoveAll();

	CString strTarget(szTarget);
	size_t intDelimiterLen = 0;
	size_t intStart = 0;
	int intEnd = 0;

	strTarget += szDelimiter;
	intDelimiterLen = _tcslen(szDelimiter);
	intStart = 0;
	while (intEnd = strTarget.Find(szDelimiter, intStart), intEnd >= 0)
	{
		pstrArray->Add(strTarget.Mid(intStart, intEnd - intStart));
		intStart = intEnd + intDelimiterLen;
	}
	return;
}


void CFileErasingDlg::OnLvnItemchangedList3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	*pResult = 0;
}

void CFileErasingDlg::FindFile(CString folder,CStringArray &extension, int findCount)
{
	WIN32_FIND_DATA win32fd;


	// TODO: ここに実装コードを追加します.
	HANDLE hFind;
	CString strSeek;
	strSeek = folder + "\\*.*";
	
	hFind = FindFirstFile(strSeek, &win32fd);


	if (hFind == INVALID_HANDLE_VALUE) {
		AfxMessageBox(_T("hFind==INVALID_HANDLE_VALUE"));
		return;
	}
	do {
		CString strFind = win32fd.cFileName;
		CString strPath = folder + "\\" + win32fd.cFileName;

		if (strFind == ".") {
		}
		else if (strFind == "..") {
		}
		else if (!::PathIsDirectory(strPath))
		{
			CString str, findExtension;
			int p, i, n;
			BOOL bHit = FALSE;

			p = strPath.ReverseFind('.');
			if (p > 0) {
				findExtension = strPath.Right(strPath.GetLength() - p - 1);
			}

			n = extension.GetSize();	
			if (n == 0) { bHit = TRUE; }
			else {
				for (i = 0; i < n; i++) {
					str = extension.GetAt(i);
					if (str == findExtension) {
						bHit = TRUE;
						break;
					}
				}
			}
			if (bHit == TRUE) {
				LVITEM lvItem;

				//1
				lvItem.mask = LVIF_TEXT;
				lvItem.pszText =  win32fd.cFileName;
				lvItem.iItem = findCount;
				lvItem.iSubItem = 0;
				m_FileList.InsertItem(&lvItem);	//? SetItem

				//2
				char* lpszFileSize;
				DWORD dwHigh = win32fd.nFileSizeHigh;
				DWORD dwLow = win32fd.nFileSizeLow;
				u_int64 nSize;		//?//	_int64
				//int nLen, nCnt;
				//char szTemp[MAX_PATH];
				//char* p;
				nSize = dwHigh;
				nSize = (nSize << 32) + 1023;
				nSize += dwLow;
				nSize = (nSize >> 10);
				str.Format("%dKB", nSize);
				/*
				nLen    = lstrlen(szTemp);		//szTempの長さ
				p = lpszFileSize;
				for (nCnt = 0; nCnt < nLen; nCnt++) {
					*p++ = szTemp[nCnt];
					if ((nCnt != nLen - 1) && ((nLen - (nCnt + 1)) % 3 == 0)) {
						*p++ = ',';
					}
				}
				*p = '\0';
				lstrcat(p, " KB");
				 lvItem.pszText = lpszFileSize; 
				*/
				lvItem.pszText = str.GetBuffer(0);
				lvItem.iSubItem = 1;
				m_FileList.SetItem(&lvItem);

				//3
				SYSTEMTIME tSystemTime;
				::FileTimeToSystemTime(&win32fd.ftLastWriteTime, &tSystemTime);
				str.Format("%04d/%02d/%02d %02d:%02d:%02d"
					, tSystemTime.wYear
					, tSystemTime.wMonth
					, tSystemTime.wDay
					, tSystemTime.wHour
					, tSystemTime.wMinute
					, tSystemTime.wSecond);
				lvItem.pszText = str.GetBuffer(0);

				lvItem.iSubItem = 2;
				m_FileList.SetItem(&lvItem);
			
				//4
				lvItem.pszText = strPath.GetBuffer(0);
				lvItem.iSubItem = 3;
				m_FileList.SetItem(&lvItem);	//? SetItem
					
				
				
				findCount++;
			}
		}
		else if (::PathFileExists(strPath)) {
			FindFile(strPath, extension, findCount);
		}
	} while (FindNextFile(hFind, &win32fd));
}


void CFileErasingDlg::UpdateSetting(const BOOL bSave)
{
	// TODO: ここに実装コードを追加します.
	CWinApp* pApp = AfxGetApp();
	ASSERT(pApp);

	TCHAR szSection[256];
	wsprintf(szSection, _T("SettingFolder"));

	if (bSave) {
		pApp->WriteProfileString(szSection, _T("FolderStringValue"), folder);
	}
	else {
		folder = pApp->GetProfileString(szSection, _T("FolderStringValue"), folder);
	}
	if (bSave) {
		pApp->WriteProfileString(szSection, _T("ExtensionsStringValue"), extensions);
	}
	else {
		extensions = pApp->GetProfileString(szSection, _T("ExtensionsStringValue"), extensions);
	}
}


void CFileErasingDlg::remove()
{
	// TODO: ここに実装コードを追加します.
	int iSelected = -1;
	TCHAR selectedFile[256];
	if (m_FileList.GetSelectedCount() == 0) { AfxMessageBox(_T("ファイルが選択されていません。")); return; }
	do {
		iSelected = m_FileList.GetNextItem(iSelected, LVNI_SELECTED);
		if (iSelected >= 0) {
			m_FileList.GetItemText(iSelected, 3, selectedFile, 256);
			try {
				CFile::Remove(selectedFile);
			}
			catch (CFileException* pEx) {
				CString msg;
				char buffer[128];
				pEx->GetErrorMessage(buffer, 128, 0);
				msg.Format(_T("File %s cannot be remove [%s]"), selectedFile, buffer);
				
				pEx->Delete();

				int ret = AfxMessageBox(msg, MB_YESNO);
				if (ret == IDNO) {
					break;
				}
			}
		}
	} while (iSelected >= 0);
	
	OnBnClickedSearchButton();
}

void CAboutDlg::OnBnClickedOk()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CDialogEx::OnOK();
}
