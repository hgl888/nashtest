// DirBrowns.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "DirBrowns.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDirBrowns dialog


CDirBrowns::CDirBrowns(CWnd* pParent /*=NULL*/)
	: CDialog("DIRBROWNS", pParent)
{
	//{{AFX_DATA_INIT(CDirBrowns)
	//m_pathName = _T("c:\\");
	//}}AFX_DATA_INIT
	char temp[4096];
	//�õ���ǰ·��
	::GetCurrentDirectory(4096,temp);
	temp[3]=0;
	m_pathName=temp;
	m_currentPath=temp;
}


void CDirBrowns::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDirBrowns)
	DDX_Control(pDX, IDC_PATHNAME, m_pathEdit);
	DDX_Control(pDX, IDC_DIRTREE, m_dirTree);
	DDX_Control(pDX, IDC_DRVLIST, m_drvList);
	DDX_Text(pDX, IDC_PATHNAME, m_pathName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDirBrowns, CDialog)
	//{{AFX_MSG_MAP(CDirBrowns)	
    ON_LBN_DBLCLK(IDC_DIRTREE, OnDblclkDirtree)
	//ON_LBN_SELCHANGE(IDC_DIRTREE, OnSelchangedDirtree)
	ON_CBN_SELCHANGE(IDC_DRVLIST, OnSelchangeDrvlist)
	ON_BN_CLICKED(IDOK, OnOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDirBrowns message handlers
//˫��Ŀ¼��,�ı䵱ǰĿ¼�򷵻�ѡ�е�Ŀ¼
void CDirBrowns::OnDblclkDirtree()//NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CString temp;
	if(m_dirTree.GetSelected(temp))
	{
		if(temp==m_pathName) OnOK();//����
		else						//�ı�Ŀ¼
		{
			m_pathName=temp;
			SetDlgItemText(IDC_PATHNAME,m_pathName);
			m_dirTree.SetPath(m_pathName);
		}
	}
	//CString str;
	//str.Format("Address:%x",pResult);
	//MessageBox(str);
	//*pResult = 0;
}

void CDirBrowns::OnSelchangedDirtree()//NMHDR* pNMHDR, LRESULT* pResult) 
{
	//NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	/*CString temp;
	if(m_dirTree.GetSelected(temp))
	{
		if(temp!=m_pathName)
		{
			m_pathName=temp;
			SetDlgItemText(IDC_PATHNAME,m_pathName);
			m_dirTree.SetPath(m_pathName);
		}
	}*/
	//*pResult = 0;
}
//�ı䵱ǰ������
void CDirBrowns::OnSelchangeDrvlist() 
{
	// TODO: Add your control notification handler code here
	CString temp,drv;
	if(!m_drvList.GetSelect(temp)) return;
	drv=m_pathName.Left(2);
	drv.MakeLower();
	if(drv==temp) return;
	drv=m_currentPath.Left(2);
	drv.MakeLower();
	if(drv==temp)
		m_pathName=m_currentPath;
	else {m_pathName=temp;m_pathName+='\\';}
	SetDlgItemText(IDC_PATHNAME,m_pathName);
	m_dirTree.SetPath(m_pathName);
}

BOOL CDirBrowns::OnInitDialog() 
{
	m_pathName.Replace('/','\\');
	
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if(!CheckPath(m_pathName)) 
	 m_pathName=m_currentPath;
	SetDlgItemText(IDC_PATHNAME,m_pathName);

	CString driver=m_pathName.Left(2);
	m_drvList.Select(driver);
	m_dirTree.SetPath(m_pathName);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//����ȷ��,���Ŀ¼�ĺϷ���

void CDirBrowns::OnOK() 
{
	// TODO: Add your control notification handler code here
	CString temp;
	GetDlgItemText(IDC_PATHNAME,temp);
	if(temp==m_pathName) 
	{ EndDialog(IDOK);return;}
	temp.Replace('/','\\');
	if(!CheckPath(temp))
	{
		CString str;
		str.Format("%s����һ���Ϸ���Ŀ¼!",temp);
		AfxMessageBox(str);
		return;
	}
	m_pathName=temp;
	SetDlgItemText(IDC_PATHNAME,m_pathName);
	CString driver=m_pathName.Left(2);
	m_drvList.Select(driver);
	m_dirTree.SetPath(m_pathName);

}
//���Ŀ¼�ĺϷ���
BOOL CDirBrowns::CheckPath(CString &temp)
{	
	CString fPath;
	if(temp.Find(":")!=1) 
	{	fPath="c:";
		m_drvList.GetSelect(fPath);
		fPath+='\\';
		temp.Insert(0,fPath); }
	if(temp.Find('\\')!=2) temp.Insert(2,'\\');
	WIN32_FIND_DATA data;	   
	if(temp[temp.GetLength()-1]=='\\'&&
	   temp.GetLength()>3) temp.SetAt(temp.GetLength()-1,0);
	HANDLE handle=INVALID_HANDLE_VALUE;

	fPath=temp.Left(2);
	if(m_drvList.CheckDisk(fPath))
	{	if(temp.GetLength()>3)
		{
			handle=::FindFirstFile(temp,&data);
			::FindClose(handle);
			if(handle!=INVALID_HANDLE_VALUE&&
				(data.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)==0)
				handle=INVALID_HANDLE_VALUE;
		}
	    else handle=0;
	}	
	if(handle==INVALID_HANDLE_VALUE) return FALSE;
	return TRUE;
}
