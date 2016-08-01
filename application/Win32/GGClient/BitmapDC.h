// BitmapDC.h: interface for the CBitmapDC class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BITMAPDC_H__645B9AA8_11C9_11D3_AD5B_C31343320A91__INCLUDED_)
#define AFX_BITMAPDC_H__645B9AA8_11C9_11D3_AD5B_C31343320A91__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#ifndef VGC32_EXT_CLASS
#define VGC32_EXT_CLASS AFX_CLASS_IMPORT
#endif
////////////////////////////////////////////////////////
//�ڴ��ͼ�����
class CBitmapDC : public CDC  
{
public:
	//�õ�λͼ����
	CBitmapDC(){m_pOldBmp=NULL;}
	BOOL GetDib( HGLOBAL pDib, BITMAPINFOHEADER *pHead );
	//����ϵͳ���ݵ��ڴ���.W,Hͼ��߶�
	BOOL CreateBitmapDC( int W, int H);
	//W,Hͼ��߶�
	CBitmapDC(int W,int H);
	CBitmapDC(CBitmap*bmp);
	virtual ~CBitmapDC();

protected:
	CBitmap m_bitmap;
	CBitmap* m_pOldBmp;
};

#endif // !defined(AFX_BITMAPDC_H__645B9AA8_11C9_11D3_AD5B_C31343320A91__INCLUDED_)
