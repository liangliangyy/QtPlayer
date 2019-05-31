#ifndef MANAGEPLAYLIST_H
#define MANAGEPLAYLIST_H

#include <QVector>
#include <QFile>
#include <QTextStream>

class ManagePlayList
{
public:
    ManagePlayList();
    ~ManagePlayList();
    void obtainHistoryPlayList();
    void updateHistoryPlayList();
    QString getOneFilePath(qint32 index);
    void obtainCurrentFilePath(QString currentFilePath);

    qint32 indexOf(QString filePath);
    qint32 getOriginListCount();
    void clear();

private:
    QVector<QString> playList;
    qint32 originListCount;

};

#endif // MANAGEPLAYLIST_H
