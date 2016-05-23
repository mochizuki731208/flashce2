/////*************************************************
// Copyright (C), 2012-2013, CS&S. Co., Ltd.
// File name: MyWinpCap.h
// Author: �ƺ쳾(271562312)
// Version: 1.0
// Date: 2015/08/03
// Description:
// Others:
// History:
// <author> �ƺ쳾(271562312)
// <time> 2015/08/03
// <version> 1.0
// <desc> build this moudle
//*************************************************/

#include <afx.h>

#pragma comment(lib, "wpcap.lib")
#pragma comment(lib, "wsock32.lib")
#pragma comment(lib, "ws2_32.lib")

//#include "string.h"
#define HAVE_REMOTE
#include "pcap.h"

// MFC ����Ҫ���漸��
// #ifndef WIN32
// #include <sys/socket.h>
// #include <netinet/in.h>
// #else
// #include <winsock.h>
// #endif

#define IN
#define OUT

// typedef struct cNetworkCardInfo{
// 	CString Name;
// 	CString Description;
// };
#pragma once

enum EthernetType
{
	ARP_protocol		=0x806,
		IP_protocol			=0x800,
		PPPoE_protocol		=0x8864,
		IPversion6_protocol	=0x86DD	
};
#define EthernetSize	14

struct Ethernet{
	u_char			DestMAC[6];
	u_char			SourMAC[6];
	EthernetType	type;
};


typedef struct mac_address{
	u_char byte1;
	u_char byte2;
	u_char byte3;
	u_char byte4;
	u_char byte5;
	u_char byte6;
}mac_address;

typedef struct udp_header{
	u_short sport;       // Source port
	u_short dport;       // Destination port
	u_short len;        // Datagram length
	u_short crc;        // Checksum
}udp_header;

typedef struct ip_address{
    u_char byte1;
    u_char byte2;
    u_char byte3;
    u_char byte4;
}ip_address;

typedef struct ip_header{
	u_char		ver_ihl;			// �汾 (4 bits) + �ײ����� (4 bits)
	u_char		tos;				// ��������(Type of service)
	u_short		tlen;				// �ܳ�(Total length)
	u_short		identification;		// ��ʶ(Identification)
	u_short		flags_fo;			// ��־λ(Flags) (3 bits) + ��ƫ����(Fragment offset) (13 bits)
	u_char		ttl;				// ���ʱ��(Time to live)
	u_char		proto;				// Э��(Protocol)
	u_short		crc;				// �ײ�У���(Header checksum)
	ip_address	saddr;				// Դ��ַ(Source address)
	ip_address	daddr;				// Ŀ�ĵ�ַ(Destination address)
	u_int		op_pad;				// ѡ�������(Option + Padding)
} ip_header;

typedef struct _TCPHDR{
	u_short		nSrcPort;			// Source port
	u_short		nDstPort;			// Dest port
	u_long		nSeq;				// Sequence number
	u_long		nAck;				// Ack number
	u_char		nHdrLen;			// TCP header len (num of bytes << 2)
	u_char		nFlags;				//
	u_int		nWnd;				//
	u_int		nChk;				//
	u_int		nUrgPt;				//
} TCPHDR;





class WINPCAP_MONITOR
{
	
private:
	pcap_if_t *alldevs;
	int       _buffSize;

	/*  ��һ��unsigned long �͵�IPת��Ϊ�ַ������͵�IP */
	#define IPTOSBUFFERS   12
	char *iptos(u_long in)
	{
		static char output[IPTOSBUFFERS][3*4+3+1];
		static short which;
		u_char *p;
		
		p = (u_char *)&in;
		which = (which + 1 == IPTOSBUFFERS ? 0 : which + 1);
		sprintf(output[which], "%d.%d.%d.%d", p[0], p[1], p[2], p[3]);
		return output[which];
}

public:
	//��ȡ������Ϣǰ�ȳ�ʼ��
	int NetcardInfoInit()
	{
		char errbuf[PCAP_ERRBUF_SIZE+1];
		// ����������б� 
		if (pcap_findalldevs(&alldevs, errbuf) == -1)
		{
			fprintf(stderr,"Error in pcap_findalldevs: %s\n",errbuf);
			return -1;//exit(1);
		}
		return 0;//�Ƿ���Ҫ�ͷ�?
	}
	int	getNetcardCount()//��Ŀ
	{
		int k=0;
		for(pcap_if_t *d=alldevs;d;d=d->next)
			k++;
		return k;
	}
	void setBuffSize(int lSize)
	{
		_buffSize = lSize;
	}
	WINPCAP_MONITOR()
	{
		_buffSize = 0x1000000;
	}

