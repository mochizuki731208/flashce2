#include "StdAfx.h"
//#include "windows.h"

#include "fun1.h"
#include "MyWinpCap.h"

//#import "c:\program files\common files\system\ado\msado15.dll" no_namespace rename("EOF","adoEOF") 
#import "C:\Program Files (x86)\Common Files\System\ado\msado15.dll" no_namespace rename("EOF","adoEOF") 



#pragma once
class PCAPThreadInfo{
public:
	int pcapIndex ;//= -1;
	CWinThread* pThread2;
	WINPCAP_MONITOR	tt;
};




//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//���ﵥ��ץ��,SIP,SPORT,LPORT,����
#define MAX_CSTCP_BUFF	0xa00000		//10M

struct sCSIP
{
	//TCP
	u_long	ip;			//����IP
	u_short port;		//����Port
	//������Ϣ
	u_long  seq_init;	//
	u_long  buff_l;		//����buff_L
	u_long  buff_u;		//
	u_long  buff_seqa;	//
	u_long  buff_seqb;	//
	UCHAR	pDataBuf[MAX_CSTCP_BUFF];
};

struct MemTcpBlock
{
	MemTcpBlock *next;
	MemTcpBlock *previous;
	
	//����Զ�����һ�»�ÿ�һ��
	u_long	i_server;	//�ĸ���IP�Ƿ����		0:δ֪,δȷ��	1:ip1	2:ip2
	//TCP����
	sCSIP csInfo[2];

	bool bHadSYN;//������
};
class MemTcpMonitor
{
private:
	MemTcpBlock First;	//�׸�,���������,�������ж�

public:
	void InitLinkedList()
	{
		First.next = NULL;
		First.previous =NULL;
	}
	MemTcpBlock *Find(u_long sip,u_long dip,u_short sport,u_short dport,int &saveIndex)//ע:���صĶ��ǲ���.next��....
	{
		MemTcpBlock *pTemp = &First;
		while(pTemp->next)
		{
			//��������...
			if(pTemp->next->csInfo[0].ip == sip && pTemp->next->csInfo[1].ip == dip && pTemp->next->csInfo[0].port == sport && pTemp->next->csInfo[1].port == dport)
			{	
				saveIndex = 1;
				return pTemp;
			}
			if(pTemp->next->csInfo[0].ip == dip && pTemp->next->csInfo[1].ip == sip && pTemp->next->csInfo[0].port == dport && pTemp->next->csInfo[1].port == sport)
			{
				saveIndex = 0;
				return pTemp;
			}
			pTemp = pTemp->next;
		}
		saveIndex = -1;
		return pTemp;
	}
	MemTcpBlock *AddNew(u_long sip,u_long dip,u_short sport,u_short dport,int &saveIndex)//���ⷵ��ָ��,ȱ��:��¶..�ŵ�:����ǿ
	{
		MemTcpBlock *pTemp;
		pTemp = Find(sip,dip,sport,dport,saveIndex);//��ѯ����...
		if(!pTemp->next)
		{
			MemTcpBlock *pNew = new MemTcpBlock;
			pTemp->next = pNew;		
			pNew->previous = pTemp;
			pNew->next = NULL;
			////pNew.* = .....�������(pTempΪ��.����������)
			//pNew->a = x;
			//pNew->str = str1;
// 			pNew->lData = 0;
// 			pNew->uData = 0;
// 
// 			pNew->dip = dip;
// 			pNew->sip = sip;
// 			pNew->sport = sport;
// 			pNew->dport = dport;

			pNew->bHadSYN = false;//������

			pNew->i_server	= 0;
			memset(pNew->csInfo,0,sizeof(sCSIP) * 2);
			
			pNew->csInfo[0].ip	=	sip;
			pNew->csInfo[1].ip	=	dip;
			pNew->csInfo[0].port = sport;
			pNew->csInfo[1].port = dport;
			saveIndex = 1;
			return pTemp;
		}
		saveIndex = -1;//���ֲ��ᷢ��
		return NULL;
	}
	
	void Delete(u_long sip,u_long dip,u_short sport,u_short dport,int &saveIndex)
	{
		MemTcpBlock *pTemp,*pTemp2;
		pTemp = Find(sip,dip,sport,dport,saveIndex);//��ѯ����...
		if(pTemp->next)
		{
			pTemp2 = pTemp->next;
			pTemp->next = pTemp->next->next;//ǰ���
			if(pTemp->next)
				pTemp->next->previous = pTemp;//���ǰ
			delete pTemp2;	
		}
		return;
	}
	
	MemTcpBlock * getFirst()
	{
		return &First;
	}

	void print()
	{
		MemTcpBlock *pTemp = &First;
		while(pTemp->next)
		{
			//printf("%d  %s\n",pTemp->next->a,pTemp->next->str);
			pTemp = pTemp->next;
		}
		return ;
	}
	
	void clsAll()
	{
		MemTcpBlock *pTemp,*pTemp2;
		pTemp = &First;
		while(pTemp->next)
		{
			pTemp2 = pTemp->next->next;
			delete pTemp->next;
			pTemp->next = pTemp2;
		}
		First.next = NULL;
	}
};



#pragma once
#pragma pack(push, 1)
//////////////////////////////////////////////////////////////////////////flash�����ݸ�ʽ
struct lisInfo
{
	char gameNumName[14];
	char BankNum;
	char PlayNum;
	char CardNum;
	char Pair;//û��λ���ʾ	
};
struct lisGAME_NEWCARDBOOT
{
	char RoomName[4];
	char t1[16];
};
struct lisGAMERESULT
{
	char RoomName[4];
	char t1;
	lisInfo CardsInfo;
};
struct lisHistoryHead
{
	char RoomName[4];
	union
	{
		char t1[4];
		int  tx;
	};
	
	//lisInfo CardsInfo;//0-���,��Ŀ��һ��
};
struct glNameInfo
{
	char NickName[8];
	char RoomName[8];
	char t1[2];
};
struct lisHeader
{
	u_long tag;
	u_long len;
	u_long ttt;
};
//////////////////////////////////////////////////////////////////////////�Լ��ı�����
enum ZXHST
{
	zhuang = 0,
	xian = 1,
	he =2
};

struct oneGame
{
	lisGAMERESULT saveInfo;
	char Name[10];
	ZXHST ZXH;//ׯ�к�
	char DUI;//��
	char DX;//��С
};
struct gameDeskInfo
{
	CString RoomName;
	oneGame myList[150];
	int countList;
};
#pragma pack(pop)

//////////////////////////////////////////////////////////////////////////
void initThread();
void initGame();
void IPDataReceive(const u_char *ip_data,int len);
void NetworkCardDataReceive(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);

void SetHwndShow(HWND hwnd);

void testHAHA();


