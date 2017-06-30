#include "SGS_Proto_104.h"
#include "QDateTime"

SGS_Proto_104::SGS_Proto_104()
{
	//memset(&cmdinfo,0,sizeof(IEC104_INFO_COMMAND));
	m_open = false;
}

SGS_Proto_104::~SGS_Proto_104()
{
	m_open = false;
}

bool SGS_Proto_104::isOpen() const
{
	return m_open;
}

int 
SGS_Proto_104::Init(short stno,short chno)
{
	if(SGS_PCBasic::Init(stno,chno) == PROTO_RET_FAIL)	return	PROTO_RET_FAIL;
	memset(&config,0,sizeof(IEC104_CONFIG_T));
	memset(&info,0,sizeof(IEC104_INFO_T));
	//初始化基本配置参数
	ReadConfig();
	//初始化基本信息
	//info.SendCommand = IEC104_CMD_RESET_LINK;
	//info.SendCommand = IEC104_CMD_REQ_LINK_STATE;
	info.SendTimeFlag = TRUE; 
	info.CallAllDataFlag = TRUE;
	info.CallAllKwhFlag = TRUE;
	info.pollingTm = time(0);
	pInfo = &info;

	SGS_Printer(LOG_104_RX, "<%d-%d>open Protocol sucess!", m_chno, m_stno);

	m_open = true;
	return	PROTO_RET_OK;
}

int SGS_Proto_104::ProtoRX_Init(short stno,short chno)
{
	if(SGS_PCBasic::ProtoRX_Init(stno,chno) == PROTO_RET_FAIL)	return	PROTO_RET_FAIL;
	AppDataLen = 0;
	pAppDataBuf = NULL;

	return	PROTO_RET_OK;
}

int SGS_Proto_104::ProtoTX_Init(short stno,short chno)
{
	if(SGS_PCBasic::ProtoTX_Init(stno,chno) == PROTO_RET_FAIL)	return	PROTO_RET_FAIL;

	return	PROTO_RET_OK;
}




/*
 *	获得数据单元标识符
 */
int	
SGS_Proto_104::GetAppHead(IEC104_APP_HEAD *head)
{
	if(pAppDataBuf==NULL || AppDataLen==0)	return	FALSE;
	//unsigned char * appBuffHead = pAppDataBuf;
	int headLen = 0;
	if(config.CotLen == 2)
	{
		memcpy(head,pAppDataBuf,4);
		pAppDataBuf += 4;
		AppDataLen -= 4;
		headLen+=4;
	}
	else
	{
		memcpy(head,pAppDataBuf,3);
		pAppDataBuf += 3;
		AppDataLen -= 3;
		headLen+=3;
	}
	hUInt16	CommAddr = 0;
	if(config.CommAddrLen == 2)
	{
		memcpy(&CommAddr,pAppDataBuf,2);
		pAppDataBuf += 2;
		AppDataLen -= 2;
		headLen+=2;
	}
	else
	{
		memcpy(&CommAddr,pAppDataBuf,1);
		pAppDataBuf += 1;
		AppDataLen -= 1;
		headLen+=1;
	}
	head->CommAddr = CommAddr;
	if(head->CommAddr !=  rd->rtuAddr)	
	{
		SGS_Printer(LOG_104_RX, "! 地址不匹配,报文中地址:%d,本地路径表中配置的远程地址:%d", head->CommAddr , rd->rtuAddr); 
		//printBuffer(appBuffHead,headLen);
		return	FALSE;
	}
	return	TRUE;
}

/*
 *	搜索对象地址
 */
int	
SGS_Proto_104::GetObjAddr()
{
	hUInt32	addr;
	// 初始化
	memset(&addr,0,sizeof(hUInt32));
	memcpy(&addr,pAppDataBuf,config.ObjAddrLen);
	pAppDataBuf += config.ObjAddrLen;
	return	(int)addr;
}

/*
 *	接收
 */
void
SGS_Proto_104::ProtoRX()
{
	int		ret;
	short	len;
	NoRxAnyData();
	GetRecLength(&len);
	while( len >= 6 )
	{
		GetRecBuf(buffer,2);
		
		if(buffer[0] != 0x68)
		{
			PushRxHead(-1);
			//msgRemove(1);
			//msgDisplay(FRAME_RX_ERROR,"head错误");
			continue;
		}
		len -= 2;
		RxDataSize = buffer[1];		
		if(len >= RxDataSize)
		{
			ret = SearchAPCI();

			if(ret == IEC104_APCI_I)
			{
				SearchASDU();
			}
			else if(ret == -1)
			{
				SGS_Printer(LOG_104_RX, "IEC104-错误帧");
				base_info->errCnt++;
			}
			else
			{
				base_info->okCnt++;
			}
			RxSomeData();  
		}
		else	
		{
			PushRxHead(-2);
			break;
		}
	}//end while
}




/*
 *	发送
 */
void
SGS_Proto_104::ProtoTX()
{
	
}
/*
 *	规约基本配置信息
 */
