#ifndef _SGS_PROTO_104_H_
#define _SGS_PROTO_104_H_

#include "SGS_PCBasic.h"
#include "DBOperation.h"


//=============================================================================
#if defined (_PROTO_104_)
# define	PROTO_104_EXPORT	ACE_Proper_Export_Flag
#else
#  define	PROTO_104_EXPORT	ACE_Proper_Import_Flag
#endif
//=============================================================================
//
//
#define MakeWord(a,b)	((unsigned short)((unsigned char)(a) + (unsigned char)(b) * 256))

#define LOG_104_RX		(10000+m_stno)		//接收
#define LOG_104_TX		(20000+m_stno)		//发送
#define LOG_104_ERR		(10000+m_stno)		//错误

//YK类型定义：0——无遥控命令
#define YK_SET_CMD		1			//YK预置
#define YK_EXE_CMD		2			//YK执行
#define YK_DEL_CMD		3			//YK撤消


//--------------------应用规约控制信息格式--------------------------------------------------------
#define	IEC104_APCI_I		0		//I格式（信息传输格式）
#define	IEC104_APCI_S		0x01	//S格式（计数的监视功能）
#define	IEC104_APCI_U		0x03	//U格式（不计数的控制功能）
//--------------------应用规约控制信息--------------------------------------------------------
#define	APCI_U_STARTDT_ACT	0x04	//启动链路——激活
#define	APCI_U_STARTDT_CON	0x08	//启动链路——确认
#define	APCI_U_STOPDT_ACT	0x10	//停止链路——激活
#define	APCI_U_STOPDT_CON	0x20	//停止链路——确认
#define	APCI_U_TESTFR_ACT	0x40	//测试链路——激活
#define	APCI_U_TESTFR_CON	0x80	//测试链路——确认
//--------------------类型标识--------------------------------------------------------

////===========================================================================
////非平衡传输，启动站向从动站传输的报文控制域的功能码（PRM=1）
//#define	IEC104_LINK_FUNC_RESET_LINK			0	//远方链路复位（期待的发送/确认帧）（FCV=0）
//#define	IEC104_LINK_FUNC_RESET_USER_PROC	1	//用户进程复位（期待的发送/确认帧）（FCV=0）
////2		为平衡传输过程保留
//#define	IEC104_LINK_FUNC_USER_DATA			3	//用户数据（期待的发送/确认帧）（FCV=1）
//#define	IEC104_LINK_FUNC_USER_DATA_NO_ACK	4	//非确认的用户数据（期待的发送/无回答帧）（FCV=0）
////5			备用
////6——7	为协商的特殊应用保留
//#define	IEC104_LINK_FUNC_REQ_ACK			8	//以要求访问响应（要求访问的请求）（FCV=0）
//#define	IEC104_LINK_FUNC_REQ_STATUS			9	//请求链路状态（期待的发送/确认帧）（FCV=0）
//#define	IEC104_LINK_FUNC_REQ_USER_DATA_1	10	//请求1级用户数据（期待的发送/确认帧）（FCV=1）
//#define	IEC104_LINK_FUNC_REQ_USER_DATA_2	11	//请求2级用户数据（期待的发送/确认帧）（FCV=1）
////12——13	备用
////14——15	为协商的特殊应用保留
////---------------------------------------------------------------------------
////非平衡传输，从动站向启动站传输的报文控制域的功能码（PRM=0）
//#define	IEC104_LINK_FUNC_ACK				0	//认可：肯定认可肯定确认（确认帧）
//#define	IEC104_LINK_FUNC_NO_ACK				1	//否定认可：未收到报文，链路忙（确认帧）
////2——5	备用
////6——7	为协商的特殊应用保留
//#define	IEC104_LINK_FUNC_USER_DATA_OK		8	//用户数据（响应帧）
//#define	IEC104_LINK_FUNC_USER_DATA_NO		9	//否定认可：无请求的数据（响应帧）
////10		备用
//#define	IEC104_LINK_FUNC_STATUS_OR_ACK		11	//链路状态或要求访问（响应帧）
////12		备用
////13		为协商的特殊应用保留
//#define	IEC104_LINK_FUNC_SRV_NO_WORK		14	//链路服务未工作
//#define	IEC104_LINK_FUNC_SRV_NO_FIN			15	//链路服务未完成
////===========================================================================
////平衡传输，启动站向从动站传输的报文控制域的功能码（PRM=1）
//#define	IEC104_LINK_FUNC_RESET_LINK			0	//远方链路复位（期待的发送/确认帧）（FCV=0）
//#define	IEC104_LINK_FUNC_RESET_USER_PROC	1	//用户进程复位（期待的发送/确认帧）（FCV=0）
//#define	IEC104_LINK_FUNC_TEST_LINK			2	//链路测试（期待的发送/确认帧）（FCV=1）
//#define	IEC104_LINK_FUNC_USER_DATA			3	//用户数据（期待的发送/确认帧）（FCV=1）
//#define	IEC104_LINK_FUNC_USER_DATA_NO_ACK	4	//非确认的用户数据（期待的发送/无回答帧）（FCV=0）
////5			备用
////6——7	为协商的特殊应用保留
////8			为非平衡传输过程保留
//#define	IEC104_LINK_FUNC_REQ_STATUS			9	//请求链路状态（期待的发送/确认帧）（FCV=0）
////10——11	为非平衡传输过程保留
////12——13	备用
////14——15	为协商的特殊应用保留
////---------------------------------------------------------------------------
////平衡传输，从动站向启动站传输的报文控制域的功能码（PRM=0）
//#define	IEC104_LINK_FUNC_ACK				0	//认可：肯定认可肯定确认（确认帧）
//#define	IEC104_LINK_FUNC_NO_ACK				1	//否定认可：未收到报文，链路忙（确认帧）
////2——5	备用
////6——7	为协商的特殊应用保留
////8——9	为非平衡传输过程保留
////10		备用
//#define	IEC104_LINK_FUNC_STATUS_OR_ACK		11	//链路状态或要求访问（响应帧）
////12——13	为协商的特殊应用保留
//#define	IEC104_LINK_FUNC_SRV_NO_WORK		14	//链路服务未工作
//#define	IEC104_LINK_FUNC_SRV_NO_FIN			15	//链路服务未完成


