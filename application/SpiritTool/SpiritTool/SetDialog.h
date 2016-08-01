#pragma once


// CSetDialog �Ի���

class CSetDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CSetDialog)

public:
	CSetDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetDialog();

// �Ի�������
	enum { IDD = IDD_SET_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	void setSrcPath(const CString& srcpath);
	const CString getSrcPath();
	void setSdkPath(const CString& sdkpath);
	const CString getSdkPath();
private:
	bool makeFile();
	bool makeConfig();
	void readConfig();
public:
	CString m_iSrcPath;			//Դ��·��
	CString m_iSdkPath;			//SDK·��
	long m_nKeyDate;			//ǩ����Чʱ��
public:
	//Դ��·����ť
	afx_msg void OnBnClickedButton1();
	//sdk·����ť
	afx_msg void OnBnClickedButton2();
	//Ӧ�ð�ť
	afx_msg void OnBnClickedOk();

};
