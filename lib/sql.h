#ifndef SQL_H
#define SQL_H

#include <QThread>
#include <QtSql>
#include <QSqlDriver>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlDriverPlugin>
#include <time.h>
#include <QList>

class Sql : public QThread
{
  Q_OBJECT

public:
  explicit Sql(QObject *parent = 0, bool b = false);
  QList<QList<QString>> findAll();

  void setMavlinkX(double);
  void setMavlinkY(double);
  void setMavlinkZ(double);
  void setMavlinkGX(double);
  void setMavlinkGY(double);
  void setMavlinkGZ(double);
  void setMavlinkLatitude(double);
  void setMavlinkLongitude(double);
  void setMavlinkAltitude(double);
  void setDataAvailable(bool);

  bool Stop;

protected:
  void run();

private:
  QSqlDatabase m_db;
  time_t timer;
  double t;

  double m_mavlinkX;
  double m_mavlinkY;
  double m_mavlinkZ;
  double m_mavlinkGX;
  double m_mavlinkGY;
  double m_mavlinkGZ;
  double m_mavlinkLatitude;
  double m_mavlinkLongitude;
  double m_mavlinkAltitude;

  bool m_dataAvailable = false;
  QList<QList<QString>> m_findAllData;
};

#endif // SQL_H
