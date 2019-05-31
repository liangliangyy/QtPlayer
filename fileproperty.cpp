#include "fileproperty.h"
#include "ui_fileproperty.h"

FileProperty::FileProperty(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileProperty)
{
    ui->setupUi(this);
}

FileProperty::~FileProperty()
{
    delete ui;
}

void FileProperty::showMovieProperty(QString fileName)
{
    QFileInfo info(fileName);
    QString basename = info.completeBaseName();
    QString suffixname = info.completeSuffix();
    QString absolutefilepath = info.absoluteFilePath();

    qint64 size = info.size();
    size = size/1024;
    QDateTime created = info.created();
    QDateTime lastRead = info.lastRead();

    ui->leFileName->setText(basename+"."+suffixname);
    ui->leSize->setText(QString::number(size)+"KB");
    ui->leCreateTime->setText(created.toString());
    ui->leFilePath->setText(lastRead.toString());
    ui->leLastVisit->setText(absolutefilepath);

    show();

}

void FileProperty::on_pbOK_clicked()
{
    close();
}
