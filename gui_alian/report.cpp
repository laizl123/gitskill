#include "stdafx.h"

#include "regexp_int.h"
#include "regexp_custom.h"

#include <stdio.h>

void re_report(const char* error)
{
	// trace errors
	ATLTRACE("REGEXP ERROR: %s\n", error);
}

