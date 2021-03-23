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

// 全局静态常量数组，存储GUID码
static const GUID gs_guidInterfaceList[] =
{
	{ 0xa5dcbf10, 0x6530, 0x11d2, { 0x90, 0x1f, 0x00, 0xc0, 0x4f, 0xb9, 0x51, 0xed } },	// USB设备
	{ 0x53f56307, 0xb6bf, 0x11d0, { 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b } }, // DISK
	{ 0x4d1e55b2, 0xf16f, 0x11Cf, { 0x88, 0xcb, 0x00, 0x11, 0x11, 0x00, 0x00, 0x30 } }, // HID
	{ 0xad498944, 0x762f, 0x11d0, { 0x8d, 0xcb, 0x00, 0xc0, 0x4f, 0xc3, 0x35, 0x8c } }, // GUID_NDIS_LAN_CLASS
	{ 0x219d0508, 0x57a8, 0x4ff5, { 0x97, 0xa1, 0xbd, 0x86, 0x58, 0x7c, 0x6c, 0x7e } },
	{0x86e0d1e0L, 0x8089, 0x11d0, { 0x9c, 0xe4, 0x08, 0x00, 0x3e, 0x30, 0x1f, 0x73 } },
};

// 管理USB设备
class CUSBDeviceManager
{
public:
	CUSBDeviceManager();
	~CUSBDeviceManager();

// USB控制
private:
	int							m_deviceIndex;			// USB设备索引编号
	HDEVNOTIFY					m_NotificationHandle;	// USB设备的注册通知句柄
	HWND						m_hWnd;					// USB设备的处理窗口句柄
	std::map<UINT, std::string>	m_deviceMap;			// 存放所有满足条件的USB设备
	
private:
	CCyUSBDevice	*c_USBDevice;			// USB设备

public:
	CCyUSBEndPoint	*c_OutEndpt;			// USB设备的输出端点，相对于主机而言是输出
	CCyUSBEndPoint	*c_InEndpt;				// USB设备的输入端点，相对于主机而言是输入

// BulkLoop
private:
	LONG			m_bulkLoopDataLen;		// BulkLoop每次发送数据的长度
	int				m_dataFillMethod;		// BulkLoop循环发送的测试数据格式，0为恒定数，1为随机数，2为每次加一的递增序列
	int				m_bulkLoopDataSeed;		// BulkLoop每次发送测试数据的种子
	PUCHAR			m_bulkLoopOutData;		// BulkLoop每次发送的数据
	PUCHAR			m_bulkLoopInData;		// BulkLoop每次接收的数据

public:
	bool			m_bulkLoopingFlag;		// 是否开启BulkLoop循环的标志

// 成员函数
public:
	bool	InitDevice();												// 初始化USB设备
	bool	Refresh();													// 确保有BulkLoop方式的USB设备存在，并获取其编号
	void	GetUSBDeviceMap(std::map<UINT, std::string> *deviceMap);	// 获取USB设备Map
	void	SelectDevice(UCHAR deviceNum);								// 选择USB设备
	void	StartBulkLoopTestData();									// 开始数据传输
	void	StartBulkLoop();											// 开始数据传输
	void	SetBulkLoopData(LONG len, int seed, int dataFillMethod);	// 设置测试数据
	void	SetBulkLoopData(LONG len, PUCHAR outData, PUCHAR inData);	// BulkLoop数据设置
};

#endif // _USBDEVICEMANAGER_H_
