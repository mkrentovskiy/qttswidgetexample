#include <QApplication>
#include <QWindowsStyle>

#include "View/MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication::setStyle(new QWindowsStyle);
    QApplication app(argc, argv);
    
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    
    MainWindow window;    
    window.show();    
    
    return app.exec();
}