void
SGS_Proto_104::ReadConfig()
{
	//设置初始值――――――――开始
	//长度
	if(config.CommAddrLen == 0)	config.CommAddrLen = 2;
	if(config.ObjAddrLen == 0)	config.ObjAddrLen = 3;
	if(config.CotLen == 0)		config.CotLen = 2;
	config.FrmMinLen = 6;
	//起始地址
	if(config.Yx_Start_Addr == 0)	config.Yx_Start_Addr = IEC104_OBJ_16_ADDR_YX_START;
	if(config.Yx_End_Addr == 0)	config.Yx_End_Addr = IEC104_OBJ_16_ADDR_YX_END;
	if(config.Prot_Start_Addr == 0)	config.Prot_Start_Addr = IEC104_OBJ_16_ADDR_PROT_START;
	if(config.Prot_End_Addr == 0)	config.Prot_End_Addr = IEC104_OBJ_16_ADDR_PROT_END;
	if(config.Yc_Start_Addr == 0)	config.Yc_Start_Addr = IEC104_OBJ_16_ADDR_YC_START;
	if(config.Yc_End_Addr == 0)	config.Yc_End_Addr = IEC104_OBJ_16_ADDR_YC_END;
	if(config.Para_Start_Addr == 0)	config.Para_Start_Addr = IEC104_OBJ_16_ADDR_PARA_START;
	if(config.Para_End_Addr == 0)	config.Para_End_Addr = IEC104_OBJ_16_ADDR_PARA_END;
	if(config.Yk_Start_Addr == 0)	config.Yk_Start_Addr = IEC104_OBJ_16_ADDR_YK_START;
	if(config.Yk_End_Addr == 0)	config.Yk_End_Addr = IEC104_OBJ_16_ADDR_YK_END;
	if(config.Set_Start_Addr == 0)	config.Set_Start_Addr = IEC104_OBJ_16_ADDR_SET_START;
	if(config.Set_End_Addr == 0)	config.Set_End_Addr = IEC104_OBJ_16_ADDR_SET_END;
	if(config.Kwh_Start_Addr == 0)	config.Kwh_Start_Addr = IEC104_OBJ_16_ADDR_KWH_START;
	if(config.Kwh_End_Addr == 0)	config.Kwh_End_Addr = IEC104_OBJ_16_ADDR_KWH_END;
	if(config.Step_Start_Addr == 0)	config.Step_Start_Addr = IEC104_OBJ_16_ADDR_STEP_START;
	if(config.Step_End_Addr == 0)	config.Step_End_Addr = IEC104_OBJ_16_ADDR_STEP_END;
	if(config.Bin_Start_Addr == 0)	config.Bin_Start_Addr = IEC104_OBJ_16_ADDR_BIN_START;
	if(config.Bin_End_Addr == 0)	config.Bin_End_Addr = IEC104_OBJ_16_ADDR_BIN_END;
	if(config.Rtu_State_Addr == 0)	config.Rtu_State_Addr = IEC104_OBJ_16_ADDR_RTU_STATE;
	if(config.File_Start_Addr == 0)	config.File_Start_Addr = IEC104_OBJ_16_ADDR_FILE_START;
	if(config.File_End_Addr == 0)	config.File_End_Addr = IEC104_OBJ_16_ADDR_FILE_END;
	//设置初始值――――――――结束
	//计算基本信息――――――――开始
	config.YcMaxNum = config.Yc_End_Addr - config.Yc_Start_Addr + 1;
	config.YxMaxNum = config.Yx_End_Addr - config.Yx_Start_Addr + 1;
	//config.KwhMaxNum = config.Kwh_End_Addr - config.Kwh_Start_Addr + 1;
	//config.YkMaxNum = config.Yk_End_Addr - config.Yk_Start_Addr + 1;
	//计算基本信息――――――――结束


}

int SGS_Proto_104::SearchAPCI()
{
	GetRecBuf(buffer,4);
	//msgCopy(buffer,4);

	//I格式
	if((buffer[0]&0x01) == IEC104_APCI_I)
	{
		if(RxDataSize <= 4)	return	-1;
		// 判断对方的发送桢和我们的接受计数是否一致，如果不一致重置链路 
		if (IsNsNrMatch((unsigned char*)buffer) == FALSE)
		{
			InitInfo();//重新初始化
			return -1;
		}
		return	IEC104_APCI_I;
	}
	//S格式
	else	if((buffer[0]&0x03) == IEC104_APCI_S)
	{
		if(RxDataSize != 4)	return	-1;
		SGS_Printer(LOG_104_RX, "Rx <---------- IEC104-收到S帧");
		return	IEC104_APCI_S;
	}
	//U格式
	else	if((buffer[0]&0x03) == IEC104_APCI_U)
	{
		if(RxDataSize != 4)	return	-1;
		switch(buffer[0] & 0xFC)
		{
		case	APCI_U_STARTDT_CON:
			if(info.LinkState==STATE_UNBOUND && info.WorkState==STATE_WAIT_STARTDT_CON)
			{
				SGS_Printer(LOG_104_RX, "Rx <------------ 收到104-U格式信息报文：启动链接确认");
				info.LinkState = STATE_IDLE;
				info.WorkState = STATE_FREE;
				info.T5 = 0;
			}
			break;
		case	APCI_U_STOPDT_CON:
			SGS_Printer(LOG_104_RX, "Rx <------------ 收到停止链路确认");
			if(info.LinkState==STATE_IDLE && info.WorkState==STATE_WAIT_STOPDT_CON)
			{
				InitInfo();
			}
			break;
		case	APCI_U_TESTFR_CON:
			SGS_Printer(LOG_104_RX, "Rx <------------ 收到测试链路确认");
			if(info.LinkState==STATE_IDLE && info.WorkState==STATE_WAIT_TESTDT_CON)
			{
				info.WorkState = STATE_FREE;
				info.T5 = 0;
			}
			break;
		case	APCI_U_TESTFR_ACT:
			SGS_Printer(LOG_104_RX, "Rx <-------------- IEC-104-U 格式信息报文：激活测试帧");
			info.Send_U_TESTFR_CON_Flag = TRUE;
			if(info.LinkState==STATE_IDLE)
			{
				info.WorkState = STATE_FREE;
			}
			break;
		default:
			return	-1;
		}
		return	IEC104_APCI_U;
	}
	return	-1;
}

void SGS_Proto_104::RxSomeData()
{
	// bruce +++++++++++++++++++++++++++++++++++++++
	if (info.WorkState == STATE_FREE)// 只有受到相应的报文，例如请求全数据对方回答全数据
	{
		info.T1 = 0;
	}
	// bruce +++++++++++++++++++++++++++++++++++++++
	info.T3 = 0;
}

