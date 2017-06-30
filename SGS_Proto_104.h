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

#define LOG_104_RX		(10000+m_stno)		//����
#define LOG_104_TX		(20000+m_stno)		//����
#define LOG_104_ERR		(10000+m_stno)		//����

//YK���Ͷ��壺0������ң������
#define YK_SET_CMD		1			//YKԤ��
#define YK_EXE_CMD		2			//YKִ��
#define YK_DEL_CMD		3			//YK����


//--------------------Ӧ�ù�Լ������Ϣ��ʽ--------------------------------------------------------
#define	IEC104_APCI_I		0		//I��ʽ����Ϣ�����ʽ��
#define	IEC104_APCI_S		0x01	//S��ʽ�������ļ��ӹ��ܣ�
#define	IEC104_APCI_U		0x03	//U��ʽ���������Ŀ��ƹ��ܣ�
//--------------------Ӧ�ù�Լ������Ϣ--------------------------------------------------------
#define	APCI_U_STARTDT_ACT	0x04	//������·��������
#define	APCI_U_STARTDT_CON	0x08	//������·����ȷ��
#define	APCI_U_STOPDT_ACT	0x10	//ֹͣ��·��������
#define	APCI_U_STOPDT_CON	0x20	//ֹͣ��·����ȷ��
#define	APCI_U_TESTFR_ACT	0x40	//������·��������
#define	APCI_U_TESTFR_CON	0x80	//������·����ȷ��
//--------------------���ͱ�ʶ--------------------------------------------------------

////===========================================================================
////��ƽ�⴫�䣬����վ��Ӷ�վ����ı��Ŀ�����Ĺ����루PRM=1��
//#define	IEC104_LINK_FUNC_RESET_LINK			0	//Զ����·��λ���ڴ��ķ���/ȷ��֡����FCV=0��
//#define	IEC104_LINK_FUNC_RESET_USER_PROC	1	//�û����̸�λ���ڴ��ķ���/ȷ��֡����FCV=0��
////2		Ϊƽ�⴫����̱���
//#define	IEC104_LINK_FUNC_USER_DATA			3	//�û����ݣ��ڴ��ķ���/ȷ��֡����FCV=1��
//#define	IEC104_LINK_FUNC_USER_DATA_NO_ACK	4	//��ȷ�ϵ��û����ݣ��ڴ��ķ���/�޻ش�֡����FCV=0��
////5			����
////6����7	ΪЭ�̵�����Ӧ�ñ���
//#define	IEC104_LINK_FUNC_REQ_ACK			8	//��Ҫ�������Ӧ��Ҫ����ʵ����󣩣�FCV=0��
//#define	IEC104_LINK_FUNC_REQ_STATUS			9	//������·״̬���ڴ��ķ���/ȷ��֡����FCV=0��
//#define	IEC104_LINK_FUNC_REQ_USER_DATA_1	10	//����1���û����ݣ��ڴ��ķ���/ȷ��֡����FCV=1��
//#define	IEC104_LINK_FUNC_REQ_USER_DATA_2	11	//����2���û����ݣ��ڴ��ķ���/ȷ��֡����FCV=1��
////12����13	����
////14����15	ΪЭ�̵�����Ӧ�ñ���
////---------------------------------------------------------------------------
////��ƽ�⴫�䣬�Ӷ�վ������վ����ı��Ŀ�����Ĺ����루PRM=0��
//#define	IEC104_LINK_FUNC_ACK				0	//�Ͽɣ��϶��Ͽɿ϶�ȷ�ϣ�ȷ��֡��
//#define	IEC104_LINK_FUNC_NO_ACK				1	//���Ͽɣ�δ�յ����ģ���·æ��ȷ��֡��
////2����5	����
////6����7	ΪЭ�̵�����Ӧ�ñ���
//#define	IEC104_LINK_FUNC_USER_DATA_OK		8	//�û����ݣ���Ӧ֡��
//#define	IEC104_LINK_FUNC_USER_DATA_NO		9	//���Ͽɣ�����������ݣ���Ӧ֡��
////10		����
//#define	IEC104_LINK_FUNC_STATUS_OR_ACK		11	//��·״̬��Ҫ����ʣ���Ӧ֡��
////12		����
////13		ΪЭ�̵�����Ӧ�ñ���
//#define	IEC104_LINK_FUNC_SRV_NO_WORK		14	//��·����δ����
//#define	IEC104_LINK_FUNC_SRV_NO_FIN			15	//��·����δ���
////===========================================================================
////ƽ�⴫�䣬����վ��Ӷ�վ����ı��Ŀ�����Ĺ����루PRM=1��
//#define	IEC104_LINK_FUNC_RESET_LINK			0	//Զ����·��λ���ڴ��ķ���/ȷ��֡����FCV=0��
//#define	IEC104_LINK_FUNC_RESET_USER_PROC	1	//�û����̸�λ���ڴ��ķ���/ȷ��֡����FCV=0��
//#define	IEC104_LINK_FUNC_TEST_LINK			2	//��·���ԣ��ڴ��ķ���/ȷ��֡����FCV=1��
//#define	IEC104_LINK_FUNC_USER_DATA			3	//�û����ݣ��ڴ��ķ���/ȷ��֡����FCV=1��
//#define	IEC104_LINK_FUNC_USER_DATA_NO_ACK	4	//��ȷ�ϵ��û����ݣ��ڴ��ķ���/�޻ش�֡����FCV=0��
////5			����
////6����7	ΪЭ�̵�����Ӧ�ñ���
////8			Ϊ��ƽ�⴫����̱���
//#define	IEC104_LINK_FUNC_REQ_STATUS			9	//������·״̬���ڴ��ķ���/ȷ��֡����FCV=0��
////10����11	Ϊ��ƽ�⴫����̱���
////12����13	����
////14����15	ΪЭ�̵�����Ӧ�ñ���
////---------------------------------------------------------------------------
////ƽ�⴫�䣬�Ӷ�վ������վ����ı��Ŀ�����Ĺ����루PRM=0��
//#define	IEC104_LINK_FUNC_ACK				0	//�Ͽɣ��϶��Ͽɿ϶�ȷ�ϣ�ȷ��֡��
//#define	IEC104_LINK_FUNC_NO_ACK				1	//���Ͽɣ�δ�յ����ģ���·æ��ȷ��֡��
////2����5	����
////6����7	ΪЭ�̵�����Ӧ�ñ���
////8����9	Ϊ��ƽ�⴫����̱���
////10		����
//#define	IEC104_LINK_FUNC_STATUS_OR_ACK		11	//��·״̬��Ҫ����ʣ���Ӧ֡��
////12����13	ΪЭ�̵�����Ӧ�ñ���
//#define	IEC104_LINK_FUNC_SRV_NO_WORK		14	//��·����δ����
//#define	IEC104_LINK_FUNC_SRV_NO_FIN			15	//��·����δ���


