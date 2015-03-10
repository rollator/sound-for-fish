# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = soundcloud_unofficial

CONFIG += sailfishapp
QT += multimedia
SOURCES += src/soundcloud_unofficial.cpp \
    src/streammanager.cpp

OTHER_FILES += qml/soundcloud_unofficial.qml \
    qml/cover/CoverPage.qml \
    qml/pages/FirstPage.qml \
    qml/pages/SecondPage.qml \
    rpm/soundcloud_unofficial.changes.in \
    rpm/soundcloud_unofficial.spec \
    rpm/soundcloud_unofficial.yaml \
    translations/*.ts \
    soundcloud_unofficial.desktop

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n
TRANSLATIONS += translations/soundcloud_unofficial-de.ts

HEADERS += \
    src/streammanager.h

