#pragma once


// CConfirmationDlg ダイアログ

class CConfirmationDlg : public CDialog
{
	DECLARE_DYNAMIC(CConfirmationDlg)

public:
	CConfirmationDlg(CWnd* pParent = nullptr);   // 標準コンストラクター
	virtual ~CConfirmationDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CConfirmationDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClicked2();
};
