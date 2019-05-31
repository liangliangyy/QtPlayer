#include <iostream>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include<QDebug>
#include "player.h"
#include "ui_player.h"
#include<QTimer>
#include<QDebug>
#include<QApplication>
#include<QDesktopWidget>

using namespace std;

Player::Player(QWidget *parent) :QMainWindow(parent),ui(new Ui::Player),p(NULL),puri(NULL),
    standardItemModel(new QStandardItemModel())
{

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(mouseClick()));

    QHBoxLayout *hLayout;
    QHBoxLayout *hLayout2;
    QVBoxLayout *vLayout;

    //歌词窗口
    timelbl=new QLabel();
    timelbl->setAlignment(Qt::AlignHCenter);
    timelbl->setMargin(17);
    timelbl->adjustSize();
    timelbl->setWindowFlags(Qt::Window | Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    timelbl->setAttribute(Qt::WA_TranslucentBackground);
    timelbl->resize(150,150);  //窗体大小
    //窗体居中
    QDesktopWidget* desktop = QApplication::desktop();
    int width = desktop->width();
    int height = desktop->height();
    timelbl->move((width - timelbl->width())/2, (height - timelbl->height())/1);
    QFont ft;
    ft.setPointSize(17);
    timelbl->setFont(ft);
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::red);
    timelbl->setPalette(pa);


    ui->setupUi(this);

    media = new Phonon::MediaObject;
    vwidget = new Phonon::VideoWidget(ui->centralwidget);   //播放器界面
    Phonon::createPath(media,vwidget);

    //设置可播放的文件类型
    vwidget->setAspectRatio(Phonon::VideoWidget::AspectRatioAuto);
    //音频输出
    aOutput = new Phonon::AudioOutput(Phonon::VideoCategory);
    Phonon::createPath(media,aOutput);

    //声音控制条
    volumeSlider = new Phonon::VolumeSlider;
    volumeSlider->setAudioOutput(aOutput);

    volumeSlider->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    seekSlider = new Phonon::SeekSlider;
    seekSlider->setMediaObject(media);

    hLayout = new QHBoxLayout;
    hLayout->addWidget(ui->pbPlay);
    hLayout->addWidget(ui->pbPause);
    hLayout->addWidget(ui->pbStop);
    hLayout->addWidget(seekSlider);
    hLayout->addWidget(volumeSlider);
    //hLayout->addWidget(ui->lbVolume);
    vLayout = new QVBoxLayout;
    vLayout->addWidget(vwidget);
    vLayout->addLayout(hLayout);
    hLayout2 = new QHBoxLayout;
    hLayout2->addLayout(vLayout);
    hLayout2->addWidget(ui->lvPlayList);
    hLayout2->setAlignment(ui->lvPlayList,Qt::AlignRight);
    ui->centralwidget->setLayout(hLayout2);

    for(int i = 0;i<managepl.getOriginListCount();i++)
    {
        QString filecompletename = managepl.getOneFilePath(i);
        int begin = filecompletename.lastIndexOf("/");

        QStandardItem *item = new QStandardItem(filecompletename.mid(begin+1));
        standardItemModel->appendRow(item);
    }


    ui->lvPlayList->setModel(standardItemModel);
    QAction *exitFullScreenAction = new QAction(vwidget);
    vwidget->addAction(exitFullScreenAction);
    vwidget->setAcceptDrops(true);

    exitFullScreenAction->setShortcuts(QList<QKeySequence>() << QKeySequence(Qt::Key_Escape)<< QKeySequence(Qt::Key_MediaStop));
    connect(exitFullScreenAction, SIGNAL(triggered()), vwidget,SLOT(exitFullScreen()));
    //设置0.1秒发射一次
    media->setTickInterval(100);
    //通过设置tick槽来获得当前播放时间
    connect(media,SIGNAL(tick(qint64)),this,SLOT(showTime(qint64)));


}

Player::~Player()
{
    if(p)
        delete p;
    if(puri)
        delete puri;
    delete ui;
}


void Player::setPath()
{
    QString path = QFileDialog::getOpenFileName(this,tr("Open Image"),".",tr("Movie(*.avi *.mp4 *.rmvb *.flv *.mkv);;Music(*.mp3 *.wma)"));

    if(path.length()!=0)
    {
        filePath = path;
        media->setCurrentSource(Phonon::MediaSource(filePath));
        cout<<"now play"<<endl;
        media->play();
        cout<<"have played"<<endl;
        QFileInfo info(filePath);

        QString fileName = info.completeBaseName()+"."+info.completeSuffix();
        qint32 index = managepl.indexOf(filePath);
        if(index==-1)
        {
            QStandardItem *item = new QStandardItem(fileName);
            standardItemModel->appendRow(item);
            ui->lvPlayList->setModel(standardItemModel);
            ui->lvPlayList->setSelectionRectVisible(true);
            managepl.obtainCurrentFilePath(filePath);
        }
    }
}

void Player::incSound()
{
    qreal incStep = 0.1;
    qreal curVolume = this->volumeSlider->audioOutput()->volume();
    this->volumeSlider->audioOutput()->setVolume(curVolume+incStep);
}

void Player::decSound()
{
    qreal decStep = 0.1;
    qreal curVolume = this->volumeSlider->audioOutput()->volume();
    this->volumeSlider->audioOutput()->setVolume(curVolume-decStep);
}



