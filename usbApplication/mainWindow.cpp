#include "mainWindow.h"

mainWindow::mainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	Init();
}

// ��ʼ��
void mainWindow::Init()
{
	// ���ݳ�ʼ��
	data = (UCHAR *)malloc(1024 * sizeof(UCHAR));
	memset(data, 12, 1024 * sizeof(UCHAR));		// �������ݻ���
	inData = (UCHAR *)malloc(1024 * sizeof(UCHAR));
	memset(inData, 0, 1024 * sizeof(UCHAR));	// �������ݻ���

	// ��ʼ��USB�豸
	InitUSBDeviceISOK = false;
	InitUSBDeviceISOK = InitDevice();

	if (InitUSBDeviceISOK)
	{
		GetUSBDeviceMap(&USBDeviceMap);
		for (UCHAR i = 0; i < USBDeviceMap.size(); i++)
		{
			qDebug() << QString("USBDeviceMap:%1").arg(i) << QString::fromStdString(USBDeviceMap[i]);
			ui.comboBoxUSBDeviceSelect->addItem(QString::fromStdString(USBDeviceMap[i]));
		}
		SelectDevice(0);
		SetBulkLoopData(1024, data, inData);
	}

	// ��ʼ����ʱ��
	m_timerUpdateDevice = new QTimer;
	//m_timerUpdateDevice->start(20);
	connect(m_timerUpdateDevice, SIGNAL(timeout()), this, SLOT(slot_updateComBoxDevice()));
}

// �����豸
void mainWindow::slot_updateComBoxDevice()
{

}

// ѡ���豸
void mainWindow::on_comboBoxUSBDeviceSelect_currentIndexChanged()
{
	if (InitUSBDeviceISOK)
	{
		int USBDeviceIndex = ui.comboBoxUSBDeviceSelect->currentIndex();
		qDebug() << "Select USBDevice :" << USBDeviceIndex << " " 
			<< QString::fromStdString(USBDeviceMap[USBDeviceIndex]) << endl;
		
		SelectDevice(USBDeviceIndex);
	}
}

// ��������������
void mainWindow::on_textEditTXData_textChanged()
{
	QString transData = ui.textEditTXData->toPlainText();
	
	for (int i = 0; i < transData.size(); i++)
	{
		data[i] = transData.toStdString()[i];
	}
	SetBulkLoopData(1024, data, inData);
	//SetBulkLoopTestData(1024, 5, 2);
}


// ��ʼLoop
void mainWindow::on_pushButtonStart_clicked()
{
	if (InitUSBDeviceISOK)
	{
		StartBulkLoop();
	}

	QString inputData = "";

	for (UCHAR i = 0; i < 32; i++)
	{
		inputData.append(QString("%1  ").arg(inData[i]));
	}

	ui.textBrowserRXData->append(inputData);
}

