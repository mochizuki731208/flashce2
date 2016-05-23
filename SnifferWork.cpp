#include "StdAfx.h"
#include "SnifferWork.h"


PCAPThreadInfo MyThis;

int IIX = 0;
int bSmall = 0;

MemTcpMonitor TCPbf;
gameDeskInfo pALLGame[100];
int countAllGame = 0;

HWND _hWndShow = 0;
void SetHwndShow(HWND hwnd){
	_hWndShow = hwnd;
}

CRITICAL_SECTION m_cs;
void CODE_Init()	{	InitializeCriticalSection(&m_cs);	}
void CODE_Safe()	{	EnterCriticalSection(&m_cs);		}
void CODE_UnSafe()	{	LeaveCriticalSection(&m_cs);		}
void CODE_Cls()		{	DeleteCriticalSection(&m_cs);		}

struct SaveLast
{
	int		index1;
	int		index2;
	//本桌,其他信息
	bool	bNew;
};
SaveLast pLastRoomIndex[1000];

//////////////////////////////////////////////////////////////////////////
struct GameCard
{
	int		iIndex;
	ZXHST	ZXH;//庄闲和
	char	DUI;//对
	char	DX;//大小
};
#define MAX_DESK_CARDS	160
#define MAX_DESK_HIS	10
#define MAX_DESK_SIZE	100
struct GamePCardS	//手牌信息
{
	GameCard cards[MAX_DESK_CARDS];
	int		 cardCount;
};
struct GameDeskCards	//桌信息
{
	GamePCardS pHis[MAX_DESK_HIS];//历史记录
	int  Used;//0-n 历史
	int  DeskIndex;
	CString  DeskName;
};
GameDeskCards AllDesk[MAX_DESK_SIZE];//简单方法







void initGame()
{
	CODE_Safe();
	countAllGame = 0;
	CODE_UnSafe();
	for(int i = 0;i < 1000; i++)
	{
		pLastRoomIndex[i].index1 = 0;
		pLastRoomIndex[i].index2 = 0;
		pLastRoomIndex[i].bNew = false;
	}
	for(int i = 0; i < MAX_DESK_SIZE ; i++)
	{
		AllDesk[i].DeskIndex = 0;
		AllDesk[i].pHis->cardCount = 0;
		AllDesk[i].Used = 0;
	}	
}
void initThread()
{
	CODE_Init();
}
int getDeskNum(CString DeskName)
{
	CString str3 = DeskName.Mid(1,3);//001
	CString str5 = DeskName.Mid(0,1);//A
	CString str1 = "ATCV";
	
	int kDesk = str1.Find(str5);
	kDesk = (kDesk + 1) * 100 + atoi(str3);
	if(kDesk<100)
	{
		kDesk = 0;
	}
	return kDesk;
}

bool NewRomHadAdd = false;
void PPPdelInfo(lisHistoryHead ro)
{
	CString str1,str2,str3,str5;
	str1 = ro.RoomName;
	str2 = str1.Mid(0,4);//C001

	int kDesk = getDeskNum(str2);
	
	pLastRoomIndex[kDesk].bNew = true;//
	
// 	bool bFind = false;
// 	int  iFind = -1;
// 	CODE_Safe();
// 	for(int i = 0 ; i < countAllGame; i++)
// 	{
// 		//判断游戏房间是否相同
// 		if(str2 == pALLGame[i].RoomName)
// 		{
// 			bFind = true;
// 			iFind = i;
// 			break;
// 		}
// 	}
// 	if(bFind ==false)
// 	{
// 		CODE_UnSafe();
// 		return ;
// 	}
// 	//房间里的所有清空
// 	memset(&pALLGame[iFind].myList[0],0,sizeof(oneGame) * 150);
// 	pALLGame[iFind].countList = 0;
// 
// 	CODE_UnSafe();
}

