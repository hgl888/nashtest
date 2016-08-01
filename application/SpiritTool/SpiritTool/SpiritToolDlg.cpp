
// SpiritToolDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SpiritTool.h"
#include "SpiritToolDlg.h"
#include "afxdialogex.h"
#include "FolderDialog.h"
#include "ApkMake.h"
#include "message.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSpiritToolDlg �Ի���




CSpiritToolDlg::CSpiritToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSpiritToolDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_iAppname = _T("");
	m_iOutpath = _T("");
	m_iIconpath = _T("");
	m_iApkname = _T("");
	m_iPackagename = _T("");
	m_iSpiritUA = _T("");
	m_iChannelID = _T("");
	m_iImgPath1 = _T("");
	m_iImgPath2 = _T("");
	m_iGifPath = _T("");
	m_iBWPath = _T("");
}
CSpiritToolDlg::~CSpiritToolDlg()
{
	CApkMake *apkMake = CApkMake::Singleton();
	delete apkMake;
}

void CSpiritToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_iList);
	DDX_Text(pDX, IDC_EDITAPPNAME, m_iAppname);
	DDV_MaxChars(pDX, m_iAppname, 20);
	DDX_Text(pDX, IDC_EDITOUTPATH, m_iOutpath);
	DDV_MaxChars(pDX, m_iOutpath, 256);
	DDX_Text(pDX, IDC_EDITICONPATH, m_iIconpath);
	DDV_MaxChars(pDX, m_iIconpath, 256);
	DDX_Text(pDX, IDC_EDITAPKNAME, m_iApkname);
	DDV_MaxChars(pDX, m_iApkname, 128);
	DDX_Text(pDX, IDC_EDITPACKAGENAME, m_iPackagename);
	DDV_MaxChars(pDX, m_iPackagename, 128);
	DDX_Text(pDX, IDC_EDITSPIRITUA, m_iSpiritUA);
	DDV_MaxChars(pDX, m_iSpiritUA, 20);
	DDX_Text(pDX, IDC_EDITCHANNELID, m_iChannelID);
	DDV_MaxChars(pDX, m_iChannelID, 8);
	DDX_Text(pDX, IDC_EDITIMAGEPATH1, m_iImgPath1);
	DDV_MaxChars(pDX, m_iImgPath1, 256);
	DDX_Text(pDX, IDC_EDITIMAGEPATH2, m_iImgPath2);
	DDV_MaxChars(pDX, m_iImgPath2, 256);
	DDX_Text(pDX, IDC_EDITGIFPATH, m_iGifPath);
	DDV_MaxChars(pDX, m_iGifPath, 256);
	DDX_Text(pDX, IDC_EDITBWPATH, m_iBWPath);
	DDV_MaxChars(pDX, m_iBWPath, 256);
	DDX_Check(pDX, IDC_CHECK1, m_bIsDesk);
	DDX_Control(pDX, IDC_EDIT1, m_iShow);
}

BEGIN_MESSAGE_MAP(CSpiritToolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT1, &CSpiritToolDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTONSET, &CSpiritToolDlg::OnBnClickedButtonset)
	ON_BN_CLICKED(IDC_BUTTONCH1, &CSpiritToolDlg::OnBnClickedButtonch1)
	ON_BN_CLICKED(IDC_BUTTONCH2, &CSpiritToolDlg::OnBnClickedButtonch2)
	ON_BN_CLICKED(IDC_BUTTONCH3, &CSpiritToolDlg::OnBnClickedButtonch3)
	ON_BN_CLICKED(IDC_BUTTONCH4, &CSpiritToolDlg::OnBnClickedButtonch4)
	ON_BN_CLICKED(IDC_BUTTONCH5, &CSpiritToolDlg::OnBnClickedButtonch5)
	ON_BN_CLICKED(IDC_BUTTONCH6, &CSpiritToolDlg::OnBnClickedButtonch6)
	ON_BN_CLICKED(IDC_BUTTONADD, &CSpiritToolDlg::OnBnClickedButtonadd)
	ON_LBN_SELCHANGE(IDC_LIST1, &CSpiritToolDlg::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDOK, &CSpiritToolDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CSpiritToolDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CSpiritToolDlg ��Ϣ�������

BOOL CSpiritToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

//	ShowWindow(SW_MINIMIZE);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CApkMake *apkMake = CApkMake::Singleton();
	apkMake->setDataArray(&m_spiritList);
	apkMake->start();
	apkMake->setListener(this);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSpiritToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSpiritToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSpiritToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSpiritToolDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

/*
void CSpiritToolDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strPath;
//	CFileDialog Open(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"Bitmap Files (*.bmp)|*.bmp|JPEG Files (*.jpg)|*.jpg|All Files (*.*)|*.*||",NULL);
	CFileDialog Open(true);
	if(Open.DoModal()==IDOK)
	{
		strPath=Open.GetPathName();//�������Ҫ��·���ˡ�
	}
}
*/

void CSpiritToolDlg::OnBnClickedButtonset()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_iSetDialog.DoModal();			//�������öԻ���
}


