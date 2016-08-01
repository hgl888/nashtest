#pragma once

#include "GGType.h"	// Added by ClassView
#include "XString.h"
#include "XMutex.h"

#define ACC_CMD_INIT 3999

class _XEXT_CLASS XAcc
{
public:
	XAcc();
	~XAcc();
	static bool Init();
	//��ȡ������Ӧ���ۺϣ�����
	static double getAccX();
	static double getAccY();
	static double getAccZ();
    //��ȡ������Ӧ����������
	static void getGAcc(double&x,double&y,double&z);
	//��ȡ������Ӧ�ļ��ٶȷ���
	static void getAAcc(double&x,double&y,double&z);	
#ifdef _WIN32
	static HWND m_hMainWnd;
#endif
    static void SetAcc(double x,double y,double z);
};