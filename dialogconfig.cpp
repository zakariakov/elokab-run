#include "dialogconfig.h"
#include "ui_dialogconfig.h"
#include <QSettings>
DialogConfig::DialogConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConfig)
{

    ui->setupUi(this);

setModal(true);

    linShortcut=new LineEdit(this) ;
    ui->horizontalLayout->addWidget(linShortcut);
    loadSetting();
    linShortcut->setFocus();
}

DialogConfig::~DialogConfig()
{
    delete ui;
}
void DialogConfig::loadSetting()
{

    QSettings settings("elokab","shortcut");
    settings.beginGroup("elokab-Run");
    linShortcut->setText( settings.value("Key","Alt+F2").toString());

    settings.endGroup();


}
void DialogConfig::saveSetting()
{
if (linShortcut->text().isEmpty())
            return;
    QSettings settings("elokab","shortcut");
    settings.beginGroup("elokab-Run");

settings.setValue("Key",linShortcut->text());
settings.setValue("ProgramName",trUtf8("Run"));
settings.setValue("Comment",trUtf8("run any programme whit a cpmmand"));
    settings.endGroup();
}

void DialogConfig::on_buttonBox_accepted()
{
    saveSetting();
  emit  settingShanged();
}
