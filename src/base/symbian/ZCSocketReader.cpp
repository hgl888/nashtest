/*
 ============================================================================
 Name		: ZCSocketReader.cpp
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CZCSocketReader implementation
 ============================================================================
 */

#include "ZCSocketReader.h"
#ifndef  KErrReadMsg
#	define  KErrReadMsg  "ErrRead::"
#endif

CZCSocketReader::CZCSocketReader(MReaderObserver &aObserver,RSocket &aSocket) :
	CActive(EPriorityStandard) ,iTempBuf(0,0),m_iObserver(aObserver),m_pSocket(aSocket)// Standard priority
	{
//		 m_pSocket=&aSocket;
//		 m_iObserver=&aObserver;
		 m_pBuf=NULL;
		 m_lWrite=NULL;
		 m_nMaxLen=0;
		 m_nDataLen=0;
		 iState=0;
		 iRequest=0;
		 m_bIsStart=false;
	}

CZCSocketReader* CZCSocketReader::NewLC(MReaderObserver &aObserver,RSocket &aSocket,int space)
	{
	CZCSocketReader* self = new (ELeave) CZCSocketReader(aObserver,aSocket);
	CleanupStack::PushL(self);
	self->ConstructL(space);
	return self;
	}

CZCSocketReader* CZCSocketReader::NewL(MReaderObserver &aObserver,RSocket &aSocket,int space)
	{
	CZCSocketReader* self = CZCSocketReader::NewLC(aObserver,aSocket,space);
	CleanupStack::Pop(); // self;
	return self;
	}

void CZCSocketReader::ConstructL(int space)
	{
	CActiveScheduler::Add(this); // Add to scheduler
	m_nMaxLen=space;
	m_pBuf=new unsigned char[m_nMaxLen];
	m_lWrite=m_pBuf;
//	StartL();
	}

CZCSocketReader::~CZCSocketReader()
	{
	Cancel(); // Cancel any request, if outstanding
	Release();
	}

void CZCSocketReader::DoCancel()
	{
	if(IsActive())
		m_pSocket.CancelRecv();
	}

void CZCSocketReader::StartL()
	{
	Cancel(); // Cancel any request, just to be sure
	iTempBuf.Set(m_pBuf,m_nMaxLen,m_nMaxLen);
	iRequest=ERead;
	iStatus = 100;
//	int err = iStatus.iStatus;
//	int err1 = iStatus.iFlags;
	m_pSocket.RecvOneOrMore(iTempBuf,0,iStatus,m_nRecvLen);
//			err = iStatus.iStatus;
//			err1 = iStatus.iFlags;
			m_nDataLen+=m_nRecvLen();
//	SetActive();
//			err = iStatus.iStatus;
//			err1 = iStatus.iFlags;
	m_bIsStart = true;
	}

int CZCSocketReader::Read(char *buf,int len)
	{
	if(iState>0 && len>0)
		{
		int templen=(len>m_nDataLen)?m_nDataLen:len;     //ȡ����Ч���ݳ���   
		unsigned char *read;
		int i;
		
		//��������
		for(i=0;i<=templen;i++) buf[i]=m_pBuf[i]; 
		read=m_pBuf+templen;
		m_nDataLen-=templen;
		
		//�������ݿռ�
		for(i=0;i<=m_nDataLen;i++) m_pBuf[i]=read[i];
		m_lWrite=m_pBuf+m_nDataLen+1;
		
		//����������
		if(IsActive())
			return templen;    //����Ѿ���������ֱ�ӷ���
		else
			{
			iTempBuf.Set(m_lWrite,0,m_nMaxLen-m_nDataLen);
			m_pSocket.RecvOneOrMore(iTempBuf,0,iStatus,m_nRecvLen);
			iRequest=ERead;
			SetActive();
			}
		return templen;
		}
	return 0;
	}

int CZCSocketReader::SetSpace(int space)
	{
	if(IsActive() && iRequest==ERead ) return 0;              //����������������
	if(space<m_nDataLen) return 0;        //��������
	unsigned char *tempL;
	tempL=m_pBuf;
	m_pBuf=new unsigned char[space];
	memmove(m_pBuf,tempL,m_nDataLen);
	delete[] tempL;
	if(m_nDataLen==space) m_lWrite=NULL;
	else m_lWrite=m_pBuf+m_nDataLen+1;
	m_nMaxLen=space;
	return 1;
	}

int CZCSocketReader::GetSpace()
	{
	return m_nMaxLen;
	}

int CZCSocketReader::GetDataSpace()
	{
	return m_nDataLen;
	}

int CZCSocketReader::Check()
	{
	return m_nDataLen!=0;
//	int err = iStatus.iStatus;
//	int err1 = iStatus.iFlags;
//	if(err1 != 2)
//		int a=0;
//	if(err == 0 && err1 == 2)
//		return false;
//	else
//		return false;
	}


int CZCSocketReader::Release()
	{
	Cancel();
//	Stop();
	delete m_pBuf;
	m_pBuf=NULL;
	m_lWrite=NULL;
	iState&= ~KISSTART;
	iRequest=0;
	m_nMaxLen=0;
	m_nDataLen=0;
	return 0;
	}


void CZCSocketReader::RunL()
	{
	int err=iStatus.Int();
	switch(iRequest)
		{
		case ERead:
			{
			if(err==KErrNone)
				{
				if(!(iState & KISSTART))
					iState|=KISSTART;
				m_iObserver.OnReceive(m_pBuf,err);
				}
			else
				{
				iState|=KREADERR;
//				Fault();            //�������ݽ���ʧ��
				unsigned char msg[]=KErrReadMsg;
				m_iObserver.OnReceive(msg,err);
				}
			
			m_nDataLen+=m_nRecvLen();
			if(m_nDataLen>=m_nMaxLen)
				m_lWrite=NULL;
			else
				m_lWrite+=m_nRecvLen()+1;
			}
			break;
		default:
			{
			
			}
			break;
		}
	}

TInt CZCSocketReader::RunError(TInt aError)
	{
	return aError;
	}
