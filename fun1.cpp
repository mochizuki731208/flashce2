#include "StdAfx.h"
#include "fun1.h"

#include "stdio.h"
#include "stdarg.h"

void Output(const char * szFormat, ...)	//可用TRACE()  替代
{
	char szBuffer[560];
    va_list pArgs ;
    va_start (pArgs, szFormat) ;
    int iReturn = vsprintf (szBuffer, szFormat, pArgs) ;
    va_end (pArgs) ;
	OutputDebugStringA(szBuffer);
    return ;
}






BOOL StoreStringToFile2(	//保存文件
						CString &strData,		//保存的数据(如果是byte_char[],通过=cstring(char[],lenth)获得,str_char直接复制
						CString strFileName,		//保存的文件路径
						int Filelen,				//默认长度:strData.GetLength(),除外,就用实际长度 
						int FileOffset,			//写入的文件偏移位置(>0,向右偏移;<0,向左偏移)
						BOOL isPointFileEnd)	//从哪开始计算偏移,头,尾
{
	HANDLE hFile = CreateFile(strFileName, 
		GENERIC_WRITE, 
		NULL,
		NULL,
		OPEN_EXISTING,				//文件存在,则打开
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if(hFile == NULL || hFile == INVALID_HANDLE_VALUE)
	{
		hFile = CreateFile(strFileName, 
			GENERIC_WRITE, 
			NULL,
			NULL,
			CREATE_ALWAYS,		//一直建立文件
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