#ifndef MESSAGE_H
#define MESSAGE_H

#include <QStringList>

class Message {

public:
    enum class State {Unknown, Initialize, StartRequest, Started, FinishRequest, Finished,
        RoutesAddRequest, RouteDeleteRequest, ClearSavedRoutesRequest, FlushDnsRequest, InstallDriverRequest};
    Message(State state, const QStringList& args);
    Message(const QString& data);

    QString argAtIndex(int index) const;
    QString argsToString() const;
    QString toString() const;
    QStringList args() const;
    State state() const;
    bool isValid() const;
    QString rawData() const;

protected:
    QString textState() const;

    const QString m_argSeparator = ",";
    const QString m_dataSeparator = "|";

    bool m_valid;
    State m_state;
    QStringList m_args;
    QString m_rawData;
};

#endif // MESSAGE_H