//===========================================================================
//--------------------���ͱ�ʶ--------------------------------------------------------
//�ڼ��ӷ���Ĺ�����Ϣ��0����44��������30����40��IEC 60870-5-101�Ĳ����A1�ж��壩
//0									//δ����
#define	M_SP_NA_1			1		//������Ϣ
#define	M_SP_TA_1			2		//��CP24Time2aʱ��ĵ�����Ϣ
#define	M_DP_NA_1			3		//˫����Ϣ
#define	M_DP_TA_1			4		//��CP24Time2aʱ���˫����Ϣ
#define	M_ST_NA_1			5		//��λ����Ϣ
#define	M_ST_TA_1			6		//��CP24Time2aʱ��Ĳ�λ����Ϣ
#define	M_BO_NA_1			7		//32���ش�
#define	M_BO_TA_1			8		//��CP24Time2aʱ���32���ش�
#define	M_ME_NA_1			9		//����ֵ����һ��ֵ
#define	M_ME_TA_1			10		//��CP24Time2aʱ��Ĳ���ֵ����һ��ֵ
#define	M_ME_NB_1			11		//����ֵ����Ȼ�ֵ
#define	M_ME_TB_1			12		//��CP24Time2aʱ��Ĳ���ֵ���ƶȻ�ֵ
#define	M_ME_NC_1			13		//����ֵ���̸�����
#define	M_ME_TC_1			14		//��CP24Time2aʱ��Ĳ���ֵ���̸�����
#define	M_IT_NA_1			15		//�ۻ���
#define	M_IT_TA_1			16		//��CP24Time2aʱ����ۻ���
#define	M_EP_TA_1			17		//��CP24Time2aʱ��ļ̵籣��װ���¼�
#define	M_EP_TB_1			18		//��CP24Time2aʱ��ļ̵籣��װ�ó��������¼�
#define	M_EP_TC_1			19		//��ʱ��ļ̵籣��װ�ó��������·��Ϣ
#define	M_PS_NA_1			20		//����λ����ĳ��鵥����Ϣ
#define	M_ME_ND_1			21		//����ֵ������Ʒ�������ʵĹ�һ��ֵ
//22����29							//Ϊ�������ݶ��屣��
#define	M_SP_TB_1			30		//��CP56Time2aʱ��ĵ�����Ϣ
#define	M_DP_TB_1			31		//��CP56Time2aʱ���˫����Ϣ
#define	M_ST_TB_1			32		//��CP56Time2aʱ��Ĳ�λ����Ϣ
#define	M_BO_TB_1			33		//��CP56Time2aʱ���32 ���ش�
#define	M_ME_TD_1			34		//��CP56Time2aʱ��Ĳ���ֵ����һ��ֵ
#define	M_ME_TE_1			35		//��CP56Time2aʱ��Ĳ���ֵ����Ȼ�ֵ
#define	M_ME_TF_1			36		//��CP56Time2aʱ��Ĳ���ֵ���̸�����
#define	M_IT_TB_1			37		//��CP56Time2aʱ����ۻ���
#define	M_EP_TD_1			38		//��CP56Time2aʱ��ļ̵籣��װ���¼�
#define	M_EP_TE_1			39		//��CP56Time2aʱ��ļ̵籣��װ�ó��������¼�
#define	M_EP_TF_1			40		//��CP56Time2aʱ��ļ̵籣��װ�ó��������·��Ϣ
//41����44							//Ϊ�������ݶ��屣��
//�ڿ��Ʒ���Ĺ�����Ϣ��45����69��
#define	C_SC_NA_1			45		//��������
#define	C_DC_NA_1			46		//˫������
#define	C_RC_NA_1			47		//���ڲ�����
#define	C_SE_NA_1			48		//�趨ֵ�����һ��ֵ
#define	C_SE_NB_1			49		//�趨ֵ�����Ȼ�ֵ
#define	C_SE_NC_1			50		//�趨ֵ����̸�����
#define	C_BO_NA_1			51		//32 ���ش�
//52����57							//Ϊ�������ݶ��屣��
#define	C_SC_TA_1			58		//��CP56Time2aʱ��ĵ�������
#define	C_DC_TA_1			59		//��CP56Time2aʱ���˫������
#define	C_RC_TA_1			60		//��CP56Time2aʱ��ĵ��ڲ�����
#define	C_SE_TA_1			61		//��CP56Time2aʱ����趨ֵ�����һ��ֵ
#define	C_SE_TB_1			62		//��CP56Time2aʱ����趨ֵ�����Ȼ�ֵ
#define	C_SE_TC_1			63		//��CP56Time2aʱ����趨ֵ����̸�����
#define	C_BO_TA_1			64		//��CP56Time2aʱ���32���ش�
//65����69							//Ϊ�������ݶ��屣��
//�ڼ��ӷ����ϵͳ���70����99��
#define	M_EI_NA_1			70		//��ʼ������
//71����99							//Ϊ�������ݶ��屣��
//�ڿ��Ʒ����ϵͳ���100����109��
#define	C_IC_NA_1			100		//���ٻ�����
#define	C_CI_NA_1			101		//�������ٻ�����
#define	C_RD_NA_1			102		//������
#define	C_CS_NA_1			103		//ʱ��ͬ������
#define	C_TS_NA_1			104		//��������
#define	C_RP_NA_1			105		//��λ��������
#define	C_CD_NA_1			106		//�ռ�������ʱ
#define	C_TS_TA_1			107		//��CP56Time2aʱ��Ĳ�������
//108����109						//Ϊ�������ݶ��屣��
//�ڿ��Ʒ���Ĳ������110����119��
#define	P_ME_NA_1			110		//����ֵ��������һ��ֵ
#define	P_ME_NB_1			111		//����ֵ��������Ȼ�ֵ
#define	P_ME_NC_1			112		//����ֵ�������̸�����
#define	P_AC_NA_1			113		//��������
//110����119						//Ϊ�������ݶ��屣��
//�ļ����䣨120����127��
#define	F_FR_NA_1			120		//�ļ���������
#define	F_SR_NA_1			121		//�ڻ�������
#define	F_SC_NA_1			122		//�ٻ�Ŀ¼��ѡ���ļ����ٻ��ļ��ٻ���
#define	F_LS_NA_1			123		//���Ľ�,���Ķ�
#define	F_AF_NA_1			124		//�Ͽ��ļ�,�Ͽɽ�
#define	F_SG_NA_1			125		//��
#define	F_DR_NA_1			126		//Ŀ¼
//127								//Ϊ�������ݶ��屣��
#define P_PL_NA_1			144		//�ƻ�ֵ
#define A_HD_NA_1			145		//��ʷֵ--ң��
#define E_HD_NA_1			146		//��ʷֵ--���
//--------------------����ԭ��--------------------------------------------------------
//0											//δ����
#define	CAUSE_PER_CYC				1		//���ڡ�ѭ��
#define	CAUSE_BACK					2		//����ɨ��
#define	CAUSE_SPONT					3		//ͻ�����Է���
#define	CAUSE_INIT					4		//��ʼ��
#define	CAUSE_REQ					5		//���������
#define	CAUSE_ACT					6		//����
#define	CAUSE_ACT_CON				7		//����ȷ��
#define	CAUSE_STOP_ACT				8		//ֹͣ����
#define	CAUSE_STOPACT_CON			9		//ֹͣ����ȷ��
#define	CAUSE_ACT_TERM				10		//������ֹ
#define	CAUSE_RET_REMOTE			11		//Զ����������ķ�����Ϣ
#define	CAUSE_RET_LOCAL				12		//������������ķ�����Ϣ
#define	CAUSE_FILE					13		//�ļ�����
//14����19									//Ϊ���ױ�׼���ݷ�Χ����
#define	CAUSE_RESP_CALL_ALL			20		//��Ӧ���ٻ�
#define	CAUSE_RESP_CALL_GRP_1		21		//��Ӧ��1���ٻ�
#define	CAUSE_RESP_CALL_GRP_2		22		//��Ӧ��2���ٻ�
#define	CAUSE_RESP_CALL_GRP_3		23		//��Ӧ��3���ٻ�
#define	CAUSE_RESP_CALL_GRP_4		24		//��Ӧ��4���ٻ�
#define	CAUSE_RESP_CALL_GRP_5		25		//��Ӧ��5���ٻ�
#define	CAUSE_RESP_CALL_GRP_6		26		//��Ӧ��6���ٻ�
#define	CAUSE_RESP_CALL_GRP_7		27		//��Ӧ��7���ٻ�
#define	CAUSE_RESP_CALL_GRP_8		28		//��Ӧ��8���ٻ�
#define	CAUSE_RESP_CALL_GRP_9		29		//��Ӧ��9���ٻ�
#define	CAUSE_RESP_CALL_GRP_10		30		//��Ӧ��10���ٻ�
#define	CAUSE_RESP_CALL_GRP_11		31		//��Ӧ��11���ٻ�
#define	CAUSE_RESP_CALL_GRP_12		32		//��Ӧ��12���ٻ�
#define	CAUSE_RESP_CALL_GRP_13		33		//��Ӧ��13���ٻ�
#define	CAUSE_RESP_CALL_GRP_14		34		//��Ӧ��14���ٻ�
#define	CAUSE_RESP_CALL_GRP_15		35		//��Ӧ��15���ٻ�
#define	CAUSE_RESP_CALL_GRP_16		36		//��Ӧ��16���ٻ�
#define	CAUSE_RESP_CALL_KWH			37		//��Ӧ���������ۼ������ٻ�
#define	CAUSE_RESP_CALL_KWH_GRP_1	38		//��Ӧ��1����������ۼ������ٻ�
#define	CAUSE_RESP_CALL_KWH_GRP_2	39		//��Ӧ��2����������ۼ������ٻ�
#define	CAUSE_RESP_CALL_KWH_GRP_3	40		//��Ӧ��3����������ۼ������ٻ�
#define	CAUSE_RESP_CALL_KWH_GRP_4	41		//��Ӧ��4����������ۼ������ٻ�
//42����43									//Ϊ���ױ�׼���ݷ�Χ����
#define	CAUSE_UNKOWN_TYPE			44		//δ֪�����ͱ�ʶ
#define	CAUSE_UNKOWN_CAUSE			45		//δ֪�Ĵ���ԭ��
#define	CAUSE_UNKOWN_APDUADDR		46		//δ֪��Ӧ�÷������ݵ�Ԫ������ַ
#define	CAUSE_UNKOWN_DATAADDR		47		//δ֪����Ϣ���ַ
//48����63									//����Ӧ�ñ�����ר�÷�Χ��
//--------------------״̬����--------------------------------------------------------
//--------------------״̬����--------------------------------------------------------
//��·״̬
#define	STATE_UNBOUND				0		//δ����
#define	STATE_IDLE					1		//��������
//����״̬
#define	STATE_FREE					0		//����
#define	STATE_WAIT_STARTDT_CON		1		//�ȴ�������·ȷ��
#define	STATE_WAIT_STOPDT_CON		2		//�ȴ�ֹͣ��·ȷ��
#define	STATE_WAIT_TESTDT_CON		3		//�ȴ�������·ȷ��
#define	STATE_WAIT_ALLDATA_CON		11		//�ȴ����ٻ�ȷ��
#define	STATE_WAIT_ALLKWH_CON		12		//�ȴ��������ٻ�ȷ��
#define	STATE_WAIT_TIME_CON			13		//�ȴ�ʱ��ͬ��ȷ��
#define	STATE_WAIT_ALLDATA			14		//�ȴ����ٻ�������
#define	STATE_WAIT_ALLKWH			15		//�ȴ��������ٻ�������
#define	STATE_WAIT_YK_SEL_CON		21		//�ȴ�YKѡ��ȷ��
#define	STATE_WAIT_YK_EXE_CON		22		//�ȴ�YKִ��ȷ��
#define	STATE_WAIT_YK_DEL_CON		23		//�ȴ�YK����ȷ��

