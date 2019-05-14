// CConfirmationDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "FileErasing.h"
#include "CConfirmationDlg.h"
#include "afxdialogex.h"
#include"FileErasingDlg.h"


// CConfirmationDlg ダイアログ

IMPLEMENT_DYNAMIC(CConfirmationDlg, CDialog)

CConfirmationDlg::CConfirmationDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CConfirmationDlg, pParent)
{

}

CConfirmationDlg::~CConfirmationDlg()
{
}

void CConfirmationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CConfirmationDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CConfirmationDlg::OnBnClickedOk)
	ON_BN_CLICKED(2, &CConfirmationDlg::OnBnClicked2)
END_MESSAGE_MAP()


// CConfirmationDlg メッセージ ハンドラー


void CConfirmationDlg::OnBnClickedOk()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CConfirmationDlg::OnOK();
	return;
}


void CConfirmationDlg::OnBnClicked2()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CConfirmationDlg::OnCancel();
}