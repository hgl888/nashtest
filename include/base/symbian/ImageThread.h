/*
 ============================================================================
 Name		: ImageThread.h
 Author	  : zhangchen
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CImageThread declaration
 ============================================================================
 */

#ifndef IMAGETHREAD_H
#define IMAGETHREAD_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include "XVector.h"
#include <fbs.h>
#include "XMutex.h"
#include "symbiandebug.h"

#define KImageMsgMax 63

/////////////////////////////////////////////
//����ͼƬû���ͷ�
#define KMemoryNotFree		-1000

////////////////////////////////////////////
//�ڴ治�����
#define KMemoryErr			-1
////////////////////////////////////////////
//newͼƬ���ɹ�
#define KNewErr				-2
////////////////////////////////////////////
//createͼƬ���ɹ�
#define KCreateErr			-3
////////////////////////////////////////////
//������ʱ��
#define KDebugErr			-6

/////////////////////////////////////////////
//

class XImageDec;
// CLASS DECLARATION

//��Ϣ
class XMessageEvent
	{
public:
	enum
	{
		ENewImage,
		ECreateImage,
		EReleaseImage,
		EReleaseXImage,
		EDecodeImage
	};
	XMessageEvent(CFbsBitmap*& image,TSize size = TSize(),TDisplayMode mode = EGray2); 
	~XMessageEvent();
	void ResetMsg(int EMsg)
		{
		m_nMessage = EMsg;
		m_bInQueue = false;
		m_nIndex = 0;
		}
public:
	int		m_nMessage;			//��Ϣ����
	XEvent*	m_hEvent;			//��Ϣ�¼�
	CFbsBitmap*& m_hImage;		//Ҫ�����ָ��
	TSize		m_Size;			//Ҫ����ߴ�
	TDisplayMode m_Mode;		//Ҫ����ģʽ
	bool		 m_bInQueue;	//�Ƿ��ڶ�����
	int			 m_nIndex;		//��Ϣ�����е�������¼
	};

class XMessageDecode : public XMessageEvent
	{
public:
	XMessageDecode(CFbsBitmap*& image,CFbsBitmap*& mask);
	~XMessageDecode();
//	void CallBack();
public:
	CFbsBitmap*& m_hMask;
	void		*m_hBuf;
	void		*m_hFname;
	XImageDec	*m_hDec;
	int			 m_nFrameIndex;				//Ҫ�����֡��
	int			 m_nFrames;					//ͼƬ��֡��
	XU8*		 m_pDelay;					//֡����ʱ��
	};

/**
 *  CImageThread
 * 
 */
class XImageThread : public CActive
	{
public:
	class MObserver
		{
		public:
		virtual bool ErrObserver(int err)=0; 
		};
public:
	// Constructors and destructor
	/**
	 * Constructor for performing 1st stage construction
	 */
	XImageThread();
	/**
	 * Destructor.
	 */
	virtual ~XImageThread();
	
	static XImageThread* NewL();
	static XImageThread* NewLC();

	//�õ�����
	static XImageThread* GetInstance()
			{
#ifdef _LostImage
			return NULL;
#endif
			static XImageThread* instance = NULL;
			if(instance == NULL)
				instance = XImageThread::NewL();
			return instance;
			}
public:
	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();
	//�̺߳���
	static int TFonction(TAny* aThread);
public:
	void RunL();                            //CActive virtual function     
	TInt RunError(TInt aError);             //CActive virtual function
	void DoCancel();                        //CActive virtual function
	//ѭ���ص�
	int CallBack();
	//ֹͣ�߳�
	int Stop();
	//���ûص�������
	void SetObserver(MObserver* observer){m_pObserver = observer;}
public:
	//����ͼ�񣬷��ش���ͼ���ID
	bool NewImage(XMessageEvent& msg);
	//����Id���ͼ��
	bool FreeImage(XMessageEvent& msg);
	//ɾ��XImage
	bool FreeXImage(XMessageDecode& msg);
	//������ͼ
	bool CreateBitmap(XMessageEvent& msg);
	//����ͼƬ
	int DecoderImage(XMessageDecode& msg);
	//���ͼ���߳��Ƿ��Ѿ�����
	bool IsStart(){return m_bIsStart;}
protected:
	void _Sleep();
protected:
	//����������Ϣ
	bool _AddMsg(XMessageEvent& msg);
	bool _AddHighMsg(XMessageEvent &msg);
	XMessageEvent* _GetMsg();
	bool _LostMsg(XMessageEvent& msg);
public:
	//����ʱ���첽
	void Starter();
	//�쳣����
	void ErrExecuted(int aErr);
protected:
	int _NewImage(XMessageEvent &msg);
	void _FreeImage(XMessageEvent &msg);
	int _CreateImage(XMessageEvent &msg);
	int _DecoderImage(XMessageDecode &msg);
	void _FreeXImage(XMessageDecode &msg);
protected:
	RThread 	m_iThread;						//�߳�
	RTimer		m_iTimer;						//�첽������
//	XVector<CFbsBitmap*>		m_rImageVector;			//���ݶ���
	int			m_nImageNum;					//����ͼ����Ŀ
	int			m_nCreateNum;					//����ͼ����Ŀ
	XEvent		m_iStop;						//�߳�ֹͣ��Ϣ
	XEvent		m_iStoped;						//�߳�ֹͣ��־
//	XEvent		m_iStart;						//�߳������¼�
	XMessageEvent	*m_rFlag[KImageMsgMax];						//ͬ����Ϣ
	XMessageEvent **m_hSetMsg;
	XMessageEvent **m_hGetMsg;		//���ж�дָ��
	XEvent		m_iEvent;						//�¼�,����������Ϣ�ͻᴥ������¼�
	bool		m_bIsStart;
//	TSize		m_iImageSize;					//����ͼ��ߴ�
//	TDisplayMode	m_nImageMode;				//ͼ��ģʽ
//	XVector<XMessageEvent*>		m_rEvent;		//�¼�
	MObserver	*m_pObserver;					//�쳣�¼��ص�
	};

#endif // IMAGETHREAD_H
