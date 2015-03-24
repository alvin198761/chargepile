/***********************************************************************
˵�����˶�̬��֧��ͬʱ�������MODEM��ÿ��MODEM����һ��Ψһ��ţ��з���š�
	  �������ʹ��SMSStartServiceEx��SMSStartService��������ʱ�᷵�أ�

	  ���Ͷ��ſ�����SMSSendMessage��SMSSendMessageEx������ֻҪ��������
	  ���ݣ����ݸ������������ɣ�������ų��ȹ��������Զ��ϳɶ������ŷ��͡�
	  ʹ��SMSSendMessageEx���Ͷ���ʱ��3�ָ�ʽ����ѡ��:
	  0��7BIT���˸�ʽֻ���ڷ���Ӣ�Ķ��š�
	  4��8BIT���˸�ʽ�������ڷ������Ķ��Ż���16���ƶ��ţ���Ҫ���ڷ���16���ƶ��š�
	  8��UCS2���˸�ʽ��Ҫ���ڷ������Ķ��š�
	  255���Զ�ʶ��

      ���ն��������ַ�ʽ:
	  һ����ʹ�ûص��������������ж��ŵ���ʱ���Զ���ת���ص�����ִ�У�
	  �ص������Ĳ��������յ��Ķ������ݺ�ʱ�䣬�����ڻص��������洦��
	  ���յ��Ķ��š�����װ�����ݿ⣬Ҳ������ʾ�����н��档�Ƽ�ʹ����
	  �ַ�ʽ��
	  
	  ��һ����ʹ��SMSGetNextMessageEx����SMSGetNextMessage��ѯ��ʽ��ÿ��
	  һ��ʱ��ȥ��ѯһ�Σ�����Ѿ��ж��ŵ������˺���ÿʹ��һ�ν���һ�����š�
	  ��������Ѿ������꣬ͨ���˺�������ֵ�����жϡ�

	  ���⻹��һЩ����������������ѯָ�������Ƿ��ͳɹ�����ѯ����MODEM״̬��
	  ��ѯ����״̬����ѯָ��MODEM�źź��Ƿ��������Ź��ܵȵȡ�

	  ע�⣺������һ�����ͽ�����湦�ܣ������ú���SMSEnableReportѡ��
	  ������ر�������ܣ�Ĭ�Ϲرա��˹������������Ӧ����SMSReportEx
	  ����SMSReport��������ȥ��ѯ���ŷ��ͱ��棬����ÿ����һ�������ڴ�
	  �ͻᱻ�����ȥһ�㣬ʹ�ô˺�����ȡһ�����棬�ڴ��оͻ����һ�����档
	  �Ƽ���������ʹ�ò�ѯSMSQuery��������ѯ�����Ƿ��ͳɹ���

***********************************************************************/

#ifndef __SMS_DLL_FILE_HEAD__
#define __SMS_DLL_FILE_HEAD__

#define DLL_FUCTION_HEAD		__declspec (dllexport)