//Ӧ�ù���״̬
#define	STATE_APP_FREE				0		//����
#define	STATE_APP_CALL_ALL			20		//���ٻ�
#define	STATE_APP_CALL_GRP_1		21		//�ٻ���1������
#define	STATE_APP_CALL_GRP_2		22		//�ٻ���2������
#define	STATE_APP_CALL_GRP_3		23		//�ٻ���3������
#define	STATE_APP_CALL_GRP_4		24		//�ٻ���4������
#define	STATE_APP_CALL_GRP_5		25		//�ٻ���5������
#define	STATE_APP_CALL_GRP_6		26		//�ٻ���6������
#define	STATE_APP_CALL_GRP_7		27		//�ٻ���7������
#define	STATE_APP_CALL_GRP_8		28		//�ٻ���8������
#define	STATE_APP_CALL_GRP_9		29		//�ٻ���9������
#define	STATE_APP_CALL_GRP_10		30		//�ٻ���10������
#define	STATE_APP_CALL_GRP_11		31		//�ٻ���11������
#define	STATE_APP_CALL_GRP_12		32		//�ٻ���12������
#define	STATE_APP_CALL_GRP_13		33		//�ٻ���13������
#define	STATE_APP_CALL_GRP_14		34		//�ٻ���14������
#define	STATE_APP_CALL_GRP_15		35		//�ٻ���15������
#define	STATE_APP_CALL_GRP_16		36		//�ٻ���16������
#define	STATE_APP_CALL_KWH			37		//�������ٻ�
#define	STATE_APP_CALL_KWH_GRP_1	38		//�ٻ���1�����������
#define	STATE_APP_CALL_KWH_GRP_2	39		//�ٻ���2�����������
#define	STATE_APP_CALL_KWH_GRP_3	40		//�ٻ���3�����������
#define	STATE_APP_CALL_KWH_GRP_4	41		//�ٻ���4�����������
#define	STATE_APP_SYNC_TIME			50		//ʱ��ͬ��
#define	STATE_APP_CALL_DATA_1		51		//�ٻ�1������
#define	STATE_APP_CALL_DATA_2		52		//�ٻ�2������
#define	STATE_APP_YK_SEL			101		//YKѡ��
#define	STATE_APP_YK_EXE			102		//YKִ��
#define	STATE_APP_YK_DEL			103		//YK����
//----------------------------��Ϣ�����ַ����------------------------------------------------
#define	IEC104_OBJ_ADDR_UNKOWN				0			//�޹ص���Ϣ�����ַ
//2�ֽ���Ϣ�����ַ
#define	IEC104_OBJ_16_ADDR_YX_START			0x0001		//ң�š�����ʼ
#define	IEC104_OBJ_16_ADDR_YX_END			0x1000		//ң�š�����ֹ
#define	IEC104_OBJ_16_ADDR_PROT_START		0x1001		//�̵籣��������ʼ
#define	IEC104_OBJ_16_ADDR_PROT_END			0x4000		//�̵籣��������ֹ
#define	IEC104_OBJ_16_ADDR_YC_START			0x4001		//ң�⡪����ʼ��ԭ����0x0701��
#define	IEC104_OBJ_16_ADDR_YC_END			0x5000		//ң�⡪����ֹ
#define	IEC104_OBJ_16_ADDR_PARA_START		0x5001		//����������ʼ
#define	IEC104_OBJ_16_ADDR_PARA_END			0x6000		//����������ֹ
#define	IEC104_OBJ_16_ADDR_YK_START			0x6001		//ң�ء�����������ʼ
#define	IEC104_OBJ_16_ADDR_YK_END			0x6200		//ң�ء�����������ֹ
#define	IEC104_OBJ_16_ADDR_SET_START		0x6201		//�趨������ʼ
#define	IEC104_OBJ_16_ADDR_SET_END			0x6400		//�趨������ֹ
#define	IEC104_OBJ_16_ADDR_KWH_START		0x6401		//�����ۼ���������ʼ��ԭ����0x0C01��
#define	IEC104_OBJ_16_ADDR_KWH_END			0x6600		//�����ۼ���������ֹ
#define	IEC104_OBJ_16_ADDR_STEP_START		0x6601		//��λ�á�����ʼ
#define	IEC104_OBJ_16_ADDR_STEP_END			0x6700		//��λ�á�����ֹ
#define	IEC104_OBJ_16_ADDR_BIN_START		0x6701		//�򱻿�վ���Ͷ�������Ϣ������ʼ
#define	IEC104_OBJ_16_ADDR_BIN_END			0x6800		//�򱻿�վ���Ͷ�������Ϣ������ֹ
#define	IEC104_OBJ_16_ADDR_RTU_STATE		0x6801		//Զ���ն�״̬
#define	IEC104_OBJ_16_ADDR_FILE_START		0x6802		//�ļ����͡�����ʼ
#define	IEC104_OBJ_16_ADDR_FILE_END			0x7000		//�ļ����͡�����ֹ
////----------------------------------------------------------------------------
////�������ͣ��Լ����壬�͹�Լ��׼�޹أ�
//#define	IEC104_CMD_RESET_LINK				1			//Զ����·��λ
//#define	IEC104_CMD_REQ_LINK_STATE			4			//������·״̬
//#define	IEC104_CMD_CALL_ALL					20			//���ٻ���YC��YX��
//#define	IEC104_CMD_CALL_GRP_1				21			//�ٻ���1������
//#define	IEC104_CMD_CALL_GRP_2				22			//�ٻ���2������
//#define	IEC104_CMD_CALL_GRP_3				23			//�ٻ���3������
//#define	IEC104_CMD_CALL_GRP_4				24			//�ٻ���4������
//#define	IEC104_CMD_CALL_GRP_5				25			//�ٻ���5������
//#define	IEC104_CMD_CALL_GRP_6				26			//�ٻ���6������
//#define	IEC104_CMD_CALL_GRP_7				27			//�ٻ���7������
//#define	IEC104_CMD_CALL_GRP_8				28			//�ٻ���8������
//#define	IEC104_CMD_CALL_GRP_9				29			//�ٻ���9������
//#define	IEC104_CMD_CALL_GRP_10				30			//�ٻ���10������
//#define	IEC104_CMD_CALL_GRP_11				31			//�ٻ���11������
//#define	IEC104_CMD_CALL_GRP_12				32			//�ٻ���12������
//#define	IEC104_CMD_CALL_GRP_13				33			//�ٻ���13������
//#define	IEC104_CMD_CALL_GRP_14				34			//�ٻ���14������
//#define	IEC104_CMD_CALL_GRP_15				35			//�ٻ���15������
//#define	IEC104_CMD_CALL_GRP_16				36			//�ٻ���16������
//#define	IEC104_CMD_CALL_KWH					37			//�ٻ����������ۼ�����
//#define	IEC104_CMD_CALL_KWH_GRP_1			38			//�ٻ���1����������ۼ�����
//#define	IEC104_CMD_CALL_KWH_GRP_2			39			//�ٻ���2����������ۼ�����
//#define	IEC104_CMD_CALL_KWH_GRP_3			40			//�ٻ���3����������ۼ�����
//#define	IEC104_CMD_CALL_KWH_GRP_4			41			//�ٻ���4����������ۼ�����
//#define	IEC104_CMD_SYNC_TIME				50			//ʱ��ͬ������
//#define	IEC104_CMD_CALL_DATA_1				51			//�ٻ�1������
//#define	IEC104_CMD_CALL_DATA_2				52			//�ٻ�2������
//#define	IEC104_CMD_YK_SEL					101			//YKѡ��
//#define	IEC104_CMD_YK_EXE					102			//YKִ��
//#define	IEC104_CMD_YK_DEL					103			//YK����
////----------------------------------------------------------------------------
//#define	IEC104_YX_GRP_START					1			//YX��š�����ʼ
//#define	IEC104_YX_GRP_END					8			//YX��š�����ֹ
//#define	IEC104_YC_GRP_START					9			//YC��š�����ʼ
//#define	IEC104_YC_GRP_END					14			//YC��š�����ֹ
//#define	IEC104_STEP_GRP						15			//��λ����Ϣ���
//#define	IEC104_RTUSTATE_GRP					16			//Զ���ն�״̬���
//#define	IEC104_KWH_GRP_START				1			//��ȡ�����ʼ
//#define	IEC104_KWH_GRP_END					4			//��ȡ�����ֹ
//----------------------------------------------------------------------------
//��ʱ����ʱ����
#define	TIMEOUT_LINK				(3*PROTO_ONESEC_TIMES)	//�������ӳ�ʱ
#define	TIMEOUT_RECV				(5*PROTO_ONESEC_TIMES)	//���ձ��ĳ�ʱ
#define	TIMEOUT_CALL_ALL			(10*PROTO_ONESEC_TIMES)	//����ȫ���ݱ��ĳ�ʱ
#define	TIMEOUT_CALL_KWH			(8*PROTO_ONESEC_TIMES)	//����KWH���ݱ��ĳ�ʱ
#define	TIMEOUT_CALL_GRP			(7*PROTO_ONESEC_TIMES)	//���շ������ݱ��ĳ�ʱ
#define	TIMEOUT_CALL_KWH_GRP		(6*PROTO_ONESEC_TIMES)	//����KWH�������ݱ��ĳ�ʱ
//������ֵ
#define	RETRY_SEND_LIMIT			3						//�ط�������
//----------------------------------------------------------------------------
////������
//typedef	union
//{
//	struct
//	{
//		unsigned char		FuncCode:4;		//�����롪��3��2��1��0λ
//		//FCV��֡������Чλ������վ��Ӷ�վ���䣺0����FCB�仯��Ч��1����FCB�仯��Ч
//		//DCF������������λ���Ӷ�վ������վ���䣺0������վ���Լ����������ݣ�1������վ�����������޷�����������
//		unsigned char		FcvDcf:1;		//4λ
//		//FCB��֡����λ������վ��Ӷ�վ���䣩������վ��Ӷ�վ������һ�ֵķ���/ȷ�ϡ�����/��Ӧ����ʱ����ǰһ��FCBȡ�෴ֵ
//		//ACD��Ҫ�����λ����վ���Ӷ�վʱACDλ��ʵ�����壬ֵΪ0��
//		//ACD��Ҫ�����λ����վ���Ӷ�վʱ��0������վ��1���û����ݣ�1������վ��1���û����ݣ�ϣ������վ���䣩
//		unsigned char		FcbAcd:1;		//5λ
//		unsigned char		Prm:1;			//��������λ��0�����Ӷ�վ�� ����Ϊȷ�ϱ��Ļ���Ӧ���ģ�1��������վ������Ϊ���ͻ������ģ�����6λ
//		unsigned char		Dir:1;			//���䷽��λ��0������վ����վ��1������վ����վ������7λ
//	}byte;
//	unsigned char		value;
//}IEC104_CONTROL_FIELD;
//Ӧ�ò�ͷ
typedef	struct
{
	unsigned char			Type;			//���ͱ�ʶ
	struct
	{
		unsigned char		Num:7;			//���ݸ�������6��5��4��3��2��1��0λ
		unsigned char		SQ:1;			//��������˳��0����������1����˳�򣩡���7λ
	}VSQ;							//�ɱ�ṹ�޶���
	struct
	{
		unsigned char		Cause:6;		//����ԭ����š���5��4��3��2��1��0λ
		unsigned char		PN:1;			//ȷ�ϣ�0�����϶�ȷ�ϣ�1������ȷ�ϣ�����6λ
		unsigned char		T:1;			//���ԣ�0����δ���飬1�������飩����7λ
		unsigned char		SrcAddr;		//Դ��վ��ַ
	}COT;							//����ԭ��
	unsigned short			CommAddr;		//Ӧ�÷������ݵ�Ԫ������ַ
}IEC104_APP_HEAD;
//----------------------------------------------------------------------------
typedef	struct
{
	//��Լ����������������������ʼ
	//����
	unsigned char			LinkAddrLen;			//��·��ַ���ȣ�1����2��
	unsigned char			CommAddrLen;			//Ӧ�÷������ݵ�Ԫ������ַ���ȣ�1����2��
	unsigned char			ObjAddrLen;				//��Ϣ�����ַ���ȣ�1����3����һ��Ϊ2��
	unsigned char			CotLen;					//����ԭ�򳤶ȣ�1����2����һ��Ϊ2��
	//��ʼ��ַ
	unsigned short		Yx_Start_Addr;			//ң�š�����ʼ
	unsigned short		Yx_End_Addr;			//ң�š�����ֹ
	unsigned short		Prot_Start_Addr;		//�̵籣��������ʼ
	unsigned short		Prot_End_Addr;			//�̵籣��������ֹ
	unsigned short		Yc_Start_Addr;			//ң�⡪����ʼ
	unsigned short		Yc_End_Addr;			//ң�⡪����ֹ
	unsigned short		Para_Start_Addr;		//����������ʼ
	unsigned short		Para_End_Addr;			//����������ֹ
	unsigned short		Yk_Start_Addr;			//ң�ء�����������ʼ
	unsigned short		Yk_End_Addr;			//ң�ء�����������ֹ
	unsigned short		Set_Start_Addr;			//�趨������ʼ
	unsigned short		Set_End_Addr;			//�趨������ֹ
	unsigned short		Kwh_Start_Addr;			//�����ۼ���������ʼ
	unsigned short		Kwh_End_Addr;			//�����ۼ���������ֹ
	unsigned short		Step_Start_Addr;		//��λ�á�����ʼ
	unsigned short		Step_End_Addr;			//��λ�á�����ֹ
	unsigned short		Bin_Start_Addr;			//�򱻿�վ���Ͷ�������Ϣ������ʼ
	unsigned short		Bin_End_Addr;			//�򱻿�վ���Ͷ�������Ϣ������ֹ
	unsigned short		Rtu_State_Addr;			//Զ���ն�״̬
	unsigned short		File_Start_Addr;		//�ļ����͡�����ʼ
	unsigned short		File_End_Addr;			//�ļ����͡�����ֹ
	//��ʼ���
	unsigned char			Yx_Start_Group;			//ң���顪����ʼ��1��
	unsigned char			Yx_End_Group;			//ң���顪����ֹ��8��
	unsigned char			Yc_Start_Group;			//ң���顪����ʼ��9��
	unsigned char			Yc_End_Group;			//ң���顪����ֹ��14��
	unsigned char			Step_Group;				//��λ���飨15��
	unsigned char			Rtu_State_Group;		//Զ���ն�״̬�飨16��
	//��Լ������������������������
	//�̶���Ϣ������������������ʼ
	unsigned short		FrmMinLen;				//��С֡��
	unsigned short		YcMaxNum;				//YC������
	unsigned short		YxMaxNum;				//YX������
	unsigned short		YcMaxNumInPerGroup;		//ÿ��YC������
	unsigned short		YxMaxNumInPerGroup;		//ÿ��YX������
	//�̶���Ϣ��������������������
}IEC104_CONFIG_T,*IEC104_CONFIG_Ptr_T;
//
//typedef	struct
//{
//	unsigned char					LinkWorkStatus;			//��·״̬
//	unsigned char					AppWorkStatus;			//Ӧ�ò�״̬
//
//	unsigned char					SendCommand;			//���͵�ָ��
//
//	IEC104_CONTROL_FIELD	ControlField;			//������
//
//	unsigned char					RetrySendFlag;			//�ط���־
//
//	unsigned int					RecvCount;				//���ձ��ļ������յ���ȷ���Ļ��ط�ʱ���㣬�����1��
//	unsigned int					RetrySendCount;			//�ط����ļ������յ���ȷ���Ļ򳬹��ط�����ʱ���㣬�����1��
//	unsigned int					CallAllDataCount;		//�ٻ�ȫ���ݼ������ɹ�����ȫ���ݻ�ʱ�ٻ���������ʱ���㣬�����1��
//
//	unsigned short					RecvGrpDataNum[16];		//�Ѿ����յ�ÿ�����ݣ�YC��YX��STEP��RTUSTATE���ĸ���
//
//	unsigned char					CallAllDataFlag;		//����ȫ���ݣ�YC��YX����־
//	unsigned char					CallAllKwhFlag;			//����ȫKWH��־
//	unsigned char					CallGroupFlag[16];		//����������ݣ�YC��YX����־��0���������ٻ���1������Ҫ�ٻ���2�����Ѿ��ٻ���
//	unsigned char					Call_1_LevelDataFlag;	//����1�����ݱ�־
//	unsigned char					Call_2_LevelDataFlag;	//����2�����ݱ�־
//	unsigned char					SendTimeFlag;			//ͬ��ʱ�ӱ�־
//}IEC104_INFO_T,*IEC104_INFO_Ptr_T;

