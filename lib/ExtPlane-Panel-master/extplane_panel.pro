QT       += core gui network qml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = panel
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

HEADERS = \
   $$PWD/dialogs/bindingcurvedialog.h \
   $$PWD/dialogs/edititemdialog.h \
   $$PWD/dialogs/hardwaredialog.h \
   $$PWD/dialogs/panelitemselectiondialog.h \
   $$PWD/dialogs/panelsdialog.h \
   $$PWD/dialogs/settingsdialog.h \
   $$PWD/hardware/chromaoutputdevice.h \
   $$PWD/hardware/hardwarebinding.h \
   $$PWD/hardware/hardwaremanager.h \
   $$PWD/hardware/nulloutputdevice.h \
   $$PWD/hardware/outputdevice.h \
   $$PWD/hardware/pololuoutputdevice.h \
   $$PWD/hardware/servoblasteroutputdevice.h \
   $$PWD/needles/gabalancedneedle.h \
   $$PWD/needles/needle.h \
   $$PWD/needles/triangleneedle.h \
   $$PWD/panelitems/airspeedindicator.h \
   $$PWD/panelitems/altimeter.h \
   $$PWD/panelitems/attitudeindicator.h \
   $$PWD/panelitems/button.h \
   $$PWD/panelitems/compass.h \
   $$PWD/panelitems/datarefdebugger.h \
   $$PWD/panelitems/di.h \
   $$PWD/panelitems/dial.h \
   $$PWD/panelitems/displayinstrument.h \
   $$PWD/panelitems/engine_battery.h \
   $$PWD/panelitems/engine_fuel_p.h \
   $$PWD/panelitems/engine_rpm.h \
   $$PWD/panelitems/enginedisplay.h \
   $$PWD/panelitems/gaugecover.h \
   $$PWD/panelitems/genericlittlegauge.h \
   $$PWD/panelitems/gpsmap.h \
   $$PWD/panelitems/hsi_ks55.h \
   $$PWD/panelitems/indicatordisplay.h \
   $$PWD/panelitems/indicatorlight.h \
   $$PWD/panelitems/mapinstrument.h \
   $$PWD/panelitems/navdisplay.h \
   $$PWD/panelitems/needleinstrument.h \
   $$PWD/panelitems/panelitem.h \
   $$PWD/panelitems/pfddisplay.h \
   $$PWD/panelitems/radarmap.h \
   $$PWD/panelitems/rotaryknob.h \
   $$PWD/panelitems/slipindicator.h \
   $$PWD/panelitems/switch.h \
   $$PWD/panelitems/tankleveler.h \
   $$PWD/panelitems/turnbank.h \
   $$PWD/panelitems/variometer.h \
   $$PWD/util/console.h \
   $$PWD/util/interpolation.h \
   $$PWD/util/perlinnoise.h \
   $$PWD/widgets/colorselector.h \
   $$PWD/widgets/distanceunitcombobox.h \
   $$PWD/widgets/numberinputlineedit.h \
   $$PWD/widgets/velocityunitcombobox.h \
   $$PWD/menubutton.h \
   $$PWD/panel.h \
   $$PWD/panelitemfactory.h \
   $$PWD/panelwindow.h \
   $$PWD/settings.h \
   $$PWD/units.h \
   $$PWD/valueinterpolator.h \
    panelitems/clientdataref.h \
    panelitems/clientdatarefprovider.h \
    panelitems/extplaneclient.h \
    panelitems/extplaneconnection.h \
    panelitems/simulatedextplaneconnection.h \
    panelitems/simulateddatarefs/alternatingsimulateddataref.h \
    panelitems/simulateddatarefs/fixedsimulateddataref.h \
    panelitems/simulateddatarefs/simulateddataref.h