int SGS_Proto_104::SearchASDU()
{
	if(info.LinkState == STATE_UNBOUND)
	{
		SGS_Printer(LOG_104_RX, "Rx <------------- 链路未启用，收到报文，不处理");
		return	FALSE;
	}

	info.NR = (info.NR + 1) % (unsigned short)0x8000;
	AppDataLen = RxDataSize - 4;
	GetRecBuf(buffer,AppDataLen);

	pAppDataBuf = buffer;
	IEC104_APP_HEAD		AppHead;
	if(GetAppHead(&AppHead) == FALSE)
	{
		SGS_Printer(LOG_104_RX, "Rx <------------- GetAppHead() == FALSE");
		return	FALSE;
	}

	base_info->okCnt++;
	info.W ++;
	info.Send_S_ACK_Flag = TRUE;
	//logprint(LOG_104_RX, "Rx <------------- GetAppHead() == TRUE, AppHead.Type = %d", AppHead.Type);
	switch(AppHead.Type)
	{
	case	C_IC_NA_1:		//总召唤
		DoCallAllDataAck(AppHead);
		break;
	case	C_CI_NA_1:		//计数量召唤
		DoCallAllKwhAck(AppHead);
		break;
	case	C_CS_NA_1:		//时钟同步
		DoSyncTimeAck(AppHead);
		break;
	case	C_SC_NA_1:		//遥控（单点命令）
	case	C_DC_NA_1:		//遥控（双点命令）
		SGS_Printer(LOG_104_RX, "Rx <--------- 设备控制返校报文 <激活确认>");
		DoYkAck(AppHead);
		break;
	case	C_RC_NA_1:		//遥调
		break;
	case	C_SE_NA_1:		//设点归一化
	case	C_SE_NB_1:		//标度化
	case	C_SE_NC_1:		//浮点
		SGS_Printer(LOG_104_RX, "Rx <--------- 控制设点返校报文 <激活确认>");
		DoAnalogOutPutAck(AppHead);
		break;
	case	M_SP_NA_1:		//单点信息
	case	M_DP_NA_1:		//双点信息
	case	M_PS_NA_1:		//带变位检出的成组单点信息
		YX_RxProc(AppHead);
		break;
	case	M_SP_TA_1:		//带CP24Time2a时标的单点信息
	case	M_DP_TA_1:		//带CP24Time2a时标的双点信息
	case	M_SP_TB_1:		//带CP56Time2a时标的单点信息
	case	M_DP_TB_1:		//带CP56Time2a时标的双点信息
		SOE_RxProc(AppHead);
		break;
	case	M_ME_NA_1:		//测量值，规一化值
	case	M_ME_NB_1:		//测量值，标度化值
	case	M_ME_NC_1:		//测量值，短浮点数
	case	M_ME_TA_1:		//带CP24Time2a时标的测量值，规一化值
	case	M_ME_TB_1:		//带CP24Time2a时标的测量值，标度化值
	case	M_ME_TC_1:		//带CP24Time2a时标的测量值，短浮点数
	case	M_ME_TD_1:		//带CP56Time2a时标的测量值，规一化值
	case	M_ME_TE_1:		//带CP56Time2a时标的测量值，标度化值
	case	M_ME_TF_1:		//带CP56Time2a时标的测量值，短浮点数
	case	M_ME_ND_1:		//测量值，不带品质描述词的规一化值
		YC_RxProc(AppHead);
		break;
	case	M_IT_NA_1:		//累积量
	case	M_IT_TA_1:		//带CP24Time2a时标的累积量
	case	M_IT_TB_1:		//带CP56Time2a时标的累积量
		//KWH_RxProc(AppHead);
		break;
	case P_PL_NA_1:
		//PLAN_RxProc(AppHead);
		break;
	default:
		SGS_Printer(LOG_104_RX,"错误:未知类型");
		break;
	}

	return	TRUE;
}

void SGS_Proto_104::NoRxAnyData()
{
	//info.T1++;//T1超时应在I桢无应答或者T3超时后测试连接无应答后发生
	if (info.WorkState!=STATE_FREE)
	{
		info.T1++;
	}
	info.T3++;
}

void SGS_Proto_104::InitInfo()
{
	info.T1 = 0;
	info.T2 = 0;
	info.T3 = 0;
	info.T4 = 0;
	info.T5 = 0;

	info.LinkState = STATE_UNBOUND;
	info.WorkState = STATE_FREE;
	info.NS = 0;
	info.NR = 0;
	info.SendTimeFlag    = TRUE;   
	info.CallAllDataFlag = TRUE;
	info.CallAllKwhFlag =  TRUE;
	info.Send_S_ACK_Flag = FALSE;
	info.Send_U_TESTFR_ACT_Flag = FALSE;
	info.Send_U_STOPDT_ACT_Flag = FALSE;
	info.W = 0;
}

int SGS_Proto_104::IsNsNrMatch( unsigned char * buff )
{
	int nPeerNs = (buff[0]>>1)+buff[1]*128;

	if (info.NR == nPeerNs)// && info.Ns == nPeerNr)
		return TRUE;

	SGS_Printer(LOG_104_RX, "Rx <---------- 对方发送桢计数(%d)和我们的接受计数(%d)不一致, 重置链路",nPeerNs,info.NR);
	return FALSE;
}

