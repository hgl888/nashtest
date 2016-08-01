#pragma once

#define Unoneerr	0;
#define Uerr		-1;
#define Unofind		-2;


class CStaticUtil
{
public:
	CStaticUtil(void);
	~CStaticUtil(void);
public:
	static int movefile(const char* dpath,const char* spath);
	static int removefile(const char* dpath);
	//��str1����str2������str2��str1�е�λ��
	static int findstr(const char* str1,const char* str2,int len = -1);
	//��str1����str2������str2��str1�д����ҵ�λ�ã�offsetΪƫ������styleΪtrue������Ѱ�ң�false�����ҵ���Ѱ��
	static int findstr(const char* str1,const char* str2,int offset,bool style);
	//�滻�ļ��е�Ŀ���ֶΣ�content�滻Ϊsrc
	static bool replaceFileContent(const char* filename,const char* content,const char* src);
	//gbkתutf8,����utf8���ĳ���
	static int GbkToUtf8(char*& utf8,const char* gbk);
};