void CSpiritToolDlg::OnBnClickedButtonch1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*
	CFileDialog Open(true);
	if(Open.DoModal()==IDOK)
	{
		m_iOutpath=Open.GetPathName();//�������Ҫ��·���ˡ�
		UpdateData(false);
	}
	*/
	/*
	CString path;
	CFolderDialog open(&path,this);
	if(open.DoModal() == IDOK)
	{
		m_iOutpath=open.GetPathName();//�������Ҫ��·���ˡ�
		UpdateData(false);
	}
	*/
	UpdateData();
	CString path;
	if(CFolderDialog::GetFolder(path))
	{
		m_iOutpath = path;
		UpdateData(false);
	}
}

void CSpiritToolDlg::OnBnClickedButtonch2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	CFileDialog Open(true);
	UpdateData();
	CFileDialog Open(TRUE,
		NULL,
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"PNG File (*.png)|*.png||",
		NULL,
		0UL,
		1);
	if(Open.DoModal()==IDOK)
	{
		m_iIconpath=Open.GetPathName();
		UpdateData(false);
	}
}


void CSpiritToolDlg::OnBnClickedButtonch3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	CFileDialog Open(TRUE,
		NULL,
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"PNG File (*.png)|*.png||",
		NULL,
		0UL,
		1);
	if(Open.DoModal()==IDOK)
	{
		m_iImgPath1=Open.GetPathName();
		UpdateData(false);
	}
}


void CSpiritToolDlg::OnBnClickedButtonch4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	CFileDialog Open(TRUE,
		NULL,
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"PNG File (*.png)|*.png||",
		NULL,
		0UL,
		1);
	if(Open.DoModal()==IDOK)
	{
		m_iImgPath2=Open.GetPathName();
		UpdateData(false);
	}
}


void CSpiritToolDlg::OnBnClickedButtonch5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	CFileDialog Open(TRUE,
		NULL,
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"GIF File (*.gif)|*.gif||",
		NULL,
		0UL,
		1);
	if(Open.DoModal()==IDOK)
	{
		m_iGifPath=Open.GetPathName();
		UpdateData(false);
	}
}


void CSpiritToolDlg::OnBnClickedButtonch6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	CFileDialog Open(TRUE,
		NULL,
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"APK File (*.apk)|*.apk||",
		NULL,
		0UL,
		1);
	if(Open.DoModal()==IDOK)
	{
		m_iBWPath=Open.GetPathName();
		UpdateData(false);
	}
}


