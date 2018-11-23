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
  void replayLastFLight();

private:
  void setPFD(QVBoxLayout *);
  void setRawData(QVBoxLayout *);
  void setActionButton(QVBoxLayout *);
  void setMap(QVBoxLayout *, int, int);
  void setPosition(float, float);
  void treatmentData(QList<QString>);
  void resizeEvent(QResizeEvent *);

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
  QPushButton *m_buttonReplayFlight;

  QInstrument *m_instrument;

  int m_mavlinkAutopilot = 0;
  int m_mavlinkBasemode = 0;
  int m_mavlinkCustommode = 0;
  int m_mavlinkVersion = 0;
  int m_mavlinkSystemstatus = 0;
  int m_mavlinkType = 0;

  float m_mavlinkX = 0;
  float m_mavlinkY = 0;
  float m_mavlinkZ = 0;

  float m_mavlinkGx = 0;
  float m_mavlinkGy = 0;
  float m_mavlinkGz = 0;

  float m_mavlinkLatitude = 0;
  float m_mavlinkLongitude = 0;

  float m_oldLatitude = 0;
  float m_oldLongitude = 0;

  float m_mavlinkAltitude = 0;
  float m_offsetAltitude = 0;

  int m_TestSpeed = 0;

  int width;
  int height;

  std::shared_ptr<LayerGeometry> m_customLayer;
  QMapControl* m_mapControl;

  Sql *m_sql;

  bool m_flagRecordFlight = false;
  bool m_flagValidRecordSql = true;

  int m_flagDisplayMap;

  float m_longitudeDefault = 3.2689;
  float m_latitudeDefault = 50.1425;
};

#endif // MAINWINDOW_H
