#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <QString>
#include <QThread>
#include <QMap>
#include <QMetaType>
#include <QDebug>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include "lib/mavlink/standard/mavlink.h"
#include "telemetryserial.h"
#include "telemetrysocket.h"

class Telemetry : public QThread
{
  Q_OBJECT

public:
  explicit Telemetry(QObject *parent = 0, bool b = false);
  ~Telemetry();
  bool Stop;

signals:
  void valueChanged(QList<QString>);
  void messageEmitted(QString);

protected:
  void run();

private:
  void initSerial();

  struct termios m_toptions;
  int m_openSerial;


  QString m_typeConnexion;
  QString m_telemetryMessage;
  int m_telemetryLength;

  char *m_telemetryData;

  mavlink_message_t m_mavlinkMessage;
  mavlink_status_t m_mavlinkStatus;
  mavlink_status_t lastStatus;

  int m_mavlinkMsgReceived;
  int m_mavlinkMsgReadyToDecode;

  char m_buffer;

  int m_mavlinkAutopilot;
  int m_mavlinkBasemode;
  int m_mavlinkCustommode;
  int m_mavlinkVersion;
  int m_mavlinkSystemstatus;
  int m_mavlinkType;

  float m_mavlinkX;
  float m_mavlinkY;
  float m_mavlinkZ;

  float m_mavlinkGx;
  float m_mavlinkGy;
  float m_mavlinkGz;

  QSerialPort *m_serialPort;

  QString m_mavlinkLatitude;
  QString m_mavlinkLongitude;
  float m_mavlinkAltitude;

  QList<QString> m_mavlinkData;
};

#endif // TELEMETRY_H
