//
// CObjectList.h
//

#ifndef __H_CObjectList__
#define __H_CObjectList__

#include <afxcoll.h>

class CObjectList : public CPtrArray
{
public:
	CObjectList(void);
	virtual ~CObjectList(void);

	int GetIndex(void * inPointer);
	int Add(void * inPointer);
	int Add(void * inPointer, int inIndex);
	void Remove(void * inPointer);

	void * GetPrevious(void * inPointer);
	void * GetNext(void * inPointer);
};

#endif // __H_CObjectList__