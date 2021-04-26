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

	PUCHAR data;		// 输出数据
	PUCHAR inData;		// 输入数据

	std::map<UINT, std::string> USBDeviceMap;		// USB设备Map
	QTimer *m_timerUpdateDevice;					// 计时器，更新USB设备显示

private:
    Ui::mainWindowClass ui;
};
