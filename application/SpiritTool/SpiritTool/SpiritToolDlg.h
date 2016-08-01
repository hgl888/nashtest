
// SpiritToolDlg.h : ͷ�ļ�
//

#pragma once

#include "PointerArray.h"
#include "SpiritData.h"
#include "SetDialog.h"
#include "ApkMake.h";
// CSpiritToolDlg �Ի���
class CSpiritToolDlg : public CDialogEx , public CApkMake::MakeListener
{
// ����
public:
	CSpiritToolDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CSpiritToolDlg();
// �Ի�������
	enum { IDD = IDD_SPIRITTOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton2();

public:
	void onListen(int type,unsigned long data);

protected:
	CPointerArray<CSpiritData>	m_spiritList;	//�����б�����
public:
	CListBox m_iList;				//�����б��
	CString m_iAppname;				//app����
	CString m_iOutpath;				//���·��
	CString m_iIconpath;			//ͼ��·��
	CString m_iApkname;				//�������
	CString m_iPackagename;			//�����ʶ���������
	CString m_iSpiritUA;			//����UA
	CString m_iChannelID;			//����������
	CString m_iImgPath1;			//ͼƬ1·��
	CString m_iImgPath2;			//ͼƬ2·��
	CString m_iGifPath;				//gifͼƬ·��
	CString m_iBWPath;				//�����ͼƬ·��
	BOOL m_bIsDesk;					//����ͼ��
	CEdit m_iShow;					//��Ϣ��ʾ����
private:
	CSetDialog m_iSetDialog;
public:
	//���ð�ť
	afx_msg void OnBnClickedButtonset();
	//���·����ť
	afx_msg void OnBnClickedButtonch1();
	//ͼ��·����ť
	afx_msg void OnBnClickedButtonch2();
	//ͼƬ1��ť
	afx_msg void OnBnClickedButtonch3();
	//ͼƬ2��ť
	afx_msg void OnBnClickedButtonch4();
	//gifͼƬ��ť
	afx_msg void OnBnClickedButtonch5();
	//�����·����ť
	afx_msg void OnBnClickedButtonch6();
	//��Ӱ�ť
	afx_msg void OnBnClickedButtonadd();
	//listbox����ı��б����
	afx_msg void OnLbnSelchangeList1();
	//���ִ�а�ť
	afx_msg void OnBnClickedOk();
	//���remove��ť
	afx_msg void OnBnClickedButton1();
};