int PPPaddInfo(lisInfo NewGameinfo,int &DeskNumber)
{
	int iErr = 0;

	CString str1,str2,str4;
	_variant_t var;
	CString strName;

	
	str1 = NewGameinfo.gameNumName;//"GA0011582103M"
	Output(">>>>>>>>> %s ",str1);
	str1 = str1.Mid(0,13);
	str2 = str1.Mid(1,4);//A001

// 	str3 = str1.Mid(2,3);//001
// 	str5 = str1.Mid(1,1);//A
	if(str1.GetLength()<2 || NewGameinfo.CardNum <4 || NewGameinfo.CardNum>6)
	{
		return 1;
	}
	
	int kDesk = getDeskNum(str2);
	DeskNumber = kDesk;
// 	int kDesk = 0;
// 	if(str5=="A")
// 	{
// 		kDesk = 100;
// 	}else if(str5 == "T")
// 	{
// 		kDesk = 200;
// 	}
// 	else if(str5 == "C")
// 	{
// 		kDesk = 300;
// 	}
// 	else if(str5 == "V")
// 	{
// 		kDesk = 400;
// 	}
// 	kDesk = kDesk + atoi(str3);

	if(kDesk < 100)
	{
		return 1 ;
	}

	int kDate;
	str4 = str1.Mid(5,2);	//年
	kDate = atoi(str4) * 10000;
	str4 = str1.Mid(8,2);	//日
	kDate = kDate + atoi(str4);

	str4 = str1.Mid(7,1);
	int k2 = atoi(str4);
	if(k2 == 0)
	{
		k2 = 10;	//暂时解决 10月的问题	150821
	}
	kDate = kDate + k2 * 100;
	
	oneGame card1;
	
	if(NewGameinfo.BankNum>NewGameinfo.PlayNum){
		card1.ZXH= zhuang;
	}else if(NewGameinfo.BankNum<NewGameinfo.PlayNum){
		card1.ZXH = xian;
	}else{
		card1.ZXH = he;
	}

	if(4==NewGameinfo.CardNum)
	{
		card1.DX = 0;
	}
	else
	{
		card1.DX = 1;
	}

	if(NewGameinfo.Pair>0)
	{
		card1.DUI = 1;
	}else{
		card1.DUI = 0;
	}

	CString strSQL;

	iErr = 1;
	//Output("iErr = %d \n",iErr);

	::CoInitialize(NULL);

 	_ConnectionPtr	m_pConnection;
 	_RecordsetPtr	m_pRecordset;
	_RecordsetPtr	m_pRecordset2;
 	m_pConnection.CreateInstance(__uuidof(Connection));
 	m_pRecordset.CreateInstance(__uuidof(Recordset));
	m_pRecordset2.CreateInstance(__uuidof(Recordset));
 	m_pRecordset->CursorLocation = adUseClient;
	m_pRecordset2->CursorLocation = adUseClient;

	iErr = 2;
	//Output("iErr = %d \n",iErr);

	try
	{	//Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" & dbPath & ";Persist Security Info=False
 		m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source='001.mdb'","","",adModeUnknown);
	}
	catch(_com_error *e)
	{
		Output("错误错误1:",0);
		Output(e->ErrorMessage());
		return 2;
	}

	iErr = 3;
	//Output("iErr = %d \n",iErr);

		strSQL.Format("SELECT * FROM gev where daynum=%d and desknum=%d and gameid='%s'",
		kDate,kDesk,str1);
	
	try
	{
		m_pRecordset->Open((LPCTSTR)strSQL,
			m_pConnection.GetInterfacePtr()		
			,adOpenDynamic ,adLockOptimistic,adCmdText);
	}
	catch(_com_error *e)
	{
		//AfxMessageBox(e->ErrorMessage());
		Output("错误错误2:",0);
		Output(e->ErrorMessage());
		return 3;
	}
	
	bool bHadAdd = false;
	
	if(!m_pRecordset->BOF)	//完全相同,同一条数据
	{
		iErr = 4;
		Output("iErr = %d \n",iErr);

		m_pRecordset->MoveFirst();
		while(!m_pRecordset->adoEOF)
		{
			var = m_pRecordset->GetCollect("index1");
			int kk6 = var.iVal;
			var = m_pRecordset->GetCollect("index2");
			int kk7 = var.iVal;
			//Output(">>>> %s %d %d\n",(PCHAR)NewGameinfo.gameNumName,kDate,kDesk);

			pLastRoomIndex[kDesk].index1 = kk6;
			pLastRoomIndex[kDesk].index2 = kk7;
			pLastRoomIndex[kDesk].bNew = false;
			break;
			//获取当条数据的index1,index2
		}

		iErr = 5;
		//Output("iErr = %d \n",iErr);
	}
	else
	{	//没有的数据,我默认服务器正常排序,不会故意乱序
		iErr = 6;
		Output("iErr=%d \n",iErr);

		if(pLastRoomIndex[kDesk].index1==0 || pLastRoomIndex[kDesk].index2==0)
		{	//找出最后序号(没有一条当日当桌数据;有找出来)
			//	select blog_id,count(*) c1,min(create_date) c2 from blog_art group by blog_id order by c1,c2 
			//	先按数量排,再按时间排
			strSQL.Format("select * from gev where daynum=%d and desknum=%d order by index1,index2 desc",
				kDate,kDesk);

			//////////////////////////////////////////////////////////////////////////
			//m_pRecordset->Close();
			m_pRecordset2->Open((LPCTSTR)strSQL,
				m_pConnection.GetInterfacePtr()		
 				,adOpenDynamic ,adLockOptimistic,adCmdText);
			
			iErr = 7;
			//Output("iErr = %d \n",iErr);

			if(!m_pRecordset2->BOF)	//今日本桌有数据
			{
				m_pRecordset2->MoveFirst();

				iErr = 8;
				Output("iErr = %d \n",iErr);

				while(!m_pRecordset2->adoEOF)
				{
					var = m_pRecordset2->GetCollect("desknum");
					int kk2 = var.iVal;

					var = m_pRecordset2->GetCollect("index1");
					int kk3 = var.iVal;
					var = m_pRecordset2->GetCollect("index2");
					int kk4 = var.iVal;

					pLastRoomIndex[kDesk].index1 = kk3;
					pLastRoomIndex[kDesk].index2 = kk4 + 1;


					iErr = 9;
					Output("iErr = %d \n",iErr);
					break;
					//下一条:
					//m_pRecordset2->MoveNext();
				}
			}
			else
			{	//今日本桌无数据
				pLastRoomIndex[kDesk].index1 = 1;
				pLastRoomIndex[kDesk].index2 = 1;
				pLastRoomIndex[kDesk].bNew = false;
				Output("新桌: %s %d %d  \n",NewGameinfo.gameNumName,pLastRoomIndex[kDesk].index1 ,pLastRoomIndex[kDesk].index2);
			}
			//////////////////////////////////////////////////////////////////////////
		}
		else
		{
			if(pLastRoomIndex[kDesk].bNew == false)
			{
				pLastRoomIndex[kDesk].index2 ++;
			}
			else
			{
				pLastRoomIndex[kDesk].index1 ++;
				pLastRoomIndex[kDesk].index2 = 1;
				pLastRoomIndex[kDesk].bNew = false;
			}	
		}


		//iErr = 10;
		Output("==== %s %d %d\n",(PCHAR)NewGameinfo.gameNumName,kDate,kDesk);
		
		try
		{
			m_pRecordset->AddNew();
			m_pRecordset->PutCollect("daynum", _variant_t((long)kDate));
			m_pRecordset->PutCollect("desknum",_variant_t((long)kDesk));
			m_pRecordset->PutCollect("gameid", _variant_t(str1));
			
			m_pRecordset->PutCollect("index1",_variant_t((long)pLastRoomIndex[kDesk].index1 ));
			m_pRecordset->PutCollect("index2",_variant_t((long)pLastRoomIndex[kDesk].index2 ));
			
			m_pRecordset->PutCollect("ZHX",_variant_t((long)card1.ZXH));
			m_pRecordset->PutCollect("DUI",_variant_t((long)card1.DUI));
			m_pRecordset->PutCollect("DX",_variant_t((long)card1.DX));

			long lk1 = 0;
			memcpy(&lk1,&NewGameinfo.BankNum,4);
			m_pRecordset->PutCollect("gameinfo",_variant_t(lk1));

			m_pRecordset->Update();

			bHadAdd = true;
		}
		catch(_com_error *e)
		{
			Output("错误错误3:",0);
			Output(e->ErrorMessage());
			return 4;
		}

		iErr = 11;
		Output("iErr = %d \n",iErr);
	}

	m_pRecordset->Close();
	m_pConnection->Close();

	::CoUninitialize();

	if(bHadAdd)
		return 0;
	else
		return -1;
}

