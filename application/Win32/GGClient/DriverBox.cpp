// DriverBox.cpp : implementation file
//

#include "stdafx.h"
#include "DriverBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDriverBox

CDriverBox::CDriverBox()
{
}

CDriverBox::~CDriverBox()
{
}


BEGIN_MESSAGE_MAP(CDriverBox, CComboBox)
	//{{AFX_MSG_MAP(CDriverBox)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDriverBox message handlers
//�����ؼ�ʱ���ã��ú����в������п��õ�������
//���������Ʊ��浽�б��ַ��б��кͼ��뵽��ʾ�б���
void CDriverBox::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CComboBox::PreSubclassWindow();
    DWORD drives=GetLogicalDrives();
	int nums=0;	
	drives>>=2;
	WCHAR disk[]=_T("c:\\");	
	while(drives)
	{
		if(drives&0x01)
		{						
			UINT type=GetDriveType(disk);
			if(type==DRIVE_FIXED||type==DRIVE_REMOTE)
			{
				disk[2]=0;
				AddString(disk);
				m_drvList.AddTail(disk);
				disk[2]='\\';
			}
		}
		disk[0]++;
		drives>>=1;
	} 

}
//��ʾ��Ŀ����ʾ��ǰ����ʾ�����������ͼ��
//�������ʾ��������������
void CDriverBox::DrawItem(LPDRAWITEMSTRUCT lpDS) 
{
	// TODO: Add your code to draw the specified item
	if(lpDS->itemID==LB_ERR) return;
	CDC* pDC=CDC::FromHandle(lpDS->hDC);
	//
	CRect r(lpDS->rcItem);	
	BOOL bEnable=(GetStyle()&WS_DISABLED)==0;
	CImageList list;
	//�õ�������ͼ�겢��ʾ
	list.Create(_T("IDB_DIRBROWNS"),16,0,0xffffff);
	r.left+=4;
	list.Draw(pDC,0,r.TopLeft(),bEnable?ILD_TRANSPARENT:ILD_BLEND);	
	r.left+=20;
	CBrush br;
	//�����ַ�����
	if( bEnable&&(/*(lpDS->itemAction & (ODA_SELECT |ODA_SELECT|ODA_FOCUS))
		&&*/(lpDS->itemState & ODS_SELECTED))|
		((lpDS->itemState&ODS_COMBOBOXEDIT)&&(lpDS->itemState&ODS_FOCUS)))
	{   //����Ŀ��ѡ�в�������
		br.CreateSolidBrush(GetSysColor(COLOR_HIGHLIGHT));		
		pDC->FillRect(&r, &br);		
		pDC->SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));
		pDC->SetBkMode(TRANSPARENT);		
		if(lpDS->itemState&ODS_COMBOBOXEDIT)
			pDC->DrawFocusRect(r);
	}		
	else 
	{	br.CreateSolidBrush(GetSysColor(COLOR_WINDOW));
		if(bEnable)pDC->FillRect(&r, &br); 		
		pDC->SetTextColor(GetSysColor(bEnable?COLOR_WINDOWTEXT:COLOR_GRAYTEXT)); 
		pDC->SetBkMode(TRANSPARENT);		
	}
	CString text=m_drvList.GetAt(m_drvList.FindIndex(lpDS->itemID));
	//this->GetItemDataPtr(0);
	//GetLBText(lpDS->itemID,text);

	pDC->TextOut(r.left,r.top,text);
}

void CDriverBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	// TODO: Add your code to determine the size of specified item
	
}
//�ȽϺ������ÿؼ��ܲ�����
int CDriverBox::CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct) 
{
	// TODO: Add your code to determine the sorting order of the specified items
	// return -1 = item 1 sorts before item 2
	// return 0 = item 1 and item 2 sort the same
	// return 1 = item 1 sorts after item 2
	
	return 0;
}
//�õ�ѡ������������ƣ������������
BOOL CDriverBox::GetSelect(CString &driver)
{
   int index=GetCurSel();
   if(index<0||index>=m_drvList.GetCount()) return FALSE;
   driver=m_drvList.GetAt(m_drvList.FindIndex(index));
   return TRUE;
}
//ѡ��ָ������������������ʾ����������
void CDriverBox::Select(LPCWSTR driver)
{
   int index=0;
   //��ʽ������
   CString dr(driver);
   dr.MakeLower();
   //������ת��������
   POSITION pos=m_drvList.GetHeadPosition();
   while(pos)
   {
	   if(m_drvList.GetNext(pos)==dr) break;
	   index++;
   }
   if(index>=m_drvList.GetCount()) index=0;
   SetCurSel(index);
}
//���ָ���������������Ƿ�Ϸ�
BOOL CDriverBox::CheckDisk(LPCWSTR drv)
{  
   //��ʽ����������
   CString dr(drv);
   dr.MakeLower();
   //���������б��в����Ƿ����ָ����������
   POSITION pos=m_drvList.GetHeadPosition();
   while(pos)
   {
	   //ָ�������������ڣ��Ϸ�
	   if(m_drvList.GetNext(pos)==dr) return TRUE;
   }
   //û�У����Ϸ�
   return FALSE;
}
