HEADERS = Variables.h \
    ../Interaction/Variables.h \
    View/MainWindow.h \
    View/WidgetControl.h \
    View/WidgetFabric.h \
    View/Widgets/ControlLine.h \
    View/Widgets/Frame.h \
    View/Widgets/FrameSet.h \
    View/Widgets/Keyboard.h \
    View/Widgets/PicButton.h \
    View/Widgets/Slider.h \
    View/Widgets/ValueButton.h \
    View/Widgets/View.h \
    Model/DevicesSubSystem.h \
    ../Interaction/Database.h \
    ../Interaction/Device.h \
    ../Interaction/DeviceControl.h \
    ../Interaction/DevicesPool.h \
    ../Interaction/DeviceValues.h 
    
SOURCES = main.cpp \
    View/MainWindow.cpp \
    View/WidgetControl.cpp \
    View/WidgetFabric.cpp \
    View/Widgets/ControlLine.cpp \
    View/Widgets/Frame.cpp \
    View/Widgets/FrameSet.cpp \
    View/Widgets/Keyboard.cpp \
    View/Widgets/PicButton.cpp \
    View/Widgets/Slider.cpp \
    View/Widgets/ValueButton.cpp \
    View/Widgets/View.cpp \
    Model/DevicesSubSystem.cpp \
    ../Interaction/Database.cpp \
    ../Interaction/Device.cpp \
    ../Interaction/DeviceControl.cpp \
    ../Interaction/DevicesPool.cpp \
    ../Interaction/DeviceValues.cpp 
    
QT += xml \
    sql \
    network

RESOURCES = Resources/tc.qrc

sources.files = $$SOURCES \
    $$HEADERS \
    $$RESOURCES

sources.path = . \
    Model \
    View \
    ../Interaction
