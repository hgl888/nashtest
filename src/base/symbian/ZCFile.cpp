#include <f32file.h>
#include "ZCFile.h"

ZCFile::ZCFile()
{

}

ZCFile::~ZCFile()
{

}
//////////////////////////////////////////////////////////////
//ɾ���ļ�
int ZCFile::ZCDeleteFile(const TDesC& fileName)
{
	//�����ļ��������������ļ��Ự
	fsession.Connect();
	int err;
	
	err=fsession.Delete(fileName);
	//�ر��ļ��Ự
	fsession.Close();
	return err;
}

/////////////////////////////////////////////////////////////
//ɾ��Ŀ¼,Ŀ¼�±���Ϊ��
int ZCFile::ZCDeleteDirectory(const TDesC& strPath)
{
	//�ر��ļ��Ự
	fsession.Connect();
	int err;

		err=fsession.RmDir(strPath);
	//�ر��ļ��Ự
	fsession.Close();
	return err;
}

////////////////////////////////////////////////////////////
//����Ŀ¼
int ZCFile::ZCCreateDirectory(const TDesC& strPath)
{
	fsession.Connect();
	int err;

		err=fsession.MkDir(strPath);
	fsession.Close();
	return err;
}

///////////////////////////////////////////////////////////
//�õ��������б�
void ZCFile::ZCGetDriverList(TDriveList &drivelist)
	{
	fsession.Connect();
	fsession.DriveList(drivelist);        //�õ���ǰ�������б�
	fsession.Close();
	}

///////////////////////////////////////////////////////////
//�õ��̷�
void ZCFile::ZCGetDrverChar(int aDriver,TUint &aChar)
	{
	fsession.Connect();
	TChar buf;
	fsession.DriveToChar(aDriver,buf);
	fsession.Close();
	aChar=(TUint)buf;
	}

///////////////////////////////////////////////////////////
//�õ���������
void ZCFile::ZCGetDriverName(int aDriver,TDes &aDriverName)
	{
	fsession.Connect();
	fsession.GetDriveName(aDriver,aDriverName);
	fsession.Close();
	}

////////////////////////////////////////////////////////////
//������������
void ZCFile::ZCSetDriverName(int aDriver,const TDes &aDriverName)
	{
	fsession.Connect();
	fsession.SetDriveName(aDriver,aDriverName);
	fsession.Close();
	}
//void ZCFile::ZCGetDriverList(char** drvers,char** name)
//{
//
//	char dick[]="C:\\";
//	char str[]="(C:)";
//	TDriveList drivelist;  //�����������б�����
//	TChar driveLetter;     //�������̷�
//	TInt driveNumber=EDriveA;    //�����������б�������
//
//	User::LeaveIfError(fsession.DriveList(drivelist));  //�õ���ǰ�������б�
//		for(;driveNumber<=EDriveZ;driveNumber++)
//		{    
//		if (drivelist[driveNumber])
//			{
//				char strName[64];
//				TPtr buf(strName);     
//			User::LeaveIfError(fsession.DriveToChar(driveNumber,driveLetter));
//			User::LeaveIfError(fsession.GetDriveName(driveNumber,buf));
////			console->Printf(KDrive, TUint(driveLetter), drivelist[driveNumber]);
//			dick[0]=driveLetter;
//			*drvers=new char[strlen(dick)];
//			strcpy(*drvers++,dick);
//			str[1]=dick[0];
//			strcat(strName,str);
//			*name=new char[strlen(strName)];
//			strcpy(*name++,strName);
//			}
//		}
//}


////////////////////////////////////////////////////////////
//�鿴�Ƿ����ļ��� �ɹ����ش���0��ʧ�ܷ���С��0
int ZCFile::ZCIsDir(const TDesC& fileName)
	{
	fsession.Connect();
		TEntry theEntry;
		int err;
		err=fsession.Entry(fileName,theEntry);
	fsession.Close();
		if(err == KErrNone)
			{
				return theEntry.IsDir();
			}
		else
			return err;
	}
	
////////////////////////////////////////////////////////////
//ȡ���ļ����ļ��е�����
int ZCFile::ZCGetEntry(const TDesC& fileName,TEntry&entry)
{
	//TEntry theEntry;
	fsession.Connect();
	int err;
	err = fsession.Entry(fileName,entry);
	fsession.Close();
	if(err!=KErrNone) return 0;
	return 1;
}


////////////////////////////////////////////////////////////
//ȡ��ָ��Ŀ¼�µ�������,��CDirָ����ܷ���ֵ��ʹ�ý�����delete
CDir* ZCFile::ZCGetDir(const TDesC& strPath)
{
	CDir *dir;
	fsession.Connect();
	int err = fsession.GetDir(strPath,KEntryAttNormal|KEntryAttMatchMask,ESortByDate,dir);
	fsession.Close();
	return dir;
}

////////////////////////////////////////////////////////////
//����ļ����Ƿ����,����������·����
int ZCFile::ZCDirFinder(const TDesC& strPath,const TDesC& fileName,TFileName& FullFileName)
{
	CDir *dir=NULL;
	int len;
	dir=ZCGetDir(strPath);
	len=dir->Count();
	for(int i=0;i<len;i++)
		{
		if(ZCIsDir((*dir)[i].iName))
			{
			if(!fileName.CompareC((*dir)[i].iName))
				{
				FullFileName=strPath;
				FullFileName.Append(_L("\\"));
				FullFileName.Append((*dir)[i].iName);
				delete dir;
				return TRUE;
				}
			else
				{
				TBuf<KMaxFileName> tmp;
				tmp=strPath;
				tmp.Append(_L("\\"));
				tmp.Append((*dir)[i].iName);
				if(ZCDirFinder(tmp,fileName,FullFileName))
					{
					delete dir;
					return TRUE;
					}
				}
			}
		}
	delete dir;
	return false;
}


////////////////////////////////////////////////////////////
//����ļ��Ƿ���ڣ����ҷ����ļ�����·��
int ZCFile::ZCFileFinder(const TDesC& strPath,const TDesC& fileName,TFileName& FullFileName)
	{
	CDir* dir=NULL;
	int len;
	dir=ZCGetDir(strPath);
	len=dir->Count();
	for(int i=0;i<len;i++)
		{
		if(!ZCIsDir((*dir)[i].iName)) 
			{//��������ļ���
			if(!(*dir)[i].iName.CompareC(fileName))
				{
				FullFileName=strPath;
				FullFileName.Append(_L("\\"));
				FullFileName.Append((*dir)[i].iName);
				delete dir;
				return TRUE;
				}
			}
		else
			{//������ļ���
			TBuf<KMaxFileName> tmp;
			tmp=strPath;
			tmp.Append(_L("\\"));
			tmp.Append((*dir)[i].iName);
			if(ZCFileFinder(tmp,fileName,FullFileName))
				{
				delete dir;
				return TRUE;
				}
			}
		}
	delete dir;
	return FALSE;
	}
