#include "stdafx.h"
#include "Hidusb.h"

CHidusb::CHidusb()
{
	NumberOfBytesRead = NULL;
	InputReport[0] = NULL;
	ReadHandle = NULL;
	buffertem[1024] = { 0 };
	bSend_for_recv[1024] = { 0 };
	gcount = NULL;
	MyDeviceDetected = FALSE;
}

CHidusb::~CHidusb()
{
	NumberOfBytesRead = NULL;
	InputReport[0] = NULL;
	ReadHandle = NULL;
	buffertem[1024] = { 0 };
	bSend_for_recv[1024] = { 0 };
	gcount = NULL;
	MyDeviceDetected = FALSE;
}

/*
*�������ƣ�CloseHandles()
*�������ܣ��ڹر��豸ʱ���ر��豸�������������ڴ�й©
*����˵������
*/
BOOL CHidusb::CloseHandles(void)
{
	//Close open handles.

	if (DeviceHandle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(DeviceHandle);
	}

	if (ReadHandle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(ReadHandle);
	}

	if (WriteHandle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(WriteHandle);
	}
	return TRUE;
}

/*
*�������ƣ�datadeal
*�������ܣ���usb���������̺߳��������Դ����ص�����
*����˵����char* pchar
*		   int count	
*/
BOOL CHidusb::datadeal(char* pchar, int count)//���ݴ���
{
	if (count < 0) count = 0;
	memcpy(&buffertem[gcount], pchar + 1, count);
	gcount += count;
	return TRUE;
}

/*
*�������ƣ�RecvThread
*�������ܣ�usb���������̺߳���
*����˵����LPVOID lpParamete  //�̲߳���
*ע�⣺	   ʹ�����еĲ���ʱ�����뽨���߳�ָ��
*/
DWORD CHidusb::RecvThread(LPVOID lpParamete)//���շ�����Ϣ�߳�
{
	HANDLE hEvent = NULL;
	CHidusb *pParamete = (CHidusb *)lpParamete;

	while (1)
	{
		DWORD	Result = 0;
		char send_dat[1024] = { 0 };
		hEvent = NULL;
		hEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
		pParamete->HIDOverlapped.Internal = 0;
		pParamete->HIDOverlapped.InternalHigh = 0;
		pParamete->HIDOverlapped.Offset = pParamete->Capabilities.InputReportByteLength;
		pParamete->HIDOverlapped.Offset = 0;
		pParamete->HIDOverlapped.OffsetHigh = 0;
		pParamete->HIDOverlapped.hEvent = hEvent;

		if (pParamete->ReadHandle != INVALID_HANDLE_VALUE)
		{
			Result = ReadFile
			(pParamete->ReadHandle,
				pParamete->InputReport,
				pParamete->Capabilities.InputReportByteLength,
				&pParamete->NumberOfBytesRead,
				(LPOVERLAPPED)&pParamete->HIDOverlapped);
		}
		else
		{
			continue;
		}
		DWORD dwError = GetLastError();

		Result = WaitForSingleObject(hEvent, 1000);

		switch (Result)
		{
		case WAIT_OBJECT_0:
		{
			DWORD dresult = GetOverlappedResult(pParamete->ReadHandle, &pParamete->HIDOverlapped, &pParamete->NumberOfBytesRead, FALSE);
			if (dresult)
			{
				memcpy(send_dat, pParamete->InputReport, pParamete->NumberOfBytesRead);
				pParamete->datadeal(send_dat, pParamete->NumberOfBytesRead - 1);

				Result = CancelIo(pParamete->ReadHandle);
				ResetEvent(hEvent);
				memset(pParamete->InputReport, 0, 1024);
			}
			break;
		}
		case WAIT_TIMEOUT:
		{
			pParamete->datadeal(NULL, 0);
			pParamete->ValueToDisplay.Format("%s", "ReadFile timeout");
			Result = CancelIo(pParamete->ReadHandle);
			ResetEvent(hEvent);
			break;
		}
		default:
		{
			pParamete->ValueToDisplay.Format("%s", "Undefined error");
			Result = CancelIo(pParamete->ReadHandle);
			ResetEvent(hEvent);
			break;
		}
		}
		CloseHandle(hEvent);//����hEvent�߳̾������Ҫ�رգ�
	}
	return 0;
}

