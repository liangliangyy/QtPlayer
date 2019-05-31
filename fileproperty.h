#ifndef FILEPROPERTY_H
#define FILEPROPERTY_H

#include <QDialog>
#include <QFileInfo>
#include <QDateTime>

namespace Ui {
    class FileProperty;
}

class FileProperty : public QDialog
{
    Q_OBJECT

public:
    explicit FileProperty(QWidget *parent = 0);
    ~FileProperty();

private:
    Ui::FileProperty *ui;
public:
    void showMovieProperty(QString fileName);


private slots:
    void on_pbOK_clicked();
};

#endif // FILEPROPERTY_H
