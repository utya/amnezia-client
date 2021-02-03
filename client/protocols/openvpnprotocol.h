#ifndef OPENVPNPROTOCOL_H
#define OPENVPNPROTOCOL_H

#include <QObject>
#include <QString>
#include <QTimer>

#include "managementserver.h"
#include "message.h"
#include "vpnprotocol.h"

#include "core/ipcclient.h"

class OpenVpnProtocol : public VpnProtocol
{
    Q_OBJECT

public:
    explicit OpenVpnProtocol(const QString& args = QString(), QObject* parent = nullptr);
    virtual ~OpenVpnProtocol() override;

    ErrorCode start() override;
    void stop() override;

protected slots:
    void onMessageReceived(const Message& message);
    void onOpenVpnProcessFinished(int exitCode);
    void onReadyReadDataFromManagementServer();

protected:
    QString configPath() const;
    QString openVpnExecPath() const;
    bool openVpnProcessIsRunning() const;
    bool sendTermSignal();
    bool setConfigFile(const QString& configFileNamePath);
    void disconnectFromManagementServer();
    void killOpenVpnProcess();
    void openVpnStateSigTermHandler();
    void openVpnStateSigTermHandlerTimerEvent();
    void sendByteCount();
    void sendInitialData();
    void writeCommand(const QString& command);

    const QString m_managementHost = "127.0.0.1";
    const unsigned int m_managementPort = 57775;

    ManagementServer m_managementServer;
    QString m_configFileName;
    QTimer m_openVpnStateSigTermHandlerTimer;
    //bool m_requestFromUserToStop;


private:
    void updateRouteGateway(QString line);
    void updateVpnGateway();

    QSharedPointer<IpcProcessInterfaceReplica> m_openVpnProcess;
};

#endif // OPENVPNPROTOCOL_H