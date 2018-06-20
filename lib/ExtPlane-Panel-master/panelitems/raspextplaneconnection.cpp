#include "raspextplaneconnection.h"
#include "simulateddatarefs/simulateddataref.h"
#include "simulateddatarefs/fixedsimulateddataref.h"
#include "simulateddatarefs/alternatingsimulateddataref.h"
#include <unistd.h>
#include "../util/console.h"

#include <QDebug>

#define DATAREF_PITCH "sim/cockpit2/gauges/indicators/pitch_vacuum_deg_pilot"
#define DATAREF_ROLL "sim/cockpit2/gauges/indicators/roll_electric_deg_pilot"
#define DATAREF_SLIP "sim/cockpit2/gauges/indicators/slip_deg"
#define DATAREF_AIRSPEED_KTS "sim/cockpit2/gauges/indicators/airspeed_kts_pilot"
#define DATAREF_ALTITUDE_FT "sim/cockpit2/gauges/indicators/altitude_ft_pilot"
#define DATAREF_AIRSPEED_ACC_KTS "sim/cockpit2/gauges/indicators/airspeed_acceleration_kts_sec_pilot"
#define DATAREF_HEADING_DEG "sim/cockpit2/gauges/indicators/heading_electric_deg_mag_pilot"
#define DATAREF_VERTICALSPEED_FPM "sim/cockpit2/gauges/indicators/vvi_fpm_pilot"


RaspExtPlaneConnection::RaspExtPlaneConnection(QObject *parent) :
  ExtPlaneConnection(parent)
{
  enableSimulatedRefs = true;
}

void RaspExtPlaneConnection::connectTo(QString host, unsigned int port) {
  _host = host;
  _port = port;
  server_ok = true;
  emit connectionMessage("Connected to ExtPlane (raspberry)");
}

ClientDataRef *RaspExtPlaneConnection::createDataRef(QString name, double accuracy) {

  if (name == DATAREF_AIRSPEED_KTS) {
      simRefSpeed = new SimulatedDataRef(this, accuracy, accuracy, 50.0, false, 0, DATAREF_AIRSPEED_KTS);
      return simRefSpeed->clientRef();
    } else if (name == DATAREF_ALTITUDE_FT) {
      simRefAltitude = new SimulatedDataRef(this, accuracy, accuracy, 50.0, false, 0, DATAREF_ALTITUDE_FT);
      return simRefAltitude->clientRef();
    } else if (name == DATAREF_PITCH) {
      simRefPitch = new SimulatedDataRef(this, accuracy, accuracy, 50.0, false, 0, DATAREF_PITCH);
      return simRefPitch->clientRef();
    } else if (name == DATAREF_ROLL) {
      simRefRoll = new SimulatedDataRef(this, accuracy, accuracy, 50.0, false, 0, DATAREF_ROLL);
      return simRefRoll->clientRef();
    } if (name == DATAREF_SLIP) {
      simRefSlip = new SimulatedDataRef(this, accuracy, accuracy, 50.0, false, 0, DATAREF_SLIP);
      return simRefSlip->clientRef();
    } else {
      simRef = new SimulatedDataRef(this, accuracy, accuracy, 50.0, false, 0, name);
      return simRef->clientRef();
    }
}

void RaspExtPlaneConnection::tickTime(double dt, int total) {
  Q_UNUSED(dt);
  Q_UNUSED(total);
}

void RaspExtPlaneConnection::update() {
  simRefSpeed->newValue(m_speed);
  simRefAltitude->newValue(m_alt);
  simRefPitch->newValue(m_x);
  simRefRoll->newValue(m_y);
  simRefSlip->newValue(m_z);
}

void RaspExtPlaneConnection::setX(double x) {
  m_x = x;
}

void RaspExtPlaneConnection::setY(double y) {
  m_y = y;
}

void RaspExtPlaneConnection::setZ(double z) {
  m_z = z;
}

void RaspExtPlaneConnection::setAlt(double alt) {
  m_alt = alt;
}

void RaspExtPlaneConnection::setSpeed(double speed) {
  m_speed = speed;
}
