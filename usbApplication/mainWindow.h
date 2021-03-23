#pragma once

#include <windows.h>
#include <QtWidgets/QMainWindow>
#include "ui_mainWindow.h"
#include <QDebug>
#include <QMap>
#include "./Hpp/dataTransfer.h"

class mainWindow : public QMainWindow
{
    Q_OBJECT

public:
    mainWindow(QWidget *parent = Q_NULLPTR);

private:
    Ui::mainWindowClass ui;
};
