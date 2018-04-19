#include "simulateddataref.h"

#include <QDebug>
#include <qmath.h>
#include <unistd.h>

SimulatedDataRef::SimulatedDataRef(QObject *parent, double minV, double maxV, double changeDivisor, bool round, int arrayCount, QString refName) :
  QObject(parent), minValue(minV), maxValue(maxV), currentValue(minV), actualCurrentValue(minV), change((maxValue - minValue)/changeDivisor), round(round), arrayCount(arrayCount), RefName(refName), myClientRef(0, refName, 0)
{
  connect(&changeTimer, SIGNAL(timeout()), this, SLOT(changeTimeout()));
  changeTimer.setSingleShot(false);
  changeTimer.setInterval(5);
  changeTimer.start();
}

SimulatedDataRef::~SimulatedDataRef() {
}

void SimulatedDataRef::tickTime(double dt, int total) {
  Q_UNUSED(dt);
  Q_UNUSED(total);
}

void SimulatedDataRef::changeTimeout() {
  myClientRef.updateValue(QString::number(minValue));
}

void SimulatedDataRef::newValue(double newValue) {
  minValue = newValue;
}

ClientDataRef *SimulatedDataRef::clientRef() {
  return &myClientRef;
}
