#ifndef RUN_ADAPTOR_H
#define RUN_ADAPTOR_H

#include <QtCore/QObject>
#include <QtDBus/QtDBus>

QT_BEGIN_NAMESPACE


class QString;

QT_END_NAMESPACE

/*
 * Adaptor class for interface org.tawhid.session.org
 */

class run_adaptor: public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.elokab.run.Interface")
    Q_CLASSINFO("D-Bus Introspection", ""
                "  <interface name=\"org.elokab.run.Interface\">\n"
                "    <method name=\"run\"/>\n"
                "    <method name=\"setShortcut\">\n"
                     "<arg name=\"shortcut\" type=\"s\" direction=\"in\"/>"
                "    </method>"
                 "  </interface>\n"
                "")
public:
    run_adaptor(QObject *parent);
    virtual ~run_adaptor();


public Q_SLOTS: // METHODS
    void run();
    void setShortcut(const QString &shortcut);

};

#endif
