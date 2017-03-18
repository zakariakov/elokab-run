#include "dialogrun.h"
#include "ui_dialogrun.h"


#include "dialogconfig.h"
#include <QDesktopWidget>
#include <QProcess>
#include <QDebug>
#include <QCompleter>
#include <QStyleFactory>
#include <QDir>
#include <QDesktopServices>
#include <QUrl>
#include <QTextCodec>

DialogRun::DialogRun(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogRun)
{

  //m_settings=new ElokabSettings(this);
    ui->setupUi(this);
  setAttribute(Qt::WA_ShowModal,true);
    // connect(m_settings,SIGNAL(iconThemeChanged()) ,this,SLOT(loadIconThemes()));
    // connect(m_settings,SIGNAL(shortcutsKeysChanged()) ,this,SLOT(loadSetting()));


   //m_pkey = new QxtGlobalShortcut;
    // connect(m_pkey, SIGNAL(activated()), this, SLOT(showMeHideMe()));
    ui->pushButtonIcon->setIcon(QIcon::fromTheme("application-x-executable").pixmap(32));
     //ui->toolButtonConfig->setIcon(QIcon::fromTheme("configure",QIcon::fromTheme("document-properties")).pixmap(32));
     setWindowFlags( Qt::WindowStaysOnTopHint);
   loadSetting();
    QStringList dirs = QString(getenv("PATH")).split(":");
    dirs<<"/usr/share/applications";
    foreach(QString dir,dirs)
    {
       qDebug()<<dir;
        chargeCompliterDirs( dir);
    }
    foreach(QString file,m_apllicationsList)
    {
     //   qDebug()<<file;

        m_wordList<<file.section("|",0,0);
        m_wordList<<file.section("|",1,1);
    }

    m_wordList.removeDuplicates();
    QCompleter *completer = new QCompleter(m_wordList, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->lineEditProg->setCompleter(completer);
    ui->lineEditProg->setFocus();
     centerMe();
     loadIconThemes();

}

DialogRun::~DialogRun()
{
    delete ui;
}

/************************
***اخفاء اظهار النافذة***
*************************/
void DialogRun::run()
{
    showMeHideMe();
}
void DialogRun::setShortcut(const QString &shortcut)
{
    qDebug()<<m_pkey<<shortcut;
    if(m_pkey==shortcut)
    showMeHideMe();
}

void DialogRun::showMeHideMe()
{

    if (isVisible() )
    {
        hide();
    }
    else
    {
      centerMe();
        show();

        QApplication::setActiveWindow(this);

        this->raise();

          ui->lineEditProg->setFocus();
    }
}

/********************************
 ***توسيط النافذة على الشاشة*****
 ********************************/

void DialogRun::centerMe()
{

QDesktopWidget desktop;

  QRect rect = this->geometry();
  rect.moveCenter(desktop.availableGeometry().center());
    setGeometry(rect);

}


/************************************
 ***تحميل قائمة بالبرامج المثبتة*****
 ************************************/

void DialogRun::chargeCompliterDirs(QString dir)
{
          chargeCompliterFiles(dir);
          //qDebug()<<dir;
          QString subdir;
          QDir dirS(dir);
          foreach ( subdir, dirS.entryList(QDir::AllDirs| QDir::NoSymLinks| QDir::NoDotAndDotDot )){
                    chargeCompliterDirs(dir+"/"+subdir);

          }
}

/************************************
 ***تحميل قائمة بالبرامج المثبتة*****
 ************************************/

void DialogRun::chargeCompliterFiles(QString dir)
{
          QString subfile;
          QDir dirS(dir);
          foreach ( subfile, dirS.entryList(QDir::AllEntries)){
                    QFileInfo fi(dir+"/"+subfile);
                    if(fi.suffix()=="desktop"){
                        getInfoFromDesktopFile( dir+"/"+subfile);

                    }
                    if(fi.isExecutable()&&fi.isFile()){
                          QString name=fi.baseName();
                           m_wordList.append(name);

                    }
          }
}

/*******************************************
 **البحث عن ايقونة للبرنامج كلما تغير النص**
 *******************************************/

void DialogRun::on_lineEditProg_textChanged(const QString &arg1)
{

    if(arg1.count()<=2){
        ui->pushButtonIcon->setIcon(QIcon::fromTheme(arg1,QIcon::fromTheme("application-x-executable")).pixmap(32));
        m_command=arg1;
          return;
    }


    QStringList result=m_apllicationsList.filter(arg1+"|");


            if(result.count()==1){
               ui->pushButtonIcon->setIcon(QIcon::fromTheme(result.at(0).section("|",2,2),QIcon::fromTheme("application-x-executable")).pixmap(32));
       m_command=result.at(0).section("|",3,3);
            }else{
               ui->pushButtonIcon->setIcon(QIcon::fromTheme(arg1,QIcon::fromTheme("application-x-executable")).pixmap(32));
           m_command=arg1;
            }

            QFileInfo fi(m_command);

}

/************************************
 *************تنفيذ الامر*************
 ************************************/

void DialogRun::on_buttonBox_accepted()
{
    QFileInfo fi(m_command);
    qDebug()<<"isDir : "<<fi.isDir();
    qDebug()<<"isfile : "<<fi.isFile();
    qDebug()<<"isExecutable : "<<fi.isExecutable();
    qDebug()<<"isRoot : "<<fi.isRoot();
  QProcess process;
    if(fi.isDir()){

        QDesktopServices::openUrl( QUrl::fromLocalFile(m_command) );

    }else if(fi.isExecutable()){

        process.startDetached(m_command);
    }else if(fi.isFile()){
        QDesktopServices::openUrl( QUrl::fromLocalFile(m_command) );
    }else{

        process.startDetached(m_command);
    }


}

/************************************
 ***استخراج معلومات ملف سطح المكتب***
 ************************************/
void DialogRun::getInfoFromDesktopFile(QString fileName)
{
     QString lC = this->locale().name().section("_",0,0);
          QFileInfo fi(fileName);
          QString baseName=fi.baseName();
          QSettings settings(fileName,QSettings::IniFormat);
          settings.setIniCodec(QTextCodec::codecForName("UTF-8"));
          settings.beginGroup("Desktop Entry");
          QString name=settings.value("Name",baseName).toString();
          QString nameLc=settings.value("Name["+lC+"]",name).toString();
        QString exec=settings.value("Exec",baseName).toString();

//          QString Commentold=settings.value("Comment",baseName).toString();
//          QString Comment=settings.value("Comment["+lC+"]",Commentold).toString();


         QString icon=settings.value("Icon",baseName).toString();
          settings.endGroup();
//    m_wordList.append(name);
//    m_wordList.append(nameLc);
          QRegExp ex("\\%[A-Z]");
          QRegExp ex2("\\%[a-z]");
          exec.remove(ex);
          exec.remove(ex2);
          exec.remove("-caption");
 m_apllicationsList<< name.trimmed()+"|"+nameLc.trimmed()+"|"+icon.trimmed()+"|"+exec.trimmed();
}

void DialogRun::loadSetting()
{


    QSettings settings("elokab","shortcut");
    settings.beginGroup("elokab-Run");
    if(!settings.contains("Key")){
        settings.setValue("Key","Alt+F2");
         settings.setValue("Comment","Run any programme whit a command");
        settings.setValue("Destination","run");

    }
    m_pkey=( settings.value("Key","Alt+F2").toString());

     settings.endGroup();
//     if (! m_pkey->setShortcut(ks)||ks.isEmpty())
//     {
//               qDebug()<<QString(" Global shortcut %1 cannot be registered").arg(ks.toString());
//               int ret = QMessageBox::question(this, tr("Run Applicatione"),
//                                               QString(tr(" Global shortcut %1 cannot be registered \n Do you to change it")).arg(ks.toString()),
//                                               QMessageBox::Ok | QMessageBox::Cancel );
//               if (ret==QMessageBox::Ok){
//                   on_toolButtonConfig_clicked();
//               }

//     }else{
//               qDebug()<<QString(" Global shortcut %1 is registered").arg(ks.toString());

//     }

}

//void DialogRun::on_toolButtonConfig_clicked()
//{
//    DialogConfig *dlg=new DialogConfig(this);
//    connect(dlg,SIGNAL(settingShanged()),this,SLOT(loadSetting()));
//    dlg->exec();
//}
void DialogRun::loadIconThemes()
{
    QString icnThem=QIcon::themeName();

    QByteArray sS=qgetenv("DESKTOP_SESSION");

    if(sS=="elokab-session"){
        QSettings setting("elokab","elokabsettings");
        setting.beginGroup("Themes");
        icnThem=  setting.value("iconsTheme",QIcon::themeName()).toString();
        setting.endGroup();

    }

    if(icnThem=="hicolor"||icnThem.isEmpty()){

        QStringList failback;
        failback << "oxygen"<< "Mint-X"<< "Humanity"<< "Tango"<< "Prudence-icon"<< "elementary"<< "gnome"<<"Adwaita";

        QDir dir("/usr/share/icons/");
        foreach (QString s, failback)
        {
            if (dir.exists(s))
            {
                icnThem=s;

                break;
            }
        }
    }

    if(icnThem.isEmpty())
        icnThem="hicolor";

    qDebug()<<"icon theme :"<< icnThem;
    QIcon::setThemeName(icnThem);




}
