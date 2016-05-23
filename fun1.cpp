#include "StdAfx.h"
#include "fun1.h"

#include "stdio.h"
#include "stdarg.h"

void Output(const char * szFormat, ...)	//����TRACE()  ���
{
	char szBuffer[560];
    va_list pArgs ;
    va_start (pArgs, szFormat) ;
    int iReturn = vsprintf (szBuffer, szFormat, pArgs) ;
    va_end (pArgs) ;
	OutputDebugStringA(szBuffer);
    return ;
}






BOOL StoreStringToFile2(	//�����ļ�
						CString &strData,		//���������(�����byte_char[],ͨ��=cstring(char[],lenth)���,str_charֱ�Ӹ���
						CString strFileName,		//������ļ�·��
						int Filelen,				//Ĭ�ϳ���:strData.GetLength(),����,����ʵ�ʳ��� 
						int FileOffset,			//д����ļ�ƫ��λ��(>0,����ƫ��;<0,����ƫ��)
						BOOL isPointFileEnd)	//���Ŀ�ʼ����ƫ��,ͷ,β
{
	HANDLE hFile = CreateFile(strFileName, 
		GENERIC_WRITE, 
		NULL,
		NULL,
		OPEN_EXISTING,				//�ļ�����,���
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if(hFile == NULL || hFile == INVALID_HANDLE_VALUE)
	{
		hFile = CreateFile(strFileName, 
			GENERIC_WRITE, 
			NULL,
			NULL,
			CREATE_ALWAYS,		//һֱ�����ļ�
			FILE_ATTRIBUTE_NORMAL,
			NULL);
	}
	if(hFile != NULL && hFile != INVALID_HANDLE_VALUE)
	{
		DWORD dwBytesWritten=0;
		if(FileOffset)
		{
			DWORD dwPtr;
			if(isPointFileEnd)
				dwPtr = SetFilePointer(hFile, FileOffset, NULL, FILE_END);
			else
				dwPtr = SetFilePointer(hFile, FileOffset, NULL, FILE_BEGIN);
			if(dwPtr == 0xFFFFFFFF)
				return FALSE;
		}
		if(-1==Filelen)
			WriteFile(hFile, (LPCSTR)strData, strData.GetLength(), &dwBytesWritten, NULL);
		else
			WriteFile(hFile, (LPCSTR)strData, Filelen, &dwBytesWritten, NULL);
		
		CloseHandle(hFile);
		return TRUE;
	}
	return FALSE;
}