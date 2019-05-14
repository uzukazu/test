
// FileErasingDlg.h : ヘッダー ファイル
//

#pragma once


// CFileErasingDlg ダイアログ
class CFileErasingDlg : public CDialogEx
{
// コンストラクション
public:
	CFileErasingDlg(CWnd* pParent = nullptr);	// 標準コンストラクター

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILEERASING_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSearchButton();
	CString folder;
	afx_msg void OnBnClickedSelectButton();
	BOOL SelectFolder(HWND hWnd, LPCTSTR lpDefFolder, LPTSTR lpSelectPath, UINT nFlag, LPCTSTR lpTitle);
	static  int  CALLBACK BrowseCallbackProc(HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData);
	CString extensions;
	CString strfileList;
	CListCtrl m_FileList;

	afx_msg void OnBnClickedErasingButton();
	afx_msg void OnBnClickedAllSelectButton();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	void Split(CStringArray* pstrArray, LPCTSTR szTarget, LPCTSTR szDelimiter);
	afx_msg void OnLvnItemchangedList3(NMHDR *pNMHDR, LRESULT *pResult);
	void FindFile(CString folder,CStringArray &extension, int i);
	void UpdateSetting(const BOOL bSave);
	CString counter;
//	static void remove();
	void remove();
	afx_msg void OnBnClickedButton();
};