//===========================================================================
//--------------------类型标识--------------------------------------------------------
//在监视方向的过程信息（0——44）（类型30——40在IEC 60870-5-101的补充件A1中定义）
//0									//未定义
#define	M_SP_NA_1			1		//单点信息
#define	M_SP_TA_1			2		//带CP24Time2a时标的单点信息
#define	M_DP_NA_1			3		//双点信息
#define	M_DP_TA_1			4		//带CP24Time2a时标的双点信息
#define	M_ST_NA_1			5		//步位置信息
#define	M_ST_TA_1			6		//带CP24Time2a时标的步位置信息
#define	M_BO_NA_1			7		//32比特串
#define	M_BO_TA_1			8		//带CP24Time2a时标的32比特串
#define	M_ME_NA_1			9		//测量值，规一化值
#define	M_ME_TA_1			10		//带CP24Time2a时标的测量值，规一化值
#define	M_ME_NB_1			11		//测量值，标度化值
#define	M_ME_TB_1			12		//带CP24Time2a时标的测量值，称度化值
#define	M_ME_NC_1			13		//测量值，短浮点数
#define	M_ME_TC_1			14		//带CP24Time2a时标的测量值，短浮点数
#define	M_IT_NA_1			15		//累积量
#define	M_IT_TA_1			16		//带CP24Time2a时标的累积量
#define	M_EP_TA_1			17		//带CP24Time2a时标的继电保护装置事件
#define	M_EP_TB_1			18		//带CP24Time2a时标的继电保护装置成组启动事件
#define	M_EP_TC_1			19		//带时标的继电保护装置成组输出电路信息
#define	M_PS_NA_1			20		//带变位检出的成组单点信息
#define	M_ME_ND_1			21		//测量值，不带品质描述词的规一化值
//22——29							//为将来兼容定义保留
#define	M_SP_TB_1			30		//带CP56Time2a时标的单点信息
#define	M_DP_TB_1			31		//带CP56Time2a时标的双点信息
#define	M_ST_TB_1			32		//带CP56Time2a时标的步位置信息
#define	M_BO_TB_1			33		//带CP56Time2a时标的32 比特串
#define	M_ME_TD_1			34		//带CP56Time2a时标的测量值，规一化值
#define	M_ME_TE_1			35		//带CP56Time2a时标的测量值，标度化值
#define	M_ME_TF_1			36		//带CP56Time2a时标的测量值，短浮点数
#define	M_IT_TB_1			37		//带CP56Time2a时标的累积量
#define	M_EP_TD_1			38		//带CP56Time2a时标的继电保拌装置事件
#define	M_EP_TE_1			39		//带CP56Time2a时标的继电保拌装置成组启动事件
#define	M_EP_TF_1			40		//带CP56Time2a时标的继电保拌装置成组输出电路信息
//41——44							//为将来兼容定义保留
//在控制方向的过程信息（45——69）
#define	C_SC_NA_1			45		//单点命令
#define	C_DC_NA_1			46		//双点命令
#define	C_RC_NA_1			47		//调节步命令
#define	C_SE_NA_1			48		//设定值命令，规一化值
#define	C_SE_NB_1			49		//设定值命令，标度化值
#define	C_SE_NC_1			50		//设定值命令，短浮点数
#define	C_BO_NA_1			51		//32 比特串
//52——57							//为将来兼容定义保留
#define	C_SC_TA_1			58		//带CP56Time2a时标的单点命令
#define	C_DC_TA_1			59		//带CP56Time2a时标的双点命令
#define	C_RC_TA_1			60		//带CP56Time2a时标的调节步命令
#define	C_SE_TA_1			61		//带CP56Time2a时标的设定值命令，规一化值
#define	C_SE_TB_1			62		//带CP56Time2a时标的设定值命令，标度化值
#define	C_SE_TC_1			63		//带CP56Time2a时标的设定值命令，短浮点数
#define	C_BO_TA_1			64		//带CP56Time2a时标的32比特串
//65——69							//为将来兼容定义保留
//在监视方向的系统命令（70——99）
#define	M_EI_NA_1			70		//初始化结束
//71——99							//为将来兼容定义保留
//在控制方向的系统命令（100——109）
#define	C_IC_NA_1			100		//总召唤命令
#define	C_CI_NA_1			101		//计数量召唤命令
#define	C_RD_NA_1			102		//读命令
#define	C_CS_NA_1			103		//时钟同步命令
#define	C_TS_NA_1			104		//测试命令
#define	C_RP_NA_1			105		//复位进程命令
#define	C_CD_NA_1			106		//收集传输延时
#define	C_TS_TA_1			107		//带CP56Time2a时标的测试命今
//108——109						//为将来兼容定义保留
//在控制方向的参数命令（110——119）
#define	P_ME_NA_1			110		//测量值参数，规一化值
#define	P_ME_NB_1			111		//测量值参数，标度化值
#define	P_ME_NC_1			112		//测量值参数，短浮点数
#define	P_AC_NA_1			113		//参数激活
//110——119						//为将来兼容定义保留
//文件传输（120——127）
#define	F_FR_NA_1			120		//文件淮备就绪
#define	F_SR_NA_1			121		//节淮备就绪
#define	F_SC_NA_1			122		//召唤目录，选择文件，召唤文件召唤节
#define	F_LS_NA_1			123		//最后的节,最后的段
#define	F_AF_NA_1			124		//认可文件,认可节
#define	F_SG_NA_1			125		//段
#define	F_DR_NA_1			126		//目录
//127								//为将来兼容定义保留
#define P_PL_NA_1			144		//计划值
#define A_HD_NA_1			145		//历史值--遥测
#define E_HD_NA_1			146		//历史值--电度
//--------------------传送原因--------------------------------------------------------
//0											//未定义
#define	CAUSE_PER_CYC				1		//周期、循环
#define	CAUSE_BACK					2		//背景扫描
#define	CAUSE_SPONT					3		//突发（自发）
#define	CAUSE_INIT					4		//初始化
#define	CAUSE_REQ					5		//请求或被请求
#define	CAUSE_ACT					6		//激活
#define	CAUSE_ACT_CON				7		//激活确认
#define	CAUSE_STOP_ACT				8		//停止激活
#define	CAUSE_STOPACT_CON			9		//停止激活确认
#define	CAUSE_ACT_TERM				10		//激活终止
#define	CAUSE_RET_REMOTE			11		//远方命令引起的返送信息
#define	CAUSE_RET_LOCAL				12		//当地命令引起的返送信息
#define	CAUSE_FILE					13		//文件传输
//14——19									//为配套标准兼容范围保留
#define	CAUSE_RESP_CALL_ALL			20		//响应总召唤
#define	CAUSE_RESP_CALL_GRP_1		21		//响应第1组召唤
#define	CAUSE_RESP_CALL_GRP_2		22		//响应第2组召唤
#define	CAUSE_RESP_CALL_GRP_3		23		//响应第3组召唤
#define	CAUSE_RESP_CALL_GRP_4		24		//响应第4组召唤
#define	CAUSE_RESP_CALL_GRP_5		25		//响应第5组召唤
#define	CAUSE_RESP_CALL_GRP_6		26		//响应第6组召唤
#define	CAUSE_RESP_CALL_GRP_7		27		//响应第7组召唤
#define	CAUSE_RESP_CALL_GRP_8		28		//响应第8组召唤
#define	CAUSE_RESP_CALL_GRP_9		29		//响应第9组召唤
#define	CAUSE_RESP_CALL_GRP_10		30		//响应第10组召唤
#define	CAUSE_RESP_CALL_GRP_11		31		//响应第11组召唤
#define	CAUSE_RESP_CALL_GRP_12		32		//响应第12组召唤
#define	CAUSE_RESP_CALL_GRP_13		33		//响应第13组召唤
#define	CAUSE_RESP_CALL_GRP_14		34		//响应第14组召唤
#define	CAUSE_RESP_CALL_GRP_15		35		//响应第15组召唤
#define	CAUSE_RESP_CALL_GRP_16		36		//响应第16组召唤
#define	CAUSE_RESP_CALL_KWH			37		//响应计数量（累计量）召唤
#define	CAUSE_RESP_CALL_KWH_GRP_1	38		//响应第1组计数量（累计量）召唤
#define	CAUSE_RESP_CALL_KWH_GRP_2	39		//响应第2组计数量（累计量）召唤
#define	CAUSE_RESP_CALL_KWH_GRP_3	40		//响应第3组计数量（累计量）召唤
#define	CAUSE_RESP_CALL_KWH_GRP_4	41		//响应第4组计数量（累计量）召唤
//42——43									//为配套标准兼容范围保留
#define	CAUSE_UNKOWN_TYPE			44		//未知的类型标识
#define	CAUSE_UNKOWN_CAUSE			45		//未知的传送原因
#define	CAUSE_UNKOWN_APDUADDR		46		//未知的应用服务数据单元公共地址
#define	CAUSE_UNKOWN_DATAADDR		47		//未知的信息体地址
//48——63									//特殊应用保留（专用范围）
//--------------------状态定义--------------------------------------------------------
//--------------------状态定义--------------------------------------------------------
//链路状态
#define	STATE_UNBOUND				0		//未连接
#define	STATE_IDLE					1		//连接正常
//工作状态
#define	STATE_FREE					0		//空闲
#define	STATE_WAIT_STARTDT_CON		1		//等待启动链路确认
#define	STATE_WAIT_STOPDT_CON		2		//等待停止链路确认
#define	STATE_WAIT_TESTDT_CON		3		//等待测试链路确认
#define	STATE_WAIT_ALLDATA_CON		11		//等待总召唤确认
#define	STATE_WAIT_ALLKWH_CON		12		//等待计数量召唤确认
#define	STATE_WAIT_TIME_CON			13		//等待时钟同步确认
#define	STATE_WAIT_ALLDATA			14		//等待总召唤的数据
#define	STATE_WAIT_ALLKWH			15		//等待计数量召唤的数据
#define	STATE_WAIT_YK_SEL_CON		21		//等待YK选择确认
#define	STATE_WAIT_YK_EXE_CON		22		//等待YK执行确认
#define	STATE_WAIT_YK_DEL_CON		23		//等待YK撤消确认