void SGS_Proto_104::YC_RxProc( IEC104_APP_HEAD &head )
{
	SGS_Printer(LOG_104_RX, "RX <----------------------- YC_RxProc");
	if(head.VSQ.Num == 0)	
	{
		//msgDisplay(FRAME_RX_ERROR,"错误:VSQ不合理");
		return;
	}

	unsigned short	i,no,num,maxnum;
	//nDateTime		cp24Time;
	//int				ms;

	num = head.VSQ.Num;
	maxnum = rd->ycnum;

	//解析后报文信息
	char descr[64] = "";
	ACE_OS::sprintf(descr,"遥测值 num=%d",num);
	//msgDisplay(FRAME_RX,descr);

	float val = 0.0;

	switch(head.Type)
	{
	case	M_ME_NA_1:		//测量值，规一化值
	case	M_ME_NB_1:		//测量值，标度化值
		{
			SGS_Printer(LOG_104_RX, "RX <------------ 测量值 num=%d", num);
			for(i=0;i<num;i++)
			{
				if(i==0 || head.VSQ.SQ==0)
				{
					int objaddr = GetObjAddr();
					unsigned short ycstartaddr = config.Yc_Start_Addr;
					SGS_Printer(LOG_104_RX, "RX <------------ Obj Address=%d, YC Start Address = %d", objaddr, ycstartaddr);
					no = objaddr - ycstartaddr;
				}
				else no++;

				if(no >= maxnum)
				{
					SGS_Printer(LOG_104_RX, "RX <------------ no(%d)>maxnum(%d)", no,maxnum);
					if(head.VSQ.SQ)
					{
						break;
					}
					pAppDataBuf += 3;
					continue;
				}
				if(pAppDataBuf[2] & 0x80)	 // 未被激活,wfp changed at 20080403 for henan,old=81
				{
					SGS_Printer(LOG_104_RX, "RX <------------ pAppDataBuf[2]=%x, continue", pAppDataBuf[2]);
					pAppDataBuf += 3;	
					continue;
				}
				val = 0.0;
				val = (float)MakeWord(pAppDataBuf[0],(pAppDataBuf[1]&0x7F));
				if(pAppDataBuf[1] & 0x80)	val = -(float)(0xFFFF - MakeWord(pAppDataBuf[0],pAppDataBuf[1]) + 1);
				pAppDataBuf += 3;

				SetOneYc(no,val);
			}
			break;
		}
	case	M_ME_TA_1:		//带CP24Time2a时标的测量值，规一化值
	case	M_ME_TB_1:		//带CP24Time2a时标的测量值，标度化值
		{
			for(i=0;i<num;i++)
			{
				if(i==0 || head.VSQ.SQ==0)	no = GetObjAddr() - config.Yc_Start_Addr;
				else	no++;
				if(no >= maxnum)
				{
					if(head.VSQ.SQ)	break;
					pAppDataBuf += 6;
					continue;
				}
				if(pAppDataBuf[2] & 0x80)	 // 未被激活,wfp changed at 20080403 for henan,old=81
				{
					pAppDataBuf += 6;	
					continue;
				}
				val = 0.0;
				val = (float)MakeWord(pAppDataBuf[0],(pAppDataBuf[1]&0x7F));
				if(pAppDataBuf[1] & 0x80)	val = -(float)(0xFFFF - MakeWord(pAppDataBuf[0],pAppDataBuf[1]) + 1);
				pAppDataBuf += 3;
				//时间处理
	/*			ms = MakeWord(pAppDataBuf[0],pAppDataBuf[1]);

				CDateTime::currentDateTime(cp24Time);
				cp24Time.min = pAppDataBuf[2] & 0x3F;
				cp24Time.sec = ms / 1000;
				cp24Time.msec = ms % 1000;
				pAppDataBuf += 3;
				data.updateTime = (hUInt32)CDateTime(cp24Time.year,cp24Time.mon,cp24Time.day,
					cp24Time.hour,cp24Time.min,cp24Time.sec).toTimeT();*/

				SetOneYc(no,val);
			}
			break;
		}
	case	M_ME_TD_1:	//带CP56Time2a时标的测量值，规一化值
	case	M_ME_TE_1:	//带CP56Time2a时标的测量值，标度化值
		{
			for(i=0;i<num;i++)
			{
				if(i==0 || head.VSQ.SQ==0)	no = GetObjAddr() - config.Yc_Start_Addr;
				else	no++;
				if(no >= maxnum)
				{
					if(head.VSQ.SQ)	break;
					pAppDataBuf += 10;
					continue;
				}
				if(pAppDataBuf[2] & 0x80)	 // 未被激活,wfp changed at 20080403 for henan,old=81
				{
					pAppDataBuf += 10;	
					continue;
				}
				val = 0.0;
				val = MakeWord(pAppDataBuf[0],(pAppDataBuf[1]&0x7F));
				if(pAppDataBuf[1] & 0x80)	val = -(float)(0xFFFF - MakeWord(pAppDataBuf[0],pAppDataBuf[1]) + 1);
				pAppDataBuf += 3;
				////时间处理  
				//int ms = MakeWord(pAppDataBuf[0],pAppDataBuf[1]);
				//int seconds = ms/1000;
				//int minute = pAppDataBuf[2] & 0x3F;
				//int hour = pAppDataBuf[3] & 0x3F;
				//int day = pAppDataBuf[4] & 0x1F;
				//int month = pAppDataBuf[5] & 0x0F;
				//int year = (pAppDataBuf[6] & 0x7F) + 2000;
				//if ( year > (CDateTime().year() + 1) ) year -= 100;
				//if ( year == 1970 ) seconds += 30;
				//data.updateTime = (hUInt32)CDateTime(year,month,day,hour,minute,seconds).toTimeT();
				pAppDataBuf += 7;
				SetOneYc(no,val);
			}
			break;
		}
	case	M_ME_NC_1:		//测量值，短浮点数
		{
			SGS_Printer(LOG_104_RX, "RX <------------ 测量值 短浮点数 num=%d", num);
			for(i=0;i<num;i++)
			{
				if(i==0 || head.VSQ.SQ==0)	no = GetObjAddr() - config.Yc_Start_Addr;
				else	no++;
				if(no >= maxnum)
				{
					if(head.VSQ.SQ)	break;
					pAppDataBuf += 5;
					continue;
				}

				// ------------------ 质量码相关 --------------------------------
				if(pAppDataBuf[4] & 0x80)     // 未被激活,wfp changed at 20080403 for henan,old=81
				{
					pAppDataBuf += 5;	
					continue;
				}
				//memset(&data,0,sizeof(data));

				// ------------------ 质量码相关 --------------------------------
				//hUInt32 quality = 0;
				//if(pAppDataBuf[4] & 0x40)    // 无效标志
				//	PDT_SET_BITS(quality,QUALITY_BIT_IV);
				//if(pAppDataBuf[4] & 0x20)    // 人工标志
				//	PDT_SET_BITS(quality,QUALITY_BIT_MS);
				//if(pAppDataBuf[4] & 0x01)    // wfp added at 20080403 for henan
				//	PDT_SET_BITS(quality,QUALITY_BIT_OV);

				//data.quality = quality;
				val = 0.0;
				memcpy(&val,pAppDataBuf,4);
				pAppDataBuf += 5;
				SetOneYc(no,val);
			}
			break;
		}
	case	M_ME_TC_1:		//带CP24Time2a时标的测量值，短浮点数
		{
			for(i=0;i<num;i++)
			{
				if(i==0 || head.VSQ.SQ==0)	no = GetObjAddr() - config.Yc_Start_Addr;
				else	no++;
				if(no >= maxnum)
				{
					if(head.VSQ.SQ)	break;
					pAppDataBuf += 8;
					continue;
				}
				if(pAppDataBuf[4] & 0x80)	 // 未被激活,wfp changed at 20080403 for henan,old=81
				{
					pAppDataBuf += 5;
					continue;
				}
				//memset(&data, 0, sizeof(data));
				val = 0.0;
				memcpy(&val,pAppDataBuf,4);
				pAppDataBuf += 5;
				////时间处理
				//ms = MakeWord(pAppDataBuf[0],pAppDataBuf[1]);

				//CDateTime::currentDateTime(cp24Time);
				//cp24Time.min = pAppDataBuf[2] & 0x3F;
				//cp24Time.sec = ms / 1000;
				//cp24Time.msec = ms % 1000;
				//pAppDataBuf += 3;
				//data.updateTime = (hUInt32)CDateTime(cp24Time.year,cp24Time.mon,cp24Time.day,
				//	cp24Time.hour,cp24Time.min,cp24Time.sec).toTimeT();

				SetOneYc(no,val);
			}
			break;
		}
	case	M_ME_TF_1:		//带CP56Time2a时标的测量值，短浮点数
		{
			for(i=0;i<num;i++)
			{
				if(i==0 || head.VSQ.SQ==0)	no = GetObjAddr() - config.Yc_Start_Addr;
				else	no++;
				if(no >= maxnum)
				{
					if(head.VSQ.SQ)	break;
					pAppDataBuf += 12;
					continue;
				}
				if(pAppDataBuf[4] & 0x80)	 // 未被激活,wfp changed at 20080403 for henan,old=81
				{
					pAppDataBuf += 12;	
					continue;
				}
				val = 0.0;
				memcpy(&val,pAppDataBuf,4);
				// ------------------ 质量码相关 --------------------------------
				//hUInt32 quality = 0;
				//if(pAppDataBuf[4] & 0x40)    // 无效标志
				//	PDT_SET_BITS(quality,QUALITY_BIT_IV);
				//if(pAppDataBuf[4] & 0x20)    // 人工标志
				//	PDT_SET_BITS(quality,QUALITY_BIT_MS);
				//if(pAppDataBuf[4] & 0x01)    // wfp added at 20080403 for henan
				//	PDT_SET_BITS(quality,QUALITY_BIT_OV);

				//data.quality = quality;
				pAppDataBuf += 5;
				////七个字节的时间信息暂时未处理
				//int ms = MakeWord(pAppDataBuf[0],pAppDataBuf[1]);
				//int seconds = ms/1000;
				//int minute = pAppDataBuf[2] & 0x3F;
				//int hour = pAppDataBuf[3] & 0x3F;
				//int day = pAppDataBuf[4] & 0x1F;
				//int month = pAppDataBuf[5] & 0x0F;
				//int year = (pAppDataBuf[6] & 0x7F) + 2000;
				//if ( year > (CDateTime().year() + 1) ) year -= 100;
				//if ( year == 1970 ) seconds += 30;
				//data.updateTime = (hUInt32)CDateTime(year,month,day,hour,minute,seconds).toTimeT();
				pAppDataBuf += 7;
				//时间处理

				SetOneYc(no,val);
			}
			break;
		}
	case	M_ME_ND_1:		//测量值，不带品质描述词的规一化值
		{
			for(i=0;i<num;i++)
			{
				if(i==0 || head.VSQ.SQ==0)	no = GetObjAddr() - config.Yc_Start_Addr;
				else	no++;
				if(no >= maxnum)
				{
					if(head.VSQ.SQ)	break;
					pAppDataBuf += 2;
					continue;
				}
				val = 0.0;
				val = (float)MakeWord(pAppDataBuf[0],(pAppDataBuf[1]&0x7F));
				if(pAppDataBuf[1] & 0x80)	val = -(float)(0xFFFF - MakeWord(pAppDataBuf[0],pAppDataBuf[1]) + 1);
				pAppDataBuf += 2;
				SetOneYc(no,val);
			}
			break;
		}
	default:
		break;
	}
}

