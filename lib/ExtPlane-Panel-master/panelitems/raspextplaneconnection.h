#ifndef RASPEXTPLANECONNECTION_H
#define RASPEXTPLANECONNECTION_H

#include "simulateddatarefs/fixedsimulateddataref.h"
#include "extplaneconnection.h"

/**
 * @brief The RaspExtPlaneConnection class presents some
 * Raspberry Pi's aircraft data.
 *
 * @see ExtPlaneConnection
 */
class RaspExtPlaneConnection : public ExtPlaneConnection {
    Q_OBJECT

public:
    explicit RaspExtPlaneConnection(QObject *parent = 0);
    void setX(double);
    void setY(double);
    void setZ(double);
    void setAlt(double);
    void setSpeed(double);
    void update();
    virtual ClientDataRef *createDataRef(QString name, double accuracy=0);

public slots:
    virtual void connectTo(QString host, unsigned int port);
    void tickTime(double dt, int total);

private:
    //QList<SimulatedDataRef*> simulatedRefs;
    QList<SimulatedDataRef*> simulatedRefs;

    SimulatedDataRef *simRef = 0;
    SimulatedDataRef *simRefSpeed = 0;
    SimulatedDataRef *simRefAltitude = 0;
    SimulatedDataRef *simRefPitch = 0;
    SimulatedDataRef *simRefRoll = 0;
    SimulatedDataRef *simRefSlip = 0;


    // Informations du PFD
    double m_x = 0;
    double m_y = 0;
    double m_z = 0;

    double m_alt = 0;
    double m_speed = 0;
};

#endif // RASPEXTPLANECONNECTION_H