//应用工作状态
#define	STATE_APP_FREE				0		//空闲
#define	STATE_APP_CALL_ALL			20		//总召唤
#define	STATE_APP_CALL_GRP_1		21		//召唤第1组数据
#define	STATE_APP_CALL_GRP_2		22		//召唤第2组数据
#define	STATE_APP_CALL_GRP_3		23		//召唤第3组数据
#define	STATE_APP_CALL_GRP_4		24		//召唤第4组数据
#define	STATE_APP_CALL_GRP_5		25		//召唤第5组数据
#define	STATE_APP_CALL_GRP_6		26		//召唤第6组数据
#define	STATE_APP_CALL_GRP_7		27		//召唤第7组数据
#define	STATE_APP_CALL_GRP_8		28		//召唤第8组数据
#define	STATE_APP_CALL_GRP_9		29		//召唤第9组数据
#define	STATE_APP_CALL_GRP_10		30		//召唤第10组数据
#define	STATE_APP_CALL_GRP_11		31		//召唤第11组数据
#define	STATE_APP_CALL_GRP_12		32		//召唤第12组数据
#define	STATE_APP_CALL_GRP_13		33		//召唤第13组数据
#define	STATE_APP_CALL_GRP_14		34		//召唤第14组数据
#define	STATE_APP_CALL_GRP_15		35		//召唤第15组数据
#define	STATE_APP_CALL_GRP_16		36		//召唤第16组数据
#define	STATE_APP_CALL_KWH			37		//计数量召唤
#define	STATE_APP_CALL_KWH_GRP_1	38		//召唤第1组计数量数据
#define	STATE_APP_CALL_KWH_GRP_2	39		//召唤第2组计数量数据
#define	STATE_APP_CALL_KWH_GRP_3	40		//召唤第3组计数量数据
#define	STATE_APP_CALL_KWH_GRP_4	41		//召唤第4组计数量数据
#define	STATE_APP_SYNC_TIME			50		//时钟同步
#define	STATE_APP_CALL_DATA_1		51		//召唤1级数据
#define	STATE_APP_CALL_DATA_2		52		//召唤2级数据
#define	STATE_APP_YK_SEL			101		//YK选择
#define	STATE_APP_YK_EXE			102		//YK执行
#define	STATE_APP_YK_DEL			103		//YK撤消
//----------------------------信息对象地址定义------------------------------------------------
#define	IEC104_OBJ_ADDR_UNKOWN				0			//无关的信息对象地址
//2字节信息对象地址
#define	IEC104_OBJ_16_ADDR_YX_START			0x0001		//遥信——起始
#define	IEC104_OBJ_16_ADDR_YX_END			0x1000		//遥信——终止
#define	IEC104_OBJ_16_ADDR_PROT_START		0x1001		//继电保护——起始
#define	IEC104_OBJ_16_ADDR_PROT_END			0x4000		//继电保护——终止
#define	IEC104_OBJ_16_ADDR_YC_START			0x4001		//遥测——起始（原来：0x0701）
#define	IEC104_OBJ_16_ADDR_YC_END			0x5000		//遥测——终止
#define	IEC104_OBJ_16_ADDR_PARA_START		0x5001		//参数——起始
#define	IEC104_OBJ_16_ADDR_PARA_END			0x6000		//参数——终止
#define	IEC104_OBJ_16_ADDR_YK_START			0x6001		//遥控、升降——起始
#define	IEC104_OBJ_16_ADDR_YK_END			0x6200		//遥控、升降——终止
#define	IEC104_OBJ_16_ADDR_SET_START		0x6201		//设定——起始
#define	IEC104_OBJ_16_ADDR_SET_END			0x6400		//设定——终止
#define	IEC104_OBJ_16_ADDR_KWH_START		0x6401		//电能累计量——起始（原来：0x0C01）
#define	IEC104_OBJ_16_ADDR_KWH_END			0x6600		//电能累计量——终止
#define	IEC104_OBJ_16_ADDR_STEP_START		0x6601		//步位置——起始
#define	IEC104_OBJ_16_ADDR_STEP_END			0x6700		//步位置——终止
#define	IEC104_OBJ_16_ADDR_BIN_START		0x6701		//向被控站传送二进制信息——起始
#define	IEC104_OBJ_16_ADDR_BIN_END			0x6800		//向被控站传送二进制信息——终止
#define	IEC104_OBJ_16_ADDR_RTU_STATE		0x6801		//远东终端状态
#define	IEC104_OBJ_16_ADDR_FILE_START		0x6802		//文件传送——起始
#define	IEC104_OBJ_16_ADDR_FILE_END			0x7000		//文件传送——终止
////----------------------------------------------------------------------------
////命令类型（自己定义，和规约标准无关）
//#define	IEC104_CMD_RESET_LINK				1			//远方链路复位
//#define	IEC104_CMD_REQ_LINK_STATE			4			//请求链路状态
//#define	IEC104_CMD_CALL_ALL					20			//总召唤（YC、YX）
//#define	IEC104_CMD_CALL_GRP_1				21			//召唤第1组数据
//#define	IEC104_CMD_CALL_GRP_2				22			//召唤第2组数据
//#define	IEC104_CMD_CALL_GRP_3				23			//召唤第3组数据
//#define	IEC104_CMD_CALL_GRP_4				24			//召唤第4组数据
//#define	IEC104_CMD_CALL_GRP_5				25			//召唤第5组数据
//#define	IEC104_CMD_CALL_GRP_6				26			//召唤第6组数据
//#define	IEC104_CMD_CALL_GRP_7				27			//召唤第7组数据
//#define	IEC104_CMD_CALL_GRP_8				28			//召唤第8组数据
//#define	IEC104_CMD_CALL_GRP_9				29			//召唤第9组数据
//#define	IEC104_CMD_CALL_GRP_10				30			//召唤第10组数据
//#define	IEC104_CMD_CALL_GRP_11				31			//召唤第11组数据
//#define	IEC104_CMD_CALL_GRP_12				32			//召唤第12组数据
//#define	IEC104_CMD_CALL_GRP_13				33			//召唤第13组数据
//#define	IEC104_CMD_CALL_GRP_14				34			//召唤第14组数据
//#define	IEC104_CMD_CALL_GRP_15				35			//召唤第15组数据
//#define	IEC104_CMD_CALL_GRP_16				36			//召唤第16组数据
//#define	IEC104_CMD_CALL_KWH					37			//召唤计数量（累计量）
//#define	IEC104_CMD_CALL_KWH_GRP_1			38			//召唤第1组计数量（累计量）
//#define	IEC104_CMD_CALL_KWH_GRP_2			39			//召唤第2组计数量（累计量）
//#define	IEC104_CMD_CALL_KWH_GRP_3			40			//召唤第3组计数量（累计量）
//#define	IEC104_CMD_CALL_KWH_GRP_4			41			//召唤第4组计数量（累计量）
//#define	IEC104_CMD_SYNC_TIME				50			//时钟同步命令
//#define	IEC104_CMD_CALL_DATA_1				51			//召唤1级数据
//#define	IEC104_CMD_CALL_DATA_2				52			//召唤2级数据
//#define	IEC104_CMD_YK_SEL					101			//YK选择
//#define	IEC104_CMD_YK_EXE					102			//YK执行
//#define	IEC104_CMD_YK_DEL					103			//YK撤销
////----------------------------------------------------------------------------
//#define	IEC104_YX_GRP_START					1			//YX组号——起始
//#define	IEC104_YX_GRP_END					8			//YX组号——终止
//#define	IEC104_YC_GRP_START					9			//YC组号——起始
//#define	IEC104_YC_GRP_END					14			//YC组号——终止
//#define	IEC104_STEP_GRP						15			//步位置信息组号
//#define	IEC104_RTUSTATE_GRP					16			//远动终端状态组号
//#define	IEC104_KWH_GRP_START				1			//电度——起始
//#define	IEC104_KWH_GRP_END					4			//电度——终止
//----------------------------------------------------------------------------
//定时器超时定义
#define	TIMEOUT_LINK				(3*PROTO_ONESEC_TIMES)	//建立链接超时
#define	TIMEOUT_RECV				(5*PROTO_ONESEC_TIMES)	//接收报文超时
#define	TIMEOUT_CALL_ALL			(10*PROTO_ONESEC_TIMES)	//接收全数据报文超时
#define	TIMEOUT_CALL_KWH			(8*PROTO_ONESEC_TIMES)	//接收KWH数据报文超时
#define	TIMEOUT_CALL_GRP			(7*PROTO_ONESEC_TIMES)	//接收分组数据报文超时
#define	TIMEOUT_CALL_KWH_GRP		(6*PROTO_ONESEC_TIMES)	//接收KWH分组数据报文超时
//定义限值
#define	RETRY_SEND_LIMIT			3						//重发次数限
//----------------------------------------------------------------------------
////控制域
//typedef	union
//{
//	struct
//	{
//		unsigned char		FuncCode:4;		//功能码——3、2、1、0位
//		//FCV：帧计数有效位（启动站向从动站传输：0——FCB变化无效，1——FCB变化有效
//		//DCF：数据流控制位（从动站向启动站传输：0——子站可以继续接收数据，1——子站数据区满，无法接收新数据
//		unsigned char		FcvDcf:1;		//4位
//		//FCB：帧计数位（启动站向从动站传输）（启动站向从动站传输新一轮的发送/确认、请求/响应服务时，将前一轮FCB取相反值
//		//ACD：要求访问位（主站做从动站时ACD位无实际意义，值为0）
//		//ACD：要求访问位（子站做从动站时：0——子站无1级用户数据，1——子站有1级用户数据，希望向主站传输）
//		unsigned char		FcbAcd:1;		//5位
//		unsigned char		Prm:1;			//启动报文位（0——从动站， 报文为确认报文或响应报文，1——启动站，报文为发送或请求报文）——6位
//		unsigned char		Dir:1;			//传输方向位（0——主站到子站，1——子站到主站）——7位
//	}byte;
//	unsigned char		value;
//}IEC104_CONTROL_FIELD;
//应用层头
typedef	struct
{
	unsigned char			Type;			//类型标识
	struct
	{
		unsigned char		Num:7;			//数据个数——6、5、4、3、2、1、0位
		unsigned char		SQ:1;			//单个或者顺序（0——单个，1——顺序）——7位
	}VSQ;							//可变结构限定词
	struct
	{
		unsigned char		Cause:6;		//传送原因序号——5、4、3、2、1、0位
		unsigned char		PN:1;			//确认（0——肯定确认，1——否定确认）——6位
		unsigned char		T:1;			//测试（0——未试验，1——试验）——7位
		unsigned char		SrcAddr;		//源发站地址
	}COT;							//传送原因
	unsigned short			CommAddr;		//应用服务数据单元公共地址
}IEC104_APP_HEAD;
//----------------------------------------------------------------------------
typedef	struct
{
	//规约特征————————开始
	//长度
	unsigned char			LinkAddrLen;			//链路地址长度（1——2）
	unsigned char			CommAddrLen;			//应用服务数据单元公共地址长度（1——2）
	unsigned char			ObjAddrLen;				//信息对象地址长度（1——3）（一般为2）
	unsigned char			CotLen;					//传送原因长度（1——2）（一般为2）
	//起始地址
	unsigned short		Yx_Start_Addr;			//遥信——起始
	unsigned short		Yx_End_Addr;			//遥信——终止
	unsigned short		Prot_Start_Addr;		//继电保护——起始
	unsigned short		Prot_End_Addr;			//继电保护——终止
	unsigned short		Yc_Start_Addr;			//遥测——起始
	unsigned short		Yc_End_Addr;			//遥测——终止
	unsigned short		Para_Start_Addr;		//参数——起始
	unsigned short		Para_End_Addr;			//参数——终止
	unsigned short		Yk_Start_Addr;			//遥控、升降——起始
	unsigned short		Yk_End_Addr;			//遥控、升降——终止
	unsigned short		Set_Start_Addr;			//设定——起始
	unsigned short		Set_End_Addr;			//设定——终止
	unsigned short		Kwh_Start_Addr;			//电能累计量——起始
	unsigned short		Kwh_End_Addr;			//电能累计量——终止
	unsigned short		Step_Start_Addr;		//步位置——起始
	unsigned short		Step_End_Addr;			//步位置——终止
	unsigned short		Bin_Start_Addr;			//向被控站传送二进制信息——起始
	unsigned short		Bin_End_Addr;			//向被控站传送二进制信息——终止
	unsigned short		Rtu_State_Addr;			//远动终端状态
	unsigned short		File_Start_Addr;		//文件传送——起始
	unsigned short		File_End_Addr;			//文件传送——终止
	//起始组号
	unsigned char			Yx_Start_Group;			//遥信组——起始（1）
	unsigned char			Yx_End_Group;			//遥信组——终止（8）
	unsigned char			Yc_Start_Group;			//遥测组——起始（9）
	unsigned char			Yc_End_Group;			//遥测组——终止（14）
	unsigned char			Step_Group;				//步位置组（15）
	unsigned char			Rtu_State_Group;		//远动终端状态组（16）
	//规约特征————————结束
	//固定信息————————开始
	unsigned short		FrmMinLen;				//最小帧长
	unsigned short		YcMaxNum;				//YC最大个数
	unsigned short		YxMaxNum;				//YX最大个数
	unsigned short		YcMaxNumInPerGroup;		//每组YC最大个数
	unsigned short		YxMaxNumInPerGroup;		//每组YX最大个数
	//固定信息————————结束
}IEC104_CONFIG_T,*IEC104_CONFIG_Ptr_T;
//
//typedef	struct
//{
//	unsigned char					LinkWorkStatus;			//链路状态
//	unsigned char					AppWorkStatus;			//应用层状态
//
//	unsigned char					SendCommand;			//发送的指令
//
//	IEC104_CONTROL_FIELD	ControlField;			//控制域
//
//	unsigned char					RetrySendFlag;			//重发标志
//
//	unsigned int					RecvCount;				//接收报文计数（收到正确报文或重发时清零，否则加1）
//	unsigned int					RetrySendCount;			//重发报文计数（收到正确报文或超过重发次数时清零，否则加1）
//	unsigned int					CallAllDataCount;		//召唤全数据计数（成功接收全数据或超时召唤分组数据时清零，否则加1）
//
//	unsigned short					RecvGrpDataNum[16];		//已经接收的每组数据（YC、YX、STEP、RTUSTATE）的个数
//
//	unsigned char					CallAllDataFlag;		//请求全数据（YC、YX）标志
//	unsigned char					CallAllKwhFlag;			//请求全KWH标志
//	unsigned char					CallGroupFlag[16];		//请求分组数据（YC、YX）标志（0——无需召唤，1——需要召唤，2——已经召唤）
//	unsigned char					Call_1_LevelDataFlag;	//请求1级数据标志
//	unsigned char					Call_2_LevelDataFlag;	//请求2级数据标志
//	unsigned char					SendTimeFlag;			//同步时钟标志
//}IEC104_INFO_T,*IEC104_INFO_Ptr_T;