void CSpiritToolDlg::OnBnClickedButtonadd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();

	CSpiritData *Item = new CSpiritData();

	char *tempI;
	int len;
	//app����
	if(m_iAppname.GetLength()<=0)
	{
		CString str(L"����дapp����");
		m_iShow.SetWindowTextW(str);
		delete Item;
		return;
	}
	len = ::WideCharToMultiByte(CP_ACP,0,m_iAppname.GetBuffer(),-1,NULL,0,NULL,NULL);
	tempI = new char[len];
	::WideCharToMultiByte(CP_ACP,0,m_iAppname.GetBuffer(),-1,tempI,len,NULL,NULL);
	Item->m_hAppname = tempI;

	//���·��
	if(m_iOutpath.GetLength()<=0)
	{
		CString str(L"����д���·��");
		m_iShow.SetWindowTextW(str);
		delete Item;
		return;
	}
	len = ::WideCharToMultiByte(CP_ACP,0,m_iOutpath.GetBuffer(),-1,NULL,0,NULL,NULL);
	tempI = new char[len];
	::WideCharToMultiByte(CP_ACP,0,m_iOutpath.GetBuffer(),-1,tempI,len,NULL,NULL);
	Item->m_hOutpath = tempI;

	//ͼ��·��
	if(m_iIconpath.GetLength()<=0)
	{
		CString str(L"����дͼ��·��");
		m_iShow.SetWindowTextW(str);
		delete Item;
		return;
	}
	len = ::WideCharToMultiByte(CP_ACP,0,m_iIconpath.GetBuffer(),-1,NULL,0,NULL,NULL);
	tempI = new char[len];
	::WideCharToMultiByte(CP_ACP,0,m_iIconpath.GetBuffer(),-1,tempI,len,NULL,NULL);
	Item->m_hIconpath = tempI;

	//�������
	if(m_iApkname.GetLength()<=0)
	{
		CString str(L"����д�������");
		m_iShow.SetWindowTextW(str);
		delete Item;
		return;
	}
	len = ::WideCharToMultiByte(CP_ACP,0,m_iApkname.GetBuffer(),-1,NULL,0,NULL,NULL);
	tempI = new char[len];
	::WideCharToMultiByte(CP_ACP,0,m_iApkname.GetBuffer(),-1,tempI,len,NULL,NULL);
	Item->m_hApkname = tempI;

	//��ʶ��
	if(m_iPackagename.GetLength()<=0)
	{
		CString str(L"����д�����ʶ��");
		m_iShow.SetWindowTextW(str);
		delete Item;
		return;
	}
	len = ::WideCharToMultiByte(CP_ACP,0,m_iPackagename.GetBuffer(),-1,NULL,0,NULL,NULL);
	tempI = new char[len];
	::WideCharToMultiByte(CP_ACP,0,m_iPackagename.GetBuffer(),-1,tempI,len,NULL,NULL);
	Item->m_hPackagename = tempI;

	//����UA
	if(m_iSpiritUA.GetLength()<=0)
	{
		CString str(L"����д����UA");
		m_iShow.SetWindowTextW(str);
		delete Item;
		return;
	}
	len = ::WideCharToMultiByte(CP_ACP,0,m_iSpiritUA.GetBuffer(),-1,NULL,0,NULL,NULL);
	tempI = new char[len];
	::WideCharToMultiByte(CP_ACP,0,m_iSpiritUA.GetBuffer(),-1,tempI,len,NULL,NULL);
	Item->m_hSpiritUA = tempI;

	//����������
	if(m_iChannelID.GetLength()<=0)
	{
		CString str(L"����д����������");
		m_iShow.SetWindowTextW(str);
		delete Item;
		return;
	}
	len = ::WideCharToMultiByte(CP_ACP,0,m_iChannelID.GetBuffer(),-1,NULL,0,NULL,NULL);
	tempI = new char[len];
	::WideCharToMultiByte(CP_ACP,0,m_iChannelID.GetBuffer(),-1,tempI,len,NULL,NULL);
	Item->m_hChannelId = tempI;

	//ͼƬ1·��
	if(m_iImgPath1.GetLength()<=0)
	{
		CString str(L"�����ͼƬ1");
		m_iShow.SetWindowTextW(str);
		delete Item;
		return;
	}
	len = ::WideCharToMultiByte(CP_ACP,0,m_iImgPath1.GetBuffer(),-1,NULL,0,NULL,NULL);
	tempI = new char[len];
	::WideCharToMultiByte(CP_ACP,0,m_iImgPath1.GetBuffer(),-1,tempI,len,NULL,NULL);
	Item->m_hImagepath1 = tempI;

	//ͼƬ2·��
	if(m_iImgPath2.GetLength()<=0)
	{
		CString str(L"�����ͼƬ2");
		m_iShow.SetWindowTextW(str);
		delete Item;
		return;
	}
	len = ::WideCharToMultiByte(CP_ACP,0,m_iImgPath2.GetBuffer(),-1,NULL,0,NULL,NULL);
	tempI = new char[len];
	::WideCharToMultiByte(CP_ACP,0,m_iImgPath2.GetBuffer(),-1,tempI,len,NULL,NULL);
	Item->m_hImagepath2 = tempI;

	//gifͼƬ·��
	if(m_iGifPath.GetLength()<=0)
	{
		CString str(L"�����gifͼƬ");
		m_iShow.SetWindowTextW(str);
		delete Item;
		return;
	}
	len = ::WideCharToMultiByte(CP_ACP,0,m_iGifPath.GetBuffer(),-1,NULL,0,NULL,NULL);
	tempI = new char[len];
	::WideCharToMultiByte(CP_ACP,0,m_iGifPath.GetBuffer(),-1,tempI,len,NULL,NULL);
	Item->m_hGifpath = tempI;

	//�����·��
	if(m_iBWPath.GetLength()>0)
	{
		len = ::WideCharToMultiByte(CP_ACP,0,m_iBWPath.GetBuffer(),-1,NULL,0,NULL,NULL);
		tempI = new char[len];
		::WideCharToMultiByte(CP_ACP,0,m_iBWPath.GetBuffer(),-1,tempI,len,NULL,NULL);
		Item->m_hBWpath = tempI;
	}

	m_spiritList.addData(Item);
	m_iList.AddString(m_iAppname);
	CString text = m_iAppname;
	text+=L"-��ӳɹ�";
	m_iShow.SetWindowTextW(text);
}


