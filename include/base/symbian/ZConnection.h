/*
 ============================================================================
 Name		: ZConnection.h
 Author	  : zhangchen
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CZConnection declaration
 ============================================================================
 */

#ifndef ZCONNECTION_H
#define ZCONNECTION_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <es_sock.h>
#include <in_sock.h>

// CLASS DECLARATION

/**
 *  CZConnection
 * 
 */
class CZConnection : public CBase
	{
public:
	static CZConnection* GetInstance();
public:
	CZConnection()
		{
		m_iapId=0;
		m_bProxy=false;
		}
	~CZConnection()
		{
		}
	void start();
	void close();
	void GetConnectionName(char*& name);
	bool IsProxy(){return m_bProxy;}
public:
	RSocketServ m_server;
	RConnection m_globalConnection;     //�������ӿ���
	TUint32		m_iapId;				//�����Id
	TInetAddr	m_address;				//����������Ϣ
	TBool		m_bProxy;				//�Ƿ��ô���
	};

#endif // ZCONNECTION_H
