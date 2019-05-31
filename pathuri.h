#ifndef PATHURI_H
#define PATHURI_H

#include <QDialog>

namespace Ui {
    class PathURI;
}

class PathURI : public QDialog
{
    Q_OBJECT

public:
    explicit PathURI(QWidget *parent = 0);
    ~PathURI();
    QString GetFilePath();

private:
    Ui::PathURI *ui;
    QString filePath;
protected slots:
    void pbOpenEnable();
    void pbOpenFile();

};

#endif // PATHURI_H
