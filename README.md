# 基于Qt的多媒体播放器
这个播放器是大学时候做的毕业设计，使用qt+phonon实现，支持音视频播放，支持同步显示歌词。  
## 主界面:
启动界面：
![](https://resource.lylinux.net/image/2019/05/31/541eca6cf298465d886713c60c415e5e.png)
主界面如下图:  
![](https://resource.lylinux.net/image/2019/05/31/73063431ecc147b6936129ca552f5453.png)

同步显示歌词:
![](https://resource.lylinux.net/image/2019/05/31/b49d1d230f3b47d386a8633a47c3ab71.png)
## 安装方式:
以ubuntu为例：
### 安装依赖
```bash
sudo apt update
#安装qt环境：
sudo apt install qt4* -y
sudo apt install qtcreator -y
#安装phonon
sudo apt install build-essential phonon phonon-backend-gstreamer  phonon4qt5 phonon4qt5-backend-gstreamer -y
#安装解码器
sudo apt install ubuntu-restricted-extras -y
```
### 编译
终端进入项目目录，执行：
```bash
#生成Makrfile文件
qmake Player.pro
#编译
make
#运行
./Player
```
至此，你就可以看到启动界面了。
## 说明
### `phonon`
因为`phonon`在`qt5`中貌似不支持了，所以建议使用`qt4`，另外`phonon`只是提供了媒体文件交互功能，并没有解码器，所以你的系统必须要有解码器支持。
### 歌词同步显示
歌词文件命名必须为`歌曲文件名.lrc`格式，以张国荣的怪你过分美丽这首歌为例：
>歌曲文件：怪你过份美丽.mp3  
>歌词文件：怪你过份美丽.mp3.lrc  

开始播放歌曲文件后，通过菜单->View->show lrc 来显示。