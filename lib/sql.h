#ifndef SQL_H
#define SQL_H

#include <QtSql>
#include <QDebug>

class Sql
{
public:
  Sql();
  bool AddDataTelemetry(
    double mavlinkX
    ,double mavlinkY
    ,double mavlinkZ
    ,double mavlinkGX
    ,double mavlinkGY
    ,double mavlinkGZ
    ,QString mavlinkLatitude
    ,QString mavlinkLongitude
    ,double mavlinkAltitude
  );

private:
  QSqlDatabase m_db;
  QSqlQuery m_query;

};

#endif // SQL_H
