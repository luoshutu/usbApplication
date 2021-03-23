// ����USB�豸
#include "usbDeviceManager.h"

//#pragma comment(linker,"/nodefaultlib:libcmt.lib")

CUSBDeviceManager::CUSBDeviceManager()
{
	m_bulkLoopingFlag	= false;
	m_deviceIndex		= 0;
	m_dataFillMethod	= 2;
	m_bulkLoopDataLen	= 1024;
	m_bulkLoopDataSeed	= 2;
}

CUSBDeviceManager::~CUSBDeviceManager()
{
	c_USBDevice->Close();
}

/*Summary
��ʼ��USB�豸����USB�豸��ע�ᡣ
*/
bool CUSBDeviceManager::InitDevice()
{
	c_USBDevice = new CCyUSBDevice(m_hWnd);
	bool isOk = Refresh();

	DEV_BROADCAST_DEVICEINTERFACE dbch;					// ���������豸��Ϣ
	dbch.dbcc_size = sizeof(dbch);
	dbch.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
	dbch.dbcc_classguid = gs_guidInterfaceList[0];		// USB�豸��GUID
	dbch.dbcc_name[0] = '\0';
	// ��ϵͳע�Ტ��ȡ������Ϣ
	m_NotificationHandle = RegisterDeviceNotification(m_hWnd, &dbch, DEVICE_NOTIFY_WINDOW_HANDLE);

	return isOk;
}

/*Summary
ˢ�£�ȷ����BulkLoop��ʽ��USB�豸���ڣ�����ȡ����
*/
bool CUSBDeviceManager::Refresh()
{
	// ����ڽ������ݷ���ѭ���������ö˵�
	if (m_bulkLoopingFlag)
	{
		c_InEndpt->Abort();
		c_InEndpt->Reset();
		c_OutEndpt->Abort();
		c_OutEndpt->Reset();
	}

	// ȷ������������һ��USB�豸
	std::cout << UINT(c_USBDevice->DeviceCount()) << std::endl;
	if (c_USBDevice->DeviceCount())
	{
		// ��������BulkLoop��ʽ��USB�豸������ӵ�����
		for (int i = 0; i < c_USBDevice->DeviceCount(); i++)
		{
			c_USBDevice->Open(i);

			//Get config descriptor
			USB_CONFIGURATION_DESCRIPTOR ConfDesc;
			c_USBDevice->GetConfigDescriptor(&ConfDesc);

			if (ConfDesc.bNumInterfaces == 1)	// Number of interface one
			{
				//Get Interface descriptor
				USB_INTERFACE_DESCRIPTOR IntfDesc;
				c_USBDevice->GetIntfcDescriptor(&IntfDesc);
				if (IntfDesc.bAlternateSetting == 0)
				{//
					//if(IntfDesc.bNumEndpoints==4)
					{
						m_deviceMap[i] = c_USBDevice->DeviceName;
						m_deviceIndex = i;
						return true;
					}
				}
			}
		}
	}

	return false;
}


/*Summary
usb�豸Map
*/
void CUSBDeviceManager::GetUSBDeviceMap(std::map<UINT, std::string> *deviceMap)
{
	*deviceMap = m_deviceMap;
}

/*Summary
ѡ��Ҫʹ�õ�USB�豸
*/
void CUSBDeviceManager::SelectDevice(UCHAR deviceNum)
{
	m_deviceIndex = deviceNum;
	c_USBDevice->Open(m_deviceIndex);

	int epts = c_USBDevice->EndPointCount();
	CCyUSBEndPoint *endpt;

	// Skip endpoint 0, which we know is the Control Endpoint
	for (int i = 1; i < epts; i++)
	{
		endpt = c_USBDevice->EndPoints[i];

		if (endpt->Attributes == 2)    // Bulk
		{
			char endptAddress[12];
			if (endpt->Address & 0x80)
			{
				snprintf(endptAddress, sizeof(endptAddress), "0x%02X", endpt->Address);
				//sprintf(endptAddress, "0x%02X", endpt->Address);
				std::cout << "m_inEndpt:" << endptAddress << std::endl;
			}
			else
			{
				//endptAddress = endpt->Address;
				snprintf(endptAddress, sizeof(endptAddress), "0x%02X", endpt->Address);
				std::cout << "m_outEndpt:" << endptAddress << std::endl;
			}
		}
	}

	c_OutEndpt = c_USBDevice->EndPoints[1];
	c_InEndpt = c_USBDevice->EndPoints[2];

	if (c_USBDevice->IsOpen())
	{
		m_bulkLoopingFlag = true;
	}
}

/*Summary
BulkLoop������������
*/
void CUSBDeviceManager::SetBulkLoopData(LONG len, int seed, int dataFillMethod)
{
	m_bulkLoopDataLen = len;
	m_bulkLoopDataSeed = seed;
	m_dataFillMethod = dataFillMethod;
}

/*Summary
BulkLoop��������
*/
void CUSBDeviceManager::SetBulkLoopData(LONG len, PUCHAR outData, PUCHAR inData)
{
	m_bulkLoopDataLen = len;
	m_bulkLoopOutData = outData;
	m_bulkLoopInData = inData;
}

/*Summary
��ʼѭ�����Ͳ���ȡ��������
*/
void CUSBDeviceManager::StartBulkLoopTestData()
{
	if (m_bulkLoopingFlag)
	{
		CBulkLoopDlg	c_BulkLoopDlg;
		c_BulkLoopDlg.InitBulkLoop(m_bulkLoopDataLen, m_bulkLoopDataSeed);
		c_BulkLoopDlg.StuffBuff(m_dataFillMethod);
		c_BulkLoopDlg.XferLoop(this);
		c_BulkLoopDlg.GetRXData(m_bulkLoopInData);
	}
}

/*Summary
��ʼѭ�����Ͳ���ȡ����
*/
void CUSBDeviceManager::StartBulkLoop()
{
	if (m_bulkLoopingFlag)
	{
		CBulkLoopDlg	c_BulkLoopDlg;
		c_BulkLoopDlg.InitBulkLoop(m_bulkLoopDataLen, m_bulkLoopDataSeed);
		c_BulkLoopDlg.SetTXData(m_bulkLoopOutData);
		c_BulkLoopDlg.XferLoop(this);
		c_BulkLoopDlg.GetRXData(m_bulkLoopInData);
	}
}
