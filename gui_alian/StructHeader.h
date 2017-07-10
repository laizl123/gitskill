typedef struct _CreUDPStructForFile
{
	short nSeq;          //包序号。
	short nAck;         //是否是确认包。0：否；1：指定重发标志；2：重发包；3：要求重发重发包；4：一段包发送完毕；5：终止连接。
	short nDataSize;//上：0：数据包；1：重发请求；2：重发包；3：没用到；4：没用到；5：一段包发送完毕？
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
	short nSequence;	//当前序列号---段内
	short nSendedSeq;	//发送过的最大序列号
	short nReceivedSeq;	//已收到的最大连续序号？
	short nLastSeq;		//最后一个包的序号/SendEnd时赋值
	short nMiddleSeq;	//好像没用到
	short nSegmentLastSeq;	//当前段中最后一个包的序号？
	int nAckTime;	//收到Ack=1的时间
	int nSendSize_1ms;  //每毫秒要发出的字节数
	int nSegmentCount;	//每段的包数
	MapInt  mSendMap;	//<包序号－包>，原始,最多为SENDINTERVALCOUNT
	vector<UDPStructForFile*> vReqSeqVector;//放置重发请求
	vector<int> vDeleteVector;	//放置Ack=2（之前完全收到？）的消息
//	HANDLE hAckEvent;	//收到Ack=1?,2?	SendProc
//	HANDLE hReqSeqEvent;//收到Ack=1	ReqSeqProc
//	HANDLE hDeleteEvent;//收到Ack=2?	DeleteProc
//	HANDLE hContinueSendEvent;//收到Ack=2?	SendProc
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
	short nReqSeq;                //用以确定发送nAck == 1的包的序列号。
	short nCompleteSeq;           //用以确定发送nAck == 2的包的序列号。
	short nReceivedSeq;           //已收到并且已经处理包的序号。
	short nWaitTime;		//好像没用到
	short nLastSeq;              //存放段中最后一个包的序号。
	bool  bReturnSend;	//好像没用到
	bool bSeqFlag[10000];	//放置是否收到的标志
	MapInt  mRecvMap;                         //存放刚接收的数据。<序号－数据>
	vector<UDPStructForFile*> vRecvVector;           //存放已经处理过的数据（包括重新排序等）。
	vector<short> vLostSeqVector;               //存放丢失包的序号。
	vector<int> vCompleteVector;              //存放收到包的最大序列号。
//	HANDLE hProcEvent;	//收到Ack=5并且没有收全	AfterRecvProc
//	HANDLE hRecvEvent;	//i号收到，i之前没有丢包	ReceiveData
//	HANDLE hCompleteEvent;	//收到Ack=5并且收全了，或计算丢包时认为收全了	SendCompleteSeqProc
//	HANDLE hLostEvent;	//计算丢包时认为没收全	SendLostProc
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
