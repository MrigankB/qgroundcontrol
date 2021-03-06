/****************************************************************************
 *
 *   (c) 2009-2016 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/


/// @file
///     @author Don Gagne <don@thegagnes.com>

#ifndef PX4FirmwarePlugin_H
#define PX4FirmwarePlugin_H

#include "FirmwarePlugin.h"
#include "ParameterManager.h"
#include "PX4ParameterMetaData.h"
#include "PX4GeoFenceManager.h"

class PX4FirmwarePlugin : public FirmwarePlugin
{
    Q_OBJECT

public:
    PX4FirmwarePlugin(void);

    // Overrides from FirmwarePlugin

    QList<VehicleComponent*> componentsForVehicle(AutoPilotPlugin* vehicle) override;
    QList<MAV_CMD> supportedMissionCommands(void) override;

    AutoPilotPlugin*    autopilotPlugin                 (Vehicle* vehicle) override;
    bool                isCapable                       (const Vehicle *vehicle, FirmwareCapabilities capabilities) override;
    QStringList         flightModes                     (Vehicle* vehicle) override;
    QString             flightMode                      (uint8_t base_mode, uint32_t custom_mode) const override;
    bool                setFlightMode                   (const QString& flightMode, uint8_t* base_mode, uint32_t* custom_mode) override;
    void                setGuidedMode                   (Vehicle* vehicle, bool guidedMode) override;
    void                pauseVehicle                    (Vehicle* vehicle) override;
    void                guidedModeRTL                   (Vehicle* vehicle) override;
    void                guidedModeLand                  (Vehicle* vehicle) override;
    void                guidedModeTakeoff               (Vehicle* vehicle, double altitudeRel) override;
    void                guidedModeOrbit                 (Vehicle* vehicle, const QGeoCoordinate& centerCoord = QGeoCoordinate(), double radius = NAN, double velocity = NAN, double altitude = NAN) override;
    void                guidedModeGotoLocation          (Vehicle* vehicle, const QGeoCoordinate& gotoCoord) override;
    void                guidedModeChangeAltitude        (Vehicle* vehicle, double altitudeRel) override;
    bool                isGuidedMode                    (const Vehicle* vehicle) const override;
    int                 manualControlReservedButtonCount(void) override;
    bool                supportsManualControl           (void) override;
    void                initializeVehicle               (Vehicle* vehicle) override;
    bool                sendHomePositionToVehicle       (void) override;
    void                addMetaDataToFact               (QObject* parameterMetaData, Fact* fact, MAV_TYPE vehicleType) override;
    QString             missionCommandOverrides         (MAV_TYPE vehicleType) const override;
    QString             getVersionParam                 (void) override { return QString("SYS_PARAM_VER"); }
    QString             internalParameterMetaDataFile   (Vehicle* vehicle) override { Q_UNUSED(vehicle); return QString(":/FirmwarePlugin/PX4/PX4ParameterFactMetaData.xml"); }
    void                getParameterMetaDataVersionInfo (const QString& metaDataFile, int& majorVersion, int& minorVersion) override { PX4ParameterMetaData::getParameterMetaDataVersionInfo(metaDataFile, majorVersion, minorVersion); }
    QObject*            loadParameterMetaData           (const QString& metaDataFile) final;
    bool                adjustIncomingMavlinkMessage    (Vehicle* vehicle, mavlink_message_t* message) override;
    GeoFenceManager*    newGeoFenceManager              (Vehicle* vehicle) override { return new PX4GeoFenceManager(vehicle); }
    QString             offlineEditingParamFile(Vehicle* vehicle) override { Q_UNUSED(vehicle); return QStringLiteral(":/FirmwarePlugin/PX4/PX4.OfflineEditing.params"); }
    QString             brandImage                      (const Vehicle* vehicle) const override { Q_UNUSED(vehicle); return QStringLiteral("/qmlimages/PX4/BrandImage"); }
    QString             missionFlightMode               (void) override;
    QString             rtlFlightMode                   (void) override;
    QString             takeControlFlightMode           (void) override;

    // NOTE: For internal use only. Do not use in mainline QGC code.
    // Use these constants to set flight modes using setFlightMode method. Don't use hardcoded string names since the
    // names may change.
    static const char* _manualFlightMode;
    static const char* _acroFlightMode;
    static const char* _stabilizedFlightMode;
    static const char* _rattitudeFlightMode;
    static const char* _altCtlFlightMode;
    static const char* _posCtlFlightMode;
    static const char* _offboardFlightMode;
    static const char* _readyFlightMode;
    static const char* _takeoffFlightMode;
    static const char* _holdFlightMode;
    static const char* _missionFlightMode;
    static const char* _rtlFlightMode;
    static const char* _landingFlightMode;
    static const char* _rtgsFlightMode;
    static const char* _followMeFlightMode;
    static const char* _simpleFlightMode;

private:
    void _handleAutopilotVersion(Vehicle* vehicle, mavlink_message_t* message);

    bool _versionNotified;  ///< true: user notified over version issue
};

#endif
