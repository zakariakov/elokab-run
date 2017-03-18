/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)GPL3+
 *
 * elokab - a lightweight, Qt based, desktop toolset
 * https://sourceforge.net/project/elokab/
 *
 * Copyright: 2013-2014 elokab team
 * Authors:
 *   Abou Zakaria <yahiaui@gmail.com>
 *
 * This program or library is free software; you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA
 *
 * END_COMMON_COPYRIGHT_HEADER */

#ifndef DIALOGRUN_H
#define DIALOGRUN_H
#include <QSettings>
#include <QDialog>
#include <QDebug>
namespace Ui {
class DialogRun;
}

class DialogRun : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogRun(QWidget *parent = 0);
    ~DialogRun();

public  slots:
void run();
void setShortcut(const QString &shortcut);
private:
    Ui::DialogRun *ui;
QStringList  m_wordList;
QStringList  m_apllicationsList;
QString m_command;
QString  m_pkey ;

//QSettings *m_settings;

private slots:


    void showMeHideMe();//اخفاء اظهار النافذة
    void centerMe();//توسيط النافذة على الشاشة
    void loadIconThemes();

void chargeCompliterDirs(QString dir);
void chargeCompliterFiles(QString   dir);
void on_lineEditProg_textChanged(const QString &arg1);
void getInfoFromDesktopFile(QString fileName);
void loadSetting();
void on_buttonBox_accepted();
//void on_toolButtonConfig_clicked();
};

#endif // DIALOGRUN_H
