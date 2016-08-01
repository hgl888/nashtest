#pragma once
#include "afxcmn.h"


// CFlashBar �Ի���

class CFlashBar : public CDialog
{
	DECLARE_DYNAMIC(CFlashBar)

public:
	void EnableItem();
	CFlashBar(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFlashBar();
	virtual BOOL OnInitDialog();
// �Ի�������
	enum { IDD = IDD_FLASHBAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnCancel();
	virtual void OnClose();
	afx_msg void OnQuit();
	afx_msg void OnRestart();
	afx_msg void OnZoomin();
	afx_msg void OnZoomout();
	afx_msg void OnRotate();
	afx_msg void OnRadio();
	afx_msg void OnScore();
	afx_msg void OnPay();
	DECLARE_MESSAGE_MAP()
public:
	XFlashView* m_pView;

	CSliderCtrl m_zoomBar;

	afx_msg void OnNMCustomdrawZoombar(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureZoombar(NMHDR *pNMHDR, LRESULT *pResult);
};
