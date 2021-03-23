// 库的接口函数
# include "dataTransfer.h"

CUSBDeviceManager c_USBDeviceManager;

bool InitDevice()
{
	bool ok = c_USBDeviceManager.InitDevice();
	return ok;
}

// 获取USB设备Map
void GetUSBDeviceMap(std::map<UINT, std::string> *deviceMap)
{
	c_USBDeviceManager.GetUSBDeviceMap(deviceMap);
}

// 选择用于传输数据的设备
void SelectDevice(UCHAR deviceNum)		
{
	c_USBDeviceManager.SelectDevice(deviceNum);
}

// 开始进行BulkLoop,收发测试数据
void StartBulkLoopTest()
{
	c_USBDeviceManager.StartBulkLoopTestData();
}

// 开始进行BulkLoop
void StartBulkLoop()
{
	c_USBDeviceManager.StartBulkLoop();
}

// 设置测试数据
void SetBulkLoopTestData(LONG len, int seed, int dataFillMethod)
{
	c_USBDeviceManager.SetBulkLoopData(len, seed, dataFillMethod);
}

// BulkLoop数据设置
void SetBulkLoopData(LONG len, PUCHAR outData, PUCHAR inData)
{
	c_USBDeviceManager.SetBulkLoopData(len, outData, inData);
}

