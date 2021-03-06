QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult t^he documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    Consolereader.cpp \
    ../PCA9685/PCA9685.cpp \
    ../I2C/I2C.cpp \
    steppercontroller.cpp \
    ../SyncServo/SyncServo.cpp \
    ../ServoUnit/ServoUnit.cpp

target.path = /home/pi
INSTALLS += target

# INCLUDEPATH +=../../sysroot/usr/include/
# INCLUDEPATH +=../../sysroot/usr/include/linux

INCLUDEPATH +=../PCA9685 \
                ../ServoUnit \
                ../LinkedList

HEADERS += \
    Consolereader.h \
    ../PCA9685/PCA9685.h \
    ../PCA9685/PCA9685.h \
    ../I2C/I2C.h \
    ../SyncServo/SyncServo.h \
    ../ServoUnit/ServoUnit.h \
    ../LinkedList/LinkedList.h
