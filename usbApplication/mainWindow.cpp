#include "mainWindow.h"

mainWindow::mainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	bool ok = InitDevice();
	std::map<UINT, std::string> USBDeviceMap;
	GetUSBDeviceMap(&USBDeviceMap);

	qDebug() << QString::fromStdString( USBDeviceMap[0] );

	if (ok)
	{
		PUCHAR data = (UCHAR *)malloc(1024 * sizeof(UCHAR));
		memset(data, 12, 1024 * sizeof(UCHAR));		// 发射数据缓存
		PUCHAR inData = (UCHAR *)malloc(1024 * sizeof(UCHAR));
		memset(inData, 0, 1024 * sizeof(UCHAR));		// 发射数据缓存
		
		SelectDevice(0);
		SetBulkLoopData(1024, data, inData);
		SetBulkLoopTestData(1024, 5, 2);
		//StartBulkLoopTest();
		StartBulkLoop();
		for (int i = 0; i < 10; i++)
		{
			qDebug() << inData[i];
		}
	}
}
