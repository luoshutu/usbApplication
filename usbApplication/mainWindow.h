#pragma once

#include <windows.h>
#include <QtWidgets/QMainWindow>
#include "ui_mainWindow.h"
#include <QDebug>
#include <QMap>
#include <QTimer>
#include <string>
#include ".\Hpp\dataTransfer.h"

class mainWindow : public QMainWindow
{
    Q_OBJECT

public:
    mainWindow(QWidget *parent = Q_NULLPTR);
	void Init();

public slots:
	void on_pushButtonStart_clicked();
	void on_comboBoxUSBDeviceSelect_currentIndexChanged();
	void on_textEditTXData_textChanged();

	void slot_updateComBoxDevice();

private:
	bool InitUSBDeviceISOK;

	PUCHAR data;		// �������
	PUCHAR inData;		// ��������

	std::map<UINT, std::string> USBDeviceMap;		// USB�豸Map
	QTimer *m_timerUpdateDevice;					// ��ʱ��������USB�豸��ʾ

private:
    Ui::mainWindowClass ui;
};
