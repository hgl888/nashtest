#pragma once
#include "webshow.h"


// CWebDialog �Ի���

class CWebDialog : public CDialog
{
	DECLARE_DYNAMIC(CWebDialog)

public:
	virtual BOOL OnInitDialog();
	void ShowCnt();
	CWebDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWebDialog();

// �Ի�������
	enum { IDD = IDD_WEBDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CWebshow m_webCnt;
};