SOURCES = \
   $$PWD/dialogs/bindingcurvedialog.cpp \
   $$PWD/dialogs/edititemdialog.cpp \
   $$PWD/dialogs/hardwaredialog.cpp \
   $$PWD/dialogs/panelitemselectiondialog.cpp \
   $$PWD/dialogs/panelsdialog.cpp \
   $$PWD/dialogs/settingsdialog.cpp \
   $$PWD/hardware/chromaoutputdevice.cpp \
   $$PWD/hardware/hardwarebinding.cpp \
   $$PWD/hardware/hardwaremanager.cpp \
   $$PWD/hardware/nulloutputdevice.cpp \
   $$PWD/hardware/outputdevice.cpp \
   $$PWD/hardware/pololuoutputdevice.cpp \
   $$PWD/hardware/servoblasteroutputdevice.cpp \
   $$PWD/needles/gabalancedneedle.cpp \
   $$PWD/needles/needle.cpp \
   $$PWD/needles/triangleneedle.cpp \
   $$PWD/panelitems/airspeedindicator.cpp \
   $$PWD/panelitems/altimeter.cpp \
   $$PWD/panelitems/attitudeindicator.cpp \
   $$PWD/panelitems/button.cpp \
   $$PWD/panelitems/compass.cpp \
   $$PWD/panelitems/datarefdebugger.cpp \
   $$PWD/panelitems/di.cpp \
   $$PWD/panelitems/dial.cpp \
   $$PWD/panelitems/displayinstrument.cpp \
   $$PWD/panelitems/engine_battery.cpp \
   $$PWD/panelitems/engine_fuel_p.cpp \
   $$PWD/panelitems/engine_rpm.cpp \
   $$PWD/panelitems/enginedisplay.cpp \
   $$PWD/panelitems/gaugecover.cpp \
   $$PWD/panelitems/genericlittlegauge.cpp \
   $$PWD/panelitems/gpsmap.cpp \
   $$PWD/panelitems/hsi_ks55.cpp \
   $$PWD/panelitems/indicatordisplay.cpp \
   $$PWD/panelitems/indicatorlight.cpp \
   $$PWD/panelitems/mapinstrument.cpp \
   $$PWD/panelitems/navdisplay.cpp \
   $$PWD/panelitems/needleinstrument.cpp \
   $$PWD/panelitems/panelitem.cpp \
   $$PWD/panelitems/pfddisplay.cpp \
   $$PWD/panelitems/radarmap.cpp \
   $$PWD/panelitems/rotaryknob.cpp \
   $$PWD/panelitems/slipindicator.cpp \
   $$PWD/panelitems/switch.cpp \
   $$PWD/panelitems/tankleveler.cpp \
   $$PWD/panelitems/turnbank.cpp \
   $$PWD/panelitems/variometer.cpp \
   $$PWD/util/interpolation.cpp \
   $$PWD/util/perlinnoise.cpp \
   $$PWD/widgets/colorselector.cpp \
   $$PWD/widgets/distanceunitcombobox.cpp \
   $$PWD/widgets/numberinputlineedit.cpp \
   $$PWD/widgets/velocityunitcombobox.cpp \
   $$PWD/main.cpp \
   $$PWD/menubutton.cpp \
   $$PWD/panel.cpp \
   $$PWD/panelitemfactory.cpp \
   $$PWD/panelwindow.cpp \
   $$PWD/settings.cpp \
   $$PWD/units.cpp \
   $$PWD/valueinterpolator.cpp \
    panelitems/clientdataref.cpp \
    panelitems/clientdatarefprovider.cpp \
    panelitems/extplaneclient.cpp \
    panelitems/extplaneconnection.cpp \
    panelitems/simulatedextplaneconnection.cpp \
    panelitems/simulateddatarefs/alternatingsimulateddataref.cpp \
    panelitems/simulateddatarefs/fixedsimulateddataref.cpp \
    panelitems/simulateddatarefs/simulateddataref.cpp

INCLUDEPATH = \
    $$PWD/. \
    $$PWD/dialogs \
    $$PWD/hardware \
    $$PWD/needles \
    $$PWD/panelitems \
    $$PWD/util \
    $$PWD/widgets

#DEFINES = 

FORMS += \
    dialogs/bindingcurvedialog.ui \
    dialogs/edititemdialog.ui \
    dialogs/hardwaredialog.ui \
    dialogs/panelitemselectiondialog.ui \
    dialogs/panelsdialog.ui \
    dialogs/settingsdialog.ui

DISTFILES += \
    images/bezel2.png \
    images/bezel_square_.png \
    images/DR400_Battery_Amp.png \
    images/DR400_engine_FUELP.png \
    images/DR400_engine_FUEL_Tank.png \
    images/DR400_engine_FUEL_Tank_needle.png \
    images/DR400_engine_generic.png \
    images/DR400_engine_generic_needle.png

RESOURCES += \
    applicationresources.qrc

