// TextDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GGClient.h"
#include "TextDlg.h"


// CTextDlg �Ի���

IMPLEMENT_DYNAMIC(CTextDlg, CDialog)

CTextDlg::CTextDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTextDlg::IDD, pParent)
	, m_strText(_T(""))
{
	m_bOK=FALSE;
}

CTextDlg::~CTextDlg()
{
}

void CTextDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TEXT, m_strText);
	DDV_MaxChars(pDX, m_strText, 64000);
}


BEGIN_MESSAGE_MAP(CTextDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CTextDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CTextDlg ��Ϣ�������

void CTextDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bOK=TRUE;
	OnOK();
}



BOOL CTextDlg::OnInitDialog(void)
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_TEXT)->SetFocus();
	return XTRUE;
}
