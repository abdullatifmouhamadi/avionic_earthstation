#include "ihm/menubarstation.h"

menuBarStation::menuBarStation(){}

void menuBarStation::setBar(QMainWindow *parent)
{
  parent->menuBar()->addMenu("File");
}
