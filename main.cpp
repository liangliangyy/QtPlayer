#include <QtGui/QApplication>
#include <QTextCodec>
#include "player.h"
#include "wizardpage.h"

int main(int argc,char *argv[])
{
    QApplication a(argc,argv);
    a.setApplicationName("VideoPlayer");
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));


    WizardPage pg;
    pg.show();
    pg.processbar();

    Player w;
    pg.close();

    w.show();
    return a.exec();
}



