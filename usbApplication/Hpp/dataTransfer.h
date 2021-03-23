#pragma once

extern"C" bool __declspec(dllexport) InitDevice();																// ��ʼ��USB�豸
extern"C" void __declspec(dllexport) SelectDevice(unsigned char deviceNum);										// ѡ�����ڴ������ݵ��豸
extern"C" void __declspec(dllexport) StartBulkLoopTest();														// ��ʼ����BulkLoop
extern"C" void __declspec(dllexport) StartBulkLoop();															// ��ʼ����BulkLoop
extern"C" void __declspec(dllexport) SetBulkLoopTestData(long len, int seed, int dataFillMethod);				// ���ò�������
extern"C" void __declspec(dllexport) SetBulkLoopData(long len, unsigned char *outData, unsigned char *inData);	// BulkLoop��������
extern"C" void __declspec(dllexport) GetUSBDeviceMap(std::map<unsigned int, std::string> *deviceMap);			// ��ȡUSB�豸Map