void SGS_Proto_104::YX_RxProc( IEC104_APP_HEAD &head )
{
	if(head.VSQ.Num == 0)	
	{
		//msgDisplay(FRAME_RX_ERROR,"错误:VSQ不合理");
		return;
	}

	unsigned short	i,no,num,maxnum;
	//DAC_YX_DATA data;
	//memset(&data, 0, sizeof(data));
	num = head.VSQ.Num;
	maxnum = rd->yxnum;

	unsigned char		val;

	////解析后报文信息
	//char descr[64] = "";
	//ACE_OS::sprintf(descr,"遥信值 num=%d",num);
	//msgDisplay(FRAME_RX,descr);


	switch(head.Type)
	{
	case	M_SP_NA_1:		//单点信息
		{
			SGS_Printer(LOG_104_RX, "Rx <----------- 单点信息(num=%d)", num);
			for(i=0;i<num;i++)
			{
				if(i==0 || head.VSQ.SQ==0)	no = GetObjAddr() - config.Yx_Start_Addr;
				else	no++;
				if(no >= maxnum)
				{
					if(head.VSQ.SQ)	
					{
						break;
					}
					pAppDataBuf += 1;
					continue;
				}

				// ------------------ 质量码相关 --------------------------------
				if(pAppDataBuf[0] & 0x80)     // 未被激活==规约无效位
				{
					pAppDataBuf += 1;
					SGS_Printer(LOG_104_RX,"未被激活");
					continue;
				}
				

				//// ------------------ 质量码相关 --------------------------------
				//hUInt32 quality = 0;
				//if(pAppDataBuf[0] & 0x40)    // 老值标志=无效
				//	PDT_SET_BITS(quality,QUALITY_BIT_IV);
				//if(pAppDataBuf[0] & 0x20)    // 取代=人工标志
				//	PDT_SET_BITS(quality,QUALITY_BIT_MS);

				//data.quality = quality;
				val = 0;
				val = pAppDataBuf[0] & 0x0F;	//wfp changed at 20110218 (0x01-->0x0F)

				pAppDataBuf += 1;
				SetOneYx(no,val);
			}
			break;
		}
	case	M_DP_NA_1:		//双点信息
		{
			for(i=0;i<num;i++)
			{
				if(i==0 || head.VSQ.SQ==0)	no = GetObjAddr() - config.Yx_Start_Addr;
				else	no++;
				if(no >= maxnum)
				{
					if(head.VSQ.SQ)	break;
					pAppDataBuf += 1;
					continue;
				}

				val = 0;
				val = pAppDataBuf[0] & 0x03;
				pAppDataBuf += 1;
				if(val!=0x01 && val!=0x02)	continue;
				val -= 0x01;
				SetOneYx(no,val);
			}
			break;
		}
	case	M_PS_NA_1:		//带变位检出的成组单点信息
		break;
	default:
		break;
	}
}

void SGS_Proto_104::DoCallAllDataAck( IEC104_APP_HEAD &head )
{
	//结构限定词
	if(head.VSQ.SQ!=0 || head.VSQ.Num!=1)	
	{
		SGS_Printer(LOG_104_RX, "Rx <----------- head.VSQ.SQ == %d ,head.VSQ.Num = %d, 不合理",
			head.VSQ.SQ, head.VSQ.Num);
		//msgDisplay(FRAME_RX_ERROR,"错误:VSQ不合理");
		return;
	}
	//传输原因
	switch(head.COT.Cause)
	{
	case	CAUSE_ACT_CON:
		SGS_Printer(LOG_104_RX, "Rx <----------- 全数据 激活确认");
		//msgDisplay(FRAME_RX,"全数据激活确认");
		if(info.WorkState == STATE_WAIT_ALLDATA_CON)	
		{
			info.WorkState = STATE_WAIT_ALLDATA;
			info.T5 = 0;
		}
		break;
	case	CAUSE_STOPACT_CON:
		SGS_Printer(LOG_104_RX, "Rx <----------- 全数据 停止激活确认");
		//msgDisplay(FRAME_RX,"全数据停止激活确认");
		if(info.WorkState == STATE_WAIT_ALLDATA_CON)
		{
			info.WorkState = STATE_FREE;
			info.T5 = 0;
		}
		break;
	case	CAUSE_ACT_TERM:
		SGS_Printer(LOG_104_RX, "Rx <----------- 全数据 激活终止");
		//msgDisplay(FRAME_RX,"全数据 激活终止");
		if(info.WorkState == STATE_WAIT_ALLDATA)
		{
			info.WorkState = STATE_FREE;
			info.T5 = 0;
		}
		break;
	default:
		SGS_Printer(LOG_104_RX, "Rx <----------- head.COT.Cause = %d, 未知的确认原因",head.COT.Cause);
		//msgDisplay(FRAME_RX_ERROR,"错误:未知的确认原因");
		break;
	}
}

