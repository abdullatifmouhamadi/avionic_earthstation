#include "telemetry.h"

/**
 * Constructeur :
 * - On récupère le type de télémétrie par défaut
 * @brief Telemetry::Telemetry
 */
Telemetry::Telemetry(QObject *parent, bool b) :
  QThread(parent), Stop(b)
{
}

Telemetry::~Telemetry()
{
}

/**
 * Méthode run du thread
 * @brief Telemetry::run
 */
void Telemetry::run()
{
  initSerial();
  bool booExecuteTelemetry = true;
  int i = 0;

  while(booExecuteTelemetry) {
      uint8_t buffer[2041];
      mavlink_message_t message;
      mavlink_status_t status;
      int msgReceived;
      QList<QString> m_mavlinkData;

      msgReceived = read(m_openSerial, &buffer, 1);

      if (msgReceived > 0) {
          for (i = 0; i < msgReceived; ++i){
              m_mavlinkMsgReadyToDecode = mavlink_parse_char(MAVLINK_COMM_1,buffer[i], &message, &status);
            }
          memset(buffer, 0, 201);
        }

      // Si des informations sont à décoder
      if (m_mavlinkMsgReadyToDecode) {
          switch (message.msgid) {
            // HearBeat
            case MAVLINK_MSG_ID_HEARTBEAT:
              mavlink_heartbeat_t heartbeat;
              mavlink_msg_heartbeat_decode(&message, &heartbeat);

              m_mavlinkAutopilot = heartbeat.autopilot;
              m_mavlinkBasemode = heartbeat.base_mode;
              m_mavlinkCustommode = heartbeat.custom_mode;
              m_mavlinkVersion = heartbeat.mavlink_version;
              m_mavlinkSystemstatus = heartbeat.system_status;
              m_mavlinkType = heartbeat.type;

              break;
              // Data de la centrale inertielle
            case MAVLINK_MSG_ID_ATTITUDE:
              mavlink_attitude_t imu;
              mavlink_msg_attitude_decode(&message, &imu);

              m_mavlinkX = imu.pitch;
              m_mavlinkY = imu.roll;
              m_mavlinkZ = imu.yaw;
              m_mavlinkGx = imu.pitchspeed;
              m_mavlinkGy = imu.rollspeed;
              m_mavlinkGz = imu.yawspeed;

              break;
              // Data du GPS
            case MAVLINK_MSG_ID_GPS_RAW_INT:
              mavlink_global_position_int_t position;
              mavlink_msg_global_position_int_decode(&message, &position);

              m_mavlinkLatitude = position.lat;
              m_mavlinkLongitude = position.lon;
              m_mavlinkAltitude = position.alt;

              break;
            }

          // On prépare les informations avant de la envoyer au "emit"
          m_mavlinkData.append(QString::number(m_mavlinkAutopilot));
          m_mavlinkData.append(QString::number(m_mavlinkBasemode));
          m_mavlinkData.append(QString::number(m_mavlinkCustommode));
          m_mavlinkData.append(QString::number(m_mavlinkAutopilot));
          m_mavlinkData.append(QString::number(m_mavlinkSystemstatus));
          m_mavlinkData.append(QString::number(m_mavlinkType));

          m_mavlinkData.append(QString::number(m_mavlinkX));
          m_mavlinkData.append(QString::number(m_mavlinkY));
          m_mavlinkData.append(QString::number(m_mavlinkZ));

          m_mavlinkData.append(QString::number(m_mavlinkGx));
          m_mavlinkData.append(QString::number(m_mavlinkGy));
          m_mavlinkData.append(QString::number(m_mavlinkGz));

          m_mavlinkData.append(m_mavlinkLatitude);
          m_mavlinkData.append(m_mavlinkLongitude);
          m_mavlinkData.append(QString::number(m_mavlinkAltitude));
        }
      usleep(18);
      emit valueChanged(m_mavlinkData);
    }
}

void Telemetry::initSerial()
{
  speed_t brate = B57600;
  m_openSerial = open("/dev/serial/by-id/usb-FTDI_FT230X_Basic_UART_DN02TP8D-if00-port0", O_RDWR | O_NOCTTY | O_NDELAY);

  if (m_openSerial == -1) {
      QString strTxtEmitted = "Can't get telemetry data (port)";
      emit messageEmitted (strTxtEmitted);
    } else if (tcgetattr(m_openSerial, &m_toptions) < 0) {
      QString strTxtEmitted = "Can't get telemetry data (option)";
      emit messageEmitted (strTxtEmitted);
    } else {

      cfsetispeed(&m_toptions, brate);
      cfsetospeed(&m_toptions, brate);

      // 8N1
      m_toptions.c_cflag &= ~PARENB;
      m_toptions.c_cflag &= ~CSTOPB;
      m_toptions.c_cflag &= ~CSIZE;
      m_toptions.c_cflag |= CS8;

      // no flow control
      m_toptions.c_cflag &= ~CRTSCTS;

      m_toptions.c_cflag |= CREAD | CLOCAL; // turn on READ & ignore ctrl lines
      m_toptions.c_iflag &= ~(IXON | IXOFF | IXANY); // turn off s/w flow ctrl

      m_toptions.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // make raw
      m_toptions.c_oflag &= ~OPOST; // make raw

      m_toptions.c_cc[VMIN] = 0;
      m_toptions.c_cc[VTIME] = 20;

      if (tcsetattr(m_openSerial, TCSANOW, &m_toptions) < 0) {
          QString strTxtEmitted = "Can't get telemetry data (attributes)";
          emit messageEmitted (strTxtEmitted);
        }
    }
}




