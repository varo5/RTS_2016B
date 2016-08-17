// WorldDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Application.h"
#include "WorldDlg.h"
#include "afxdialogex.h"


// CWorldDlg dialog

IMPLEMENT_DYNAMIC(CWorldDlg, CDialogEx)

CWorldDlg::CWorldDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_APPLICATION_DIALOG, pParent)
{

}

CWorldDlg::~CWorldDlg()
{
}

void CWorldDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWorldDlg, CDialogEx)
END_MESSAGE_MAP()


// CWorldDlg message handlers
