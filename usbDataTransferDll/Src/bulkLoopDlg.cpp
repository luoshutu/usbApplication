// BulkLoopDlg.cpp : 实现bulkLoop

#include "bulkLoopDlg.h"

CBulkLoopDlg::CBulkLoopDlg()
{
	m_dataLen	= 1024;
	m_dataSeed	= 2;
}

CBulkLoopDlg::~CBulkLoopDlg()
{
	CloseHandle(m_outOvLap.hEvent);
	CloseHandle(m_inOvLap.hEvent);
}

/*Summary
设置参数，并初始化BulkLoop状态
*/
void CBulkLoopDlg::InitBulkLoop(LONG dataLen, int dataSeed )
{
	m_dataLen	= dataLen;
	m_dataSeed	= dataSeed;

	m_data = (UCHAR *)malloc(m_dataLen * sizeof(UCHAR));
	memset(m_data, 0, m_dataLen * sizeof(UCHAR));		// 发射数据缓存
	m_inData = (UCHAR *)malloc(m_dataLen * sizeof(UCHAR));
	memset(m_inData, 0, m_dataLen * sizeof(UCHAR));	// 接收的数据缓存区

	m_outOvLap.hEvent = CreateEvent(NULL, false, false, LPCWSTR("OUT"));
	m_inOvLap.hEvent = CreateEvent(NULL, false, false, LPCWSTR("IN"));
}

/*Summary
设置要发送的数据
*/
void CBulkLoopDlg::SetTXData(PUCHAR data)
{
	memcpy(m_data, data, m_dataLen * sizeof(UCHAR));
}

/*Summary
获取接收到的数据
*/
void CBulkLoopDlg::GetRXData(PUCHAR data)
{
	memcpy(data, m_inData, m_dataLen * sizeof(UCHAR));
}

/*Summary
循环发送的数据的缓存，选择一种方法确定缓存中的数据形式
0为恒定数；
1为随机数；
2为每次加一的递增序列；
*/
void CBulkLoopDlg::StuffBuff(int method) 
{
    DWORD *dwBuf = (DWORD *)m_data;
    srand((UINT)m_dataSeed);

    int cnt = (method == 3) ? m_dataLen / 4 : m_dataLen;
    for (int i=0; i<cnt; i++) {
		switch (method) {
		case 0:
			m_data[i] = (CHAR)m_dataSeed;
			break;
		case 1:
			m_data[i] = rand();
			break;
		case 2:
			m_data[i] = (UCHAR)m_dataSeed + i;
			break;
		case 3:
			dwBuf[i] = m_dataSeed + i;
			break;
		}
    }

}

/*Summary
BulkLooping函数
*/
bool CBulkLoopDlg::XferLoop(LPVOID params) 
{
	CUSBDeviceManager *c_USBDevice = (CUSBDeviceManager *)params;
	bool success = false;

	if (c_USBDevice->m_bulkLoopingFlag) 
	{
		c_USBDevice->c_OutEndpt->TimeOut = 2000;
		c_USBDevice->c_InEndpt->TimeOut = 2000;

		LONG outlen, inlen, len;
		outlen = inlen = len = m_dataLen;     // Use temp var because XferData can change the value of len

		UCHAR  *outContext = c_USBDevice->c_OutEndpt->BeginDataXfer(m_data, outlen, &m_outOvLap);
		UCHAR  *inContext = c_USBDevice->c_InEndpt->BeginDataXfer(m_inData, inlen, &m_inOvLap);

		c_USBDevice->c_OutEndpt->WaitForXfer(&m_outOvLap, 20);
		c_USBDevice->c_InEndpt->WaitForXfer(&m_inOvLap, 20);

		success = c_USBDevice->c_OutEndpt->FinishDataXfer(m_data, outlen, &m_outOvLap, outContext);
		success = c_USBDevice->c_InEndpt->FinishDataXfer(m_inData, inlen, &m_inOvLap, inContext);

		if (success) {
			bool pass = (memcmp(m_data, m_inData, len) == 0);
			if (pass)
			{
				/*for (int i = 0; i < 5; i++)
				{
					printf("data[%d] is %d \n", i, m_data[i]);
					printf("inData[%d] is %d \n", i, m_inData[i]);
				}*/
				return true;
			}
			else
				return false;
		}
		else
			return false;
	}
}