bool checkRoom(unsigned char *pRoom)
{
	if(pRoom[1] == '0')
	{
		if(pRoom[0] == 'A' || pRoom[0] == 'C' || pRoom[0] == 'T' || pRoom[0] == 'V')
		{
			if(pRoom[2] >='0' && pRoom[2] <='3')
			{
				if(pRoom[3] >='0' && pRoom[3] <='9')
				{
					return true;
				}
			}
		}
	}
	return false;
}

void testHAHA()
{
// 	lisInfo ff;
// 	memcpy(ff.gameNumName,"GV01515819073",13);
// 	ff.PlayNum = 4;
// 	ff.Pair = 1 ;
// 	PPPaddInfo(ff);
// 
// 	memcpy(ff.gameNumName,"GV01515819075",13);
// 	ff.PlayNum = 5;
// 	ff.Pair = 1 ;
// 	PPPaddInfo(ff);

}

void WINAPI DataPump(u_long sip,u_long dip,u_short sport,u_short dport,PBYTE pPuff,	int lNewLen,int &ihadReadBuff,bool fullTCP)
{
	bool bHead;
	int  offHead;
	lisHeader pHead;
	
	if(sport != 5000)
	{
		ihadReadBuff = -1;
		return;
	}

	//测试中,屏蔽此句
// 	if(fullTCP == false)//★新增
// 	{
// 		Output("非完整");
// 		ihadReadBuff = -1;
// 		return;
// 	}

	UCHAR *allData;
	allData = pPuff;
	bHead = false;
	int lmyRet;
	int ltestLen;

	int ret = 0;

	lisHistoryHead hisHead ;
	lisInfo		   hisInfo;
	UINT i,j;

	UINT myDataL = 0;
	UINT myDataU = lNewLen;

	int DeskNumber = 0;

	CString newlen;
	newlen.Format("newlen=%d\n", lNewLen);
	Output((LPCTSTR)newlen);

	while(myDataU > myDataL + 12)//长度判断
	{
		bHead = false;
		offHead = 0;
		lmyRet = -1;
		bool bFinish = FALSE;
		bool bFirstMove = true;
		for(i = myDataL; i < (myDataU - 12); i++)
		{
			//初始判断(限定太松:可能有不良数据错当成,限定太紧:偏移容易出问题)
			if(    allData[i] == 0   // && allData[i+2] < 3  
				&& allData[i + 4] ==0 && allData[i + 5] ==0 
				&& allData[i + 8] ==0 && allData[i + 9] ==0 && allData[i + 10] ==0 && allData[i + 11] ==0)
			{	
				offHead = i;
				memcpy(&pHead,allData + i,12);
				pHead.tag = htonl(pHead.tag);
				pHead.len = htonl(pHead.len);

				ltestLen = 	(myDataU - myDataL);

				if(pHead.len>= 12 )//	&& (pHead.len < 0x10000) //长度判断
				{
					//二次判断...根据类型和长度.
					switch (pHead.tag)
					{
					//////////////////////////////////////////////////////////////////////////
					case 0x020008:
						if(pHead.len > (UINT)ltestLen){
							lmyRet = 4;
							break;
						}
						if(pHead.len < 0x14){
							lmyRet = 2;
							break;
						}
						if(!checkRoom(allData + i + 12)){	//房间名A001
							lmyRet = 3;
							break;
						}
						memcpy(&hisHead,allData + i + 12,8);
						if((UINT)pHead.len != (UINT)(hisHead.t1[3] * 18 + 20))
						{
							lmyRet = 0;
							break;
						}
						
						Output("房间名:%s \n",(char *)(allData + i + 12),0);
						for(j = 0 ;j < (pHead.len - 20) / 18 ; j++)
						{
							memcpy(&hisInfo,allData + i + 20 + j * 18,18);
							
							if(hisInfo.CardNum>6 || hisInfo.CardNum<4)
							{
								break;
							}
							//Output("[%s] %d",hisInfo.gameNumName,hisInfo.PlayNum);
							ret = PPPaddInfo(hisInfo,DeskNumber);
							if(0 == ret)
							{
								SetWindowText(_hWndShow,hisInfo.gameNumName);
							}
						}
						lmyRet = 0;
						break;
						//////////////////////////////////////////////////////////////////////////
					case 0x020011://new
						if(pHead.len > (UINT)ltestLen){
							lmyRet = 4;
							break;
						}
						if(pHead.len != 0x23){
							lmyRet = 2;
							break;
						}
						if(!checkRoom(allData + i + 12 )){	//房间名A001
							lmyRet = 3;
							break;
						}
						lisGAMERESULT retNewInfo;
						memcpy(&retNewInfo,allData + i + 12,sizeof(lisGAMERESULT));
						
						
						ret = PPPaddInfo(retNewInfo.CardsInfo,DeskNumber);
						if(0==ret)
						{
							SetWindowText(_hWndShow,retNewInfo.CardsInfo.gameNumName);

							//如果....从数据库读历史数据到链表
							//	 历史判断(满足数目再判断)
							//	 当前判断
							//	   计算和得分
							//		排序?得分
							//		显示
							bool bfindDesk = false;
							int  findDeskNO = -1;
							if(DeskNumber>MAX_DESK_SIZE)
							{
								for(i = 0;i < MAX_DESK_SIZE;i++)
								{
									if(AllDesk[i].DeskIndex == DeskNumber)//桌号相同
									{
										//找到桌号
										findDeskNO = i;
										bfindDesk = true;
										break;
									}
								}
								if(false==bfindDesk)
								{
									for(i = 0 ; i < MAX_DESK_SIZE ; i++)
									{
										if(0 == AllDesk[i].DeskIndex)//新增桌号
										{
											findDeskNO = i;
											
											for(j = 0 ; j < MAX_DESK_HIS ; j ++ )
											{
												AllDesk[findDeskNO].pHis[j].cardCount = 0;
											}
											AllDesk[findDeskNO].Used = 0;
											
											AllDesk[findDeskNO].DeskIndex = DeskNumber;

											break;
										}
									}
								}
								//把数据存储到
								//lDesk[findDeskNO].Used
								if(findDeskNO > -1)
								{
									//添加新信息

									//AllDesk[findDeskNO].DeskName = 
									//AllDesk[findDeskNO].Used = true;
									AllDesk[findDeskNO].pHis->cardCount ++;
								}
							}
							else
							{
								Output("桌号错误错误....");
							}
						}
						else
						{
							Output("数据库已存在!");
						}
						lmyRet = 0 ;
						break;
						//////////////////////////////////////////////////////////////////////////
					case 0x2001C://start
						if(pHead.len > (UINT)ltestLen){
							lmyRet = 4;
							break;
						}
						if(pHead.len != 0x20){
							lmyRet = 2;
							break;
						}
						if(!checkRoom(allData + i + 12 )){	//房间名A001
							lmyRet = 3;
							break;
						}
						memcpy(&hisHead,allData + i + 12,8);
						PPPdelInfo(hisHead);
						lmyRet = 0 ;
						break;
					default:
						if(pHead.len > (UINT)ltestLen){
							lmyRet = 4;
							break;
						}
						lmyRet = 0 ;
						break;
					}
				}
				else
				{
					lmyRet = 1;//太长,或太短
				}
				//////////////////////////////////////////////////////////////////////////
				if(lmyRet == 4)
				{
					//继续接受
					return ;
				}
				if(lmyRet == 0 )
				{	//满足条件
					myDataL = i + pHead.len;
					ihadReadBuff = myDataL;

					if(myDataL == myDataU)
					{
						ihadReadBuff = -1;
						myDataL = 0;
						myDataU = 0;
					}
					break;
				}
			}
			else
			{
				if(bFirstMove)
				{
					bFirstMove = false;
				}

				if(i == (myDataU - 12) - 1)
					bFinish = true;
			}
		}

		if(bFinish == true)
		{
			ihadReadBuff = -1;
 			myDataL = 0;
 			myDataU = 0;
			break ;
		}
	}
}



