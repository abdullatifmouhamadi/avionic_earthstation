#ifndef TELEMETRYSERIAL_H
#define TELEMETRYSERIAL_H

#include <QSerialPort>
#include <QTextStream>
#include <QTimer>
#include <QByteArray>
#include <QObject>
#include <QString>
#include <QDebug>
#include "config.h"

class TelemetrySerial : public QObject
{
public:
  TelemetrySerial();
  char* getReadData();
  QString getMessage();
  int getLength();
  ~TelemetrySerial();

private slots:
  void handleReadyRead();
  void handleTimeout();
  void handleError(QSerialPort::SerialPortError error);

private:
  void initDataTelemetry();

  QSerialPort m_serialPort;
  char *m_readData;
  QTimer m_timer;
  Config m_config;

  QString m_configPort;
  QString m_configBaud;
  QString m_message;

  int m_length;
};

#endif // TELEMETRYSERIAL_H