typedef	struct
{
	//运行时信息
	unsigned int	T1;						//等待接收对端应答信息定时器（超时占用关闭）
	unsigned int	T2;						//等待本端信息处理完成定时器（超时发送S帧）
	unsigned int	T3;						//等待双方进行数据传输定时器（超时启动测试过程）
	unsigned int	T4;						//等待启动链路确认定时器（超时占用关闭）
	unsigned int	T5;						//等待总召唤终止确认定时器（超时占用关闭）
	unsigned char	LinkState;				//当前链路状态
	unsigned char	WorkState;				//当前工作状态
	unsigned short	NS;						//发送序号
	unsigned short	NR;						//接收序号
	unsigned char	CallAllDataFlag;		//请求全数据（YC、YX）标志
	unsigned char	CallAllKwhFlag;			//请求全KWH标志
	unsigned char	Send_S_ACK_Flag;		//发送S帧确认的标志
	unsigned char	Send_U_TESTFR_ACT_Flag;	//发送U帧测试链路激活标志
	unsigned char	Send_U_TESTFR_CON_Flag; //发送U帧测试链路确认标志
	unsigned char	Send_U_STOPDT_ACT_Flag;	//发送U帧停止链路激活标志
	unsigned char	SendTimeFlag;			//同步时钟标志  dhy


	//FDC_YKBUF		cur_ykbuf;				//当前YK缓冲区
	unsigned short  W;
	int	pollingTm;
}IEC104_INFO_T,*IEC104_INFO_Ptr_T;

