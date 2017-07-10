typedef struct _CreUDPStructForFile
{
	short nSeq;          //����š�
	short nAck;         //�Ƿ���ȷ�ϰ���0����1��ָ���ط���־��2���ط�����3��Ҫ���ط��ط�����4��һ�ΰ�������ϣ�5����ֹ���ӡ�
	short nDataSize;//�ϣ�0�����ݰ���1���ط�����2���ط�����3��û�õ���4��û�õ���5��һ�ΰ�������ϣ�
    char *data;
	_CreUDPStructForFile(int nSize)
	{
		nSeq = 0;
		nAck = 0;
		nDataSize = nSize;
		if (nSize > 0)
		{
			if (nSize > 1400)
				nSize = 1400;
			data = new char[nSize];
			ZeroMemory(data,nSize);
		}
		else
			data = NULL;
	}
	~_CreUDPStructForFile()
	{
		if (data != NULL)
			delete data;
	}
	
}UDPStructForFile;

typedef struct _RoleIPPort
{
	unsigned long ip;
	unsigned short port;
	_RoleIPPort()
	{
		ip = 0;
		port = 0;
	};
}RoleIPPort;

typedef map<int,UDPStructForFile*> MapInt;

typedef struct _SendStruct 
{
	short nSequence;	//��ǰ���к�---����
	short nSendedSeq;	//���͹���������к�
	short nReceivedSeq;	//���յ������������ţ�
	short nLastSeq;		//���һ���������/SendEndʱ��ֵ
	short nMiddleSeq;	//����û�õ�
	short nSegmentLastSeq;	//��ǰ�������һ��������ţ�
	int nAckTime;	//�յ�Ack=1��ʱ��
	int nSendSize_1ms;  //ÿ����Ҫ�������ֽ���
	int nSegmentCount;	//ÿ�εİ���
	MapInt  mSendMap;	//<����ţ���>��ԭʼ,���ΪSENDINTERVALCOUNT
	vector<UDPStructForFile*> vReqSeqVector;//�����ط�����
	vector<int> vDeleteVector;	//����Ack=2��֮ǰ��ȫ�յ���������Ϣ
//	HANDLE hAckEvent;	//�յ�Ack=1?,2?	SendProc
//	HANDLE hReqSeqEvent;//�յ�Ack=1	ReqSeqProc
//	HANDLE hDeleteEvent;//�յ�Ack=2?	DeleteProc
//	HANDLE hContinueSendEvent;//�յ�Ack=2?	SendProc
//	HANDLE hAckEvent2;
	CRITICAL_SECTION cSendBufferLock;
	CRITICAL_SECTION cReqSeqLock;
	CRITICAL_SECTION cDeleteLock;
	_SendStruct(string sEventName)
	{
		nSequence = 0;
		nSendedSeq = -1;
		nReceivedSeq = -1;
		nLastSeq = -1;
		nMiddleSeq = 0;
		nSegmentLastSeq = 0; 
		nAckTime = -1;
		nSendSize_1ms = 0;
		nSegmentCount = 1;
		vReqSeqVector.reserve(1000);
		vDeleteVector.reserve(100);
		
//		sEventName += "SendEvent";
//		hAckEvent = CreateEvent(NULL,true,false,sEventName.c_str());
//		sEventName += "ReqSeqEvent";
//		hReqSeqEvent = CreateEvent(NULL,true,false,sEventName.c_str());
//		sEventName += "DeleteEvent";
//		hDeleteEvent = CreateEvent(NULL,true,false,sEventName.c_str());
//		sEventName += "ConSendEvent";
//		hContinueSendEvent = CreateEvent(NULL,true,false,sEventName.c_str());
//		sEventName += "AckEvent2";
//		hAckEvent2 = CreateEvent(NULL,false,false,sEventName.c_str());
		
		InitializeCriticalSection(&cSendBufferLock);
		InitializeCriticalSection(&cReqSeqLock);
		InitializeCriticalSection(&cDeleteLock);
	};
	~_SendStruct()
	{
		MapInt::iterator iter_map = NULL;
		vector<UDPStructForFile*>::iterator iter_vector = NULL;
		
		EnterCriticalSection(&cSendBufferLock);
		if (mSendMap.size() > 0)
		{
			for (iter_map=mSendMap.begin(); iter_map!=mSendMap.end(); ++iter_map)
			{
				delete iter_map->second;
			}
			mSendMap.clear();
		}
		LeaveCriticalSection(&cSendBufferLock);
		
		EnterCriticalSection(&cReqSeqLock);
		if (vReqSeqVector.size() > 0)
		{
			for (iter_vector=vReqSeqVector.begin(); iter_vector!=vReqSeqVector.end(); ++iter_vector)
			{
				delete *iter_vector;
			}
			vReqSeqVector.clear();
		}
		LeaveCriticalSection(&cReqSeqLock);
		
//		CloseHandle(hAckEvent);
//		hAckEvent = NULL;
//		CloseHandle(hReqSeqEvent);
//		hReqSeqEvent = NULL;
//		CloseHandle(hDeleteEvent);
//		hDeleteEvent = NULL;
//		CloseHandle(hContinueSendEvent);
//		hContinueSendEvent = NULL;
//		CloseHandle(hAckEvent2);
//		hAckEvent2 = NULL;
		
		DeleteCriticalSection(&cSendBufferLock);
		DeleteCriticalSection(&cReqSeqLock);
		DeleteCriticalSection(&cDeleteLock);
	};
}SendStructForFile;

