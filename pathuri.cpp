#include "pathuri.h"
#include "ui_pathuri.h"

PathURI::PathURI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PathURI)
{
    ui->setupUi(this);
}

PathURI::~PathURI()
{
    delete ui;
}


void PathURI::pbOpenEnable()
{
    ui->pbOpen->setEnabled(!ui->lePath->text().isEmpty());
    ui->pbOpen->setDefault(true);
}

void PathURI::pbOpenFile()
{
    filePath = ui->lePath->text();
    close();
}

QString PathURI::GetFilePath()
{
    return filePath;
}
