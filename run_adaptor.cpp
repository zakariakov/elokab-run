#include "run_adaptor.h"


run_adaptor::run_adaptor(QObject *parent)
    : QDBusAbstractAdaptor(parent)
{
    // constructor
    setAutoRelaySignals(true);
}

run_adaptor::~run_adaptor()
{
    // destructor

}

void run_adaptor::run()
{
    // handle method call org.tawhid.session.org.logout
    QMetaObject::invokeMethod(parent(), "run");
}
void run_adaptor::setShortcut(const QString &shortcut)
{
    // handle method call org.tawhid.session.org.logout
    QMetaObject::invokeMethod(parent(), "setShortcut", Q_ARG(QString, shortcut));
}


