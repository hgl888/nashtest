#ifndef _AS3ContextMenuBuiltInItems_
#define _AS3ContextMenuBuiltInItems_
namespace avmplus{namespace NativeID{
class ContextMenuBuiltInItemsClassSlots{
friend class SlotOffsetsAndAsserts;
public://Declare your STATIC AS3 slots here!!!

private:};
class ContextMenuBuiltInItemsObjectSlots{
friend class SlotOffsetsAndAsserts;
public:
	int forwardAndBack;//�����û�������ʱ�� SWF �ļ���ǰ�������һ֡����֡ SWF �ļ�����ʾ�����ԣ��� ContextMenuBuiltInItems 
	int loop;//�����û��� SWF �ļ�����Ϊ�ڵ������һ֡���Զ����¿�ʼ����֡ SWF �ļ�����ʾ�����ԣ��� ContextMenuBuiltInItems 
	int play;//�����û�������ͣ�� SWF �ļ�����֡ SWF �ļ�����ʾ�����ԣ��� ContextMenuBuiltInItems 
	int print;//�����û�����ʾ��֡ͼ��������ӡ���� ContextMenuBuiltInItems 
	int quality;//�����û�������ʱ���� SWF �ļ��ķֱ��ʡ� ContextMenuBuiltInItems 
	int rewind;//�����û��� SWF �ļ�����Ϊ��ʱ��ѡ���ĵ�һ֡��ʼ���ţ���֡ SWF �ļ�����ʾ�����ԣ��� ContextMenuBuiltInItems 
	int save;//����װ�� Shockmachine ���û����� SWF �ļ��� ContextMenuBuiltInItems 
	int zoom;//�����û�������ʱ�Ŵ����С SWF �ļ��� 
	inline void SetData(ContextMenuBuiltInItemsObjectSlots&d)
	{
		VMPI_memcpy(this,&d,sizeof(ContextMenuBuiltInItemsObjectSlots));
	}
//Declare your MEMBER AS3 slots here!!!
private:};
}}

namespace avmshell{
	class ContextMenuBuiltInItemsObject;
	class ContextMenuBuiltInItemsClass : public ClassClosure
	{
	public:
		ContextMenuBuiltInItemsClass(VTable *vtable);
		ScriptObject *createInstance(VTable *ivtable, ScriptObject *delegate);
		ContextMenuBuiltInItemsObject* CreateItems();
	private:
#ifdef _SYMBIAN
	public:
#endif
		friend class avmplus::NativeID::SlotOffsetsAndAsserts;
		avmplus::NativeID::ContextMenuBuiltInItemsClassSlots m_slots_ContextMenuBuiltInItemsClass;
};
class ContextMenuBuiltInItemsObject : public ScriptObject
{
	public:
		ContextMenuBuiltInItemsObject(VTable* _vtable, ScriptObject* _delegate, int capacity);
	public:
		inline bool getForwardAndBack(){return m_slots_ContextMenuBuiltInItemsObject.forwardAndBack!=0;}
		inline bool getLoop(){return m_slots_ContextMenuBuiltInItemsObject.loop!=0;}
		inline bool getPlay(){return m_slots_ContextMenuBuiltInItemsObject.play!=0;}
		inline bool getPrint(){return m_slots_ContextMenuBuiltInItemsObject.print!=0;}
		inline bool getQuality(){return m_slots_ContextMenuBuiltInItemsObject.quality!=0;}
		inline bool getRewind(){return m_slots_ContextMenuBuiltInItemsObject.rewind!=0;}
		inline bool getSave(){return m_slots_ContextMenuBuiltInItemsObject.save!=0;}
		inline bool getZoom(){return m_slots_ContextMenuBuiltInItemsObject.zoom!=0;}
		inline void getForwardAndBack(bool b){m_slots_ContextMenuBuiltInItemsObject.forwardAndBack=b;}
		inline void setLoop(bool b){m_slots_ContextMenuBuiltInItemsObject.loop=b;}
		inline void setPlay(bool b){m_slots_ContextMenuBuiltInItemsObject.play=b;}
		inline void setPrint(bool b){m_slots_ContextMenuBuiltInItemsObject.print=b;}
		inline void setQuality(bool b){m_slots_ContextMenuBuiltInItemsObject.quality=b;}
		inline void setRewind(bool b){m_slots_ContextMenuBuiltInItemsObject.rewind=b;}
		inline void setSave(bool b){m_slots_ContextMenuBuiltInItemsObject.save=b;}
		inline void setZoom(bool b){m_slots_ContextMenuBuiltInItemsObject.zoom=b;}
		inline void SetData(ContextMenuBuiltInItemsObject*p)
		{
			m_slots_ContextMenuBuiltInItemsObject.SetData(p->m_slots_ContextMenuBuiltInItemsObject);
		}
		inline void ResetData()
		{
			VMPI_memset(&m_slots_ContextMenuBuiltInItemsObject,0,sizeof(avmplus::NativeID::ContextMenuBuiltInItemsObjectSlots));
		}
	private:
#ifdef _SYMBIAN
	public:
#endif
		friend class avmplus::NativeID::SlotOffsetsAndAsserts;
		avmplus::NativeID::ContextMenuBuiltInItemsObjectSlots m_slots_ContextMenuBuiltInItemsObject;
};}
#endif