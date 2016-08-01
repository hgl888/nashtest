#include "StdAfxflash.h"
#include "splayer.h"
#include "ShellCore.h"
using namespace avmplus;

//new adds
#include "AS3TouchscreenType.h"
//new adds end

#include "AS3Capabilities.h"
namespace avmshell{

bool CapabilitiesClass::avHardwareDisable=false;//[static] [read-only] ָ�����û�������ͷ����˷�ķ������Ѿ�ͨ������ʽ��ֹ (true) �������� (false)��
bool CapabilitiesClass::hasAccessibility=false;//[read-only] ָ������������֧�� (true) �븨�����ܽ���ͨ�ŵĻ��������У������ڲ�֧�� (false) ���ֹ��ܵĻ��������С�
bool CapabilitiesClass::hasAudio=true;//[read-only] ָ���������Ƿ��ھ�����Ƶ���ܵ�ϵͳ�����С�
bool CapabilitiesClass::hasAudioEncoder=false;//[read-only] ָ���������� (true) ���ǲ��� (false) ����Ƶ������������˷����Ƶ�������б��롣
bool CapabilitiesClass::hasEmbeddedVideo=false;//[read-only] ָ������������֧�� (true) Ƕ����Ƶ��ϵͳ�����У������ڲ�֧�� (false) Ƕ����Ƶ��ϵͳ�����С�
bool CapabilitiesClass::hasIME=true;//[read-only] ָ�����������ڰ�װ�� (true) ���뷨�༭�� (IME) ��ϵͳ�����У�������δ��װ (false) IME ��ϵͳ�����С�
bool CapabilitiesClass::hasMP3=true;//[read-only] ָ�����������ھ��� (true) MP3 ��������ϵͳ�����У�������û�� (false) MP3 ��������ϵͳ�����С�
bool CapabilitiesClass::hasPrinting=false;//[static] [read-only] ָ������������֧�� (true) ��ӡ��ϵͳ�����У������ڲ�֧�� (false) ��ӡ��ϵͳ�����С�
bool CapabilitiesClass::hasScreenBroadcast=false;//[static] [read-only] ָ����������֧�� (true) ����ͨ�� Flash Media Server ���е���Ļ�㲥Ӧ�ó��򣬻��ǲ�֧�� (false) ��������Ӧ�ó���
bool CapabilitiesClass::hasScreenPlayback=false;// : Boolean[static] [read-only] ָ����������֧�� (true) ͨ�� Flash Media Server ���е���Ļ�㲥Ӧ�ó���Ļطţ����ǲ�֧�� (false) ����Ӧ�ó���Ļطš�
bool CapabilitiesClass::hasStreamingAudio=true;// [read-only] ָ���������� (true) ���ǲ��� (false) ������Ƶ����
bool CapabilitiesClass::hasStreamingVideo=true;//[read-only] ָ���������� (true) ���ǲ��� (false) ������Ƶ����
bool CapabilitiesClass::hasTLS=false;//[static] [read-only] ָ���������� (true) �� (false) λ��ͨ�� NetConnection ֧�ֱ��� SSL �׽��ֵ�ϵͳ�ϡ�
bool CapabilitiesClass::hasVideoEncoder=false;//[read-only] ָ���������� (true) ���ǲ��� (false) ����Ƶ���������� Web ����ͷ����Ƶ�������б��롣
bool CapabilitiesClass::isDebugger=false;// : Boolean[static] [read-only] ָ��������������ĵ��԰汾 (true)��������ʽ�����İ汾 (false)��
const char*  CapabilitiesClass::language="zh-CN";//[static] [read-only] ָ�����в�������ϵͳ�����Դ��롣
bool CapabilitiesClass::localFileReadDisable=true;//[static] [read-only] ָ�����û�Ӳ�̵Ķ�ȡȨ�����Ѿ�ͨ������ʽ��ֹ (true) �������� (false)��
const char* CapabilitiesClass::manufacturer="JQ";//[static] [read-only] ָ�� Flash Player �������̣����ʽΪ��Adobe OSName����
const char* CapabilitiesClass::os="Windows XP";//[static] [read-only] ָ����ǰ�Ĳ���ϵͳ��
double CapabilitiesClass::pixelAspectRatio=1;//[static] [read-only] ָ����Ļ�����ظ߿�ȡ�
const char* CapabilitiesClass::playerType="ActiveX";
const char* CapabilitiesClass::screenColor="Color";//[read-only] ָ����Ļ����ɫ��
double CapabilitiesClass::screenDPI=72;
double CapabilitiesClass::screenResolutionX=240;
double CapabilitiesClass::screenResolutionY=320;// : Number
const char* CapabilitiesClass::version="WIN 11,1,102,62";
									   //"WIN 10,0,45,3";

//new adds
bool CapabilitiesClass::m_isEmbeddedInAcrobat = false;	//ָ�� Flash ����ʱ�Ƿ�Ƕ���� Acrobat 9.0 ����߰汾�򿪵� PDF �ļ��У�����ǣ���Ϊ true������Ϊ false�� 
bool CapabilitiesClass::m_supports32BitProcesses = true;
bool CapabilitiesClass::m_supports64BitProcesses = false;

const char *CapabilitiesClass::cpuArchitecture = "ARM";	//X86,ARM...
const char *CapabilitiesClass::maxLevelIDC = "";	//�����ͻ���Ӳ��֧�ֵ���� H.264 �� IDC��
//new adds end

CapabilitiesClass::CapabilitiesClass(VTable* cvtable):ClassClosure(cvtable)
{
	createVanillaPrototype();
	InitDatas();
	MakeString();
	//prototype = new (core()->GetGC(), cvtable->getExtraSize())CapabilitiesObject(cvtable, toplevel()->objectClass->prototype, 0);
	//Add your construct code here...
};

void CapabilitiesClass::InitDatas()
{
		AvmCore*c=core();
		kLanguage=c->newConstantStringLatin1(language);//[static] [read-only] ָ�����в�������ϵͳ�����Դ��롣
 	 	localFileReadDisable=false;//[static] [read-only] ָ�����û�Ӳ�̵Ķ�ȡȨ�����Ѿ�ͨ������ʽ��ֹ (true) �������� (false)��
		kManufacturer=c->newConstantStringLatin1(manufacturer);//[static] [read-only] ָ�� Flash Player �������̣����ʽΪ��Adobe OSName����
		kOs=c->newConstantStringLatin1(os);//[static] [read-only] ָ����ǰ�Ĳ���ϵͳ��		
		kPlayerType=c->newConstantStringLatin1(playerType);
		kScreenColor=c->newConstantStringLatin1(screenColor);//[read-only] ָ����Ļ����ɫ��
		XSWFPlayer*player=((ShellCore*)c)->GetPlayer();
		screenResolutionX=player->m_winSize.cx;
		screenResolutionY=player->m_winSize.cy;// : Number		
		kVersion=c->newConstantStringLatin1(version);

		//new adds
		m_pLanguages = toplevel()->arrayClass->newArray(0);
		m_pCpuArchitecture = c->newConstantStringLatin1(cpuArchitecture);
		m_pMaxLevelIDC = c->newConstantStringLatin1(maxLevelIDC);
//		m_pTouchscreenType = ((ShellToplevel *)toplevel())->getTouchscreenTypeClass()->GetSlotFINGER();
		//new adds end
}
void CapabilitiesClass::MakeString()
{
	AvmCore*c=core();
	Stringp s=c->newConstantStringLatin1("avd=");
	Stringp ts=c->newConstantStringLatin1("t");
	Stringp fs=c->newConstantStringLatin1("f");
	s=s->concatStrings(s,avHardwareDisable?ts:fs);
	s=s->concatStrings(s,c->newConstantStringLatin1("&acc="));
	s=s->concatStrings(s,hasAccessibility?ts:fs);
	s=s->concatStrings(s,c->newConstantStringLatin1("&a="));
	s=s->concatStrings(s,hasAudio?ts:fs);
	s=s->concatStrings(s,c->newConstantStringLatin1("&ae="));
	s=s->concatStrings(s,hasAudioEncoder?ts:fs);
	s=s->concatStrings(s,c->newConstantStringLatin1("&ev="));
	s=s->concatStrings(s,hasAudioEncoder?ts:fs);
	s=s->concatStrings(s,c->newConstantStringLatin1("&ime="));
	s=s->concatStrings(s,hasIME?ts:fs);
	s=s->concatStrings(s,c->newConstantStringLatin1("&mp3="));
	s=s->concatStrings(s,hasMP3?ts:fs);
	s=s->concatStrings(s,c->newConstantStringLatin1("&pr="));
	s=s->concatStrings(s,hasPrinting?ts:fs);
	s=s->concatStrings(s,c->newConstantStringLatin1("&sb="));
	s=s->concatStrings(s,hasScreenBroadcast?ts:fs);
	s=s->concatStrings(s,c->newConstantStringLatin1("&sp="));
	s=s->concatStrings(s,hasScreenPlayback?ts:fs);
	s=s->concatStrings(s,c->newConstantStringLatin1("&sa="));
	s=s->concatStrings(s,hasStreamingAudio?ts:fs);
	s=s->concatStrings(s,c->newConstantStringLatin1("&sv="));
	s=s->concatStrings(s,hasStreamingVideo?ts:fs);
	s=s->concatStrings(s,c->newConstantStringLatin1("&tls="));
	s=s->concatStrings(s,hasTLS?ts:fs);
	s=s->concatStrings(s,c->newConstantStringLatin1("&ve="));
	s=s->concatStrings(s,hasVideoEncoder?ts:fs);
	s=s->concatStrings(s,c->newConstantStringLatin1("&deb="));
	s=s->concatStrings(s,isDebugger?ts:fs);
	s=s->concatStrings(s,c->newConstantStringLatin1("&l="));
	s=s->concatStrings(s,Toplevel::escape(this,kLanguage));
	s=s->concatStrings(s,c->newConstantStringLatin1("&lfd="));
	s=s->concatStrings(s,localFileReadDisable?ts:fs);
	s=s->concatStrings(s,c->newConstantStringLatin1("&m="));
	s=s->concatStrings(s,Toplevel::escape(this,kManufacturer));
	s=s->concatStrings(s,c->newConstantStringLatin1("&os="));
	s=s->concatStrings(s,Toplevel::escape(this,kOs));
	s=s->concatStrings(s,c->newConstantStringLatin1("&ar="));
	s=s->concatStrings(s,c->doubleToString(pixelAspectRatio));
	s=s->concatStrings(s,c->newConstantStringLatin1("&pt="));
	s=s->concatStrings(s,Toplevel::escape(this,kPlayerType));
	s=s->concatStrings(s,c->newConstantStringLatin1("&col="));
	s=s->concatStrings(s,Toplevel::escape(this,kScreenColor));
	s=s->concatStrings(s,c->newConstantStringLatin1("&dp="));
	s=s->concatStrings(s,c->doubleToString(screenDPI));
	s=s->concatStrings(s,c->newConstantStringLatin1("&r="));
	s=s->concatStrings(s,c->doubleToString(screenResolutionX));
	s=s->concatStrings(s,c->newConstantStringLatin1("x"));
	s=s->concatStrings(s,c->doubleToString(screenResolutionY));
	s=s->concatStrings(s,c->newConstantStringLatin1("&v="));
	s=s->concatStrings(s,Toplevel::escape(this,kVersion));

}

ScriptObject* CapabilitiesClass::createInstance(VTable *ivtable, ScriptObject* prototype)
{
	return new (core()->GetGC(), ivtable->getExtraSize()) CapabilitiesObject(ivtable, prototype, 0);
	//AS3 'new' opt...Add your init code here...
}
CapabilitiesObject::CapabilitiesObject(VTable *vtable, ScriptObject* proto, int capacity): ScriptObject(vtable, proto, 0)
{
	//Add your construct code here...
}
//////////////////////////////////////////////////////////
//Native Method start...
/*AvmBox CapabilitiesObject::AS3_avHardwareDisable_get(AvmMethodEnv, uint32_t, AvmBox* argv)
{
	//Add your act code here...
	return kAvmThunkUndefined;//Modify this please!
}

AvmBox CapabilitiesObject::AS3_hasAccessibility_get(AvmMethodEnv, uint32_t, AvmBox* argv)
{
	//Add your act code here...
	return kAvmThunkUndefined;//Modify this please!
}

AvmBox CapabilitiesObject::AS3_hasAudio_get(AvmMethodEnv, uint32_t, AvmBox* argv)
{
	//Add your act code here...
	return kAvmThunkUndefined;//Modify this please!
}

AvmBox CapabilitiesObject::AS3_hasAudioEncoder_get(AvmMethodEnv, uint32_t, AvmBox* argv)
{
	//Add your act code here...
	return kAvmThunkUndefined;//Modify this please!
}

AvmBox CapabilitiesObject::AS3_hasEmbeddedVideo_get(AvmMethodEnv, uint32_t, AvmBox* argv)
{
	//Add your act code here...
	return kAvmThunkUndefined;//Modify this please!
}

AvmBox CapabilitiesObject::AS3_hasIME_get(AvmMethodEnv, uint32_t, AvmBox* argv)
{
	//Add your act code here...
	return kAvmThunkUndefined;//Modify this please!
}

AvmBox CapabilitiesObject::AS3_hasMP3_get(AvmMethodEnv, uint32_t, AvmBox* argv)
{
	//Add your act code here...
	return kAvmThunkUndefined;//Modify this please!
}

AvmBox CapabilitiesObject::AS3_hasPrinting_get(AvmMethodEnv, uint32_t, AvmBox* argv)
{
	//Add your act code here...
	return kAvmThunkUndefined;//Modify this please!
}

AvmBox CapabilitiesObject::AS3_hasScreenBroadcast_get(AvmMethodEnv, uint32_t, AvmBox* argv)
{
	//Add your act code here...
	return kAvmThunkUndefined;//Modify this please!
}

AvmBox CapabilitiesObject::AS3_hasScreenPlayback_get(AvmMethodEnv, uint32_t, AvmBox* argv)
{
	//Add your act code here...
	return kAvmThunkUndefined;//Modify this please!
}

AvmBox CapabilitiesObject::AS3_hasStreamingAudio_get(AvmMethodEnv, uint32_t, AvmBox* argv)
{
	//Add your act code here...
	return kAvmThunkUndefined;//Modify this please!
}

AvmBox CapabilitiesObject::AS3_hasStreamingVideo_get(AvmMethodEnv, uint32_t, AvmBox* argv)
{
	//Add your act code here...
	return kAvmThunkUndefined;//Modify this please!
}

AvmBox CapabilitiesObject::AS3_hasTLS_get(AvmMethodEnv, uint32_t, AvmBox* argv)
{
	//Add your act code here...
	return kAvmThunkUndefined;//Modify this please!
}

AvmBox CapabilitiesObject::AS3_hasVideoEncoder_get(AvmMethodEnv, uint32_t, AvmBox* argv)
{
	//Add your act code here...
	return kAvmThunkUndefined;//Modify this please!
}

AvmBox CapabilitiesObject::AS3_isDebugger_get(AvmMethodEnv, uint32_t, AvmBox* argv)
{
	//Add your act code here...
	return kAvmThunkUndefined;//Modify this please!
}

AvmBox CapabilitiesObject::AS3_language_get(AvmMethodEnv, uint32_t, AvmBox* argv)
{
	//Add your act code here...
	return kAvmThunkUndefined;//Modify this please!
}

AvmBox CapabilitiesObject::AS3_localFileReadDisable_get(AvmMethodEnv, uint32_t, AvmBox* argv)
{
	//Add your act code here...
	return kAvmThunkUndefined;//Modify this please!
}

AvmBox CapabilitiesObject::AS3_manufacturer_get(AvmMethodEnv, uint32_t, AvmBox* argv)
{
	//Add your act code here...
	return kAvmThunkUndefined;//Modify this please!
}

AvmBox CapabilitiesObject::AS3_os_get(AvmMethodEnv, uint32_t, AvmBox* argv)
{
	//Add your act code here...
	return kAvmThunkUndefined;//Modify this please!
}

AvmBox CapabilitiesObject::AS3_pixelAspectRatio_get(AvmMethodEnv, uint32_t, AvmBox* argv)
{
	//Add your act code here...
	return kAvmThunkUndefined;//Modify this please!
}

AvmBox CapabilitiesObject::AS3_playerType_get(AvmMethodEnv, uint32_t, AvmBox* argv)
{
	//Add your act code here...
	return kAvmThunkUndefined;//Modify this please!
}

AvmBox CapabilitiesObject::AS3_screenColor_get(AvmMethodEnv, uint32_t, AvmBox* argv)
{
	//Add your act code here...
	return kAvmThunkUndefined;//Modify this please!
}

AvmBox CapabilitiesObject::AS3_screenDPI_get(AvmMethodEnv, uint32_t, AvmBox* argv)
{
	//Add your act code here...
	return kAvmThunkUndefined;//Modify this please!
}

AvmBox CapabilitiesObject::AS3_screenResolutionX_get(AvmMethodEnv, uint32_t, AvmBox* argv)
{
	//Add your act code here...
	return kAvmThunkUndefined;//Modify this please!
}

AvmBox CapabilitiesObject::AS3_screenResolutionY_get(AvmMethodEnv, uint32_t, AvmBox* argv)
{
	//Add your act code here...
	return kAvmThunkUndefined;//Modify this please!
}

AvmBox CapabilitiesObject::AS3_serverString_get(AvmMethodEnv, uint32_t, AvmBox* argv)
{
	//Add your act code here...
	return kAvmThunkUndefined;//Modify this please!
}

AvmBox CapabilitiesObject::AS3_version_get(AvmMethodEnv, uint32_t, AvmBox* argv)
{
	//Add your act code here...
	return kAvmThunkUndefined;//Modify this please!
}*/

//new adds
Stringp CapabilitiesClass::AS3_cpuArchitecture_get()
{
	return m_pCpuArchitecture;
}
bool CapabilitiesClass::AS3_isEmbeddedInAcrobat_get()
{
	return m_isEmbeddedInAcrobat;
}
ArrayObject* CapabilitiesClass::AS3_languages_get()
{
	return m_pLanguages;
}
Stringp CapabilitiesClass::AS3_maxLevelIDC_get()
{
	return m_pMaxLevelIDC;
}
bool CapabilitiesClass::AS3_supports32BitProcesses_get()
{
	return m_supports32BitProcesses;
}
bool CapabilitiesClass::AS3_supports64BitProcesses_get()
{
	return m_supports64BitProcesses;
}
Stringp CapabilitiesClass::AS3_touchscreenType_get()
{
	return m_pTouchscreenType;
}
//new adds end

//new adds 11
bool CapabilitiesClass::AS3_hasMultiChannelAudio(Stringp type)
{
	LOGWHERE();
	return false;
}

//new adds 11 end
}