void SGS_Proto_104::DoSyncTimeAck( IEC104_APP_HEAD &head )
{
	//结构限定词
	if(head.VSQ.SQ!=0 || head.VSQ.Num!=1)
	{
		SGS_Printer(LOG_104_RX, "Rx <------------ head.VSQ.SQ!=0 || head.VSQ.Num!=1");
		//msgDisplay(FRAME_RX_ERROR,"错误:VSQ不合理");
		return;
	}
	//传输原因
	if( head.COT.Cause==CAUSE_ACT_CON )
	{
		//msgDisplay(FRAME_RX,"对时确认");
		if (info.WorkState==STATE_WAIT_TIME_CON )
		{
			SGS_Printer(LOG_104_RX, "Rx <------------ 对时得到确认，将工作状态置为空闲");
			info.WorkState = STATE_FREE;
			info.T5 = 0;
		}
		else SGS_Printer(LOG_104_RX, "Rx <------------ 对时得到确认，工作状态不是Wait sync time confirm");
	}
	else 
	{
		SGS_Printer(LOG_104_RX, "Rx <------------ 对时没有得到确认");
		//msgDisplay(FRAME_RX_ERROR,"错误:对时确认失败");
	}
}

void SGS_Proto_104::DoCallAllKwhAck( IEC104_APP_HEAD &head )
{
	//结构限定词
	if(head.VSQ.SQ!=0 || head.VSQ.Num!=1)	
	{
		//msgDisplay(FRAME_RX_ERROR,"错误:VSQ不合理");
		return;
	}
	//传输原因
	switch(head.COT.Cause)
	{
	case	CAUSE_ACT_CON:
		//msgDisplay(FRAME_RX,"全电度激活确认");
		if(info.WorkState == STATE_WAIT_ALLKWH_CON)
		{
			info.WorkState = STATE_WAIT_ALLKWH;
			info.T5 = 0;
		}
		break;
	case	CAUSE_STOPACT_CON:
		//msgDisplay(FRAME_RX,"全数据停止激活确认");
		if(info.WorkState == STATE_WAIT_ALLKWH_CON)
		{
			info.WorkState = STATE_FREE;
			info.T5 = 0;
		}
		break;
	case	CAUSE_ACT_TERM:
		//msgDisplay(FRAME_RX,"全数据激活终止");
		if(info.WorkState == STATE_WAIT_ALLKWH)
		{
			info.WorkState = STATE_FREE;
			info.T5 = 0;
		}
		break;
	default:
		//msgDisplay(FRAME_RX_ERROR,"错误:未知的确认原因");
		break;
	}
}

