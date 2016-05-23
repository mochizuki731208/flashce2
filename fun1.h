#pragma once
void Output(const char * szFormat, ...);

BOOL StoreStringToFile2(	//保存文件
						CString &strData,		//保存的数据(如果是byte_char[],通过=cstring(char[],lenth)获得,str_char直接复制
						CString strFileName,		//保存的文件路径
						int Filelen = -1,				//默认长度:strData.GetLength(),除外,就用实际长度 
						int FileOffset = 0,			//写入的文件偏移位置(>0,向右偏移;<0,向左偏移)
						BOOL isPointFileEnd = FALSE);	//从哪开始计算偏移,头,尾