	CString getNetcardName(int index)//����
	{
		int k=0;
		for(pcap_if_t *d=alldevs;d;d=d->next)
		{
			if(k==index)
				return d->name;
			k++;
		}
		return "";
	}
	CString getNetcardDescription(int index)//
	{
		int k=0;
		for(pcap_if_t *d=alldevs;d;d=d->next)
		{
			if(k==index)
				return d->description;
			k++;
		}
		return "";
	}
	int getNetcardIPInfo(int index,CStringArray &strArrNetcardIP,
									CStringArray &strArrNetcardNetmask,
									CStringArray &strArrBroadcast)
	{
		pcap_addr_t *a;
		int k=0,k2=0,lCount=0;

		int lIpAddress,lBroadcast,lNetmask;
		char cIpAddress[20],cBroadcast[20],cNetmask[20];
		strArrNetcardIP.RemoveAll();
		strArrNetcardNetmask.RemoveAll();
		strArrBroadcast.RemoveAll();
		for(pcap_if_t *d=alldevs;d;d=d->next)
		{
			if(k==index)
			{
				for(a=d->addresses;a;a=a->next) 
				{
					k2=0;
					if(a->addr)
					{
						lIpAddress=((struct sockaddr_in *)a->addr)->sin_addr.s_addr;
						sprintf(cIpAddress,"%s",iptos(lIpAddress));
						if(a->addr)k2++;
					}
					if(a->broadaddr)
					{
						lBroadcast=((struct sockaddr_in *)a->broadaddr)->sin_addr.s_addr;
						sprintf(cBroadcast,"%s",iptos(lBroadcast));
						if(lBroadcast)k2++;
					}
					if(a->netmask)
					{
						lNetmask=((struct sockaddr_in *)a->netmask)->sin_addr.s_addr;
						sprintf(cNetmask,"%s",iptos(lNetmask));
						if(lNetmask)k2++;
					}
					if(k2==3)
					{
						if(memcmp(cIpAddress,"0.0.0.0",8))//���IP��Ϊ 0.0.0.0 ��Ϊ��ЧIP
						{
							strArrNetcardIP.Add(cIpAddress);
							strArrNetcardNetmask.Add(cNetmask);
							strArrBroadcast.Add(cBroadcast);
							lCount++;
						}
					}
				}
			}
			k++;
		}
		return lCount;
	}
	//////////////////////////////////////////
//***********************��������(ͬ��)**********************

//ͬ��ģʽ
//		������Ϣ,���˷�ʽ(�ִ�),�������յĻص�����
//�ص�������ʽ
//		void ���պ�����(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data)
	int NetworkCardMonitoring(char *NetworkName,char packet_filter[],pcap_handler NetworkCardDataReceive,
							  int lIpAddress=0,int lNetmask=0xffffff)
	{
		pcap_t *adhandle;
		char errbuf[PCAP_ERRBUF_SIZE];
		u_int netmask;
		//char packet_filter[] = "ip and udp";
		struct bpf_program fcode;
		
		// Open the adapter 
		//"\\Device\\NPF_{0152D01D-B8E0-4FAE-8CC4-BC35966D63C7}"
		//"\\Device\\NPF_{9CC3E017-7F28-4DB0-A38F-C463A2321BF2}"
		//memcpy(NetWork.cName,"\\Device\\NPF_{0152D01D-B8E0-4FAE-8CC4-BC35966D63C7}",100);
		//printf("ok1 \n");

		if ( (adhandle= pcap_open_live(NetworkName, // name of the device
			65536,    // portion of the packet to capture. 
			// 65536 grants that the whole packet will be captured on all the MACs.
			1,      // 1==>promiscuous mode
			1,    //1000==> read timeout(ʱ�����ó���,ץ����Ӧ��)
			errbuf    // error buffer
			) ) == NULL)
		{
			//fprintf(stderr,"\nUnable to open the adapter. %s is not supported by WinPcap\n");
			//pcap_freealldevs(alldevs);
			//return -1;
			return 1;
		}
		
		//printf("ok2 \n");

		if(strlen(packet_filter))//�Ƿ����
		{
			// Check the link layer. We support only Ethernet for simplicity. 
			if(pcap_datalink(adhandle) != DLT_EN10MB)
			{
				//fprintf(stderr,"\nThis program works only on Ethernet networks.\n");
				//pcap_freealldevs(alldevs);
				return 2;
			}
			
			if(lIpAddress != NULL)
				// Retrieve the mask of the first address of the interface 
				//netmask=((struct sockaddr_in *)(d->addresses->netmask))->sin_addr.S_un.S_addr;
				netmask=lNetmask;
			else
				// If the interface is without addresses we suppose to be in a C class network
				netmask=0xffffff; 
			
			//compile the filter
			if(pcap_compile(adhandle, &fcode, packet_filter, 1, netmask) <0 ){
				//Unable to compile the packet filter. Check the syntax.
				return 3;
			}
			
			//set the filter
			if(pcap_setfilter(adhandle, &fcode)<0)return 4;
		}
		//���û�����...
		//pcap_setuserbuffer(adhandle,_buffSize);//������10M (Ĭ��256k:0x40000)
		pcap_setbuff(adhandle, _buffSize);
		pcap_loop(adhandle, 0, NetworkCardDataReceive, NULL);
		
		return 0;
	}
	
// 	///////////////////////////////�������///////////////////////////////
// 	//��
// 	int NWOpen(char * NetworkcardName)
// 	{
// 		
// 		char error[PCAP_ERRBUF_SIZE];
// 		if((NetworkCard.fp = pcap_open_live(NetworkcardName, 100, 1, 1000, error) ) == NULL)return 1;
// 		return 0;
// 	}
// 	//����
// 	void NWSendData(cNetworkCardEnable NetworkCard,u_char *packet,int lsize)
// 	{
// 		pcap_sendpacket(NetworkCard.fp,packet,lsize);
// 	}
// 	//�ر�
// 	void NWClose(cNetworkCardEnable NetworkCard)
// 	{
// 		pcap_close (NetworkCard.fp);
// 		NetworkCard.fp=NULL;
// 	}
};