// DirTree.cpp : implementation file
//

#include "stdafx.h"
#include "DirTree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDirTree

CDirTree::CDirTree()
{
	m_nCount=1;
}

CDirTree::~CDirTree()
{
}


BEGIN_MESSAGE_MAP(CDirTree, CListBox)
	//{{AFX_MSG_MAP(CDirTree)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDirTree message handlers
//�ȽϺ�������ʾ�ܲ�����û�в���
int CDirTree::CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct) 
{
	// TODO: Add your code to determine the sorting order of the specified items
	// return -1 = item 1 sorts before item 2
	// return 0 = item 1 and item 2 sort the same
	// return 1 = item 1 sorts after item 2
	
	return 0;
}
//������Ŀ
void CDirTree::DrawItem(LPDRAWITEMSTRUCT lpDS) 
{
	// TODO: Add your code to draw the specified item
	if(lpDS->itemID==LB_ERR) return;
	CDC* pDC=CDC::FromHandle(lpDS->hDC);
	//
	CRect r(lpDS->rcItem);	
	BOOL bEnable=(GetStyle()&WS_DISABLED)==0;
	
	CBrush br;
	//������Ŀ����
	if( bEnable&&(/*(lpDS->itemAction & (ODA_SELECT |ODA_SELECT|ODA_FOCUS))
		&&*/(lpDS->itemState & ODS_SELECTED))|
		((lpDS->itemState&ODS_COMBOBOXEDIT)&&(lpDS->itemState&ODS_FOCUS)))
	{  //ѡ�в�������
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
	//������ʾͼ���б�
	CImageList list;
	list.Create(_T("IDB_DIRBROWNS"),16,0,0xffffff);	
	int image=2;
	//������ȷ����ʾͼ�����������
	if(lpDS->itemData>0) //����ĿΪ��Ŀ¼�е�һ��
	{   //���ֱ�ʾĿ¼����
		r.left+=(lpDS->itemData-1)*8;
		if(lpDS->itemData==(UINT)m_nCount) image++;
	}
	else //����ĿΪ��ǰĿ¼�е�һ����Ŀ¼ 
		{r.left+=m_nCount*8;image=1;}
	list.Draw(pDC,image,r.TopLeft(),bEnable?ILD_TRANSPARENT:ILD_BLEND);	
	r.left+=20;
	//��ʾĿ¼��
	CString text=m_pathList.GetAt(m_pathList.FindIndex(lpDS->itemID));
	if(lpDS->itemID==0) text+='\\';
	pDC->TextOut(r.left,r.top,text);
}

void CDirTree::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	// TODO: Add your code to determine the size of specified item
	
}

//���õ�ǰ��ʾĿ¼������ΪҪ���õ�Ŀ¼��ȫ��
//����ʱͬʱ���б��м���Ŀ¼���ַ��������б���ʾ
//�丽�����ݵ�ֵ����0ʱ��ʾ��ǰĿ¼�µ���Ŀ¼����������
//����0ʱ��ʾ�Ӹ�Ŀ¼��ʼ�ļ���
BOOL CDirTree::SetPath(LPCWSTR path)
{
	//���ԭ���б��е�����
    ResetContent();
	m_pathList.RemoveAll();
	ASSERT(strlen(path)>2);
	ASSERT(path[2]=='\\'||path[2]=='/');
	//�����Ŀ¼
	CString temp(path,2);
	//CString fPath=temp;
	//temp+='\\';
	int index=AddString(temp);
	m_pathList.AddTail(temp);
	SetItemData(index,1);
	m_nCount=1;
	LPCWSTR p=path+3;
	//���������Ŀ¼
	while(p[0])
	{
		temp.Empty();
		while(p[0])
		{
			if(p[0]=='\\'||p[0]=='/') {p++;break;}
			temp+=p[0];
			p++;
		}
		if(temp.IsEmpty()) continue;
		index=AddString(temp);		
		m_pathList.AddTail(temp);
		m_nCount++;
		SetItemData(index,m_nCount);		
	}
	//���ò��Һ������뵱ǰĿ¼��ȫ����Ŀ¼
	WIN32_FIND_DATA data;
	CString fPath=path;fPath+=_T("\\*.*");
	HANDLE handle=::FindFirstFile(fPath,&data);
	while(handle!=INVALID_HANDLE_VALUE)
	{
		if((data.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)&&
			(data.dwFileAttributes&FILE_ATTRIBUTE_HIDDEN)==0)
		{   //ֻ�����������Ŀ¼��
			//if(strcmp(data.cFileName,".")!=0&&
			//   strcmp(data.cFileName,"..")!=0)
			if(data.cFileName[0]!='.')
			{
				index=AddString(data.cFileName);
				SetItemData(index,0);
				m_pathList.AddTail(data.cFileName);
			}
		}
		if(!::FindNextFile(handle,&data)) break;
	}
	SetCurSel(m_nCount-1);
	return TRUE;
}
//�õ�ѡ�е�Ŀ¼ȫ��
BOOL CDirTree::GetSelected(CString &path)
{
   //�õ�ѡ�����Ŀ����
   int index=GetCurSel();
   ASSERT(m_pathList.GetCount()>=m_nCount);
   if(index<0||index>=m_pathList.GetCount()) return FALSE;
   DWORD iData=GetItemData(index);
   if(iData>0)//��ѡ�еĶ���Ϊ��Ŀ¼�е�ĳһ��
   {
	   path.Empty();
	   ASSERT(iData<=(UINT)m_nCount);
	   POSITION pos=m_pathList.GetHeadPosition();
	   while(iData--)
	   {   if(!path.IsEmpty()) path+='\\';
		   path+=m_pathList.GetNext(pos);
	   }
	   if(GetItemData(index)==1) path+='\\';
	   return TRUE;
   }
   else //��ѡ�е�Ŀ¼Ϊ��ǰĿ¼��һ����Ŀ¼
   {
	  path.Empty();
	  iData=m_nCount;
	  POSITION pos=m_pathList.GetHeadPosition();
	  while(iData--)
	  {   path+=m_pathList.GetNext(pos);
	      path+='\\';
	  }
   }
   path+=m_pathList.GetAt(m_pathList.FindIndex(index));
   return TRUE;
}
