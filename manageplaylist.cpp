#include "manageplaylist.h"

ManagePlayList::ManagePlayList():originListCount(0)
{
    obtainHistoryPlayList();
}

ManagePlayList::~ManagePlayList()
{
    updateHistoryPlayList();
}

void ManagePlayList::obtainHistoryPlayList()
{
    QFile file("playlist.txt");

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    while(!file.atEnd())
    {
        QString line = file.readLine();
        playList.push_back(line.mid(0,line.length()-1));
        originListCount++;
    }
}

void ManagePlayList::updateHistoryPlayList()
{
    QFile file("playlist.txt");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
        return;
    QTextStream out(&file);
    for(int i=originListCount;i<playList.count();i++)
    {
          out<<playList[i]<<"\n";
    }
}

QString ManagePlayList::getOneFilePath(qint32 index)
{
    return playList[index];
}

void ManagePlayList::obtainCurrentFilePath(QString currentFilePath)
{
    playList.push_back(currentFilePath);
}

qint32 ManagePlayList::indexOf(QString filePath)
{
    return playList.indexOf(filePath);
}

qint32 ManagePlayList::getOriginListCount()
{
    return playList.count();
}

void ManagePlayList::clear()
{
    playList.clear();
    originListCount = 0;
    QFile file("playlist.txt");
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
        return;
}


