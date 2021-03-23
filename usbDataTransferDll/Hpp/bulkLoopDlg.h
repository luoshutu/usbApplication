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
	// ����Ҫ����ϵͳ����һ�����ݣ���������һ��overlapped�Ķ�����
	// ������д�Ŵ�������ݵ�ƫ��λ�ã���ʼ���䣬������ȥ�ɱ����ȥ�ˡ�
	// ϵͳ��ɴ���ʹ���绰������hEvent����������
	OVERLAPPED	m_outOvLap;
	OVERLAPPED	m_inOvLap;
	PUCHAR		m_data;			// ���͵�����
	PUCHAR		m_inData;		// ���յ�������
	LONG		m_dataLen;		// ÿ�η������ݵĴ�С
	int			m_dataSeed;		// ��������

public:
	void	InitBulkLoop(LONG dataLen, int dataSeed);	// ���ò���������ʼ��BulkLoop״̬
	void	StuffBuff(int method);						// BulkLoopѭ�����͵����ݸ�ʽ��0Ϊ�㶨����1Ϊ�������2Ϊÿ�μ�һ�ĵ�������
	bool	XferLoop(LPVOID params);					// ʵ��һ��BulkLoopѭ��
	void	SetTXData(PUCHAR data);						// ����Ҫ���͵�����
	void	GetRXData(PUCHAR data);						// ��ȡ���յ�������
};