typedef	struct
{
	//����ʱ��Ϣ
	unsigned int	T1;						//�ȴ����նԶ�Ӧ����Ϣ��ʱ������ʱռ�ùرգ�
	unsigned int	T2;						//�ȴ�������Ϣ������ɶ�ʱ������ʱ����S֡��
	unsigned int	T3;						//�ȴ�˫���������ݴ��䶨ʱ������ʱ�������Թ��̣�
	unsigned int	T4;						//�ȴ�������·ȷ�϶�ʱ������ʱռ�ùرգ�
	unsigned int	T5;						//�ȴ����ٻ���ֹȷ�϶�ʱ������ʱռ�ùرգ�
	unsigned char	LinkState;				//��ǰ��·״̬
	unsigned char	WorkState;				//��ǰ����״̬
	unsigned short	NS;						//�������
	unsigned short	NR;						//�������
	unsigned char	CallAllDataFlag;		//����ȫ���ݣ�YC��YX����־
	unsigned char	CallAllKwhFlag;			//����ȫKWH��־
	unsigned char	Send_S_ACK_Flag;		//����S֡ȷ�ϵı�־
	unsigned char	Send_U_TESTFR_ACT_Flag;	//����U֡������·�����־
	unsigned char	Send_U_TESTFR_CON_Flag; //����U֡������·ȷ�ϱ�־
	unsigned char	Send_U_STOPDT_ACT_Flag;	//����Uֹ֡ͣ��·�����־
	unsigned char	SendTimeFlag;			//ͬ��ʱ�ӱ�־  dhy


	//FDC_YKBUF		cur_ykbuf;				//��ǰYK������
	unsigned short  W;
	int	pollingTm;
}IEC104_INFO_T,*IEC104_INFO_Ptr_T;