void SGS_Proto_104::SOE_RxProc( IEC104_APP_HEAD &head )
{
	if(head.VSQ.Num == 0)	
	{
		//msgDisplay(FRAME_RX_ERROR,"错误:VSQ不合理");
		return;
	}

	int				ms;
	hUInt8			value;
	unsigned short	i,no,num,maxnum;
	nDateTime		soeTime;
	SGS_SOE_Data	soedata;
	//add for SOE flush rtdb
	unsigned char yxdata;
	num = head.VSQ.Num;
	maxnum = rd->yxnum;

	////解析后报文信息
	//char descr[64] = "";
	//ACE_OS::sprintf(descr,"SOE num=%d",num);
	//msgDisplay(FRAME_RX,descr);

	switch(head.Type)
	{
	case	M_SP_TA_1:		//带CP24Time2a时标的单点信息
		{
			for(i=0;i<num;i++)
			{
				if(i==0 || head.VSQ.SQ==0)	no = GetObjAddr() - config.Yx_Start_Addr;
				else	no++;
				if(no >= maxnum)
				{
					if(head.VSQ.SQ)	break;
					pAppDataBuf += 4;
					continue;
				}
				value = pAppDataBuf[0] & 0x01;
				ms = MakeWord(pAppDataBuf[1],pAppDataBuf[2]);

				QDateTime time = QDateTime::currentDateTime();

				soeTime.year = time.date().year();
				soeTime.mon = time.date().month();
				soeTime.day = time.date().day();
				soeTime.hour = time.time().hour();
				soeTime.min = pAppDataBuf[3] & 0x3F;
				soeTime.sec = ms / 1000;
				soeTime.msec = ms % 1000;

				memset(&soedata,0,sizeof(SGS_SOE_Data));
				soedata.ctim = soeTime;
				soedata.yxno = no;
				soedata.val = value;
				//add for SOE flush rtdb 20150511 
				yxdata = value;
				//yxdata.updateTime = CDateTime(soedata.soeTime.year,soedata.soeTime.mon,soedata.soeTime.day,soedata.soeTime.hour,soedata.soeTime.min,soedata.soeTime.sec).toTimeT();
				//yxdata.quality = 0;
				SetOneYx(no,yxdata);
				//add end 20150511
				pAppDataBuf += 4;
				SetOneSoe(soedata);
			}
			break;
		}
	case	M_DP_NA_1:		//带CP24Time2a时标的双点信息
		{
			for(i=0;i<num;i++)
			{
				if(i==0 || head.VSQ.SQ==0)	no = GetObjAddr() - config.Yx_Start_Addr;
				else	no++;
				if(no >= maxnum)
				{
					if(head.VSQ.SQ)	break;
					pAppDataBuf += 4;
					continue;
				}
				value = pAppDataBuf[0] & 0x03;
				if(value!=0x01 && value!=0x02)	{pAppDataBuf += 4;	continue;}
				value -= 0x01;
				ms = MakeWord(pAppDataBuf[1],pAppDataBuf[2]);

				QDateTime time = QDateTime::currentDateTime();

				soeTime.year = time.date().year();
				soeTime.mon = time.date().month();
				soeTime.day = time.date().day();
				soeTime.hour = time.time().hour();
				soeTime.min = pAppDataBuf[3] & 0x3F;
				soeTime.sec = ms / 1000;
				soeTime.msec = ms % 1000;
				memset(&soedata,0,sizeof(SGS_SOE_Data));
				soedata.ctim = soeTime;
				soedata.yxno = no;
				soedata.val = value;
				//add for SOE flush rtdb 20150511 
				yxdata = value;
				//yxdata.updateTime = CDateTime(soedata.soeTime.year,soedata.soeTime.mon,soedata.soeTime.day,soedata.soeTime.hour,soedata.soeTime.min,soedata.soeTime.sec).toTimeT();
				//yxdata.quality = 0;
				SetOneYx(no,yxdata);
				//add end 20150511
				pAppDataBuf += 4;
				SetOneSoe(soedata);
			}
			break;
		}
	case	M_SP_TB_1:	//带CP56Time2a时标的单点信息
		{
			for(i=0;i<num;i++)
			{
				if(i==0 || head.VSQ.SQ==0)	no = GetObjAddr() - config.Yx_Start_Addr;
				else	no++;
				if(no >= maxnum)
				{
					if(head.VSQ.SQ)	break;
					pAppDataBuf += 8;
					continue;
				}
				value = pAppDataBuf[0] & 0x01;
				ms = MakeWord(pAppDataBuf[1],pAppDataBuf[2]);
				soeTime.min = pAppDataBuf[3] & 0x3F;
				soeTime.hour = pAppDataBuf[4] & 0x1F;
				soeTime.day = pAppDataBuf[5] & 0x1F;
				soeTime.wday = (pAppDataBuf[5]>>5) & 0x07;
				soeTime.mon = pAppDataBuf[6] & 0x0F;
				soeTime.year = (pAppDataBuf[7]&0x7F) + 2000;
				soeTime.sec = ms / 1000;
				soeTime.msec = ms % 1000;

/*				if( m_pRoute->timeMode == TIME_GREENWICH)
				{
					CDateTime dateTime(soeTime);
					ACE_Time_Value tv = dateTime.toTimeValue() + ACE_Time_Value(8*60*60);
					dateTime.update(tv);
					dateTime.toNDateTime(soeTime);
					soeTime.msec = ms % 1000;
				}*/				
				memset(&soedata,0,sizeof(SGS_SOE_Data));
				soedata.ctim = soeTime;
				soedata.yxno = no;
				soedata.val = value;
				//add for SOE flush rtdb 20150511 
				yxdata = value;
				//yxdata.updateTime = CDateTime(soedata.soeTime.year,soedata.soeTime.mon,soedata.soeTime.day,soedata.soeTime.hour,soedata.soeTime.min,soedata.soeTime.sec).toTimeT();
				//yxdata.quality = 0;
				SetOneYx(no,yxdata);
				//add end 20150511
				pAppDataBuf += 8;
				SetOneSoe(soedata);
			}
			break;
		}
	case	M_DP_TB_1:	//带CP56Time2a时标的双点信息
		{
			for(i=0;i<num;i++)
			{
				if(i==0 || head.VSQ.SQ==0)	no = GetObjAddr() - config.Yx_Start_Addr;
				else	no++;
				if(no >= maxnum)
				{
					if(head.VSQ.SQ)	break;
					pAppDataBuf += 8;
					continue;
				}
				value = pAppDataBuf[0] & 0x03;
				if(value!=0x01 && value!=0x02)	{pAppDataBuf += 8;	continue;}
				value -= 0x01;
				ms = MakeWord(pAppDataBuf[1],pAppDataBuf[2]);
				soeTime.min = pAppDataBuf[3] & 0x3F;
				soeTime.hour = pAppDataBuf[4] & 0x1F;
				soeTime.day = pAppDataBuf[5] & 0x1F;
				soeTime.wday = (pAppDataBuf[5]>>5) & 0x07;
				soeTime.mon = pAppDataBuf[6] & 0x0F;
				soeTime.year = (pAppDataBuf[7]&0x7F) + 2000;
				soeTime.sec = ms / 1000;
				soeTime.msec = ms % 1000;

				//if( m_pRoute->timeMode == TIME_GREENWICH )
				//{
				//	CDateTime dateTime(soeTime);
				//	ACE_Time_Value tv = dateTime.toTimeValue() + ACE_Time_Value(8*60*60);
				//	dateTime.update(tv);
				//	dateTime.toNDateTime(soeTime);
				//	soeTime.msec = ms % 1000;
				//}
				memset(&soedata,0,sizeof(SGS_SOE_Data));
				soedata.ctim = soeTime;
				soedata.yxno = no;
				soedata.val = value;

				yxdata = value;
				//yxdata.updateTime = CDateTime(soedata.soeTime.year,soedata.soeTime.mon,soedata.soeTime.day,soedata.soeTime.hour,soedata.soeTime.min,soedata.soeTime.sec).toTimeT();
				//yxdata.quality = 0;
				SetOneYx(no,yxdata);

				pAppDataBuf += 8;
				SetOneSoe(soedata);
			}
			break;
		}
	default:
		break;
	}
}

