



#if !defined(ZCFILE_H_)
#define ZCFILE_H_

#include <f32file.h>

/*
*�д�����*/

class ZCFile{
	protected:
		RFs fsession;
	public:
		ZCFile();
		~ZCFile();
		//////////////////////////////////////////////////////////////
		//ɾ���ļ�
		int ZCDeleteFile(const TDesC& fileName);

		/////////////////////////////////////////////////////////////
		//ɾ��Ŀ¼,Ŀ¼�±���Ϊ��
		int ZCDeleteDirectory(const TDesC& strPath);

		////////////////////////////////////////////////////////////
		//����Ŀ¼
		int ZCCreateDirectory(const TDesC& strPath);

		///////////////////////////////////////////////////////////
		//�õ��������б�
		void ZCGetDriverList(TDriveList &drvelist);
		
		///////////////////////////////////////////////////////////
		//�õ��̷�
		void ZCGetDrverChar(int aDriver,TUint &aChar);
		
		///////////////////////////////////////////////////////////
		//�õ���������
		void ZCGetDriverName(int aDriver,TDes &aDriverName);
		
		////////////////////////////////////////////////////////////
		//������������
		void ZCSetDriverName(int aDriver,const TDes &aDriverName);

		////////////////////////////////////////////////////////////
		//�鿴�Ƿ����ļ��� �ɹ����ش���0��ʧ�ܷ���С��0
		int ZCIsDir(const TDesC& fileName);
		
		////////////////////////////////////////////////////////////
		//ȡ���ļ����ļ��е�����
		int ZCGetEntry(const TDesC& fileName,TEntry&entry);
		
		////////////////////////////////////////////////////////////
		//ȡ��ָ��Ŀ¼�µ�������,��CDirָ����ܷ���ֵ��ʹ�ý�����delete
		CDir* ZCGetDir(const TDesC& strPath);
		////////////////////////////////////////////////////////////
		//����ļ����Ƿ����,����������·����
		int ZCDirFinder(const TDesC& strPath,const TDesC& fileName,TFileName& FullFileName);
		
		////////////////////////////////////////////////////////////
		//����ļ��Ƿ���ڣ����ҷ����ļ�����·��
		int ZCFileFinder(const TDesC& strPath,const TDesC& fileName,TFileName& FullFileName);
		
};
#endif