typedef struct
{
	unsigned char		timesync;			//ʱ��ͬ��
	unsigned char		all_data;			//ȫ����
	unsigned char		all_yc;				//ȫYC
	unsigned char		all_yx;				//ȫYX
	unsigned char		all_kwh;			//ȫKWH
	unsigned char		change_data;		//�仯����
	unsigned char		change_yc;			//�仯YC
	unsigned char		change_yx;			//�仯YX
	unsigned char		change_kwh;			//�仯KWH
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

	hUInt8			*pAppDataBuf;					//Ӧ�ò�����ָ��
	hUInt16			AppDataLen;						//Ӧ�ò����ݳ���
	hUInt16			RxDataSize;						//�յ������ݳ���
	hBool			m_open;


	//----------------------------------------------------------------------------
	void			ReadConfig();							//��ȡ��Լ����
	////----------------------------------------------------------------------------
	//void		ResetGrpData(int grpno=-1);				//��ʼ����������Ϣ
	//int			GetGrpDataNum(int grpno);				//������е�ʵ�����ݸ���
	//int			GetOneCallGrpDataCmd(int &grpno);		//Ѱ��һ����Ҫ�����ٻ����飨����ֵ��TRUE�����ҵ�,grpnoΪ���<1...16>��FALSE����δ�ҵ���
	//int			GetOneCallKwhGrpDataCmd(int &grpno);	//Ѱ��һ����Ҫ�����ٻ���ȵ��飨����ֵ��TRUE�����ҵ�,grpnoΪ���<1...4>��FALSE����δ�ҵ���
	//void		SetYcGrpData(int no);					//����YC������
	//void		SetYxGrpData(int no);					//����YX������
	////----------------------------------------------------------------------------
	//void		Init_Link();							//��ʼ����·
	////----------------------------------------------------------------------------
	//int			MakeLinkAddr(unsigned char *buf);				//������·��ַ�����س���
	//int			MakeCommAddr(unsigned char *buf);				//���ɹ�����ַ�����س���
	//int			MakeObjAddr(unsigned char *buf,int no);		//���ɶ����ַ�����س���
	//int			MakeCause(unsigned char *buf,unsigned char cause);	//���ɴ���ԭ�򣬷��س���
	int			GetAppHead(IEC104_APP_HEAD *head);		//������ݵ�Ԫ��ʶ��
	int			GetObjAddr();							//��ö����ַ
	////----------------------------------------------------------------------------
	void		InitInfo();						//��ʼ��������Ϣ
	void		NoRxAnyData();					//��һЩ�������ۼ�
	void		RxSomeData();					//���һЩ������
	//void		CheckTxFlag();							//��ⷢ�ͱ�־
	//void		Check_TimeOut();						//��ⳬʱ

	//int			MakeSendCmd();							//���ɷ�������
	//int			Send_Message_To_TxBuf(unsigned char func,unsigned short len);	//���ͱ��ĵ����ͻ�����

	//int			App_Send();								//���ɷ�������

	//int				Tx_APDU_I(unsigned char len);	//����I��ʽ��Ӧ�ù�Լ���Ƶ�Ԫ
	//int				Tx_APDU_S();					//����S��ʽ��Ӧ�ù�Լ���Ƶ�Ԫ
	//int				Tx_APDU_U(unsigned char type);	//����U��ʽ��Ӧ�ù�Լ���Ƶ�Ԫ

	//int				Tx_CtrlCmd();					//���Ϳ�������
	//int				Tx_AnalogOutPut();				//����ģ�������
	//int				Tx_CallHisdata();				//�����ٻ���ʷ��������

	//int			Tx_ResetLink();							//��λԶ����·
	//int			Tx_ReqLinkState();						//����Զ����·
	//int			Tx_Call_1_LevelData();					//�ٻ�1������
	//int			Tx_Call_2_LevelData();					//�ٻ�2������

	//void		Tx_DataCmd();					//������������
	//int			Tx_CallAllData(unsigned char QOI);			//���ٻ���QOI=20���������ٻ���QOI>=21 && QOI<=36��
	//int			Tx_SyncTime();							//ͬ��ʱ��
	
	///----------------------------------------------------------------------------
	// �ж϶Է��Ľ��ܺͷ���������ǵ��Ƿ�һ�£������һ��������· Bruce 2006-09-18
	int			IsNsNrMatch(unsigned char * buff);

	int				SearchAPCI();					//����Ӧ�ù�Լ������Ϣ

	int				SearchASDU();					//����Ӧ�÷������ݵ�Ԫ
	//int				Link_Recv();							//��·�����
	//int				App_Recv();								//Ӧ�ò����

	//int				DoCtrlField(unsigned char control);			//���������
	void			DoCallAllDataAck(IEC104_APP_HEAD &head);	//�������ٻ�Ӧ��
	void			DoCallAllKwhAck(IEC104_APP_HEAD &head);		//�����ٻ�ȫ���Ӧ��
	void			DoSyncTimeAck(IEC104_APP_HEAD &head);		//����ʱ��ͬ��Ӧ��
	void			DoYkAck(IEC104_APP_HEAD &head);				//����YK����
	void			DoAnalogOutPutAck(IEC104_APP_HEAD &head);	//����ģ�����������

	void		YC_RxProc(IEC104_APP_HEAD &head);		//YC���մ���
	void		YX_RxProc(IEC104_APP_HEAD &head);		//YX���մ���
	void		SOE_RxProc(IEC104_APP_HEAD &head);		//SOE���մ���


public:
	SGS_Proto_104();
	virtual ~SGS_Proto_104();

	virtual int		Init(short stno,short chno);					//��Լ����ĳ�ʼ��
	virtual	int		ProtoRX_Init(short stno,short chno);		//����ǰ�ĳ�ʼ������
	virtual	int		ProtoTX_Init(short stno,short chno);		//����ǰ�ĳ�ʼ������
	virtual	void	ProtoRX();					//����Լ����
	virtual	void	ProtoTX();					//����Լ����
	virtual	bool	isOpen() const;
public:

protected:
private:
};

#endif	//_SGS_PROTO_101_H_