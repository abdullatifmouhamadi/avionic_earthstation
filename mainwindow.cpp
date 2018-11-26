#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  // Taille de la fenêtre
  QSize windowSize = size();
  width = windowSize.width();
  height = windowSize.height();


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

  //Evènements, boutons d'action
  connect(m_buttonFlight, SIGNAL(clicked()), this, SLOT(launchFlight()));
  connect(m_buttonResettingAlt, SIGNAL(clicked()), this, SLOT(resettingAltimeter()));
  connect(m_buttonReplayFlight, SIGNAL(clicked()), this, SLOT(replayLastFLight()));
}

/**
 * Création et affichage du PFD
 * @brief MainWindow::setMapPFDLayout
 * @param parentElement
 */
void MainWindow::setPFD(QVBoxLayout *parentElement)
{
  m_instrument = new QInstrument();
  m_instrument->create(parentElement);
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
  // On connecte Signal/Slot de la télémétrie à l'enregistrement
  connect(mTelemetry, SIGNAL(valueChanged(QList<QString>)), this, SLOT(onRecorded(QList<QString>)));
  connect(mTelemetry, SIGNAL(messageEmitted(QString)), this, SLOT(messageDisplay(QString)));

  // Lancement du Thread de Télémétrie
  mTelemetry->start();
}

/**
 * Initialisation de la carte
 * @brief MainWindow::setMap
 * @param QVBoxLayout parentElement
 * @param int width
 * @param int height
 */
void MainWindow::setMap(QVBoxLayout *parentElement, int width, int height)
{
  // Déclaration de la carte
  m_mapControl = new QMapControl(QSizeF(width+10, height+105));
  // On garde le cache en local
  m_mapControl->enablePersistentCache();
  // Layer OpenStreetMap
  m_mapControl->addLayer(std::make_shared<LayerMapAdapter>("Map", std::make_shared<MapAdapterOSM>()));

  // Positionnement par défaut sur l'aérodrome de Niergnies :p
  m_mapControl->setMapFocusPoint(PointWorldCoord(m_longitudeDefault,m_latitudeDefault));
  m_mapControl->setZoom(15);

  // Ajout d'un Layer visant à recevoir la route
  std::shared_ptr<LayerGeometry> customLayer(std::make_shared<LayerGeometry>("route"));
  m_mapControl->addLayer(customLayer);
  m_customLayer = customLayer;

  parentElement->addWidget(m_mapControl);
}

/**
 * Affichage d'un point sur la carte suivant les coordonnées GPS
 * récupérées du raspberry
 * @brief MainWindow::setPosition
 * @param Longitude
 * @param Latitude
 */
