#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  m_TestSpeed = 0;

  // Taille de la fenêtre
  QSize windowSize = size();
  int width = windowSize.width();
  int height = windowSize.height();

  // On initialise l'ensemble des variables de télémétrie
  initDataTelemetry();

  /*
   * LAYOUT PARTIE GAUCHE
   */
  // Layout contenant la partie gauche
  m_vboxLeftLayout = new QVBoxLayout;

  // On ajoute le primary flight display
  setPFD(m_vboxLeftLayout);
  // On ajoute les données brutes
  setRawData(m_vboxLeftLayout);
  m_vboxLeftLayout->setGeometry(QRect(0, 0, 300, height));
  m_vboxLeftLayout->addStretch(1);
  // On ajoute les boutons d'action
  setActionButton(m_vboxLeftLayout);

  /*
   * LAYOUT PARTIE DROITE
   */
  // Layout contenant la partie droite
  m_vboxRightLayout = new QVBoxLayout;
  m_vboxRightLayout->setGeometry(QRect(0, 300, width+10, height+105));

  //Init de la carte
  setMap(m_vboxRightLayout, width, height);

  /*
   * PARTIE PRINCIPALE
   */
  // Widget ajouté à celui de MainWindow
  m_widget = new QWidget;

  // Layout principal, va contenir tous les autres
  m_hboxMainLayout = new QHBoxLayout;

  // On ajoute le Layout PFD/Map au layout principal
  m_hboxMainLayout->addLayout(m_vboxLeftLayout);
  m_hboxMainLayout->addLayout(m_vboxRightLayout);

  // On ajoute le layout principal au widget...
  m_widget->setLayout(m_hboxMainLayout);

  // ... Avant de l'ajouter lui-même à la feuille
  setCentralWidget(m_widget);

  /*
   * TELEMETRIE
   */
  // On lance la récupération de la télémétrie
  launchTelemetry();

  //Evènements de clique
  connect(m_buttonFlight, SIGNAL(clicked()), this, SLOT(launchFlight()));
}

/**
 * @brief MainWindow::initDataTelemetry
 */
void MainWindow::initDataTelemetry()
{
  m_mavlinkAutopilot = 0;
  m_mavlinkBasemode = 0;
  m_mavlinkCustommode = 0;
  m_mavlinkVersion = 0;
  m_mavlinkSystemstatus = 0;
  m_mavlinkType = 0;

  m_mavlinkX = 0;
  m_mavlinkY = 0;
  m_mavlinkZ = 0;

  m_mavlinkGx = 0;
  m_mavlinkGy = 0;
  m_mavlinkGz = 0;

  m_mavlinkLatitude = "";
  m_mavlinkLongitude = "";
  m_mavlinkAltitude = 0;
}

/**
 * Méthode s'occupant de lancer la récupération de la télémétrie
 * @brief MainWindow::launchTelemetry
 */
void MainWindow::launchTelemetry()
{  
  qRegisterMetaType<QList<QString> >("QList<QString>");
  // Création de l'objet Télémétrie
  mTelemetry = new Telemetry(this);
  // On connecte Signal/Slot de la télémétrie à l'IHM
  connect(mTelemetry, SIGNAL(valueChanged(QList<QString>)), this, SLOT(onValueChanged(QList<QString>)));
  connect(mTelemetry, SIGNAL(messageEmitted(QString)), this, SLOT(messageDisplay(QString)));
  // Lancement du Thread de Télémétrie
  mTelemetry->start();
}

/**
 * @brief MainWindow::setMap
 * @param QVBoxLayout parentElement
 * @param int width
 * @param int height
 */
void MainWindow::setMap(QVBoxLayout *parentElement, int width, int height)
{
  m_mapControl = new QMapControl(QSizeF(width+10, height+105));
  m_mapControl->addLayer(std::make_shared<LayerMapAdapter>("Custom Layer", std::make_shared<MapAdapterOSM>()));
  m_mapControl->setMapFocusPoint(PointWorldCoord(3.2689,50.1425));
  m_mapControl->setZoom(15);

  std::shared_ptr<LayerGeometry> m_layerGeometries(std::make_shared<LayerGeometry>("Geometry Layer"));
  m_mapControl->addLayer(m_layerGeometries);

  parentElement->addWidget(m_mapControl);
}

void MainWindow::setPosition(float Longitude, float Latitude)
{
  QPen pen(QColor(255, 0, 0, 100));
  pen.setWidth(1);
  std::vector<std::shared_ptr<GeometryPoint>> points;
  points.emplace_back(std::make_shared<GeometryPointCircle>(PointWorldCoord(Longitude,Latitude)));
  points.back()->setPen(pen);

  std::vector<PointWorldCoord> raw_points;
  for(const auto& point : points){
      raw_points.push_back(point->coord());
      m_layerGeometries->addGeometry(point);
    }
}


/**
 * @brief MainWindow::setMapPFDLayout
 */
void MainWindow::setPFD(QVBoxLayout *parentElement)
{  
  m_instrument = new QInstrument();
  m_instrument->create(parentElement);
}

/**
 * @brief MainWindow::setActionButton
 */
void MainWindow::setActionButton(QVBoxLayout *parentElement)
{
  m_buttonFlight = new QPushButton("New Flight");
  parentElement->addWidget(m_buttonFlight);
}

