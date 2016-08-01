#if !defined(AFX_DIRBROWNS_H__4FA4D035_6E74_4BDB_B930_25F2EC8CD2D8__INCLUDED_)
#define AFX_DIRBROWNS_H__4FA4D035_6E74_4BDB_B930_25F2EC8CD2D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DirBrowns.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDirBrowns dialog
#include "DriverBox.h"
#include "DirTree.h"
/////////////////////////////////////////////////////////////
//Ŀ¼����Ի���,����������������Ե�Ŀ¼����Ŀ¼
//�û��ڱ���ϵͳ��λһ��·��
class CDirBrowns : public CDialog
{
// Construction
public:
	CDirBrowns(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDirBrowns)	

	CEdit		m_pathEdit;
	CDirTree	m_dirTree;
	CDriverBox	m_drvList;
	CString	m_pathName;//��ǰ·��,����ͨ��ָ���ñ������ó�ʼλ��
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDirBrowns)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL CheckPath(CString&path);
	CString m_currentPath;

	// Generated message map functions
	//{{AFX_MSG(CDirBrowns)
	afx_msg void OnDblclkDirtree();//NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangedDirtree();//NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeDrvlist();
	virtual BOOL OnInitDialog();
	afx_msg void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIRBROWNS_H__4FA4D035_6E74_4BDB_B930_25F2EC8CD2D8__INCLUDED_)
