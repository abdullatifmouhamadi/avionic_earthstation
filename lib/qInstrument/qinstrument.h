#ifndef QINSTRUMENT_H
#define QINSTRUMENT_H

#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QMessageBox>
#include <QString>
#include <QStringList>
#include <QInputDialog>
#include <QFileDialog>
#include <QCoreApplication>
#include <QDesktopWidget>
#include <QDesktopServices>

#include <QGraphicsTextItem>
#include <QSettings>
#include <QTimer>
#include <QTime>
#include <QKeyEvent>
#include <QList>

#include "settings.h"
#include "panel.h"

#include "util/console.h"
#include "extplaneconnection.h"
#include "extplaneclient.h"
#include "simulatedextplaneconnection.h"
#include "raspextplaneconnection.h"
#include "menubutton.h"
#include "panelitemfactory.h"
#include "panelitems/panelitem.h"
#include "hardware/hardwaremanager.h"

#include "panelitems/pfddisplay.h"

#define AUTO_PANEL_DATAREF "sim/aircraft/view/acf_tailnum"
#define ADJUST_POWER_DATAREF "sim/cockpit/electrical/avionics_on"

class QInstrument : public QGraphicsView {
  Q_OBJECT

public:
  QInstrument();
  bool create(QVBoxLayout *);
  void setX(double);
  void setY(double);
  void setZ(double);
  void setAlt(double);
  void setSpeed(double);

signals:
    void tickTime(double dt, int total);

public slots:

private slots:
    void tick();

private:
  QGraphicsScene scene;
  PanelItemFactory itemFactory;

  //ExtPlaneConnection *connexion;
  //SimulatedExtPlaneConnection *connexion;
  RaspExtPlaneConnection *connexion;
  ExtPlaneClient *client;

  PanelItem *newItem;

  Settings *appSettings;
  ExtPlanePanel *currentPanel;
  QTimer tickTimer;
  QTime time, totalTime;

// Informations du PFD
  float m_x;
  float m_y;
  float m_z;

  float m_alt;
  float m_speed;

};

#endif // QINSTRUMENT_H