typedef struct
{
	unsigned char		timesync;			//时钟同步
	unsigned char		all_data;			//全数据
	unsigned char		all_yc;				//全YC
	unsigned char		all_yx;				//全YX
	unsigned char		all_kwh;			//全KWH
	unsigned char		change_data;		//变化数据
	unsigned char		change_yc;			//变化YC
	unsigned char		change_yx;			//变化YX
	unsigned char		change_kwh;			//变化KWH
	unsigned char		soe;				//SOE
}IEC104_INFO_COMMAND,*IEC104_INFO_COMMAND_ptr;
//----------------------------------------------------------------------------


class PROTO_104_EXPORT SGS_Proto_104 : public SGS_PCBasic
{
private:
	IEC104_CONFIG_T			config;
	IEC104_INFO_T			info;
	IEC104_INFO_Ptr_T		pInfo;
	IEC104_INFO_COMMAND		cmdinfo;

	hUInt8			*pAppDataBuf;					//应用层数据指针
	hUInt16			AppDataLen;						//应用层数据长度
	hUInt16			RxDataSize;						//收到的数据长度
	hBool			m_open;


	//----------------------------------------------------------------------------
	void			ReadConfig();							//读取规约配置
	////----------------------------------------------------------------------------
	//void		ResetGrpData(int grpno=-1);				//初始化组数据信息
	//int			GetGrpDataNum(int grpno);				//获得组中的实际数据个数
	//int			GetOneCallGrpDataCmd(int &grpno);		//寻找一个需要分组召唤的组（返回值：TRUE——找到,grpno为组号<1...16>，FALSE——未找到）
	//int			GetOneCallKwhGrpDataCmd(int &grpno);	//寻找一个需要分组召唤电度的组（返回值：TRUE——找到,grpno为组号<1...4>，FALSE——未找到）
	//void		SetYcGrpData(int no);					//设置YC组数据
	//void		SetYxGrpData(int no);					//设置YX组数据
	////----------------------------------------------------------------------------
	//void		Init_Link();							//初始化链路
	////----------------------------------------------------------------------------
	//int			MakeLinkAddr(unsigned char *buf);				//生成链路地址，返回长度
	//int			MakeCommAddr(unsigned char *buf);				//生成公共地址，返回长度
	//int			MakeObjAddr(unsigned char *buf,int no);		//生成对象地址，返回长度
	//int			MakeCause(unsigned char *buf,unsigned char cause);	//生成传送原因，返回长度
	int			GetAppHead(IEC104_APP_HEAD *head);		//获得数据单元标识符
	int			GetObjAddr();							//获得对象地址
	////----------------------------------------------------------------------------
	void		InitInfo();						//初始化基本信息
	void		NoRxAnyData();					//给一些计数量累加
	void		RxSomeData();					//清除一些计数量
	//void		CheckTxFlag();							//检测发送标志
	//void		Check_TimeOut();						//检测超时

