#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>

#include <lib/QMapControl/QMapControl.h>
#include "lib/QMapControl/LayerMapAdapter.h"
#include <lib/QMapControl/MapAdapterOSM.h>

#include <lib/QMapControl/GeometryLineString.h>
#include <lib/QMapControl/GeometryPointArrow.h>
#include <lib/QMapControl/GeometryPointCircle.h>
#include <lib/QMapControl/GeometryPolygon.h>
#include <lib/QMapControl/GeometryWidget.h>
#include <lib/QMapControl/LayerGeometry.h>

#include <cmath>

#include <QVBoxLayout>
#include <QFormLayout>
#include <QGridLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>

#include <QStringList>
#include <QString>

#include <QDebug>

#include "telemetry.h"
#include "lib/sql.h"
#include "config.h"

#include "lib/qInstrument/qinstrument.h"

namespace Ui {
  class MainWindow;
}

using namespace qmapcontrol;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  Telemetry *mTelemetry;

public slots:
  void onValueChanged(QList<QString>);
  void onRecorded(QList<QString>);
  void messageDisplay(QString);
  void launchTelemetry();

private slots:
  void launchFlight();
  void resettingAltimeter();

private:
  void setPFD(QVBoxLayout *);
  void setRawData(QVBoxLayout *);
  void setActionButton(QVBoxLayout *);
  void setMap(QVBoxLayout *, int, int);
  void setPosition(float, float);
  void resizeEvent(QResizeEvent *);

  void initDataTelemetry();

  Ui::MainWindow *ui;
  QWidget *m_widget;

  QHBoxLayout *m_hboxMainLayout;
  QVBoxLayout *m_vboxLeftLayout;
  QVBoxLayout *m_vboxRightLayout;

  QGridLayout *m_gridLayout;
  QTableWidget *m_tableWidget;
  QStringList m_tableHeader;

  QLabel *m_vPitch;
  QLabel *m_vRoll;
  QLabel *m_vYaw;
  QLabel *m_vGPitch;
  QLabel *m_vGRoll;
  QLabel *m_vGYaw;
  QLabel *m_vAlt;
  QLabel *m_vAltOffset;
  QLabel *m_vLong;
  QLabel *m_vLat;
  QLabel *m_vSpeed;
  QLabel *m_messageEmitted;

  QPushButton *m_buttonFlight;
  QPushButton *m_buttonResettingAlt;

  QInstrument *m_instrument;

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

  float m_mavlinkLatitude;
  float m_mavlinkLongitude;

  float m_oldLatitude;
  float m_oldLongitude;

  float m_mavlinkAltitude;
  float m_offsetAltitude;

  int width;
  int height;

  std::shared_ptr<LayerGeometry> m_customLayer;
  QMapControl* m_mapControl;

  Sql *m_sql;

  bool m_flagRecordFlight = false;

  int m_flagDisplayMap;

  int m_TestSpeed;

  float m_longitudeDefault = 3.2689;
  float m_latitudeDefault = 50.1425;
};

#endif // MAINWINDOW_H
