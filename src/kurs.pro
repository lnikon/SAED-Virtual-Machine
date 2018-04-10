QT += widgets
requires(qtConfig(listwidget))
qtHaveModule(printsupport): QT += printsupport

HEADERS         = mainwindow.h \
    cpu.h \
    watch.h \
    processor.h
SOURCES         = main.cpp \
                  mainwindow.cpp \
    cpu.cpp \
    watch.cpp
RESOURCES       = dockwidgets.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/mainwindows/dockwidgets
INSTALLS += target
