#pragma once


// CTextDlg �Ի���

class CTextDlg : public CDialog
{
	DECLARE_DYNAMIC(CTextDlg)

public:
	BOOL m_bOK;
	CTextDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTextDlg();

// �Ի�������
	enum { IDD = IDD_TEXTEDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_strText;
	virtual BOOL OnInitDialog(void);
};
