#include "StdAfxflash.h"
#include "ShellCore.h"
using namespace avmplus;
#include "XFilter.h"
#include "AS3BitmapFilter.h"
#include "AS3BevelFilter.h"// ��ʹ�� BevelFilter �����ʾ�������б��Ч���� 
//  BitmapFilter BitmapFilter ��������ͼ���˾�Ч���Ļ��ࡣ 
#include "AS3BitmapFilterQuality.h"// BitmapFilterQuality ���а�����ֵ�������� BitmapFilter ����ĳ���Ʒ�ʡ� 
#include "AS3BitmapFilterType.h"// BitmapFilterType ���а�����ֵ���������� BitmapFilter �����͡� 
#include "AS3BlurFilter.h"// ��ʹ�� BlurFilter �ཫģ���Ӿ�Ч��Ӧ������ʾ����  
#include "AS3ColorMatrixFilter.h"// ʹ�� ColorMatrixFilter ����Խ� 4 x 5 ����ת��Ӧ��������ͼ���ϵ�ÿ�����ص� RGBA ��ɫ�� Alpha ֵ�������ɾ���һ���µ� RGBA ��ɫ�� Alpha ֵ�Ľ����  
#include "AS3ConvolutionFilter.h" //ConvolutionFilter ��Ӧ�þ��������˾�Ч���� 
#include "AS3DisplacementMapFilter.h"// DisplacementMapFilter ��ʹ��ָ���� BitmapData ���󣨳�Ϊ�û�ͼͼ�񣩵�����ִֵ�ж����û��� 
#include "AS3DisplacementMapFilterMode.h"// DisplacementMapFilterMode ��Ϊ DisplacementMapFilter ��� mode �����ṩֵ�� 
#include "AS3DropShadowFilter.h"// ��ʹ�� DropShadowFilter ������ʾ�������ͶӰ��  
#include "AS3GlowFilter.h"// ʹ�� GlowFilter ����Զ���ʾ����Ӧ�÷���Ч����  
#include "AS3GradientBevelFilter.h"// ʹ�� GradientBevelFilter ����Զ���ʾ����Ӧ�ý���б��Ч����  
#include "AS3GradientGlowFilter.h" 

namespace avmshell{
BitmapFilterClass::BitmapFilterClass(VTable* cvtable):ClassClosure(cvtable)
{
	createVanillaPrototype();
	//prototype = new (core()->GetGC(), cvtable->getExtraSize())BitmapFilterObject(cvtable, toplevel()->objectClass->prototype, 0);
	//Add your construct code here...
};
ScriptObject* BitmapFilterClass::createInstance(VTable *ivtable, ScriptObject* prototype)
{
	return new (core()->GetGC(), ivtable->getExtraSize()) BitmapFilterObject(ivtable, prototype, 0);
	//AS3 'new' opt...Add your init code here...
}
BitmapFilterObject::BitmapFilterObject(VTable *vtable, ScriptObject* proto, int capacity): ScriptObject(vtable, proto, 0)
{
	//Add your construct code here...
}

BitmapFilterObject* BitmapFilterClass::CreateFilter(void*data)
{
	BitmapFilterObject*pFilter=NULL;
	ShellToplevel*top=(ShellToplevel*)toplevel();
	switch(((_XFilter*)data)->m_nFilterID)
	{
	case XFilterDropShadow:
		{
			DropShadowFilterClass*pClass=top->getDropShadowFilterClass();
			pFilter=pClass->CreateFilter(data);
		}break;
	case XFilterBlur:
		{
			BlurFilterClass*pClass=top->getBlurFilterClass();
			pFilter=pClass->CreateFilter(data);
		}break;
	case XFilterGlow:
		{
			GlowFilterClass*pClass=top->getGlowFilterClass();
			pFilter=pClass->CreateFilter(data);
		}break;
	case XFilterBevel:
		{
			BevelFilterClass*pClass=top->getBevelFilterClass();
			pFilter=pClass->CreateFilter(data);
		}break;
	case XFilterGradientGlow:
		{
			GradientGlowFilterClass*pClass=top->getGradientGlowFilterClass();
			pFilter=pClass->CreateFilter(data);
		}break;
	case XFilterConvolution:
		{
			ConvolutionFilterClass*pClass=top->getConvolutionFilterClass();
			pFilter=pClass->CreateFilter(data);
		}break;
	case XFilterColorMatrix:
		{
			ColorMatrixFilterClass*pClass=top->getColorMatrixFilterClass();
			pFilter=pClass->CreateFilter(data);
		}break;
	case XFilterGradientBevel:
		{
			GradientBevelFilterClass*pClass=top->getGradientBevelFilterClass();
			pFilter=pClass->CreateFilter(data);
		}break;
	default:
		break;
	}
	return pFilter;
}
//////////////////////////////////////////////////////////
//Native Method start...

}