#pragma once
void Output(const char * szFormat, ...);

BOOL StoreStringToFile2(	//�����ļ�
						CString &strData,		//���������(�����byte_char[],ͨ��=cstring(char[],lenth)���,str_charֱ�Ӹ���
						CString strFileName,		//������ļ�·��
						int Filelen = -1,				//Ĭ�ϳ���:strData.GetLength(),����,����ʵ�ʳ��� 
						int FileOffset = 0,			//д����ļ�ƫ��λ��(>0,����ƫ��;<0,����ƫ��)
						BOOL isPointFileEnd = FALSE);	//���Ŀ�ʼ����ƫ��,ͷ,β