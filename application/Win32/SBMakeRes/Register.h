// CRegister.h: interface for the CRegister class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CRegister_H__44FD9D23_595F_11D1_B2E3_80C2B91C42E7__INCLUDED_)
#define AFX_CRegister_H__44FD9D23_595F_11D1_B2E3_80C2B91C42E7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#ifndef VGC32_EXT_CLASS
#define VGC32_EXT_CLASS AFX_CLASS_IMPORT
#endif
class VGLineBuffer;
//////////////////////////////////////////////
// ע�������࣬��дע���
class CRegister
{
protected:
	LPCSTR m_keyName;//����
public:
	//����������
	void SetName(LPCSTR name);
	//�������������
	//д�����������
	//����ṹ����
	void Read(LPCSTR name,LPVOID lpStruct,UINT nSize );
	//д��ṹ����
	void Write(LPCSTR name,LPVOID lpStruct,UINT nSize );
	//д����������
	void Write( LPCSTR name, LPCSTR str );
	//������������
	CString Read( LPCSTR name, LPCSTR sDefault = NULL );
	//д������
	void Write( LPCSTR name, int nVal );
	//��������
	int Read( LPCSTR name, int nDefault );
	void WriteInt( LPCSTR m_sec, LPCSTR name, int nVal );
	CRegister( LPCSTR keyName );
	virtual ~CRegister();
};

#endif // !defined(AFX_CRegister_H__44FD9D23_595F_11D1_B2E3_80C2B91C42E7__INCLUDED_)
