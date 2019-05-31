#include "wizardpage.h"
#include "ui_wizardpage.h"
#include <QTime>

WizardPage::WizardPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::WizardPage)
{
    ui->setupUi(this);
    num=100;
    ui->pBar->setRange(0,num);
}

WizardPage::~WizardPage()
{
    delete ui;
}

void WizardPage::processbar()
{
    for(int i=1;i<=num;++i)
    {
        ui->pBar->setValue(i);

        QTime dieTime= QTime::currentTime().addMSecs(10);
        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}
