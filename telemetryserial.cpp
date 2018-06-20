#include "telemetryserial.h"

QT_USE_NAMESPACE

/**
 * @brief TelemetrySerial::TelemetrySerial
 * Initialisation de la connexion série
 */
TelemetrySerial::TelemetrySerial()
{
  // Configuration du port
  m_serialPort.setPortName("/dev/ttyUSB0");
  m_serialPort.setBaudRate(QSerialPort::Baud57600);
  m_serialPort.open(QIODevice::ReadOnly);

  if (m_serialPort.error() != 0) {
      qDebug() << QObject::tr("Failed to open port %1, error: %2").arg("/dev/ttyUSB0").arg(m_serialPort.error());
  }

  // Connexion des signaux pour le port série
  connect(&m_serialPort, &QSerialPort::readyRead, this, &TelemetrySerial::handleReadyRead);
  connect(&m_serialPort, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error), this, &TelemetrySerial::handleError);
  //connect(&m_timer, &QTimer::timeout, this, &TelemetrySerial::handleTimeout);

  m_timer.start(2000);
}
/**
 * @brief MainWindow::~MainWindow
 */
TelemetrySerial::~TelemetrySerial()
{
  m_serialPort.close();
}

/**
 * @brief TelemetrySerial::handleReadyRead
 * Les données de la connexion série sont prêtes
 */
void TelemetrySerial::handleReadyRead()
{  
  qint64 maxSize = 2041;

  m_length = m_serialPort.readLine(m_readData, maxSize);

  if (!m_timer.isActive()) {
      m_timer.start(2000);
  }
}

/**
 * @brief TelemetrySerial::handleTimeout
 * Timeout sur la connexion
 */
void TelemetrySerial::handleTimeout()
{
    if (strlen(m_readData) == 0) {
        m_message = QObject::tr("No data was currently available for reading from port %1").arg(m_serialPort.portName());
    } else {
        m_message = QObject::tr("Data successfully received from port %1").arg(m_serialPort.portName());
    }

    m_length = strlen(m_readData);
}

/**
 * @brief TelemetrySerial::handleError
 * @param serialPortError
 * Erreur de la connexion série
 */
void TelemetrySerial::handleError(QSerialPort::SerialPortError serialPortError)
{
    if (serialPortError == QSerialPort::ReadError) {
        m_message = QObject::tr("An I/O error occurred while reading the data from port %1, error: %2").arg(m_serialPort.portName()).arg(m_serialPort.errorString());
    }

    qDebug() << "Error Handle";

    m_length = strlen(m_readData);
}



/**
 * GETTER
 */

/**
 * @brief TelemetrySerial::getReadData
 * @return char m_readData;
 */
char* TelemetrySerial::getReadData()
{
  return m_readData;
}

/**
 * @brief TelemetrySerial::getReadData
 * @return QByteArray m_readData;
 */
QString TelemetrySerial::getMessage()
{
  return m_message;
}

/**
 * @brief TelemetrySerial::getLength
 * @return QByteArray m_length;
 */
int TelemetrySerial::getLength()
{
  return m_length;
}