extern "C" 
{
	typedef signed char         INT8, *PINT8;
	typedef signed short        INT16, *PINT16;
	typedef signed int          INT32, *PINT32;
	typedef signed __int64      INT64, *PINT64;
	typedef unsigned char       UINT8, *PUINT8;
	typedef unsigned short      UINT16, *PUINT16;
	typedef unsigned int        UINT32, *PUINT32;
	typedef unsigned __int64    UINT64, *PUINT64;
	typedef int                 BOOL;
	typedef char				CHAR;

	typedef	struct _sms_report_stu
	{
		UINT32		index;			// ���Ͷ���ʱ���ص�������
		CHAR		Msg[256];		// ��������
		INT32		Success;		// �Ƿ�ɹ���1���ɹ���0��ʧ��
		CHAR		PhoneNo[32];		// �ֻ����� 
	}SMSReportStruct;

	typedef struct _sms_msg_stu
	{
		CHAR		szMsg[256];		// ��������
		CHAR		szPhoneNo[32];		// �ֻ�����
		CHAR		szReceTime[32];		// ����ʱ��
	}SMSMessageStruct;

	typedef	struct _sms_report_ex_stu
	{
		UINT32		uIndex;			// ���Ͷ���ʱ���ص������� 
		CHAR		szMsg[256];		// ��������
		INT8		nSuccess;		// �Ƿ�ɹ���1���ɹ���0��ʧ��
		CHAR		szPhoneNo[32];		// �ֻ����� 
		UINT16		uMsgLen;		// ���ų���
	}SMSReportStructEx;

	typedef struct _sms_msg_ex_stu
	{
		CHAR		szMsg[256];		// ��������
		UINT16		uMsgLen;		// ���ų���
		CHAR		szPhoneNo[32];		// �ֻ�����
		CHAR		szReceTime[32];		// ����ʱ��
	}SMSMessageStructEx;


	typedef void (*RECV_SMS_CALLBACK)(INT32 nPort, 			// �����ţ���������ʱ����
									  SMSMessageStructEx *pMessage, 	// ���յ��Ķ���
									  void *pParam);			// �������

	typedef void (*SEND_SMS_CALLBACK)(INT32 nPort, 			// �����ţ���������ʱ����
									  UINT32 uSMSIndex, 		// ���Ͷ�������
									  SMSMessageStructEx *pMessage, 	// ���͵Ķ���
									  INT8 nSuccess, 			// �Ƿ�ɹ� 1���ɹ���0��ʧ��
									  void *pParam);			// �������

	//��������,�򿪴��ڣ���ʼ��Modem
	// ���� =< 0 ��ʾ����ʧ�ܡ�> 0 ��ʾ�����ɹ������ط�����
	DLL_FUCTION_HEAD INT32 _stdcall SMSStartService(INT32 nPort, 			// �˿ں�
								   UINT32 uBaudRate,		// ������
								   INT32 nParity,			// У��λ���������ã�
								   INT32 nDataBits, 		// ����λ���������ã�
								   INT32 nStopBits,		// ֹͣλ���������ã�
								   INT32 nFlowControl, 		// ����λ���������ã�
								   CHAR *pCsca);			// �������ĺ��룬ʹ��Ĭ�ϵ����ĺ��봫��CARD

	//��������,�򿪴��ڣ���ʼ��Modem
	// ���� < 0 ��ʾ����ʧ�ܡ�>= 0 ��ʾ�����ɹ������ط�����
	DLL_FUCTION_HEAD INT32 _stdcall SMSStartServiceEx(INT32 nPort, 			// �˿ں�
									 UINT32 uBaudRate,		// ������
									 INT32 nParity,			// У��λ���������ã�
									 INT32 nDataBits, 		// ����λ���������ã�
									 INT32 nStopBits,		// ֹͣλ���������ã�
									 INT32 nFlowControl, 		// ����λ���������ã�
									 CHAR *pCsca,			// �������ĺ��룬ʹ��Ĭ�ϵ����ĺ��봫��CARD
									 RECV_SMS_CALLBACK DealRecvSms,	// ���ն��ŵĻص�����
									 void *pRecvSmsParam,		// �ص���������Ĳ���
									 SEND_SMS_CALLBACK DealSendSms,	// ���Ͷ��Ž���Ļص�����
									 void *pSendSmsParam);		// �ص���������Ĳ���

	//ֹͣ���з���
	// ���ط�0Ϊ�ɹ���0Ϊʧ��
	DLL_FUCTION_HEAD INT32 _stdcall SMSStopService();	

	//ֹͣ���з���
	// ���ط�0Ϊ�ɹ���0Ϊʧ��
	DLL_FUCTION_HEAD INT32 _stdcall SMSStopSerice();

	// ָֹͣ������ŵķ���
	// ���ط�0Ϊ�ɹ���0Ϊʧ��
	DLL_FUCTION_HEAD INT32 _stdcall SMSStopServiceByPort(INT32 nPort);	// �����ţ���������ʱ���� 

	// �鿴�����Ƿ���һ��������
	// ���ط�0Ϊ�ǣ�0Ϊ��
	DLL_FUCTION_HEAD INT8 _stdcall SMSServiceStarted();

	// �һ����з���
	DLL_FUCTION_HEAD void _stdcall SMSServiceSuspend();

	// ���з����������
	DLL_FUCTION_HEAD void _stdcall SMSServiceResume(void);

	// �һ�ָ���ķ���
	DLL_FUCTION_HEAD void _stdcall SMSServiceSuspendByPort(INT32 nPort);	// �����ţ���������ʱ���� 

	// �һ�ָ���ķ����������
	DLL_FUCTION_HEAD void _stdcall SMSServiceResumeByPort(INT32 nPort);	// �����ţ���������ʱ���� 

	// �鿴ָ�������Ƿ���������
	// ���ط�0Ϊ�ǣ�0Ϊ��
	DLL_FUCTION_HEAD INT8 _stdcall SMSServiceStartedByPort(INT32 nPort);	// �����ţ���������ʱ���� 

	// �Ƿ����÷��ͽ�����湦�ܡ����������ڴ��˷�
	DLL_FUCTION_HEAD void _stdcall SMSEnableReport(INT8 bEnable);		// �Ƿ����ã�1�����ã�0��������

	// �Ƿ����ó����Ź��ܡ������������֧�ֳ����š�
	DLL_FUCTION_HEAD void _stdcall SMSEnableLongSms(INT8 bEnable);		// �Ƿ����ã�1�����ã�0��������

	// δ��ɳ���������ʱ�䡣ֻ�ڽ��ճ����ſ���ʱ���á��ڽ��ճ����ŵĹ����У����ܷ���������ֻ�յ�һ���ֵ������
	// ����δ��ɵĳ����ţ�����һֱפ�����ڴ��У���Ҫ�趨һ��ʱ�䣬���������ʱ��ʱ��������ջ�δ��ɣ��ͽ����δ��ɵĶ��Ŵ��ڴ������������Ĭ�ϵ�ʱ����30����
	// lifeTimeSecond�ĵ�λ����
	DLL_FUCTION_HEAD void _stdcall SMSSetLongSmsLifeTime( UINT64 lifeTimeSecond );

	//������ŷ���׳̬(�ɹ����) 
	// ���ط�0Ϊ�б��棬0Ϊ��
	DLL_FUCTION_HEAD INT32 _stdcall SMSReport(SMSReportStruct *pReport);	// ����ṹ��ָ��

	//������ŷ���׳̬(�ɹ����) 
	// ���ط�0Ϊ�б��棬0Ϊ��
	DLL_FUCTION_HEAD INT32 _stdcall SMSReportEx(SMSReportStructEx *pReport);// ����ṹ��ָ��

	//����ָ������Ķ��ŷ���׳̬(�ɹ����) 
	// ���ط�0Ϊ�б��棬0Ϊ��
	DLL_FUCTION_HEAD INT32 _stdcall SMSReportExByPort(INT32 nPort, 			// �����ţ���������ʱ���� 
									 SMSReportStructEx *pReport);	// ����ṹ��ָ��

	//��ѯָ����ŵĶ����Ƿ��ͳɹ�(�������SMSSendMessage����)
	//���� 0 ��ʾ����ʧ��
	//     1 ��ʾ���ͳɹ�
	//    -1 ��ʾû�в�ѯ������ŵĶ���,�������ڷ����С�
	DLL_FUCTION_HEAD INT32 _stdcall SMSQuery(UINT32 uIndex);				// ����������	

	// �õ����ʧ�ܵ�ԭ��
	// ������Ϣ����
	DLL_FUCTION_HEAD INT32 _stdcall SMSGetLastError(CHAR *pError, 			// ����
								   UINT16 uLen);			// �����С

	// �õ�ָ���������ʧ�ܵ�ԭ��
	// ������Ϣ����
	DLL_FUCTION_HEAD INT32 _stdcall SMSGetLastErrorEx(INT32 nPort, 			// �����ţ���������ʱ���� 
									 CHAR *pError, 			// ����
									 UINT16 uLen);			// �����С

	// ͨ�����󷵻�ֵ�鿴������Ϣ������ֻ���������񷵻ؽ����Ч��
	// ������Ϣ����
	DLL_FUCTION_HEAD INT32 _stdcall SMSGetErrorByID(INT32 nErrorID, 			// �����ţ���������ʱ���� 
								   CHAR *pError, 			// ����
								   UINT16 uLen);			// �����С

	//���Ͷ���Ϣ
	// ���ض���Ϣ���:index����0��ʼ�������ú����������������ȷ��أ����ú���SMSQuery(DWORD index)����ѯ�Ƿ��ͳɹ�
	DLL_FUCTION_HEAD UINT32 _stdcall SMSSendMessage(CHAR *pMsg, 			// ������0x00��β���ַ���
								   CHAR *pPhone); 			// ���շ��绰���� 

	// ���Ͷ���Ϣ
	// ���ؼ��뷢�ͻ�������Ƿ�ɹ���0��ʧ�ܣ�δ�ҵ������ţ���0���ɹ�
	DLL_FUCTION_HEAD INT32 _stdcall SMSSendMessageEx(INT32 nPort, 			// �����ţ���������ʱ���أ�0 ��ʾ������������Ͷ���
									CHAR *pMsg, 			// ��������
									UINT16 uMsgLen, 		// ���ų���
									CHAR *pPhone, 			// ���շ��绰���� 
									UINT8 uCode, 			// �����ʽ	0��7BIT��4��8BIT��8��UCS2��255���Զ�ʶ��
									UINT32 *pIndex);		// ����Ϣ���

	// ��ȡ���ն���
	// ����0��û�ж��ţ�1���ж���
	DLL_FUCTION_HEAD INT32 _stdcall SMSGetNextMessage(SMSMessageStruct* pMsg);	// ���Žṹ��

	// ��ȡ���ն���
	// ����0��û�ж��ţ�1���ж���
	DLL_FUCTION_HEAD INT32 _stdcall SMSGetNextMessageEx(INT32 nPort, 		// �����ţ���������ʱ���� 
									   SMSMessageStructEx* pMsg);	// ���Žṹ��

	// �õ�ָ����������MODEM��״̬
	// ����״̬��Ϣ 0��������1��δ������2���źŵͣ�3��δ������4��AT��ͨ
	DLL_FUCTION_HEAD UINT8 _stdcall SMSGetStateByID(INT32 nPort);			// �����ţ���������ʱ���� 

	// �õ�ָ����������MODME���ź�
	DLL_FUCTION_HEAD BOOL  _stdcall SMSGetCsq(INT32 nPort, 				// �����ţ���������ʱ���� 
							 UINT16 *pS, 				
							 UINT16 *pQ);	

	// ����ʹ�ù��ҡ�����ֻ�����ձ�������
	DLL_FUCTION_HEAD BOOL _stdcall SMSSetNation(INT32 nPort, 			// �����ţ���������ʱ���� 
							   UINT16 uNation);			// ������0��Ĭ�ϣ�1���ձ�  2��������

	// ���ö������ĺ������ͣ�Ĭ����91����ʽ�� +8613912345678
	// �����ֻ�������������ã����԰ٶ� TON/NPI �˽���ϸ
	DLL_FUCTION_HEAD void _stdcall SMSSetCSCAType( UINT8 u8Type );

	// ����Ŀ�ĺ������ͣ�Ĭ����91����ʽ�� +8613912345678
	DLL_FUCTION_HEAD void _stdcall SMSSetDstPhoneType( UINT8 u8Type );

	// �������š����й�����86��Ĭ����86
	DLL_FUCTION_HEAD void _stdcall SMSSetAreaCode( UINT8 u8AreaCode );
}

#endif