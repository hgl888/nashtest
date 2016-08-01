#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "DibShow.h"

// CDibInfoDlg �Ի���

class CDibInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CDibInfoDlg)

public:
	XSWFPlayer* m_pPlayer;
	CDibInfoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDibInfoDlg();

// �Ի�������
	enum { IDD = IDD_DIBINFO };

protected:
	void Release();
	int  m_nSortType;
	CDibShow m_show;
	_DIBINFO* m_pInfo;
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	//afx_msg void OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
public:
	void Reset();
	CListCtrl m_list;
	void AddList(bool bReset=true);
	
	afx_msg void OnBnClickedReset();
	afx_msg void OnLvnColumnclickList(NMHDR *pNMHDR, LRESULT *pResult);
};
