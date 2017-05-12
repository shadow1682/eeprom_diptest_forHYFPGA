#include "stdafx.h"
#include "DataProcess.h"


CDataProcess::CDataProcess()
{
}
CDataProcess::~CDataProcess()
{
}

BOOL CDataProcess::ucharTostring(unsigned char* Uchar, int iLen,CString String)//将数据保存为CString类型
{
	char Result_buffer[1024] = { 0 };
	int j = 0;
	unsigned char dat[1] = { 0 };

	for (int i = 0; i<iLen; i++)
	{
		dat[0] = (Uchar[i] & 0xF0) >> 4;
		Result_buffer[j] = (dat[0] <= 9) ? dat[0] + '0' : (dat[0] - 10) + 'A';
		j++;
		dat[0] = (Uchar[i] & 0x0F);
		Result_buffer[j] = (dat[0] <= 9) ? dat[0] + '0' : (dat[0] - 10) + 'A';
		j++;
		Result_buffer[j] = ' ';
		j++;
	}
	String.Format(_T("%s"), Result_buffer);
	return FALSE;
}

BOOL  CDataProcess::stringTouchar(CString String, unsigned char* Uchar, int iLen)//将获取的CString数据转换为unsigned char十六进制类型
{
	unsigned char charbuffer[1024] = { 0 }, dat[10] = { 0 };

	char buffer[1024] = { 0 };

	String.Remove(' ');
	int i = 0, k = 0, len = strlen(String);
	strcpy_s((char*)charbuffer, len + 10, String);

	while (i<len)
	{
		dat[0] = (charbuffer[i] <= '9') ? charbuffer[i] - '0' : (charbuffer[i] + 10) - 'A';
		if (dat[0]>0x20)dat[0] -= 0x20;
		dat[1] = (charbuffer[i + 1] <= '9') ? charbuffer[i + 1] - '0' : (charbuffer[i + 1] + 10) - 'A';
		if (dat[1]>0x20)dat[1] -= 0x20;
		buffer[k++] = dat[0] * 16 + dat[1];
		i = i + 2;
	}
	memcpy(Uchar, buffer, k);
	iLen = k;
	return FALSE;

}