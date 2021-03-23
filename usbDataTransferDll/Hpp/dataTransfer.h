#pragma once
#include "bulkLoopDlg.h"
#include "usbDeviceManager.h"

extern"C" bool __declspec(dllexport) InitDevice();													// 初始化USB设备
extern"C" void __declspec(dllexport) SelectDevice(UCHAR deviceNum);									// 选择用于传输数据的设备
extern"C" void __declspec(dllexport) StartBulkLoopTest();											// 开始进行BulkLoop
extern"C" void __declspec(dllexport) StartBulkLoop();												// 开始进行BulkLoop
extern"C" void __declspec(dllexport) SetBulkLoopTestData(LONG len, int seed, int dataFillMethod);	// 设置测试数据
extern"C" void __declspec(dllexport) SetBulkLoopData(LONG len, PUCHAR outData, PUCHAR inData);		// BulkLoop数据设置
extern"C" void __declspec(dllexport) GetUSBDeviceMap(std::map<UINT, std::string> *deviceMap);		// 获取USB设备Map

