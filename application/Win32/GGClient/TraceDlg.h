#pragma once

#include "InfoWnd.h"
// CTraceDlg �Ի���
struct TRACEINFO
{
	CString strTmp;
	TRACEINFO* pNext;
};
class CTraceDlg : public CDialog
{
	DECLARE_DYNAMIC(CTraceDlg)
public:
	TRACEINFO* m_pTraceInfo;
	XMutex	   m_lock;
public:
	void UpdateInfo();
	CInfoWnd m_info;
	XString8 m_strTraceFile;
	XFile	m_file;
	bool m_bOutput;
	void TraceText(const XU16*txt);
	void Clear()
	{
		m_pEdit->SetWindowText(_T(""));
	}
	CTraceDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTraceDlg();
	bool OpenTraceFile(const char* strWorkPath);

// �Ի�������
	enum { IDD = IDD_TRACE };
	BOOL CreateTrace(CRect&rect);
	CEdit* m_pEdit;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnCancel();	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedClear();
};
