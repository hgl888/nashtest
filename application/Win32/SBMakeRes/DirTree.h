#if !defined(AFX_DIRTREE_H__6B219840_EEC5_4867_815F_074F95460616__INCLUDED_)
#define AFX_DIRTREE_H__6B219840_EEC5_4867_815F_074F95460616__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DirTree.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDirTree window
/////////////////////////////////////////////////////
// �Էּ���ʽ��ʾָ��Ŀ¼�ṹ���б��
// ��ʾʱ��ÿһ����ǰ�水Ŀ¼˳����������ʽ��ʾһ��Ŀ¼
// ͼ�꣬�����ʾ��Ŀ¼������
// ʹ��ʱָ��һ��Ŀ¼ȫ�����ؼ�����ʾ��Ŀ¼��ȫ����Ŀ¼
// �ṹ����Ŀ¼�µ�ȫ����Ŀ¼
// �û�����ͨ�����ѡ��Ŀ¼
//////////////////////////////////////////////////////
class CDirTree : public CListBox
{
// Construction
public:
	//���캯��
	CDirTree();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDirTree)
	public:
	virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	//�õ�ѡ���Ŀ¼ȫ��(�����̷�)
	BOOL GetSelected(CString&path);
	//����������ʾ�ĵ�ǰĿ¼
	BOOL SetPath(LPCSTR path);
	virtual ~CDirTree();

	// Generated message map functions
protected:
	//��Ŀ¼����Ŀ
	int m_nCount;
	//ȫ��Ŀ¼�ַ��б�
	CStringList m_pathList;
	//{{AFX_MSG(CDirTree)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIRTREE_H__6B219840_EEC5_4867_815F_074F95460616__INCLUDED_)
