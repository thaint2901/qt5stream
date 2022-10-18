QT += multimediawidgets multimedia

INCLUDEPATH += /usr/include/gstreamer-1.0 /usr/include/orc-0.4 /usr/include/gstreamer-1.0 /usr/include/glib-2.0 /usr/lib/aarch64-linux-gnu/glib-2.0/include

LIBS += -pthread -I/usr/include/gstreamer-1.0 -I/usr/include/orc-0.4 -I/usr/include/gstreamer-1.0 -I/usr/include/glib-2.0 -I/usr/lib/aarch64-linux-gnu/glib-2.0/include -lgstvideo-1.0 -lgstbase-1.0 -lgstreamer-1.0 -lgobject-2.0 -lglib-2.0

SOURCES += main.cpp widget.cpp

HEADERS += widget.h

TARGET = main

FORMS += widget.ui
