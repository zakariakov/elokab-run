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

#ifndef DIALOGCONFIG_H
#define DIALOGCONFIG_H
#include <QDialog>
#include <QWidget>
#include <QLineEdit>
#include <QKeyEvent>
class  LineEdit : public QLineEdit
{
    Q_OBJECT
public:
     LineEdit(QWidget* parent=0)
         : QLineEdit(parent)
{
     }

protected:
void keyReleaseEvent(QKeyEvent *)
{

         txtControl=QString::null;
}
void keyPressEvent(QKeyEvent *event)
{
    if(    event->key()==Qt::Key_AltGr||event->key()==Qt::Key_Print||
            event->key()==Qt::Key_CapsLock||event->key()==Qt::Key_NumLock||
              event->key()==Qt::Key_Return||event->key()==Qt::Key_Enter
            ||event->key()==Qt::Key_Escape)

        return;

     if (event->key()==Qt::Key_Control){
        txtControl=txtControl+"Ctrl+";
        return;
    }
    if (event->key()==Qt::Key_Shift){
        txtControl=txtControl+"Shift+";
        return;
    }
    if (event->key()==Qt::Key_Alt){
        txtControl=txtControl+"Alt+";
        return;
    }
    if (event->key()==Qt::Key_Meta){
        txtControl=txtControl+"Meta+";
        return;
    }
      QKeySequence key=event->key();
       QString txt=key.toString();
    this->setText(txtControl+txt);
    txtControl=QString::null;
  //this->setText(txtControl);
}

private:
QString txtControl;
    };
namespace Ui {
class DialogConfig;
}

class DialogConfig : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogConfig(QWidget *parent = 0);
    ~DialogConfig();
signals:
    void  settingShanged();
private:
    Ui::DialogConfig *ui;
    LineEdit *linShortcut;

private slots:
    void loadSetting();
      void saveSetting();
      void on_buttonBox_accepted();
};

#endif // DIALOGCONFIG_H
