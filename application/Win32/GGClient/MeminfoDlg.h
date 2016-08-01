#pragma once
#include "afxcmn.h"


// CMeminfoDlg �Ի���
#define MAXINFO 16
class CMeminfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CMeminfoDlg)

public:
	CMeminfoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMeminfoDlg();
	virtual BOOL OnInitDialog();
// �Ի�������
	enum { IDD = IDD_MEMINFO };
	XSWFPlayer* m_pPlayer;
	XSortMemName m_data[MAXINFO];
	XU32		 m_nSize[MAXINFO];
	XSortMemName* m_pData;
protected:
	void ShowName();
	void ShowCount();
	void ShowCountInc();
	void ShowSize();
	void ShowSizeInc();
	void Show();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg void OnColumnclickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	int	m_nSortMode;
	int m_nID;
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	afx_msg void OnBnClickedReset();
	afx_msg void OnBnClickedLast();
	afx_msg void OnBnClickedNext();
};
