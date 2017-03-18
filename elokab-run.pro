#-------------------------------------------------
#
# Project created by QtCreator 2013-06-29T21:32:51
#
#-------------------------------------------------

QT       += core gui dbus

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = elokab-run
DESTDIR = usr/bin

TEMPLATE = app

CONFIG += qt \
          release
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
INCLUDEPATH +=build



SOURCES += main.cpp\
                dialogrun.cpp \
                dialogconfig.cpp\
                run_adaptor.cpp


HEADERS  += dialogrun.h \
            dialogconfig.h\
            run_adaptor.h


FORMS    += dialogrun.ui \
            dialogconfig.ui

TRANSLATIONS    =usr/share/elokab/translations/ar/elokab-run.ts\
                 usr/share/elokab/translations/fr/elokab-run.ts\
                 usr/share/elokab/translations/en/elokab-run.ts\
#CODECFORTR = UTF-8
# install



 target.path = /usr/bin

# data.files =../usr/share/elokab/elokab-run*
# data.path=/usr/share/elokab/

 INSTALLS +=                  target
#\
#                                data