/*
*�������ƣ�Send
*�������ܣ����豸����ָ��������
*����˵����unsigned char* pSendBytes  //��Ҫ���͵�����
*		   int number            //�������ݵ��ֽ���
*/
UINT CHidusb::Send(BYTE* pSendBytes, int number)//���͵�ָ��
{
	DWORD	BytesWritten = 0;
	ULONG	Result;
	BYTE	send_buffer[1024] = { 0 };
	CString	strBytesWritten = "";
	
	memset(bSend_for_recv, 1024, 0);

	for (int i = 0; i < number; i++)
	{
		send_buffer[i+1] = pSendBytes[i];
		bSend_for_recv[i] = pSendBytes[i];
	}

	unsigned char Send_buf[65] = { 0 };

	if (number >= 62) //�������ӷ���
	{
		memcpy(Send_buf, &send_buffer[0], 65);
		report = 0;
		if (report)
		{
			if (WriteHandle != INVALID_HANDLE_VALUE)
			{
				Result = HidD_SetOutputReport
				(WriteHandle,
					OutputReport,
					Capabilities.OutputReportByteLength);
			}
			if (!Result)
			{
				CloseHandles();
				MyDeviceDetected = FALSE;
			}

		}
		else
		{
			if (WriteHandle != INVALID_HANDLE_VALUE)
			{
				Result = WriteFile
				(WriteHandle,
					Send_buf,
					Capabilities.OutputReportByteLength,
					&BytesWritten,
					NULL);
			}
			if (!Result)
			{
				CancelIo(WriteHandle);
				int ierror = GetLastError();
			}
		}
		memset(Send_buf, 0, 65);

		int num_N = (number - 61) / 64;

		if (num_N == 0)
		{
			memcpy(&Send_buf[1], &send_buffer[65], 64);

			report = 0;
			if (report)
			{
				if (WriteHandle != INVALID_HANDLE_VALUE)
				{
					Result = HidD_SetOutputReport
					(WriteHandle,
						OutputReport,
						Capabilities.OutputReportByteLength);
				}
				if (!Result)
				{
					CloseHandles();
					MyDeviceDetected = FALSE;
				}

			}
			else
			{
				if (WriteHandle != INVALID_HANDLE_VALUE)
				{
					Result = WriteFile
					(WriteHandle,
						Send_buf,
						Capabilities.OutputReportByteLength,
						&BytesWritten,
						NULL);
				}
				if (!Result)
				{
					CancelIo(WriteHandle);
					int ierror = GetLastError();
				}
			}
			memset(Send_buf, 0, 65);
		}
		else
		{
			if (((number - 61) % 64) != 0) num_N = num_N + 1;

			for (int num_1 = 0; num_1<num_N; num_1++)
			{
				memcpy(&Send_buf[1], &send_buffer[65 + 64 * num_1], 64);

				if (report)
				{
					if (WriteHandle != INVALID_HANDLE_VALUE)
					{
						Result = HidD_SetOutputReport
						(WriteHandle,
							OutputReport,
							Capabilities.OutputReportByteLength);
					}
					if (!Result)
					{
						CloseHandles();
						MyDeviceDetected = FALSE;
					}

				}
				else
				{
					if (WriteHandle != INVALID_HANDLE_VALUE)
					{
						Result = WriteFile
						(WriteHandle,
							Send_buf,
							Capabilities.OutputReportByteLength,
							&BytesWritten,
							NULL);
					}
					if (!Result)
					{
						CancelIo(WriteHandle);
						int ierror = GetLastError();
					}
				}
				memset(Send_buf, 0, 65);
			}
		}
	}
	else//�������ݵ�������
	{
		report = 0;
		if (report)
		{
			if (WriteHandle != INVALID_HANDLE_VALUE)
			{
				Result = HidD_SetOutputReport
				(WriteHandle,
					OutputReport,
					Capabilities.OutputReportByteLength);
			}
			if (!Result)
			{
				CloseHandles();
				MyDeviceDetected = FALSE;
			}

		}
		else
		{
			if (WriteHandle != INVALID_HANDLE_VALUE)
			{
				Result = WriteFile
				(WriteHandle,
					send_buffer,
					Capabilities.OutputReportByteLength,
					&BytesWritten,
					NULL);
			}
			if (!Result)
			{
				CancelIo(WriteHandle);
				int ierror = GetLastError();
			}
		}
		memset(send_buffer, 0, 65);
	}
	return TRUE;
}

