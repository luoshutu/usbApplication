#pragma once

#include "pch.h"
#include "CyAPI.h"
#include "usbDeviceManager.h"
#include <initguid.h>

class CBulkLoopDlg
{
public:
	CBulkLoopDlg();
	~CBulkLoopDlg();

private:
	// 你需要操作系统传递一批数据，于是填了一个overlapped的订单，
	// 订单上写着从哪里（数据的偏移位置）开始传输，于是你去干别的事去了。
	// 系统完成传输就打个电话（激活hEvent）叫你验收
	OVERLAPPED	m_outOvLap;
	OVERLAPPED	m_inOvLap;
	PUCHAR		m_data;			// 发送的数据
	PUCHAR		m_inData;		// 接收到的数据
	LONG		m_dataLen;		// 每次发射数据的大小
	int			m_dataSeed;		// 数据种子

public:
	void	InitBulkLoop(LONG dataLen, int dataSeed);	// 设置参数，并初始化BulkLoop状态
	void	StuffBuff(int method);						// BulkLoop循环发送的数据格式，0为恒定数，1为随机数，2为每次加一的递增序列
	bool	XferLoop(LPVOID params);					// 实现一次BulkLoop循环
	void	SetTXData(PUCHAR data);						// 设置要发送的数据
	void	GetRXData(PUCHAR data);						// 获取接收到的数据
};