void SGS_Proto_104::DoAnalogOutPutAck( IEC104_APP_HEAD &head )
{
	//结构限定词
	if(head.VSQ.SQ!=0 || head.VSQ.Num!=1)	
	{
		//msgDisplay(FRAME_RX_ERROR,"错误:VSQ不合理");
		return;
	}

	unsigned short	no;
	//序号
	no = GetObjAddr() - config.Set_Start_Addr;
	//值
	hInt16		value;
	switch (head.Type)
	{
	case	C_SE_NA_1:		//归一化
	case	C_SE_NB_1:		//标度化
		memcpy(&value,pAppDataBuf,2);
		pAppDataBuf += 2;
		break;
	case	C_SE_NC_1:		//浮点
		memcpy(&value,pAppDataBuf,4);
		pAppDataBuf += 4;
		break;
	}
	//设点命令限定词
	hUInt8		S_E;   //控制类型
	hUInt8		QOS = *(pAppDataBuf++);
	//传输原因
	//CAE_CControlInterface	cae_ctrlinf;
	switch(head.COT.Cause)
	{
	case	CAUSE_ACT_CON:		//激活确认
		S_E = (QOS & 0x80)? YK_ACTION_SELECT_V:YK_ACTION_EXECUTE;	//YK_ACTION_SELECT_V――执行，YK_ACTION_EXECUTE
		SGS_Printer(30099,"收到模拟量输出激活确认 : Rtu = %d , No = %d , Value = %d",rd->order,no,(hInt32)value);
		//msgDisplay(FRAME_RX,"模拟量输出激活确认");
		//cae_ctrlinf.SendYKReturnCmd(rtu_no,no,TRUE);
		break;
	case	CAUSE_STOPACT_CON:	//停止激活确认
		S_E = YK_ACTION_CANCEL;   // YK_ACTION_CANCEL--遥控撤销
		SGS_Printer(30099,"收到模拟量输出停止激活确认 : Rtu = %d , No = %d , Value = %d",rd->order,no,(hInt32)value);
		//msgDisplay(FRAME_RX,"模拟量输出停止激活确认");
		//cae_ctrlinf.SendYKReturnCmd(rtu_no,no,FALSE);
		break;
	default:
		//msgDisplay(30099,"错误:模拟量输出确认失败");
		return;
	}

	SGS_ChanYC_Shm_Ptr_T ycptr = NULL;
	//m_pGroup = m_commInf.group( m_pRoute->group); //找到数据组
	for (hUInt32 pointNo = 0;pointNo < rd->ycnum ; pointNo++)
	{
		ycptr = da->data_yc + pointNo;
		//ycptr = m_dataInf.ycPara( m_pRoute->group,pointNo);  //根据数据组号和遥测号找到遥测表
		if (ycptr == NULL || !ycptr->valid) continue;
		if (ycptr->isctrl ==1 && ycptr->ctrlno == no)
		{
			break;
		}
		ycptr = NULL;
	}
	if(!ycptr)
	{
		SGS_Printer(30099,"<group=%d,code=%d> oo遥调返校组报文错误oo! 测点不存在",rd->order,no);
		return ;
	}

	ctrl_pro_yk_ack ack;
	memset(&ack,0,sizeof(ctrl_pro_yk_ack));
	ack.ctrlNo = no;
	ack.funcCode = S_E;
	ack.groupNo = ycptr->srcgrp;

	ack.ackState = 0;
	if ( !setCtrlCmdAckEx((char*)(&ack),sizeof(ctrl_pro_yk_ack))) 
	{
		SGS_Printer(30099,"<group=%d,code=%d> oo遥调返校输出错误oo! 信号无法传递给后台",ack.groupNo,ack.ctrlNo);
		return ;
	}
	SGS_Printer(30099,"<group = %d,no = %d,funcCode = %d,state = %d> 遥调返校验输出成功！",ack.groupNo,ack.ctrlNo,ack.funcCode,ack.ackState);


	
	return ;
}

void SGS_Proto_104::DoYkAck( IEC104_APP_HEAD &head )
{
	//结构限定词
	if(head.VSQ.SQ!=0 || head.VSQ.Num!=1)	
	{
		//msgDisplay(FRAME_RX_ERROR,"错误:VSQ不合理");
		return;
	}

	unsigned char	state;
	unsigned short	no;
	hUInt8		S_E,QU,D_SCS;
	//遥控号
	no = GetObjAddr() - config.Yk_Start_Addr;
	hUInt8		D_SCO = *(pAppDataBuf++);

	//传输原因
	switch(head.COT.Cause)
	{
	case	CAUSE_ACT_CON:		//激活确认7
		S_E = (D_SCO & 0x80)? YK_ACTION_SELECT_V:YK_ACTION_EXECUTE;	//控制类型YK_ACTION_SELECT_V――执行，YK_ACTION_EXECUTE――选择
		//msgDisplay(FRAME_RX,"遥控激活确认");
		break;
	case	CAUSE_STOPACT_CON:	//停止激活确认9
		S_E = YK_ACTION_CANCEL;   // YK_ACTION_CANCEL--遥控撤销
		//msgDisplay(FRAME_RX,"遥控停止激活确认");
		break;
	default:
		//msgDisplay(FRAME_RX_ERROR,"错误:遥控确认失败");
		return;
	}
	//遥控命令限定词
	switch(head.Type)
	{
	case	C_SC_NA_1:			//单点命令
		QU = (D_SCO & 0x7E) >> 1;
		D_SCS = D_SCO & 0x01;
		if(D_SCS == 0)	state = YK_OFF;			//开――0
		else	state = YK_ON;					//合――1
		break;
	case	C_DC_NA_1:			//双点命令
		QU = (D_SCO & 0x7C) >> 2;
		D_SCS = D_SCO & 0x03;
		if(D_SCS == 1)	state = YK_OFF;			//开――1
		else	if(D_SCS == 2)	state = YK_ON;	//合――2
		else	state = YK_ERR;					//不允许――0、3
		break;
	default:
		return;
	}

	SGS_ChanYX_Shm_Ptr_T yxptr = NULL;  //通过组号和遥控号找到源组编码与 遥测号
	//m_pGroup = m_commInf.group(m_pRoute->group); //找到数据组
	for (hUInt32 pointNo = 0;pointNo < rd->yxnum ; pointNo++)
	{
		yxptr = da->data_yx + pointNo;  //根据数据组号和遥测号找到遥测表
		if (yxptr == NULL || !yxptr->valid) continue;
		if (yxptr->isctrl ==1 && yxptr->ctrlno == no)
		{
			break;
		}
		yxptr = NULL;
	}
	if(!yxptr)
	{
		SGS_Printer(30099,"<group=%d,code=%d> oo遥控反校错误oo! 测点不存在",rd->order,no);
		return;
	}
	//DAC_GROUP* grpptr = m_commInf.group(yxptr->srcGroup);  //通过源组序号找到源组编码号
	//if(!grpptr)
	//{
	//	logprint(LOG_104_ERR,"<group=%s,code=%d> oo遥控反校错误oo! 测点不存在",grpptr->code,no);
	//	return ;
	//}
	ctrl_pro_yk_ack ack;
	memset(&ack,0,sizeof(ctrl_pro_yk_ack));
	ack.ctrlNo = no;
	ack.funcCode = S_E;
	ack.groupNo = yxptr->srcgrp;
	ack.ackState = 0;
	if ( !setCtrlCmdAckEx((char*)(&ack),sizeof(ctrl_pro_yk_ack))) 
	{
		SGS_Printer(30099,"<group=%d,code=%d> oo遥控返校输出错误oo! 信号无法传递给后台",ack.groupNo,ack.ctrlNo);
		return ;
	}
	SGS_Printer(30099,"<group = %d,no = %d,funcCode = %d,state = %d> 遥控返校验输出成功！",ack.groupNo,ack.ctrlNo,ack.funcCode,ack.ackState);

	return;
}





extern "C" PROTO_104_EXPORT SGS_PCBasic * CreateProtocol()
{
	return ( new SGS_Proto_104() );
}
