
// FileErasing.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CFileErasingApp:
// このクラスの実装については、FileErasing.cpp を参照してください
//

class CFileErasingApp : public CWinApp
{
public:
	CFileErasingApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CFileErasingApp theApp;
