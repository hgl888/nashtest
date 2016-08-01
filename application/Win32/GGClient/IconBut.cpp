// IconBut.cpp : implementation file
//

#include "stdafx.h"
#include "IconBut.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIconBut
//����ͼ��/�˵���ť
//resID:ͼ����Դ���ƣ���Ϊ�˵���ť���ò�������Ϊ��
//pMenuID:�˵���Դ���ƣ���Ϊͼ�갴ť���ò�������Ϊ��
//subID:�Ӳ˵���ţ���Ϊͼ�갴ť���ò�����Ч
CIconBut::CIconBut(BOOL bPopup)
{
	m_bLockDown=FALSE;
	m_bPopup=bPopup;
	m_strResID="IDI_ADD";
}

CIconBut::~CIconBut()
{
}


BEGIN_MESSAGE_MAP(CIconBut, CButton)
	//{{AFX_MSG_MAP(CIconBut)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//��Ϣ������������ʾ�ؼ�����ʱΪ��ʾ�ؼ��ṩ��ȷ����Ϣ���
LRESULT CIconBut::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	if( m_toolTip.GetSafeHwnd() != NULL )
	{ switch (message)
		{
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_MBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MOUSEMOVE:
		{
			MSG msg;
			msg.hwnd = m_hWnd;
			msg.message = message;
			msg.wParam = wParam;
			msg.lParam = lParam;

			m_toolTip.RelayEvent(&msg);
		}
		}
	}
	return CButton::WindowProc(message, wParam, lParam);
}
//�����ؼ�ʱ����
//enableTip��ʾ�Ƿ񴴽���ʾ�ؼ�
BOOL CIconBut::Create(BOOL enableTip )
{	
	//UINT nID=m_nID;
	if(!m_bPopup)
	{   //ͼ�갴ť�����ð�ťͼ��
		HICON icon=AfxGetApp( ) -> LoadIcon( m_strResID );
		if(icon) SetIcon( icon ); 
	}
	if( !enableTip ) return TRUE;
	//��Ҫ��ʾ�ؼ���������ʾ�ؼ���ֻ��ͼ�갴ť����Ҫ��ʾ����
	if( !m_toolTip.Create( this ) ) return FALSE;
	CString m_str;
	GetWindowText(m_str);
	//��ʾ����Ϊ��ť����
	m_toolTip.AddTool( this, m_str );
	m_toolTip.Activate(TRUE);	
	return TRUE;
}