/**
 * @brief MainWindow::setRawData
 * @param parentElement
 */
void MainWindow::setRawData(QVBoxLayout *parentElement)
{
  QFormLayout *layoutRawData = new QFormLayout;

  m_vPitch = new QLabel("0");
  m_vRoll = new QLabel("0");
  m_vYaw = new QLabel("0");
  m_vGPitch = new QLabel("0");
  m_vGRoll = new QLabel("0");
  m_vGYaw = new QLabel("0");
  m_vAlt = new QLabel("0");
  m_vLong = new QLabel("0");
  m_vLat = new QLabel("0");
  m_vSpeed = new QLabel("0");
  m_messageEmitted = new QLabel("");

  layoutRawData->addRow("Message  : ", m_messageEmitted);
  layoutRawData->addRow("Pitch  : ", m_vPitch);
  layoutRawData->addRow("Roll  : ", m_vRoll);
  layoutRawData->addRow("Yaw  : ", m_vYaw);
  layoutRawData->addRow("G Pitch  : ", m_vGPitch);
  layoutRawData->addRow("G Roll  : ", m_vGRoll);
  layoutRawData->addRow("G Yaw  : ", m_vGYaw);
  layoutRawData->addRow("Vitesse  : ", m_vSpeed);
  layoutRawData->addRow("Altitude  : ", m_vAlt);
  layoutRawData->addRow("Longitude  : ", m_vLong);
  layoutRawData->addRow("Latitude  : ", m_vLat);

  parentElement->addLayout(layoutRawData);
}

/**
 * @brief MainWindow::messageDisplay
 * @param message
 */
void MainWindow::messageDisplay(QString message)
{
  m_messageEmitted->setText("<font color=\"#e85050\">"+message+"</font>");
}

void MainWindow::launchFlight()
{
  if (m_flagRecordFlight == false) {
      m_buttonFlight->setText("Flight in progress");
      m_flagRecordFlight = true;
      m_sql = new Sql();
    } else {
      m_buttonFlight->setText("New Flight");
      m_flagRecordFlight = false;
    }
}


/**
 * @brief MainWindow::onValueChanged
 * @param mapData
 */
void MainWindow::onValueChanged(QList<QString> mapData)
{
  bool flagConvert = true;

  if (mapData.size() == 15) {
      m_mavlinkAutopilot = mapData[0].toInt(&flagConvert);
      m_mavlinkBasemode = mapData[1].toInt(&flagConvert);
      m_mavlinkCustommode = mapData[2].toInt(&flagConvert);
      m_mavlinkVersion = mapData[3].toInt(&flagConvert);
      m_mavlinkSystemstatus = mapData[4].toInt(&flagConvert);
      m_mavlinkType = mapData[5].toInt(&flagConvert);

      m_mavlinkX = mapData[6].toFloat(&flagConvert);
      m_mavlinkY = mapData[7].toFloat(&flagConvert);
      m_mavlinkZ = mapData[8].toFloat(&flagConvert);

      m_mavlinkGx = mapData[9].toFloat(&flagConvert);
      m_mavlinkGy = mapData[10].toFloat(&flagConvert);
      m_mavlinkGz = mapData[11].toFloat(&flagConvert);

      m_mavlinkLatitude = mapData[12];
      m_mavlinkLongitude = mapData[13];
      m_mavlinkAltitude = mapData[14].toFloat(&flagConvert);
    }

  m_instrument->setX(m_mavlinkX);
  m_instrument->setY(m_mavlinkY);
  m_instrument->setZ(m_mavlinkZ);
  m_instrument->setAlt(m_mavlinkAltitude);
  m_instrument->setSpeed(m_TestSpeed);

  m_vPitch->setText(QString::number((1./100.) * floor(m_mavlinkX * 100.)));
  m_vRoll->setText(QString::number((1./100.) * floor(m_mavlinkY * 100.)));
  m_vYaw->setText(QString::number((1./100.) * floor(m_mavlinkZ * 100.)));
  m_vGPitch->setText(QString::number((1./100.) * floor(m_mavlinkGx * 100.)));
  m_vGRoll->setText(QString::number((1./100.) * floor(m_mavlinkGy * 100.)));
  m_vGYaw->setText(QString::number((1./100.) * floor(m_mavlinkGz * 100.)));
  m_vAlt->setText(QString::number((1./100.) * floor(m_mavlinkAltitude * 100.)));
  m_vLong->setText((m_mavlinkLongitude=="")?"No GPS data":m_mavlinkLongitude);
  m_vLat->setText((m_mavlinkLatitude=="")?"No GPS data":m_mavlinkLatitude);
  m_vSpeed->setText(QString::number(m_TestSpeed));

  if (m_mavlinkLongitude != "") {
      setPosition(m_mavlinkLongitude.toFloat(), m_mavlinkLatitude.toFloat());
    }

  if (m_flagRecordFlight == 1) {
      m_sql->AddDataTelemetry(m_mavlinkX, m_mavlinkY, m_mavlinkZ, m_mavlinkGx, m_mavlinkGy, m_mavlinkGz, m_mavlinkLatitude, m_mavlinkLongitude, m_mavlinkAltitude);
    }
}

/**
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow()
{
  mTelemetry->quit();
  delete mTelemetry;
  delete ui;
}


