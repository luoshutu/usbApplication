// ��Ľӿں���
# include "dataTransfer.h"

CUSBDeviceManager c_USBDeviceManager;

bool InitDevice()
{
	bool ok = c_USBDeviceManager.InitDevice();
	return ok;
}

// ��ȡUSB�豸Map
void GetUSBDeviceMap(std::map<UINT, std::string> *deviceMap)
{
	c_USBDeviceManager.GetUSBDeviceMap(deviceMap);
}

// ѡ�����ڴ������ݵ��豸
void SelectDevice(UCHAR deviceNum)		
{
	c_USBDeviceManager.SelectDevice(deviceNum);
}

// ��ʼ����BulkLoop,�շ���������
void StartBulkLoopTest()
{
	c_USBDeviceManager.StartBulkLoopTestData();
}

// ��ʼ����BulkLoop
void StartBulkLoop()
{
	c_USBDeviceManager.StartBulkLoop();
}

// ���ò�������
void SetBulkLoopTestData(LONG len, int seed, int dataFillMethod)
{
	c_USBDeviceManager.SetBulkLoopData(len, seed, dataFillMethod);
}

// BulkLoop��������
void SetBulkLoopData(LONG len, PUCHAR outData, PUCHAR inData)
{
	c_USBDeviceManager.SetBulkLoopData(len, outData, inData);
}

