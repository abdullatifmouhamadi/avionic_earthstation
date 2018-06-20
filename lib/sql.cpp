#include "sql.h"

/**
 * Constructeur : Instanciation de l'objet sqLite
 * @brief Sql::Sql
 * @param parent
 * @param b
 */
Sql::Sql(QObject *parent, bool b) :
  QThread(parent), Stop(b)
{
  if (!QSqlDatabase::isDriverAvailable("QSQLITE")) {
      qDebug() << "Le Driver n'est pas disponible pour l'application";
    } else {
      m_db = QSqlDatabase::addDatabase("QSQLITE");
      if(!m_db.open()) {
          qDebug() << "La connexion a échouée :" << m_db.lastError().text();
        } else {
          m_db.setDatabaseName(qApp->applicationDirPath() + QDir::separator() + "dataFlight");
        }
    }
}

/**
 * Méthode run du thread
 * Enregistrement des informations en BDD, si et seulement si, elles sont dispos.
 * @brief Sql::run
 */
void Sql::run()
{
  while(1) {
      if (m_db.open() && m_dataAvailable) {
          time(&timer);
          t = static_cast<long int>(timer);
          QSqlQuery m_query;
          m_query.prepare("INSERT INTO flight_data (timestamp, mavlink_x, mavlink_y, mavlink_z, mavlink_gx, mavlink_gy, mavlink_gz, mavlink_latitude, mavlink_longitude, mavlink_altitude) VALUES (:T, :X, :Y, :Z, :GX, :GY, :GZ, :latitude, :longitude, :altitude)");
          m_query.bindValue(":T", t);
          m_query.bindValue(":X", m_mavlinkX);
          m_query.bindValue(":Y", m_mavlinkY);
          m_query.bindValue(":Z", m_mavlinkZ);
          m_query.bindValue(":GX", m_mavlinkGX);
          m_query.bindValue(":GY", m_mavlinkGY);
          m_query.bindValue(":GZ", m_mavlinkGZ);
          m_query.bindValue(":latitude", m_mavlinkLatitude);
          m_query.bindValue(":longitude", m_mavlinkLongitude);
          m_query.bindValue(":altitude", m_mavlinkAltitude);
          m_query.exec();
          m_dataAvailable = false;
        }
    }
}

/**
 * @brief Sql::setMavlinkX
 * @param mavlinkX
 */
void Sql::setMavlinkX(double mavlinkX)
{
  m_mavlinkX = mavlinkX;
}

/**
 * @brief Sql::setMavlinkY
 * @param mavlinkY
 */
void Sql::setMavlinkY(double mavlinkY)
{
  m_mavlinkY = mavlinkY;
}

/**
 * @brief Sql::setMavlinkZ
 * @param mavlinkZ
 */
void Sql::setMavlinkZ(double mavlinkZ)
{
  m_mavlinkZ = mavlinkZ;
}

/**
 * @brief Sql::setMavlinkGX
 * @param mavlinkGX
 */
void Sql::setMavlinkGX(double mavlinkGX)
{
  m_mavlinkGX = mavlinkGX;
}

/**
 * @brief Sql::setMavlinkGY
 * @param mavlinkGY
 */
void Sql::setMavlinkGY(double mavlinkGY)
{
  m_mavlinkGY = mavlinkGY;
}

/**
 * @brief Sql::setMavlinkGZ
 * @param mavlinkGZ
 */
void Sql::setMavlinkGZ(double mavlinkGZ)
{
  m_mavlinkGZ = mavlinkGZ;
}

/**
 * @brief Sql::setMavlinkLatitude
 * @param mavlinkLatitude
 */
void Sql::setMavlinkLatitude(double mavlinkLatitude)
{
  m_mavlinkLatitude = mavlinkLatitude;
}

/**
 * @brief Sql::setMavlinkLongitude
 * @param mavlinkLongitude
 */
void Sql::setMavlinkLongitude(double mavlinkLongitude)
{
  m_mavlinkLongitude = mavlinkLongitude;
}

/**
 * @brief Sql::setMavlinkAltitude
 * @param mavlinkAltitude
 */
void Sql::setMavlinkAltitude(double mavlinkAltitude)
{
  m_mavlinkAltitude = mavlinkAltitude;
}

/**
 * @brief Sql::setDataAvailable
 * @param dataAvailable
 */
void Sql::setDataAvailable(bool dataAvailable)
{
  m_dataAvailable = dataAvailable;
}