	//int			MakeSendCmd();							//生成发送命令
	//int			Send_Message_To_TxBuf(unsigned char func,unsigned short len);	//发送报文到发送缓冲区

	//int			App_Send();								//生成发送命令

	//int				Tx_APDU_I(unsigned char len);	//发送I格式的应用规约控制单元
	//int				Tx_APDU_S();					//发送S格式的应用规约控制单元
	//int				Tx_APDU_U(unsigned char type);	//发送U格式的应用规约控制单元

	//int				Tx_CtrlCmd();					//发送控制命令
	//int				Tx_AnalogOutPut();				//发送模拟量输出
	//int				Tx_CallHisdata();				//发送召唤历史数据命令

	//int			Tx_ResetLink();							//复位远方链路
	//int			Tx_ReqLinkState();						//请求远方链路
	//int			Tx_Call_1_LevelData();					//召唤1级数据
	//int			Tx_Call_2_LevelData();					//召唤2级数据

	//void		Tx_DataCmd();					//发送数据命令
	//int			Tx_CallAllData(unsigned char QOI);			//总召唤（QOI=20）、分组召唤（QOI>=21 && QOI<=36）
	//int			Tx_SyncTime();							//同步时钟
	
	///----------------------------------------------------------------------------
	// 判断对方的接受和发送桢和我们的是否一致，如果不一致重置链路 Bruce 2006-09-18
	int			IsNsNrMatch(unsigned char * buff);

