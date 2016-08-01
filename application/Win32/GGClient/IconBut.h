#if !defined(AFX_ICONBUT_H__14089BB6_18DF_11D2_A267_97849FE32001__INCLUDED_)
#define AFX_ICONBUT_H__14089BB6_18DF_11D2_A267_97849FE32001__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// IconBut.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CIconBut window
/////////////////////////////////////////////////////////
//ͼ�갴ť/�˵���ť�ؼ�
//��ؼ�Ϊͼ�갴ť���ͣ�����Ҫָ��ͼ����Դ���ؼ��ڰ�ť��
//���Ƹ�ͼ�꣬����������Ϊ��ʾ����
//��ÿؼ�Ϊ�˵���ť������Ҫ����ť��������Ϊ���Ի�����ʽ
//��ָ���ð�ť�Ĳ˵���Դ������ʱ�ڰ�ť�����ֺ����һ��ɫ����
//���¸ð�ť���Ե����˵�
/////////////////////////////////////////////////////////
class CIconBut : public CButton
{
// Construction
public:
	//���ð�ť��Ӧ��ͼ����Դ
	void SetID(LPCTSTR  strID){m_strResID=strID;}
	//���캯��������resID��ʾͼ����Դ���ƣ���Ϊ�˵���ť���ò�������Ϊ��
	//pMenuID��ʾ�˵���Դ���ƣ���Ϊͼ�갴ť���ò�������Ϊ�ա�subID��ʾ�����˵�
	//��ָ���˵��е��Ӳ˵����
	CIconBut(BOOL bPopup=FALSE);
	void SetPopup(BOOL bPopup){m_bPopup=bPopup;}
	//���õ����˵�����
	//menuID�˵���Դ����
	//subID�Ӳ˵����
	// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIconBut)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL Create(CWnd*pWnd,LPCTSTR pCaption,const RECT&rect,UINT nID);
	
	virtual ~CIconBut();

	// Generated message map functions
protected:	
	CString m_strResID;
	//�����ؼ�,enableTip��ʾ�Ƿ���ʾ�����ʾ
	BOOL Create( BOOL enableTip = TRUE );
	//���Ʋ˵�������
	void    DrawTriangle(CDC* pDC, CPoint& pt, int size );
	//��ʾ�����˵�
	void    DisplayMenu();
	//�˵���Դ����
	//UINT    m_menuID;
	//�Ӳ˵�����Ȼ���
	//UINT    m_subID;
	//ͼ����Դ����
	//UINT	m_iconID;
	//�Ƿ���������ť�˵�
	BOOL    m_bPopup;//�Ƿ�Ϊ�˵�����
	BOOL    m_bLockDown;
	//��ʾ�ؼ�
	CToolTipCtrl m_toolTip;
	//{{AFX_MSG(CIconBut)
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ICONBUT_H__14089BB6_18DF_11D2_A267_97849FE32001__INCLUDED_)
