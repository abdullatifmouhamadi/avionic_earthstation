#include "sql.h"

Sql::Sql()
{
  QSqlDatabase db;
  m_db = QSqlDatabase::addDatabase("QMYSQL");
  m_db.setHostName("localhost");
  m_db.setUserName("root");
  m_db.setPassword("");
  m_db.setDatabaseName("earthstation");

  qDebug() << m_db.open();
}

bool Sql::AddDataTelemetry(
  double mavlinkX
  ,double mavlinkY
  ,double mavlinkZ
  ,double mavlinkGX
  ,double mavlinkGY
  ,double mavlinkGZ
  ,QString mavlinkLatitude
  ,QString mavlinkLongitude
  ,double mavlinkAltitude
)
{
  m_query.prepare("INSERT INTO flight_data (id, mavlink_x, mavlink_y, mavlink_z, mavlink_gx, mavlink_gy, mavlink_gz, mavlink_latitude, mavlink_longitude, mavlink_altitude) VALUES (:X, :Y, :Z, :GX, :GY, :GZ, :latitude, :longitude, :altitude)");
  m_query.bindValue(":X", mavlinkX);
  m_query.bindValue(":Y", mavlinkY);
  m_query.bindValue(":Z", mavlinkZ);
  m_query.bindValue(":GX", mavlinkGX);
  m_query.bindValue(":GY", mavlinkGY);
  m_query.bindValue(":GZ", mavlinkGZ);
  m_query.bindValue(":latitude", mavlinkLatitude);
  m_query.bindValue(":longitude", mavlinkLongitude);
  m_query.bindValue(":altitude", mavlinkAltitude);

  return m_query.execBatch();
}
