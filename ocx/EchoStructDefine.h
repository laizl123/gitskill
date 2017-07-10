struct EchoHead
{
	char Head[4];

	EchoHead()
	{
		memcpy( Head, "ECHO", 4 );
	}
};

struct EchoStrust
{
	struct EchoHead Head;
	unsigned long SendTime;
};