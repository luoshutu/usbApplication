#pragma once
#include "bulkLoopDlg.h"
#include "usbDeviceManager.h"

extern"C" bool __declspec(dllexport) InitDevice();													// ��ʼ��USB�豸
extern"C" void __declspec(dllexport) SelectDevice(UCHAR deviceNum);									// ѡ�����ڴ������ݵ��豸
extern"C" void __declspec(dllexport) StartBulkLoopTest();											// ��ʼ����BulkLoop
extern"C" void __declspec(dllexport) StartBulkLoop();												// ��ʼ����BulkLoop
extern"C" void __declspec(dllexport) SetBulkLoopTestData(LONG len, int seed, int dataFillMethod);	// ���ò�������
extern"C" void __declspec(dllexport) SetBulkLoopData(LONG len, PUCHAR outData, PUCHAR inData);		// BulkLoop��������
extern"C" void __declspec(dllexport) GetUSBDeviceMap(std::map<UINT, std::string> *deviceMap);		// ��ȡUSB�豸Map