typedef struct _RecvStruct
{
	short nReqSeq;                //����ȷ������nAck == 1�İ������кš�
	short nCompleteSeq;           //����ȷ������nAck == 2�İ������кš�
	short nReceivedSeq;           //���յ������Ѿ����������š�
	short nWaitTime;		//����û�õ�
	short nLastSeq;              //��Ŷ������һ��������š�
	bool  bReturnSend;	//����û�õ�
	bool bSeqFlag[10000];	//�����Ƿ��յ��ı�־
	MapInt  mRecvMap;                         //��Ÿս��յ����ݡ�<��ţ�����>
	vector<UDPStructForFile*> vRecvVector;           //����Ѿ�����������ݣ�������������ȣ���
	vector<short> vLostSeqVector;               //��Ŷ�ʧ������š�
	vector<int> vCompleteVector;              //����յ�����������кš�
//	HANDLE hProcEvent;	//�յ�Ack=5����û����ȫ	AfterRecvProc
//	HANDLE hRecvEvent;	//i���յ���i֮ǰû�ж���	ReceiveData
//	HANDLE hCompleteEvent;	//�յ�Ack=5������ȫ�ˣ�����㶪��ʱ��Ϊ��ȫ��	SendCompleteSeqProc
//	HANDLE hLostEvent;	//���㶪��ʱ��Ϊû��ȫ	SendLostProc
	CRITICAL_SECTION cRecvBufferLock;
	CRITICAL_SECTION cRecvVectorLock;
	CRITICAL_SECTION cLostSeqLock;
	CRITICAL_SECTION cCompleteLock;
	_RecvStruct(string sEventName)
	{
		nReqSeq = 0;
		nCompleteSeq = 0;
		nReceivedSeq = -1;
		nWaitTime = 10000;
		nLastSeq = -1;
		bReturnSend = false;
		for (int i=0; i<10000; ++i)
		{
			bSeqFlag[i] = false;
		}
		vRecvVector.reserve(1000);
		vLostSeqVector.reserve(1000);
		vCompleteVector.reserve(100);
//		sEventName += "ProcEvent";
//		hProcEvent = CreateEvent(NULL,true,false,sEventName.c_str());
//		sEventName += "RecvEvent";
//		hRecvEvent = CreateEvent(NULL,true,false,sEventName.c_str());
//		sEventName += "CompleteEvent";
//		hCompleteEvent = CreateEvent(NULL,true,false,sEventName.c_str());
//		sEventName += "SendLostEvent";
//		hLostEvent = CreateEvent(NULL,true,false,sEventName.c_str());
		
		InitializeCriticalSection(&cRecvBufferLock);
		InitializeCriticalSection(&cRecvVectorLock);
		InitializeCriticalSection(&cLostSeqLock);
		InitializeCriticalSection(&cCompleteLock);
	};
	~_RecvStruct()
	{
		MapInt::iterator iter_map = NULL;
		vector<UDPStructForFile*>::iterator iter_vector = NULL;
		
		EnterCriticalSection(&cRecvBufferLock);
		if (mRecvMap.size() > 0)
		{
			for (iter_map=mRecvMap.begin(); iter_map!=mRecvMap.end(); ++iter_map)
			{
				delete iter_map->second;
			}
			mRecvMap.clear();
		}
		LeaveCriticalSection(&cRecvBufferLock);
		
		EnterCriticalSection(&cRecvVectorLock);
		if (vRecvVector.size() > 0)
		{
			for (iter_vector=vRecvVector.begin(); iter_vector!=vRecvVector.end(); ++iter_vector)
			{
				delete *iter_vector;
			}
			vRecvVector.clear();
		}
		LeaveCriticalSection(&cRecvVectorLock);
		
//		CloseHandle(hProcEvent);
//		hProcEvent = NULL;
//		CloseHandle(hRecvEvent);
//		hRecvEvent = NULL;
//		CloseHandle(hCompleteEvent);
//		hCompleteEvent = NULL;
//		CloseHandle(hLostEvent);
//		hLostEvent = NULL;
		
		DeleteCriticalSection(&cRecvBufferLock);
		DeleteCriticalSection(&cRecvVectorLock);
		DeleteCriticalSection(&cLostSeqLock);
		DeleteCriticalSection(&cCompleteLock);
	};
	
}RecvStructForFile;
