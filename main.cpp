#include <QApplication>
#include "dialogrun.h"
#include "run_adaptor.h"
#include <QDBusConnection>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
           /// جلب ترجمة البرنامج من مجلد البرنامج
          a.setApplicationName("elokab-run");


           a.setQuitOnLastWindowClosed(false);



        //------------------------------------argument-------------------------------------------------
        QString help=QObject::tr
                ("Elokab Run Gui Version 0.1 .\n"
                 " \n"
                 "Usage: elokab-run [OPTION]\n"
                 "OPTION:\n"
                 " -S         show window.\n"
                 " -H         show hiden.\n"
                 " -h         help.\n"

               );
          QString str ;
          QStringList args = a.arguments();

        if(args.count()==2)
        {
              str = args.at(1);

        }

         DialogRun *w=new DialogRun;
        QDBusConnection connection = QDBusConnection::sessionBus();
        if (! QDBusConnection::sessionBus().registerService("org.elokab.run"))
        {

            QDBusInterface dbus("org.elokab.run",
                                "/org/elokab/run",
                                "org.elokab.run.Interface");

            if (!dbus.isValid()) {
                qDebug() << "QDBusInterface is not valid!";
                return 1;
            }

            if (str == "-S" || str.isEmpty())
            {
             QDBusMessage msg = dbus.call("run");
              QString response = msg.arguments().first().toString();
              qDebug() << "dbus:run"  << "=" << response;
            }

            else if (str == "-h"|| str == "--help")
            {

                 qWarning() <<help;
            }else{
                qWarning() << "Unable to register 'org.elokab.run' service - is another instance of elokab-run running?";

            }

            return 0;
        }


//=============================================================================================

        /// مسار مجلد البرنامج
        QDir appDir(a.applicationDirPath());
        QString translatPath;
        appDir.cdUp();
        translatPath=  appDir.absolutePath()+"/share/elokab/translations";
        /// جلب اعدادات اللغة
        QSettings globalSetting("elokab","elokabsettings");
        globalSetting.beginGroup("Language");
        QString locale=globalSetting.value("Name","Default").toString();
        globalSetting.endGroup();


        /// اذاكانت اللغة الافتراضية
        if(locale=="Default")
                locale = QLocale::system().name().section("_",0,0);
        /// اللغة الحالية لجميع البرنامج
        QLocale::setDefault(QLocale(locale));
        /// جلب ترجمات كيوتي
        QString translatorFileName = QLatin1String("qt_");
        translatorFileName += locale;
        QTranslator *translatorsys = new QTranslator;
        if (translatorsys->load(translatorFileName, QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
                QApplication::installTranslator(translatorsys);
        /// جلب ترجمة البرنامج من مجلد البرنامج
        QTranslator translator;
        translator.load(QString(translatPath+"/"+locale+"/"+a.applicationName()));

        a.installTranslator(&translator);

        new run_adaptor(w);

        connection.registerObject("/org/elokab/run", w);

        if(str=="S")
            w->show();
        else
            w->hide();

        return a.exec();
}