/*
*�������ƣ�Recv
*�������ܣ������豸���ص�����
*����˵����unsigned char* pRecvBytes    //���ݻ�����
*		   unsigned long delay_ms //���õȴ���ʱ
*/
UINT CHidusb::Recv(BYTE* pRecvBytes, ULONG delay_ms)
{
	int i_Len_Data = 0, j = 0;
	unsigned char read_buffer[1024] = { 0 };

	if (bSend_for_recv[0] == 0x16)
	{
		gcount = 0;
		return 0;
	}

	if (delay_ms <10)
	{
		while (1)
		{
			::Sleep(1);
			j++;
			if (buffertem[0] != 0 && ((buffertem[1] + 2) / gcount) == 0) break;//�ȴ��������ݰ������������ѭ��
			if (j == 200) break;//��ʱ�ȴ�
		}
	}
	else ::Sleep(delay_ms);//�Զ���ȴ���ʱ

	if (gcount == 0)return -1;//��Ƭ��Ӧ��

	memcpy_s(read_buffer, 1024, buffertem, gcount);
	memset(buffertem, 0, 1024);		//������� ���´ν���ʹ��

	i_Len_Data = read_buffer[1];//����LC

	for (int i = 0; i < 1024; i++)
	{
		pRecvBytes[i] = read_buffer[i];
	}

	gcount = 0;
	return i_Len_Data;
}

