#pragma once


// CWorldDlg dialog

class CWorldDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWorldDlg)

public:
	CWorldDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CWorldDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_APPLICATION_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