//���ư�ť��ֻ�в˵���ť����Ҫ�ú���
//ͼ�갴ť�����Ի���ʽ��ʹ��ϵͳ�������л���
void CIconBut::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	//CButton::OnDrawItem(nIDCtl, lpDrawItemStruct);
	if( ( GetStyle( ) & BS_OWNERDRAW ) == BS_OWNERDRAW )
	{  //�ÿؼ�Ϊ�Ի���ʽ
		//if(m_bStayDown&&m_bLockDown) return;	  
	   CRect rect(lpDrawItemStruct->rcItem);
	   CDC* pDC=CDC::FromHandle(lpDrawItemStruct->hDC);
	   UINT state=lpDrawItemStruct->itemState;
	   UINT action=lpDrawItemStruct->itemAction;
	   //�õ�ϵͳ�İ�ť��������ɫ
	   HBRUSH hbrText=GetSysColorBrush(COLOR_BTNTEXT);
	   HBRUSH hbrFace=GetSysColorBrush(COLOR_3DFACE);
	   HBRUSH hOldBrush=(HBRUSH)SelectObject(pDC->m_hDC,hbrFace);
       //���Ʊ߽�
	   CRect edgeRect(rect);
	   pDC->Rectangle(rect);
	   if(state&ODS_FOCUS)
		   edgeRect.InflateRect(-1,-1);
	   //���ư�ť��
	   /*if((state&ODS_SELECTED)&&(action&ODA_SELECT)&&(state&ODS_FOCUS))
	   { //��ť��ѡ��
		 CPen pen(PS_SOLID,1,GetSysColor(COLOR_3DSHADOW));		 
		 CPen* pOldPen=pDC->SelectObject(&pen);		 		 
		 pDC->Rectangle(edgeRect);
		 pDC->SelectObject(pOldPen);
	   }
	   else*/
	   	 pDC->DrawEdge(edgeRect,EDGE_RAISED,BF_RECT|BF_SOFT);
	     //m_bStayDown=FALSE; }
	   //���ư�ť���ֱ���
	   CSize szTri=pDC->GetOutputTextExtent(_T("M"),1);
	   CString text;
	   GetWindowText(text);
	   CSize szText=pDC->GetOutputTextExtent(text,text.GetLength());
	   CSize szTotal(szText);
	   szTotal.cx+=szTri.cx;
	   CRect textRect=rect;
	   textRect.InflateRect(-((rect.Width()-szTotal.cx)/2),
		   -((rect.Height()-szTotal.cy)/2));
	   textRect.top--;
	   CRect triRect=textRect;
	   triRect.left=textRect.right-szTri.cx;
	   triRect.InflateRect(0,-((textRect.Height()-szTri.cy)/2));
	   pDC->SetBkMode(TRANSPARENT);
	   if(state&ODS_SELECTED)
		   textRect.OffsetRect(1,1);
	   pDC->DrawText(text,textRect,DT_SINGLELINE|DT_LEFT);
	   SelectObject(pDC->m_hDC,hbrText);
	   CPoint ptTri(textRect.left+szText.cx,textRect.top+3);
	   DrawTriangle(pDC,ptTri,10);
	   if(state&ODS_FOCUS)
	   {
		   CRect fRect(rect);
		   fRect.InflateRect(-4,-4);
		   pDC->DrawFocusRect(fRect);
	   }
	   SelectObject(pDC->m_hDC,hOldBrush);
	   if((action&ODA_SELECT)&&
		 (state&ODS_FOCUS)&&(state&ODS_SELECTED))
	        DisplayMenu();
	}
	
}
//��ʾ�����˵�
void CIconBut::DisplayMenu()
{   
   CMenu menu;
   //UINT nID=m_nID;
   if( !menu.LoadMenu(m_strResID) ) return;
   CMenu* m_pMenu=menu.GetSubMenu(0);
   if(m_pMenu==NULL) return;   
   CRect rect;
   GetWindowRect(&rect);
   m_bLockDown=TRUE;
   m_pMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,
	   rect.left,rect.bottom,GetParent(),rect);
   //SendMessage(WM_LBUTTONUP,0,MAKELPARAM(1,1));
   m_bLockDown=FALSE;
   //if( m_bStayDown ) Invalidate(FALSE);
}

//���Ʋ˵�������
void CIconBut::DrawTriangle(CDC *pDC, CPoint &pt, int size)
{  POINT tri[3]={pt.x,pt.y,pt.x+size,pt.y,
	             pt.x+size/2,pt.y+size/2};
   pDC->Polygon(tri,3);

}


//�ؼ�������ʱ�Զ����ã������ڲ�����
void CIconBut::PreSubclassWindow()
 {
 	Create(( GetStyle( ) & BS_OWNERDRAW ) != BS_OWNERDRAW);
	CButton::PreSubclassWindow(); 	
 }

BOOL CIconBut::Create(CWnd *pWnd, LPCTSTR pCaption,const RECT &rect, UINT nID)
{
	DWORD nFlag=WS_CHILD|WS_VISIBLE;
	if(m_bPopup) nFlag|=BS_OWNERDRAW;
	else         nFlag|=BS_ICON;
	if(!CButton::Create(pCaption,nFlag,rect,pWnd,nID)) return FALSE;
	return Create(TRUE);
}



//DEL void CIconBut::OnLButtonDown(UINT nFlags, CPoint point) 
//DEL {
//DEL 	// TODO: Add your message handler code here and/or call default
//DEL 	
//DEL 	CButton::OnLButtonDown(nFlags, point);
//DEL 	DisplayMenu();
//DEL }

void CIconBut::OnDestroy() 
{
	CButton::OnDestroy();
	
	// TODO: Add your message handler code here
	m_toolTip.DestroyWindow();
}
