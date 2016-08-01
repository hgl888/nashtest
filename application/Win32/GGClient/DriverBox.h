#if !defined(AFX_DRIVERBOX_H__81C3AA5B_A119_415C_8445_34B80E95EFAA__INCLUDED_)
#define AFX_DRIVERBOX_H__81C3AA5B_A119_415C_8445_34B80E95EFAA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DriverBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDriverBox window
/////////////////////////////////////////////////////////
// ��ʾ�ɶ�д������(����)�б������ʽ��Ͽ�
// ��ʾ���ݲ��������ƶ��豸
/////////////////////////////////////////////////////////
class CDriverBox : public CComboBox
{
// Construction
public:
	//���캯��
	CDriverBox();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDriverBox)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	//���ָ���������������Ƿ�Ϸ�
	//������ʾ���������Ƹ�ʽΪ ���̷�:\���确c:\��
	BOOL CheckDisk(LPCWSTR drv);
	//ѡ��ָ������������������ʾ���������ƣ���ʽͬ��
	void Select(LPCWSTR driver);
	//�õ�ѡ�������������
	BOOL GetSelect(CString&driver);
	virtual ~CDriverBox();

	// Generated message map functions
protected:
	//�����������б�
	CStringList m_drvList;
	//{{AFX_MSG(CDriverBox)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRIVERBOX_H__81C3AA5B_A119_415C_8445_34B80E95EFAA__INCLUDED_)