	int				SearchAPCI();					//搜索应用规约控制信息

	int				SearchASDU();					//搜索应用服务数据单元
	//int				Link_Recv();							//链路层接收
	//int				App_Recv();								//应用层接收

	//int				DoCtrlField(unsigned char control);			//处理控制域
	void			DoCallAllDataAck(IEC104_APP_HEAD &head);	//处理总召唤应答
	void			DoCallAllKwhAck(IEC104_APP_HEAD &head);		//处理召唤全电度应答
	void			DoSyncTimeAck(IEC104_APP_HEAD &head);		//处理时钟同步应答
	void			DoYkAck(IEC104_APP_HEAD &head);				//处理YK命令
	void			DoAnalogOutPutAck(IEC104_APP_HEAD &head);	//处理模拟量输出命令

	void		YC_RxProc(IEC104_APP_HEAD &head);		//YC接收处理
	void		YX_RxProc(IEC104_APP_HEAD &head);		//YX接收处理
	void		SOE_RxProc(IEC104_APP_HEAD &head);		//SOE接收处理


public:
	SGS_Proto_104();
	virtual ~SGS_Proto_104();

	virtual int		Init(short stno,short chno);					//规约对象的初始化
	virtual	int		ProtoRX_Init(short stno,short chno);		//接收前的初始化工作
	virtual	int		ProtoTX_Init(short stno,short chno);		//发送前的初始化工作
	virtual	void	ProtoRX();					//各规约重载
	virtual	void	ProtoTX();					//各规约重载
	virtual	bool	isOpen() const;
public:

protected:
private:
};

#endif	//_SGS_PROTO_101_H_