HEADERS = Variables.h \
    ../Interaction/Variables.h \
    View/MainWindow.h \
    View/SceneViewControl.h \
    View/Widgets/Scene.h \
    View/Widgets/SceneElement.h \
    ../Interaction/Database.h \
    ../Interaction/Device.h \
    ../Interaction/DeviceControl.h \
    ../Interaction/DevicesPool.h \
    ../Interaction/DeviceValues.h 
    
SOURCES = main.cpp \
    View/MainWindow.cpp \
    View/SceneViewControl.cpp \
    View/Widgets/Scene.cpp \
    View/Widgets/SceneElement.cpp \
    ../Interaction/Database.cpp \
    ../Interaction/Device.cpp \
    ../Interaction/DeviceControl.cpp \
    ../Interaction/DevicesPool.cpp \
    ../Interaction/DeviceValues.cpp 
    
QT += xml \
    sql \
    network

RESOURCES = Resources/vc.qrc

sources.files = $$SOURCES \
    $$HEADERS \
    $$RESOURCES

sources.path = . \
    View \
    ../Interaction
