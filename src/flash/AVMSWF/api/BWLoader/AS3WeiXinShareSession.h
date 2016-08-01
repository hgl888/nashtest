#ifndef _AS3WeiXinShareSession_
#define _AS3WeiXinShareSession_

class XDrawDib;
class SBitmapCore;
#include "AS3DisplayObject.h"

namespace avmplus
{
	namespace NativeID
	{
		class WeiXinShareSessionClassSlots
		{
			friend class SlotOffsetsAndAsserts;
		public:
		private:
		};
		class WeiXinShareSessionObjectSlots
		{
			friend class SlotOffsetsAndAsserts;
		public:
		private:
		};
	}
}

namespace avmshell
{
	class RectangleObject;
	class PointObject;
	class BitmapFilterObject;
	class WeiXinShareSessionObject;
	class ColorTransformObject;
	class MatrixObject;
	class ByteArrayObject;
	class BitmapDataObject;
	class DisplayObjectObject;

	class WeiXinShareSessionClass : public ClassClosure
	{
	public:
		WeiXinShareSessionClass(VTable *vtable);
		virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype);
		WeiXinShareSessionObject* AS3_GetWeiXinShareSession();
	private:
		friend class avmplus::NativeID::SlotOffsetsAndAsserts;
		avmplus::NativeID::WeiXinShareSessionClassSlots m_slots_WeiXinShareSessionClass;
	};

	class WeiXinShareSessionObject : public ScriptObject
	{
	public:
		WeiXinShareSessionObject(VTable* vtable, ScriptObject* proto, int capacity);
		virtual void Release();
		virtual void SetObject(void*pObject);

	public:
		bool AS3_isWeiXinIstalled();
		 //����text��Ϣ��Ϣ��΢��
 		 int AS3_sendText(int sendType, Stringp text);
 		 //����photo��Ϣ��Ϣ��΢��
 		 int AS3_sendPhoto(int sendType, BitmapDataObject *picData);
 		 //����link��Ϣ��Ϣ��΢��
 		 int AS3_sendLink(int sendType, Stringp title, Stringp description, BitmapDataObject * thumbPicData, Stringp webpageUrl);
 		 //����music��Ϣ��Ϣ��΢��
 		 int AS3_sendMusic(int sendType, Stringp title, Stringp description, BitmapDataObject * thumbPicData, Stringp musicUrl, Stringp musicDataUrl);
 		 //����video����Ϣ��Ϣ��΢��
 		 int AS3_sendVedio(int sendType, Stringp title, Stringp description, BitmapDataObject * thumbPicData, Stringp videoUrl);
 		 //����app��Ϣ��Ϣ��΢��
 		 int AS3_sendAppMessage(int sendType, Stringp title, Stringp description, BitmapDataObject * thumbPicData, Stringp extInfo, Stringp url, ByteArrayObject * fileData);
 		 //���ͷ�gif��Ϣ��Ϣ��΢��,emotionDataΪ��gif����
 		 int AS3_sendNotGifContent(int sendType, BitmapDataObject *thumbPicData,ByteArrayObject *emotionData);
 		 //����gif��Ϣ��Ϣ��΢��,emotionDataΪgif����
 		 int AS3_sendGifContent(int sendType, BitmapDataObject *thumbPicData,ByteArrayObject * emotionData);
 		 //�����ļ���Ϣ��Ϣ��΢��
 		 int AS3_sendFileContent(int sendType, Stringp title, Stringp description, BitmapDataObject *thumbPicData, ByteArrayObject *fileData, Stringp fileExt);

	private:
		friend class avmplus::NativeID::SlotOffsetsAndAsserts;
		avmplus::NativeID::WeiXinShareSessionObjectSlots m_slots_WeiXinShareSessionObject;
	};
}

#endif