void Player::myGrabWindow()
{
    QPixmap pixmap;
    media->pause();
    pixmap = pixmap.grabWindow(vwidget->winId());
    QString format = ".png";
    QString fileName = QFileDialog::getSaveFileName(this,"Save Picture",QDir::currentPath());
    fileName.append(format);
    pixmap.save(fileName);
    media->play();
}

void Player::hideShowListView()
{
    if(ui->actionHide_play_list->text()=="Hide play-list")
    {
        ui->lvPlayList->hide();
        ui->actionHide_play_list->setText("Show play-list");
    }
    else if(ui->actionHide_play_list->text()=="Show play-list")
    {
        ui->lvPlayList->show();
        ui->actionHide_play_list->setText("Hide play-list");
    }

}

void Player::showProperty()
{
    if(!p)
    {
        p = new FileProperty();
    }
    if(filePath.length())
    {
        p->showMovieProperty(filePath);
    }
}

void Player::uriOpenFile()
{
    if(!puri)
    {
        puri = new PathURI();
    }
    puri->show();
    puri->exec();
    if((puri->GetFilePath())=="")
        return;
    else
        filePath = puri->GetFilePath();
    qDebug()<<filePath;
    QFileInfo info(filePath);
    // filePath = info.absoluteFilePath();
    media->setCurrentSource(Phonon::MediaSource(filePath));
    media->play();

    QString fileName = info.completeBaseName()+"."+info.completeSuffix();
    qint32 index = managepl.indexOf(filePath);
    if(index==-1)
    {
        QStandardItem *item = new QStandardItem(fileName);
        standardItemModel->appendRow(item);
        ui->lvPlayList->setModel(standardItemModel);
        managepl.obtainCurrentFilePath(filePath);
    }
}

void Player::fullNormalScreen()
{
    if(ui->actionFull_screen->isVisible())
    {
        ui->actionFull_screen->setVisible(false);
        ui->actionNormal_screen->setVisible(true);
        ui->lvPlayList->hide();
        ui->actionHide_play_list->setText("显示播放列表");
        vwidget->enterFullScreen();
    }
    else
    {
        ui->actionFull_screen->setVisible(true);
        ui->actionNormal_screen->setVisible(false);
        vwidget->exitFullScreen();
    }
}


void Player::clearPlayList()
{
    standardItemModel->clear();
    managepl.clear();
}

void Player::selectedMoviePlay()
{
    int index = ui->lvPlayList->currentIndex().row();
    filePath = managepl.getOneFilePath(index);
    media->setCurrentSource(Phonon::MediaSource(filePath));
    if(media->currentSource().fileName().indexOf("mp3")!=-1)//修改视频切换音频后vwidget背景
    {
        qDebug()<<media->currentSource().fileName().indexOf("mp3");
        vwidget->setStyleSheet("0");
        vwidget->update();
    }
    media->play();
}

void Player::on_pbPlay_clicked()
{
    media->play();

}

void Player::on_pbPause_clicked()
{
    media->pause();
}

void Player::on_pbStop_clicked()
{
    media->stop();
}

void Player::mouseDoubleClickEvent(QMouseEvent *event)
{
    timer->stop();
    this->vwidget->enterFullScreen();

}
void Player::mouseClick()
{
    media->stop();
    //if()
    this->media->pause();
    qDebug("dff");
}



void Player::on_actionShow_lrc_2_triggered()
{
    if (media->currentSource().fileName().indexOf("mp3")==-1)
    {
    }
    else
    {
        this->timelbl->show();
    }
}
void Player::showTime(qint64 time)
{
    qint64 total_time_value = media->totalTime();
    QTime total_time(0, (total_time_value/60000)%60, (total_time_value/1000)%60);
    QTime current_time(0, (time/60000)%60, (time/1000)%60);
    QString timestr = current_time.toString("mm:ss") ;

    if((total_time_value -time)<50)
    {
        timelbl->close();
    }


    QString filename;
    QString filepath = this->media->currentSource().fileName();
    int filename_start = filepath.lastIndexOf('/');
    filename = filePath.right(filepath.length()-filename_start-1);
    QString extension=filename.right(filename.length()- filename.lastIndexOf('.')-1);
    //qDebug()<<extension;
    if(extension!="mp3"&&extension!="wma"){
        return;
    }
    QString lrcname;
    lrcname = filepath+".lrc";
    QFile file(lrcname);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"Can't open the file!"<<endl;
        timelbl->setText(filename.toUtf8());
        timelbl->adjustSize();
        timelbl->repaint();
    }
    while(!file.atEnd()) {
        QByteArray line = file.readLine();
        QString str(line);
        if (str == "")
            continue;
        int i = str.indexOf(timestr);
        if(i!=-1)
        {
            int  strstart = str.lastIndexOf(']');
            QString thelrc = str.right(str.length()-strstart-1);
            //qDebug()<<thelrc;

            timelbl->setText(thelrc.toUtf8());
            if (thelrc.length()==1)
                timelbl->setText(filename.toUtf8());
            timelbl->adjustSize();
            timelbl->repaint();
        }

    }

    QRegExp rx("\\[\\d{2}:\\d{2}\\.\\d{2}\\]");
}

void  Player::showlbl(const QString thestr)
{

}

