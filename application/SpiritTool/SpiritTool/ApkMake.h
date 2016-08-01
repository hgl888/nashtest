#pragma once

#include "PointerArray.h"
#include "SpiritData.h"

class CApkMake
{
public:
	class MakeListener
	{
	public:
		virtual void onListen(int type,unsigned long data)=0;
	};
public:
	static CApkMake* Singleton()
	{
		static CApkMake* sl = NULL;
		if(sl == NULL)
		{
			sl = new CApkMake();
		}
		return sl;
	}
public:
	CApkMake(void);
	~CApkMake(void);
public:
	//����Դ��·����sdk·��
	void setPath(const char* srcpath,const char* sdkpath);
	//��ʼ���
	void startMake();
	void stopMake();
	void setListener(MakeListener* listener);

	//���������
	void start();
	void end();
	void setDataArray(CPointerArray<CSpiritData>* data);
	int getMakedCount();
	int getMakingId();
public:
	DWORD CallBack();
private:
	void ready();
	void go();
	void modulatepath(const char *packagename,char *path);	//����·��
	void changestring(const char *appname,const char* ua,const char* channel,const char* fname);	//�޸�strings.xml
	void changeDesktop(bool bDesktop,const char* fname);
private:
	static DWORD WINAPI ThreadProc(LPVOID lpParam); 
private:
	char *m_plOldPackageName;		//�������
	CPointerArray<CSpiritData>	*m_pArray;	//���ݶ���	
	int		m_nMakedCount;			//�Ѵ����
	HANDLE	m_hthread;				//�߳̾��
	HANDLE	m_hevent;				//�¼�����
	HANDLE	m_hclose;				//�ر��¼�
	HANDLE	m_hclosed;				//�Թر��¼�
	MakeListener*	m_pListener;	//������
	char*	m_plSrcpath;			//Դ��·��
	char*	m_plSdkpath;			//sdk·��
};

