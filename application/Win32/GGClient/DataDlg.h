#pragma once
#include "afxcmn.h"


// CDataDlg �Ի���

class CDataDlg : public CDialog
{
	DECLARE_DYNAMIC(CDataDlg)

public:
	CDataDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDataDlg();

// �Ի�������
	enum { IDD = IDD_DATAPROC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	void SetMax(int nMax);
	void SetProc(int nProc);
	CProgressCtrl m_proc;
};
