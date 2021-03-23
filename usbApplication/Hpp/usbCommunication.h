#pragma once

#include <windows.h>
#include <QDebug>
#include <QMap>
#include <QObject>
#include "dataTransfer.h"

class CUSBCommu : public QObject
{
	Q_OBJECT;
public:
	CUSBCommu();
	~CUSBCommu();

private:

};