void WINAPI DataRev2(DWORD sIP,WORD sPort,DWORD dIP,WORD dPort,char *DataBuf,int dataLen,char TCPtag,
					 DWORD seq,DWORD ack)
{
	if(sPort!= 5000  &&  dPort !=5000)//sPort!= 5000  && sPort!= 7467 && sPort!= 5300
	{
		return;
	}
	else
	if((sPort ==5000 && (sIP & 0x0000a8c0)== 0x0000a8c0) ||
	   (dPort ==5000 && (dIP & 0x0000a8c0)== 0x0000a8c0) ) 
	{
		return ;//本地5000干扰
	}

	int iSaveIndex = 0;
	MemTcpBlock *p = TCPbf.Find(sIP,dIP,sPort,dPort,iSaveIndex);

	//	1找IP,需要支持交换
	//	2.看标记
	if(!(p->next))
	{
		p = TCPbf.AddNew(sIP,dIP,sPort,dPort,iSaveIndex);
	}

	int iAck = 1 - iSaveIndex;

	if(p->next)	//按端口,ip,存
	{
		//	|------------------------------|
		//		L				U
		//		.seqa				.seqb
		//		.seqa		.seqb
		if(dataLen > 0)	//填数
		{
			if(p->next->csInfo[iSaveIndex].buff_seqa > 0)
			{
				int		k1 = seq - p->next->csInfo[iSaveIndex].buff_seqa;
				u_long ukL = p->next->csInfo[iSaveIndex].buff_l;
				u_long ukU = p->next->csInfo[iSaveIndex].buff_u;
				int		kT2 = ukL + k1 + dataLen;
				
				if(kT2 < MAX_CSTCP_BUFF && ( k1 + dataLen >0 ) && dataLen>0)	//几次数据不可能太长,太长说明TCP接收错误
				{
					if(kT2 > MAX_CSTCP_BUFF)
					{
						kT2 = MAX_CSTCP_BUFF;//超出长度不保存(注意清空)
					}
					//
					if(k1 >= 0)
					{
						memcpy(&(p->next->csInfo[iSaveIndex].pDataBuf[ukL + k1]),DataBuf,dataLen);
					}
					else
					{
						memcpy(&(p->next->csInfo[iSaveIndex].pDataBuf[ukL + 0]),DataBuf - k1, dataLen + k1);
					}
					
					if( p->next->csInfo[iSaveIndex].buff_u < (UINT)kT2)
					{
						p->next->csInfo[iSaveIndex].buff_u = kT2;
					}
				}
			}
		}
		if(TCPtag & 0x1)//FIN
		{
			p->next->bHadSYN = false;
			
			
		}
		if(TCPtag & 0x2)//SYN
		{
			p->next->csInfo[iSaveIndex].buff_seqa = 0;//谁发的把谁空
			
			p->next->bHadSYN = true;//★新增

			if(TCPtag == 0x2)
			{
				p->next->i_server = iSaveIndex;
			}else if(TCPtag ==0x12)
			{
				p->next->i_server = iAck;
			}
		}
		if(TCPtag & 0x10)//ACK	确认.
		{
			if(p->next->csInfo[iAck].buff_seqa == 0)//目标的ACK判断
			{
				p->next->csInfo[iAck].buff_seqa = ack;	//初始化后第一次填值
				p->next->csInfo[iAck].buff_l = 0;
				p->next->csInfo[iAck].buff_u = 0;
			}
			else
			{
				u_long uk1 = ack - p->next->csInfo[iAck].buff_seqa;
				if(uk1 < MAX_CSTCP_BUFF && uk1>0)//确认收到(ack > p->next->csInfo[iAck].buff_seqa)
				{
					int iHadReadBuff = 0;

					////★新增
 					DataPump(dIP,sIP,dPort,sPort,&(p->next->csInfo[iAck].pDataBuf[p->next->csInfo[iAck].buff_l]),uk1,iHadReadBuff,p->next->bHadSYN);
					if(iHadReadBuff)
					{
						if(iHadReadBuff < 0 || ((UINT)iHadReadBuff == uk1))
						{	
							p->next->csInfo[iAck].buff_l = p->next->csInfo[iAck].buff_l + uk1;
							p->next->csInfo[iAck].buff_seqa = p->next->csInfo[iAck].buff_seqa + uk1;
						}
						else
						{	
							if((UINT)iHadReadBuff	<=	uk1)
							{
								p->next->csInfo[iAck].buff_l = p->next->csInfo[iAck].buff_l + iHadReadBuff;
								p->next->csInfo[iAck].buff_seqa = p->next->csInfo[iAck].buff_seqa + iHadReadBuff;
							}
// 							else
// 							{
// 								Output("读的数据长度不对\n");
// 							}
						}

						if(p->next->csInfo[iAck].buff_l ==  p->next->csInfo[iAck].buff_u)
						{
							p->next->csInfo[iAck].buff_l = 0;
							p->next->csInfo[iAck].buff_u = 0;
						}
					}
				}
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
void IPDataReceive(const u_char *ip_data,int len)
{
	//ip->tcp->http数据
	ip_header *ipHead;
	TCPHDR *tcpHead;
	u_char tcp_len;
	u_int ipHead_len;
	u_short sport, dport;
	u_char *p_data;
	
	ipHead = (ip_header *)ip_data;//ip包
	ipHead_len = (ipHead->ver_ihl & 0xf) * 4;
	tcpHead = (TCPHDR *)((u_char *)ipHead + ipHead_len);
	
	u_long *sIP ;
	sIP= (u_long *)&ipHead->saddr;
	u_long *dIP = (u_long *)&ipHead->daddr;
	
	// 将网络字节序列转换成主机字节序列
	sport = ntohs(tcpHead->nSrcPort);
	dport = ntohs(tcpHead->nDstPort);
	
	tcp_len = tcpHead->nHdrLen / 4;
	p_data = (u_char*)tcpHead + tcp_len;
	
	char lpTransMark[MAX_PATH] = "";
	
	unsigned length = ntohs(ipHead->tlen) - ipHead_len - tcp_len;
	DWORD dwSeq = ntohl(tcpHead->nSeq);
	DWORD dwAck = ntohl(tcpHead->nAck);
	
	switch(ipHead->proto)
	{				
	case IPPROTO_ICMP:
		break;
	case IPPROTO_TCP:
			DataRev2(*sIP,sport,*dIP,dport,(char *)p_data,length,tcpHead->nFlags,dwSeq,dwAck);
		break;
	}
}

void NetworkCardDataReceive(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data)
{
	Ethernet *Eth;
	Eth=(Ethernet *)pkt_data;
	if(ntohs(Eth->type)==IP_protocol)
	{	
		IPDataReceive(pkt_data+EthernetSize,header->len-14);
	}
}