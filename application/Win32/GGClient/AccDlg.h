#pragma once
#include "accenu.h"


// CAccDlg �Ի���

class CAccDlg : public CDialog
{
	DECLARE_DYNAMIC(CAccDlg)

public:
	CAccDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAccDlg();

// �Ի�������
	enum { IDD = IDD_ACC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	BOOL Create(void);

	CAccEnu m_accEnu;
};