void CSpiritToolDlg::OnLbnSelchangeList1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int index = m_iList.GetCurSel();
	if(index == LB_ERR) return;
	CSpiritData *item = m_spiritList.getData(index);
	m_iAppname = CString(item->m_hAppname);
	m_iOutpath = CString(item->m_hOutpath);
	m_iIconpath = CString(item->m_hIconpath);
	m_iApkname = CString(item->m_hApkname);
	m_iPackagename = CString(item->m_hPackagename);
	m_iSpiritUA = CString(item->m_hSpiritUA);
	m_iChannelID = CString(item->m_hChannelId);
	m_iImgPath1 = CString(item->m_hImagepath1);
	m_iImgPath2 = CString(item->m_hImagepath2);
	m_iGifPath = CString(item->m_hGifpath);
	m_iBWPath = CString(item->m_hBWpath);
	UpdateData(false);
	CString text;
	text+=L"App����";
	text+=m_iAppname;
	text+=L"\r\n";
	text+=L"UA��";
	text+=m_iSpiritUA;
	text+=L"\r\n";
	text+=L"�����ţ�";
	text+=m_iChannelID;
	m_iShow.SetWindowTextW(text);
}


void CSpiritToolDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_iSetDialog.m_iSdkPath.GetLength()<=0)
	{
		m_iShow.SetWindowTextW(L"������androidSdk·��.");
		return;
	}
	if(m_iSetDialog.m_iSrcPath.GetLength()<=0)
	{
		m_iShow.SetWindowTextW(L"������Դ��·��.");
		return;
	}
	CApkMake *apkMake = CApkMake::Singleton();
	char src[256];
	char sdk[256];
	int len = ::WideCharToMultiByte(CP_ACP,0,m_iSetDialog.m_iSrcPath.GetBuffer(),-1,NULL,0,NULL,NULL);
	::WideCharToMultiByte(CP_ACP,0,m_iSetDialog.m_iSrcPath.GetBuffer(),-1,src,len,NULL,NULL);
	src[len] = 0;
	len = ::WideCharToMultiByte(CP_ACP,0,m_iSetDialog.m_iSdkPath.GetBuffer(),-1,NULL,0,NULL,NULL);
	::WideCharToMultiByte(CP_ACP,0,m_iSetDialog.m_iSdkPath.GetBuffer(),-1,sdk,len,NULL,NULL);
	sdk[len] = 0;
	apkMake->setPath(src,sdk);
	apkMake->startMake();
	GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
	GetDlgItem(IDC_BUTTONADD)->EnableWindow(false);
	GetDlgItem(IDC_BUTTONSET)->EnableWindow(false);
	return;
//	CDialogEx::OnOK();
}


void CSpiritToolDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int index = m_iList.GetCurSel();
	if(index == LB_ERR) return;
	m_iList.DeleteString(index);
//	delete m_iList.GetItemDataPtr(index);
	delete m_spiritList.removeData(index);
	 m_iAppname = L"";				//app����
	 m_iOutpath = L"";				//���·��
	 m_iIconpath = L"";			//ͼ��·��
	 m_iApkname = L"";				//�������
	 m_iPackagename = L"";			//�����ʶ���������
	 m_iSpiritUA = L"";			//����UA
	 m_iChannelID = L"";			//����������
	 m_iImgPath1 = L"";			//ͼƬ1·��
	 m_iImgPath2 = L"";			//ͼƬ2·��
	 m_iGifPath = L"";				//gifͼƬ·��
	 m_iBWPath = L"";				//�����ͼƬ·��
	UpdateData(false);
}

void CSpiritToolDlg::onListen(int type,unsigned long data)
{
	switch(type)
	{
	case Kcomplete:
		{
			int index = data-1;
			int len = m_iShow.GetWindowTextLengthW();
			wchar_t *str = new wchar_t[len+1];
			m_iShow.GetWindowTextW(str,len);
			CString buf(str);
			buf+=L"\r\n";
			buf+=m_spiritList.getData(index)->m_hAppname;
			buf+=L"---�����";
			m_iShow.SetWindowTextW(buf);
			UpdateData(false);
			delete str;
		}
		break;
	case Kover:
		{
			int index = data-1;
			int len = m_iShow.GetWindowTextLengthW();
			wchar_t *str = new wchar_t[len+1];
			m_iShow.GetWindowTextW(str,len);
			CString buf(str);
			buf+=L"\r\n";
			buf+=L"ȫ�����";
			m_iShow.SetWindowTextW(buf);
			UpdateData(false);
			delete str;
			GetDlgItem(IDC_BUTTON1)->EnableWindow(true);
			GetDlgItem(IDC_BUTTONADD)->EnableWindow(true);
			GetDlgItem(IDC_BUTTONSET)->EnableWindow(true);
		}
		break;
	}
}