/*
*�������ƣ�OpenDev
*�������ܣ����豸
*����˵����HWND hwnd //���봰�ھ��
*����ֵ��  ������������TRUE����֮����ֵΪ״̬�룬�京�������ֵ˵����
*ע��      ��16λWindows���������еĶ�̬���ӿ⡢DOS���������еľ�̬�����ⷵ�ص��豸�����
*		   �京�����ͬ��32λWindows�����¶�̬���ӿⷵ�ص��豸�������Ϊ�����豸֮�á�
*/
BOOL CHidusb::OpenDev(HWND hwnd)//���豸
{
	//Use a series of API calls to find a HID with a specified Vendor IF and Product ID.
	HIDD_ATTRIBUTES						Attributes;
	DWORD								DeviceUsage;
	SP_DEVICE_INTERFACE_DATA			devInfoData;
	bool								LastDevice = FALSE;
	int									MemberIndex = 0;
	LONG								Result;
	CString								UsageDescription;

	Length = 0;
	detailData = NULL;
	DeviceHandle = NULL;

	HidD_GetHidGuid(&HidGuid);

	hDevInfo = SetupDiGetClassDevs
	(&HidGuid,
		NULL,
		NULL,
		DIGCF_PRESENT | DIGCF_INTERFACEDEVICE);

	devInfoData.cbSize = sizeof(devInfoData);

	//Step through the available devices looking for the one we want. 
	//Quit on detecting the desired device or checking all available devices without success.

	MemberIndex = 0;
	LastDevice = FALSE;


	do
	{

		Result = SetupDiEnumDeviceInterfaces
		(hDevInfo,
			0,
			&HidGuid,
			MemberIndex,
			&devInfoData);

		if (Result != 0)
		{
			//A device has been detected, so get more information about it.

			//Get the Length value.
			//The call will return with a "buffer too small" error which can be ignored.

			Result = SetupDiGetDeviceInterfaceDetail
			(hDevInfo,
				&devInfoData,
				NULL,
				0,
				&Length,
				NULL);

			//Allocate memory for the hDevInfo structure, using the returned Length.

			detailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(Length);

			//Set cbSize in the detailData structure.

			detailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

			//Call the function again, this time passing it the returned buffer size.

			Result = SetupDiGetDeviceInterfaceDetail
			(hDevInfo,
				&devInfoData,
				detailData,
				Length,
				&Required,
				NULL);

			// Open a handle to the device.
			// To enable retrieving information about a system mouse or keyboard,
			// don't request Read or Write access for this handle.

			DeviceHandle = CreateFile
			(detailData->DevicePath,
				0,
				FILE_SHARE_READ | FILE_SHARE_WRITE,
				(LPSECURITY_ATTRIBUTES)NULL,
				OPEN_EXISTING,
				0,
				NULL);

			//Set the Size to the number of bytes in the structure.

			Attributes.Size = sizeof(Attributes);

			Result = HidD_GetAttributes
			(DeviceHandle,
				&Attributes);

			//Is it the desired device?

			MyDeviceDetected = FALSE;

			if (m_bDeviceNoficationRegistered == FALSE)
			{

				//Register to receive device notifications.

				DEV_BROADCAST_DEVICEINTERFACE DevBroadcastDeviceInterface;

				ZeroMemory(&DevBroadcastDeviceInterface, sizeof(DevBroadcastDeviceInterface));
				DevBroadcastDeviceInterface.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);
				DevBroadcastDeviceInterface.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
				DevBroadcastDeviceInterface.dbcc_classguid = HidGuid;


				HDEVNOTIFY DeviceNotificationHandle = RegisterDeviceNotification(hwnd, &DevBroadcastDeviceInterface, DEVICE_NOTIFY_WINDOW_HANDLE);

				m_bDeviceNoficationRegistered = TRUE;

			}

			if (Attributes.VendorID == VendorID)
			{
				if (Attributes.ProductID == ProductID)
				{
					//Both the Vendor ID and Product ID match.

					MyDeviceDetected = TRUE;
					MyDevicePathName = detailData->DevicePath;

					//Get the device's capablities.

					PHIDP_PREPARSED_DATA	PreparsedData;

					HidD_GetPreparsedData
					(DeviceHandle,
						&PreparsedData);


					HidP_GetCaps
					(PreparsedData,
						&Capabilities);



					HidD_FreePreparsedData(PreparsedData);

					DeviceUsage = (Capabilities.UsagePage * 256) + Capabilities.Usage;

					if (DeviceUsage == 0x102)
					{
						UsageDescription = "mouse";
					}

					if (DeviceUsage == 0x106)
					{
						UsageDescription = "keyboard";
					}

					// Get a handle for writing Output reports.

					WriteHandle = CreateFile
					(detailData->DevicePath,
						GENERIC_WRITE,
						FILE_SHARE_READ | FILE_SHARE_WRITE,
						(LPSECURITY_ATTRIBUTES)NULL,
						OPEN_EXISTING,
						0,
						NULL);

					// Prepare to read reports using Overlapped I/O.

					ReadHandle = CreateFile
					(detailData->DevicePath,
						GENERIC_READ,
						FILE_SHARE_READ | FILE_SHARE_WRITE,
						(LPSECURITY_ATTRIBUTES)NULL,
						OPEN_EXISTING,
						FILE_FLAG_OVERLAPPED,
						NULL);

				} //if (Attributes.ProductID == ProductID)

				else
					//The Product ID doesn't match.

					CloseHandle(DeviceHandle);

			} //if (Attributes.VendorID == VendorID)

			else
				//The Vendor ID doesn't match.

				CloseHandle(DeviceHandle);

			//Free the memory used by the detailData structure (no longer needed).

			free(detailData);

		}  //if (Result != 0)

		else
			//SetupDiEnumDeviceInterfaces returned 0, so there are no more devices to check.

			LastDevice = TRUE;

		MemberIndex++;

	} //do
	while ((LastDevice == FALSE) && (MyDeviceDetected == FALSE));

	SetupDiDestroyDeviceInfoList(hDevInfo);

	HANDLE hThread = NULL;

	hThread = CreateThread(NULL, NULL,(LPTHREAD_START_ROUTINE)RecvThread,this, 0, 0);

	CloseHandle(hThread);

	if (NULL == hThread)
	{
		return FALSE;
	}

	hThread = NULL;

	if (MyDeviceDetected == FALSE)
	{
		return FALSE;//USB���Ӵ���
	}
	else return TRUE;
}

/*
�������ƣ�CloseDev
�������ܣ��ر��豸
*/
BOOL CHidusb::CloseDev(void)//�ر��豸
{
	if (MyDeviceDetected == TRUE)
	{
			CloseHandles();
			MyDeviceDetected = FALSE;
			return TRUE;
	}
	else return FALSE;
}