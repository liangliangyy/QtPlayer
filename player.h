#ifndef PLAYER_H
#define PLAYER_H

#include <QMainWindow>

#include <Phonon/AudioOutput>
#include <Phonon/SeekSlider>
#include <Phonon/VideoWidget>
#include <Phonon/MediaObject>

#include <Phonon/VolumeSlider>
#include <Phonon/BackendCapabilities>

#include <QFileDialog>
#include <QStandardItem>
#include "pathuri.h"
#include "fileproperty.h"
#include "manageplaylist.h"
#include<QLabel>

namespace Ui {
    class Player;
}

class Player : public QMainWindow
{
    Q_OBJECT

public:
    explicit Player(QWidget *parent = 0);
    ~Player();
     QLabel *timelbl;


private:
    Ui::Player *ui;
    Phonon::MediaObject *media;  //player widget
    Phonon::VideoWidget *vwidget;   //video widget
    Phonon::AudioOutput *aOutput;
    Phonon::VolumeSlider *volumeSlider;
    Phonon::SeekSlider *seekSlider;
    QString filePath;
    FileProperty *p;
    PathURI *puri;
    ManagePlayList managepl;
    QStandardItemModel *standardItemModel;
    //解析lrc歌词
     void resolve_lrc(const QString &source_file_name);


   // void getlrc(QString *filename);
    void getlrc();
    void mouseDoubleClickEvent(QMouseEvent *event);
 //   void mouseClick(QMouseEvent *event);
    QTimer *timer;
     void showlbl(const QString thestr);
private slots:
    void on_pbStop_clicked();
    void on_pbPause_clicked();
    void on_pbPlay_clicked();

    void setPath();
    void incSound();
    void decSound();
    void myGrabWindow();
    void hideShowListView();
    void showProperty();
    void uriOpenFile();
    void fullNormalScreen();
    void selectedMoviePlay();
    void clearPlayList();

    void showTime(qint64);
    void mouseClick();

    void on_actionShow_lrc_2_triggered();
};

#endif // PLAYER_H