void MainWindow::setPosition(float Longitude, float Latitude)
{
  // On affiche un point si et seulement si latitude et longitude sont différents du point précédent.
  if (Longitude != m_oldLongitude || Latitude != m_oldLatitude) {
      QPen pen(Qt::red, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
      std::shared_ptr<GeometryPoint>point = std::make_shared<GeometryPointCircle>(PointWorldCoord(Longitude,Latitude));
      point->setPen(pen);
      m_customLayer->addGeometry(point);
      m_mapControl->setMapFocusPoint(PointWorldCoord(Longitude,Latitude));

      m_oldLatitude = Latitude;
      m_oldLongitude = Longitude;
    }
}

/**
 * Boutons d'action (Enregistrement de vol, mise à 0 de l'altimètre)
 * @brief MainWindow::setActionButton
 */
void MainWindow::setActionButton(QVBoxLayout *parentElement)
{
  m_buttonFlight = new QPushButton("New Flight");
  m_buttonResettingAlt = new QPushButton("Resetting the altimeter");
  m_buttonReplayFlight = new QPushButton("Replay last flight");

  parentElement->addWidget(m_buttonResettingAlt);
  parentElement->addWidget(m_buttonFlight);
  parentElement->addWidget(m_buttonReplayFlight);
}

/**
 * Affichage des données brutes
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
  m_vAltOffset = new QLabel("0");
  m_vSpeed = new QLabel("0");
  m_messageEmitted = new QLabel("");

  // Messages d'information
  layoutRawData->addRow("Message  : ", m_messageEmitted);

  // Affichage des données inertielles
  layoutRawData->addRow("Pitch  : ", m_vPitch);
  layoutRawData->addRow("Roll  : ", m_vRoll);
  layoutRawData->addRow("Yaw  : ", m_vYaw);

  // Affichage des données d'acceléromètre
  layoutRawData->addRow("G Pitch  : ", m_vGPitch);
  layoutRawData->addRow("G Roll  : ", m_vGRoll);
  layoutRawData->addRow("G Yaw  : ", m_vGYaw);

  // Affichage des données vitesse et altitude
  layoutRawData->addRow("Vitesse  : ", m_vSpeed);
  layoutRawData->addRow("Altitude  : ", m_vAlt);
  layoutRawData->addRow("Altitude Offset  : ", m_vAltOffset);

  // Affichage des données GPS
  layoutRawData->addRow("Longitude  : ", m_vLong);
  layoutRawData->addRow("Latitude  : ", m_vLat);

  parentElement->addLayout(layoutRawData);
}

/**
 * @brief MainWindow::launchFlight
 */
void MainWindow::launchFlight()
{
  if (m_flagRecordFlight == false) {
      m_oldLongitude = 0;
      m_oldLatitude = 0;
      m_buttonFlight->setText("Flight in progress");
      m_flagRecordFlight = true;
      m_sql = new Sql(this);
      m_sql->start();
    } else {
      m_buttonFlight->setText("New Flight");
      m_flagRecordFlight = false;
    }
}

/**
 * @brief MainWindow::replayLastFLight
 */
void MainWindow::replayLastFLight()
{
  m_flagValidRecordSql = false;
  QList<QList<QString>> dataLastFlight;
  m_sql = new Sql(this);
  dataLastFlight = m_sql->findAll();

  QList<QString> mapData;
  foreach( mapData, dataLastFlight ) {
      treatmentData(mapData);
      usleep(50000);
    }
}

/**
 * @brief MainWindow::onValueChanged
 * @param mapData
 */
void MainWindow::onValueChanged(QList<QString> mapData)
{
  m_flagValidRecordSql = true;
  treatmentData(mapData);
}

void MainWindow::treatmentData(QList<QString> mapData)
{
  bool flagConvert = true;

  // Récupération des informations provenant des capteurs
  if (mapData.size() == 15) {
      // Statut
      m_mavlinkAutopilot = mapData[0].toInt(&flagConvert);
      m_mavlinkBasemode = mapData[1].toInt(&flagConvert);
      m_mavlinkCustommode = mapData[2].toInt(&flagConvert);
      m_mavlinkVersion = mapData[3].toInt(&flagConvert);
      m_mavlinkSystemstatus = mapData[4].toInt(&flagConvert);
      m_mavlinkType = mapData[5].toInt(&flagConvert);

      // Attitude
      m_mavlinkX = mapData[6].toFloat(&flagConvert);
      m_mavlinkY = mapData[7].toFloat(&flagConvert);
      m_mavlinkZ = mapData[8].toFloat(&flagConvert);

      // Accélération
      m_mavlinkGx = mapData[9].toFloat(&flagConvert);
      m_mavlinkGy = mapData[10].toFloat(&flagConvert);
      m_mavlinkGz = mapData[11].toFloat(&flagConvert);

      // Position
      m_mavlinkLatitude = mapData[12].toFloat(&flagConvert);
      m_mavlinkLongitude = mapData[13].toFloat(&flagConvert);
      m_mavlinkAltitude = mapData[14].toFloat(&flagConvert);
    }

  // Envoi vers l'instrument PFD
  m_instrument->setX(m_mavlinkX);
  m_instrument->setY(m_mavlinkY);
  m_instrument->setZ(m_mavlinkZ);
  m_instrument->setAlt(m_mavlinkAltitude - m_offsetAltitude);
  m_instrument->setSpeed(m_TestSpeed);

  // Affichage de la valeur brute des capteurs
  m_vPitch->setText(QString::number((1./100.) * floor(m_mavlinkX * 100.)));
  m_vRoll->setText(QString::number((1./100.) * floor(m_mavlinkY * 100.)));
  m_vYaw->setText(QString::number((1./100.) * floor(m_mavlinkZ * 100.)));
  m_vGPitch->setText(QString::number((1./100.) * floor(m_mavlinkGx * 100.)));
  m_vGRoll->setText(QString::number((1./100.) * floor(m_mavlinkGy * 100.)));
  m_vGYaw->setText(QString::number((1./100.) * floor(m_mavlinkGz * 100.)));
  m_vAlt->setText(QString::number((1./100.) * floor((m_mavlinkAltitude - m_offsetAltitude) * 100.)));
  m_vAltOffset->setText(QString::number(m_offsetAltitude));
  m_vLong->setText((m_mavlinkLongitude==0)?"No GPS data":QString::number((1./100.) * floor(m_mavlinkLongitude * 100.)));
  m_vLat->setText((m_mavlinkLatitude==0)?"No GPS data":QString::number((1./100.) * floor(m_mavlinkLatitude)));
  m_vSpeed->setText(QString::number(m_TestSpeed));

  // Affichage de la position sur la carte
  if (m_mavlinkLongitude != 0) {
      setPosition(m_mavlinkLongitude, m_mavlinkLatitude);
    }
}

/**
 * @brief MainWindow::onRecorded
 * @param mapData
 */
void MainWindow::onRecorded(QList<QString> mapData)
{
  bool flagConvert = true;
  // Récupération des informations provenant des capteurs
  if (mapData.size() == 15 && m_flagValidRecordSql) {
      // Attitude
      m_sql->setMavlinkX(mapData[6].toFloat(&flagConvert));
      m_sql->setMavlinkY(mapData[7].toFloat(&flagConvert));
      m_sql->setMavlinkZ(mapData[8].toFloat(&flagConvert));

      // Accélération
      m_sql->setMavlinkGX(mapData[9].toFloat(&flagConvert));
      m_sql->setMavlinkGY(mapData[10].toFloat(&flagConvert));
      m_sql->setMavlinkGZ(mapData[11].toFloat(&flagConvert));

      // Position
      m_sql->setMavlinkLatitude(mapData[12].toFloat(&flagConvert));
      m_sql->setMavlinkLongitude(mapData[13].toFloat(&flagConvert));
      m_sql->setMavlinkAltitude(mapData[14].toFloat(&flagConvert));

      m_sql->setDataAvailable(true);
    }
}

/**
 * SLOT : Affichage des messages d'info
 * @brief MainWindow::messageDisplay
 * @param message
 */
void MainWindow::messageDisplay(QString message)
{
  m_messageEmitted->setText("<font color=\"#e85050\">"+message+"</font>");
}

/**
 * @brief MainWindow::launchFlight
 */
void MainWindow::resettingAltimeter()
{
  m_offsetAltitude = m_mavlinkAltitude;
}

/**
 * @brief MainWindow::resizeEvent
 * @param event
 */
void MainWindow::resizeEvent(QResizeEvent * event)
{
  // Taille de la fenêtre
  QSize windowSize = size();
  width = windowSize.width();
  height = windowSize.height();
  m_mapControl->setViewportSize(QSizeF(width+10, height+105));
}

/**
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow()
{
  mTelemetry->quit();
  m_sql->quit();
  delete mTelemetry;
  delete ui;
}
