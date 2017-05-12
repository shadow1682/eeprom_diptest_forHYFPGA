

#pragma once

#ifndef __HIDUSB_H__
#define __HIDUSB_H__

#include <dbt.h>

extern "C"
{
	// This file is in the Windows DDK available from Microsoft.
#include "hidsdi.h"

#include <setupapi.h>
}

#pragma comment(lib,"hid")
#pragma comment(lib,"setupapi")

class CHidusb
{
public:
	CHidusb();
	virtual ~CHidusb();

	BOOL CloseHandles(void);
	BOOL datadeal(char* pchar, int count);
	UINT Send(BYTE* pSendBytes, int number);
	UINT Recv(BYTE* pchar, ULONG delay_ms);
	BOOL OpenDev(HWND hwnd);
	BOOL CloseDev(void);

protected:

static DWORD RecvThread(LPVOID lpParamete);
	

private:
	DWORD								ActualBytesRead;
	DWORD								BytesRead;
	HIDP_CAPS							Capabilities;
	DWORD								cbBytesRead;
	PSP_DEVICE_INTERFACE_DETAIL_DATA	detailData;
	HANDLE								DeviceHandle;
	DWORD								dwError;
	char								FeatureReport[1024];
	HANDLE								hEventObject;
	HANDLE								hDevInfo;
	GUID								HidGuid;
	OVERLAPPED							HIDOverlapped;
	char								InputReport[1024];
	ULONG								Length;
	LPOVERLAPPED						lpOverLap;
	bool								MyDeviceDetected;
	CString								MyDevicePathName;
	DWORD								NumberOfBytesRead;
	char								OutputReport[1024];
	HANDLE								ReadHandle;
	DWORD								ReportType;
	ULONG								Required;
	CString								ValueToDisplay;
	HANDLE								WriteHandle;
	DWORD								counts;
	int									report;
	BYTE								buffertem[1024];
	int									gcount;
	BOOL								m_bDeviceNoficationRegistered;

	//These are the vendor and product IDs to look for.
	//Uses Lakeview Research's Vendor ID.
	int VendorID = 0x04B4;
	int ProductID = 0xA112;

	BYTE bSend_for_recv[1024];//只发送无返回的数据
};

#endif