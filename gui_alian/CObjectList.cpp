//
// CObjectList.cpp
//

#include "stdafx.h"
#include "CObjectList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CObjectList::CObjectList(void)
{
}

CObjectList::~CObjectList(void)
{
}

int CObjectList::GetIndex(void * inPointer)
{
	int index = -1;
	for (int i = 0; i < GetSize() && index == -1; i ++)
	{
		void * obj = GetAt(i);
		if (obj == inPointer)
		{
			index = i;
		}
	}
	return index;
}

int CObjectList::Add(void * inPointer)
{
	return CPtrArray::Add(inPointer);
}
	
int CObjectList::Add(void * inPointer, int inIndex)
{
	CPtrArray::InsertAt(inIndex, inPointer);
	return inIndex;
}
	
void CObjectList::Remove(void * inPointer)
{
	int index = GetIndex(inPointer);
	if (index != -1)
	{
		RemoveAt(index);
	}
}

void * CObjectList::GetPrevious(void * inPointer)
{
	int index = GetIndex(inPointer);
	if (index > 0)
	{
		index --;
		return GetAt(index);
	}
	return 0;
}

void * CObjectList::GetNext(void * inPointer)
{
	int index = GetIndex(inPointer);
	if (index != -1)
	{
		index ++;
		if (index < GetSize())
		{
			return GetAt(index);
		}
	}
	return 0;
}