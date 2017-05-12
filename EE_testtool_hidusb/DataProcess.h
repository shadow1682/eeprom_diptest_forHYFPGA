#pragma once

#ifndef __DATAPROCESS_H__
#define __DATAPROCESS_H__

class CDataProcess
{
public:
	CDataProcess();
	~CDataProcess();

	BOOL ucharTostring(unsigned char* Uchar, int iLen, CString String);
	BOOL stringTouchar(CString String, unsigned char* Uchar, int iLen);

};
#endif
