#pragma once

extern"C" bool __declspec(dllexport) InitDevice();																// 初始化USB设备
extern"C" void __declspec(dllexport) SelectDevice(unsigned char deviceNum);										// 选择用于传输数据的设备
extern"C" void __declspec(dllexport) StartBulkLoopTest();														// 开始进行BulkLoop
extern"C" void __declspec(dllexport) StartBulkLoop();															// 开始进行BulkLoop
extern"C" void __declspec(dllexport) SetBulkLoopTestData(long len, int seed, int dataFillMethod);				// 设置测试数据
extern"C" void __declspec(dllexport) SetBulkLoopData(long len, unsigned char *outData, unsigned char *inData);	// BulkLoop数据设置
extern"C" void __declspec(dllexport) GetUSBDeviceMap(std::map<unsigned int, std::string> *deviceMap);			// 获取USB设备Map
