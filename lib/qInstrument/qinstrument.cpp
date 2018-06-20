#include "qinstrument.h"

QInstrument::QInstrument()
{
  m_x = 0;
  m_y = 0;
  m_z = 0;
  m_alt = 0;
  m_speed = 0;
}

bool QInstrument::create(QVBoxLayout *parentElement)
{  
  // Setup window
  setScene(&scene);
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setSceneRect(300, 300, 300, 300);
  setBackgroundBrush(QBrush(Qt::black));
  setFrameShape(QFrame::NoFrame);

  // Create panel object
  currentPanel = new ExtPlanePanel(NULL,parentElement);

  // Create connection and item factory
  connexion = new RaspExtPlaneConnection();

  // Setup tick timer
  connect(&tickTimer, SIGNAL(timeout()), this, SLOT(tick()));
  tickTimer.setInterval(64);
  tickTimer.setSingleShot(false);
  connect(this, SIGNAL(tickTime(double,int)), connexion, SLOT(tickTime(double,int)));

  // Reprise de la fonction additem, pas besoin ici
  newItem = itemFactory.itemForName("display/pfd",currentPanel,connexion);
  newItem->setPos(0, 0);
  newItem->setPanelRotation(0);
  newItem->setEditMode(true);
  newItem->setInterpolationEnabled(false);
  newItem->setAntialiasEnabled(false);
  newItem->setDefaultFontSize(15);
  newItem->setSize(300, 300);

  client = new ExtPlaneClient(this,"PanelWindow",connexion);
  connexion->registerClient(client);

  scene.addItem(newItem);
  QGraphicsView *graphic = new QGraphicsView(&scene);
  graphic->setFixedWidth(302);
  parentElement->addWidget(graphic);


  // Setup tick timer
  connect(&tickTimer, SIGNAL(timeout()), this, SLOT(tick()));
  tickTimer.setInterval(5);
  tickTimer.setSingleShot(false);
  connect(this, SIGNAL(tickTime(double,int)), newItem, SLOT(tickTime(double,int)));

  // Start timers
  totalTime.start();
  time.start();
  tickTimer.start();

  return true;
}

void QInstrument::setX(double x)
{
  m_x = x;
}

void QInstrument::setY(double y)
{
  m_y = y;
}

void QInstrument::setZ(double z)
{
  m_z = z;
}

void QInstrument::setAlt(double alt)
{
  m_alt = alt;
}

void QInstrument::setSpeed(double speed)
{
  m_speed = speed;
}

void QInstrument::tick() {

  double dt = time.elapsed() / 1000.0f;
  time.start();
  if(dt > 0.2f) {
      dt = 0;
    }

  // On envoie les informations à l'instrument
  connexion->setX(m_x);
  connexion->setY(m_y);
  connexion->setZ(m_z);
  connexion->setAlt(m_alt);
  connexion->setSpeed(m_speed);

  connexion->update();

  emit tickTime(dt, totalTime.elapsed());
}
