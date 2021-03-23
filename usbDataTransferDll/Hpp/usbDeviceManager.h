#pragma once
#ifndef _USBDEVICEMANAGER_H_
#define _USBDEVICEMANAGER_H_

#include "pch.h"
#include "CyAPI.h"
#include "bulkLoopDlg.h"
#include <initguid.h>
#include <map>
#include <string>
#include <iostream>

// ȫ�־�̬�������飬�洢GUID��
static const GUID gs_guidInterfaceList[] =
{
	{ 0xa5dcbf10, 0x6530, 0x11d2, { 0x90, 0x1f, 0x00, 0xc0, 0x4f, 0xb9, 0x51, 0xed } },	// USB�豸
	{ 0x53f56307, 0xb6bf, 0x11d0, { 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b } }, // DISK
	{ 0x4d1e55b2, 0xf16f, 0x11Cf, { 0x88, 0xcb, 0x00, 0x11, 0x11, 0x00, 0x00, 0x30 } }, // HID
	{ 0xad498944, 0x762f, 0x11d0, { 0x8d, 0xcb, 0x00, 0xc0, 0x4f, 0xc3, 0x35, 0x8c } }, // GUID_NDIS_LAN_CLASS
	{ 0x219d0508, 0x57a8, 0x4ff5, { 0x97, 0xa1, 0xbd, 0x86, 0x58, 0x7c, 0x6c, 0x7e } },
	{0x86e0d1e0L, 0x8089, 0x11d0, { 0x9c, 0xe4, 0x08, 0x00, 0x3e, 0x30, 0x1f, 0x73 } },
};

// ����USB�豸
class CUSBDeviceManager
{
public:
	CUSBDeviceManager();
	~CUSBDeviceManager();

// USB����
private:
	int							m_deviceIndex;			// USB�豸�������
	HDEVNOTIFY					m_NotificationHandle;	// USB�豸��ע��֪ͨ���
	HWND						m_hWnd;					// USB�豸�Ĵ����ھ��
	std::map<UINT, std::string>	m_deviceMap;			// �����������������USB�豸
	
private:
	CCyUSBDevice	*c_USBDevice;			// USB�豸

public:
	CCyUSBEndPoint	*c_OutEndpt;			// USB�豸������˵㣬������������������
	CCyUSBEndPoint	*c_InEndpt;				// USB�豸������˵㣬�������������������

// BulkLoop
private:
	LONG			m_bulkLoopDataLen;		// BulkLoopÿ�η������ݵĳ���
	int				m_dataFillMethod;		// BulkLoopѭ�����͵Ĳ������ݸ�ʽ��0Ϊ�㶨����1Ϊ�������2Ϊÿ�μ�һ�ĵ�������
	int				m_bulkLoopDataSeed;		// BulkLoopÿ�η��Ͳ������ݵ�����
	PUCHAR			m_bulkLoopOutData;		// BulkLoopÿ�η��͵�����
	PUCHAR			m_bulkLoopInData;		// BulkLoopÿ�ν��յ�����

public:
	bool			m_bulkLoopingFlag;		// �Ƿ���BulkLoopѭ���ı�־

// ��Ա����
public:
	bool	InitDevice();												// ��ʼ��USB�豸
	bool	Refresh();													// ȷ����BulkLoop��ʽ��USB�豸���ڣ�����ȡ����
	void	GetUSBDeviceMap(std::map<UINT, std::string> *deviceMap);	// ��ȡUSB�豸Map
	void	SelectDevice(UCHAR deviceNum);								// ѡ��USB�豸
	void	StartBulkLoopTestData();									// ��ʼ���ݴ���
	void	StartBulkLoop();											// ��ʼ���ݴ���
	void	SetBulkLoopData(LONG len, int seed, int dataFillMethod);	// ���ò�������
	void	SetBulkLoopData(LONG len, PUCHAR outData, PUCHAR inData);	// BulkLoop��������
};

#endif // _USBDEVICEMANAGER_H_
